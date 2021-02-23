#define _USE_MATH_DEFINES
#include <DxLib.h>
#include <array>
#include <cmath>

#include "CPlayer_CFall.h"
#include "CPuyoPuyo.h"
#include "ImagePuyoPuyo.h"

static const int row = 12;
static const int col = 6;

using namespace PuyoPuyo;
CPuyoPuyo::CPuyoPuyo(int colors, int row, int col, int puyo_size,
                     std::unordered_map<PointName, const Point> point)
    : mDefaultPoint(point)
    , mPuyoField(std::make_shared<CPuyoField>(12, 6, 38))
    , mColors(colors)
    , mRow(row)
    , mCol(col)
    , mPuyoSize(puyo_size)
    , m_background(std::make_shared<ImageBackground>())
    , m_frame(std::make_shared<ImageFrame>())
    , m_left_next_frame(std::make_shared<ImageLeftNextFrame>(
          mDefaultPoint.at(PointName::next_field).x,
          mDefaultPoint.at(PointName::next_field).y, ORIGIN::UPPER_LEFT)) {
	mPuyoSet[(int)SetName::current]  = std::make_shared<PuyoSet>();
	mPuyoSet[(int)SetName::next]     = std::make_unique<PuyoSet>();
	mPuyoSet[(int)SetName::nextnext] = std::make_unique<PuyoSet>();

	mFallMgr = std::make_unique<CFall>(mPuyoSet[(int)SetName::current],
	                                   mDefaultPoint.at(PointName::field),
	                                   mPuyoField, mPuyoSize, mRow, mCol);

	mScene = Scene::init;
	mCount = 0;
}
CPuyoPuyo::~CPuyoPuyo() {}
void CPuyoPuyo::Run() {
	Calc();
	Draw();
}

void CPuyoPuyo::Calc() {
	const std::array<PuyoType, 4> getPuyoType = {PuyoType::blue, PuyoType::red,
	                                             PuyoType::green, PuyoType::pink};
	switch (mScene) {
	case Scene::init:
		mPuyoSet[(int)SetName::current]->angle = M_PI_2;
		mPuyoSet[(int)SetName::current]->point =
		    mDefaultPoint.at(PointName::current);

		mPuyoSet[(int)SetName::next]->angle = M_PI_2;
		mPuyoSet[(int)SetName::next]->point = mDefaultPoint.at(PointName::next);

		mPuyoSet[(int)SetName::nextnext]->angle = M_PI_2;
		mPuyoSet[(int)SetName::nextnext]->point =
		    mDefaultPoint.at(PointName::nextnext);

		for (int i = 0; i < 2; i++) {
			mPuyoSet[(int)SetName::nextnext]->type[i] =
			    getPuyoType[GetRand(mColors - 1)];
			mPuyoSet[(int)SetName::next]->type[i] = getPuyoType[GetRand(mColors - 1)];
			mPuyoSet[(int)SetName::current]->type[i] = PuyoType::none;
		}

		mScene = Scene::next;
		break;
	case Scene::next:
		mCount++;
		if (mCount > 27) {
			*mPuyoSet[(int)SetName::current] = *mPuyoSet[(int)SetName::next];
			*mPuyoSet[(int)SetName::next]    = *mPuyoSet[(int)SetName::nextnext];

			mPuyoSet[(int)SetName::current]->point =
			    mDefaultPoint.at(PointName::current);
			mPuyoSet[(int)SetName::next]->point = mDefaultPoint.at(PointName::next);

			mPuyoSet[(int)SetName::nextnext]->point =
			    mDefaultPoint.at(PointName::nextnext);
			for (int i = 0; i < 2; i++) {
				mPuyoSet[(int)SetName::nextnext]->type[i] =
				    getPuyoType[GetRand(mColors - 1)];
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

void CPuyoPuyo::Draw() const {
	switch (mScene) {
	case Scene::init:
		break;
	default:
		m_background->draw();
		m_left_next_frame->draw();

		DrawPuyoSet(*mPuyoSet[(int)SetName::next]);
		DrawPuyoSet(*mPuyoSet[(int)SetName::nextnext]);

		mPuyoField->Draw(mDefaultPoint.at(PointName::field));

		if (mScene == Scene::fall) {
			DrawPuyoSet(*mPuyoSet[(int)SetName::current]);
		}

		m_frame->draw();
		break;
	}
}
void CPuyoPuyo::DrawPuyoSet(PuyoSet puyoset) const {
	Puyo puyo0, puyo1;

	puyo1.point = puyoset.point;
	puyo1.type  = puyoset.type[1];

	puyo0.point.x =
	    (int)std::round(puyo1.point.x + mPuyoSize * std::cos(puyoset.angle));
	puyo0.point.y =
	    (int)std::round(puyo1.point.y - mPuyoSize * std::sin(puyoset.angle));
	puyo0.type = puyoset.type[0];

	puyo1.Draw();
	puyo0.Draw();
}
void CPuyoPuyo::setPuyo(std::unique_ptr<const Puyo> puyo) const {
	mPuyoField->set(
	    *puyo,
	    (int)std::floor(
	        (double)(puyo->point.y - mDefaultPoint.at(PointName::field).y) /
	        mPuyoSize),
	    (int)std::floor(
	        (double)(puyo->point.x - mDefaultPoint.at(PointName::field).x) /
	        mPuyoSize));
}
