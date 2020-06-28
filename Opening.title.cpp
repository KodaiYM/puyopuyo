#include <DxLib.h>
#include <assert.h>
#include "Opening.title.h"
#include "CBright.h"
#include "key.h"
#include "Opening.logo.h"

using namespace Opening;

TitleMgr::TitleMgr(std::weak_ptr<ISceneChanger> sceneChanger)
	:CObjMgr(sceneChanger) {
}
void TitleMgr::init() {
	if (!mTitleMovie) {
		mTitleMovie = std::make_shared<Object::TitleMovie>();
	}

	mTitleMovie->init();
	CBright::getInstance().SetDrawBright(255, 255, 255);
	mCounter = 0;
}
void TitleMgr::deinit() {
	CBright::getInstance().SetDrawBright(255, 255, 255);
}
void TitleMgr::update() {
	switch (mCounter) {
	case 0:
		addToDrawList(mTitleMovie);
		mCounter++;
	case 1:
		if (KeyStateOf(KEY_INPUT_RETURN) == 1) {
			mCounter++;
		} else if (mTitleMovie->update() == Object::CMovieObj::STATUS::END) {
			// ムービー終了
			mSceneChanger.lock()->ChangeScene(typeid(Opening::LogoMgr));
		}
		break;
	case 2:
		if (CBright::getInstance().Fade(0, 0, 0, 30) == 0) {
			// 輝度を最大に戻す
			CBright::getInstance().SetDrawBright(255, 255, 255);

			// シーンの変更
//			mSceneChanger->ChangeScene(std::make_unique<CGame>(mSceneChanger));
			assert(0);
		}
		break;
	}
}
