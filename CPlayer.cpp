#define _USE_MATH_DEFINES
#include <array>
#include <cmath>
#include <DxLib.h>
#include "CPlayer.h"
#include "CPlayer_CFall.h"

static const int row = 12;
static const int col = 6;

using namespace Game;
CPlayer::CPlayer(int colors, int row, int col, int puyo_size, std::shared_ptr<const CResourceMgr> resourceMgr, std::unordered_map<PointName, const Point> point)
	:mResourceMgr(std::move(resourceMgr)), mDefaultPoint(point), mPuyoField(std::make_shared<CPuyoField>(12, 6, 38, mResourceMgr)),
	mColors(colors), mRow(row), mCol(col), mPuyoSize(puyo_size) {
	mPuyoSet[(int)SetName::current] = std::make_shared<PuyoSet>();
	mPuyoSet[(int)SetName::next] = std::make_unique<PuyoSet>();
	mPuyoSet[(int)SetName::nextnext] = std::make_unique<PuyoSet>();

	mFallMgr = std::make_unique<CFall>(mPuyoSet[(int)SetName::current], mDefaultPoint.at(PointName::field), mPuyoField, mPuyoSize, mRow, mCol, mResourceMgr);

	mScene = Scene::init;
	mCount = 0;
}
CPlayer::~CPlayer() {
}
void CPlayer::Run() {
	Calc();
	Draw();
}

void CPlayer::Calc() {
	const std::array<PuyoType, 4> getPuyoType = {
		PuyoType::blue,
		PuyoType::red,
		PuyoType::green,
		PuyoType::pink
	};
	switch (mScene) {
	case Scene::init:
		mPuyoSet[(int)SetName::current]->angle = M_PI_2;
		mPuyoSet[(int)SetName::current]->point = mDefaultPoint.at(PointName::current);

		mPuyoSet[(int)SetName::next]->angle = M_PI_2;
		mPuyoSet[(int)SetName::next]->point = mDefaultPoint.at(PointName::next);

		mPuyoSet[(int)SetName::nextnext]->angle = M_PI_2;
		mPuyoSet[(int)SetName::nextnext]->point = mDefaultPoint.at(PointName::nextnext);

		for (int i = 0; i < 2; i++) {
			mPuyoSet[(int)SetName::nextnext]->type[i] = getPuyoType[GetRand(mColors - 1)];
			mPuyoSet[(int)SetName::next]->type[i] = getPuyoType[GetRand(mColors - 1)];
			mPuyoSet[(int)SetName::current]->type[i] = PuyoType::none;
		}

		mScene = Scene::next;
		break;
	case Scene::next:
		mCount++;
		if (mCount > 27) {
			*mPuyoSet[(int)SetName::current] = *mPuyoSet[(int)SetName::next];
			*mPuyoSet[(int)SetName::next] = *mPuyoSet[(int)SetName::nextnext];

			mPuyoSet[(int)SetName::current]->point = mDefaultPoint.at(PointName::current);
			mPuyoSet[(int)SetName::next]->point = mDefaultPoint.at(PointName::next);

			mPuyoSet[(int)SetName::nextnext]->point = mDefaultPoint.at(PointName::nextnext);
			for (int i = 0; i < 2; i++) {
				mPuyoSet[(int)SetName::nextnext]->type[i] = getPuyoType[GetRand(mColors - 1)];
			}

			mCount = 0;
			mScene = Scene::fall;
			break;
		} else {
			mPuyoSet[(int)SetName::next]->point.y -= 3;
			mPuyoSet[(int)SetName::nextnext]->point.y -= 3;

			if (mCount % 2 == 1) {
				mPuyoSet[(int)SetName::nextnext]->point.x--;
			}
		}
		break;
	case Scene::fall:
		// 操作シーン
		if (mFallMgr->Run() == 0) {
			// 着地したら
			mScene = Scene::pop;
		}
		break;
	case Scene::pop:
		// 連鎖シーン
		if (mPuyoField->Pop() == 0) {
			// 連鎖が終わったら

			// ゲームオーバー
			if (mPuyoField->GameOvered()) {
				mScene = Scene::gameover;
			} else {
				mScene = Scene::next;
			}
		}
		break;
	case Scene::gameover:
		printf("終わり―");
		break;
	}
}

void CPlayer::Draw() const {
	switch (mScene) {
	case Scene::init:
		break;
	default:
		DrawGraph(0, 0, mResourceMgr->getGraphicHandle((int)GraphicName::background), TRUE);
		DrawGraph(mDefaultPoint.at(PointName::next_field).x, mDefaultPoint.at(PointName::next_field).y, mResourceMgr->getGraphicHandle((int)GraphicName::left_next), TRUE);

		DrawPuyoSet(*mPuyoSet[(int)SetName::next]);
		DrawPuyoSet(*mPuyoSet[(int)SetName::nextnext]);

		mPuyoField->Draw(mDefaultPoint.at(PointName::field));

		if (mScene == Scene::fall) {
			DrawPuyoSet(*mPuyoSet[(int)SetName::current]);
		}

		DrawGraph(0, 0, mResourceMgr->getGraphicHandle((int)GraphicName::frame), TRUE);
		break;
	}
}
void CPlayer::DrawPuyoSet(PuyoSet puyoset) const {
	Puyo puyo0, puyo1;

	puyo1.point = puyoset.point;
	puyo1.type = puyoset.type[1];

	puyo0.point.x = (int)std::round(puyo1.point.x + mPuyoSize * std::cos(puyoset.angle));
	puyo0.point.y = (int)std::round(puyo1.point.y - mPuyoSize * std::sin(puyoset.angle));
	puyo0.type = puyoset.type[0];

	puyo1.Draw(mResourceMgr);
	puyo0.Draw(mResourceMgr);
}
void CPlayer::setPuyo(std::unique_ptr<const Puyo> puyo) const {
	mPuyoField->set(*puyo, (int)std::floor((double)(puyo->point.y - mDefaultPoint.at(PointName::field).y) / mPuyoSize), (int)std::floor((double)(puyo->point.x - mDefaultPoint.at(PointName::field).x) / mPuyoSize));
}
