#include <DxLib.h>
#include <assert.h>
#include "Opening.logo.h"
#include "Opening.title.h"
#include "CBright.h"

using namespace Opening;

LogoMgr::LogoMgr(std::weak_ptr<ISceneChanger> sceneChanger) :CSceneMgr(sceneChanger) {
}
void LogoMgr::ChangeScene(const std::type_info& nextScene) {
	if (nextScene == typeid(MyLogo)) {
		AssignScene(mMyLogo);
	} else if (nextScene == typeid(SSLogo)) {
		AssignScene(mSSLogo);
	} else if (nextScene == typeid(Opening::TitleMgr)) {
		mSceneChanger.lock()->ChangeScene(typeid(Opening::TitleMgr));
	}
}
void LogoMgr::init() {
	if (!mMyLogo) {
		mMyLogo = std::make_shared<MyLogo>(shared_from_this());
	}
	if (!mSSLogo) {
		mSSLogo = std::make_shared<SSLogo>(shared_from_this());
	}
	mMyLogo->init();
	mSSLogo->init();

	ChangeScene(typeid(MyLogo));
}
void LogoMgr::deinit() {
	mMyLogo->deinit();
	mSSLogo->deinit();

	CBright::getInstance().SetDrawBright(255, 255, 255);
}
void LogoMgr::update() {
	getScene()->update();
}

MyLogo::MyLogo(std::weak_ptr<ISceneChanger> sceneChanger) :CObjMgr(sceneChanger) {
}
void MyLogo::init() {
	if (!mMyLogo) {
		mMyLogo = std::make_shared<Object::MyLogo>();
	}

	mWaitCounter = 0;
	mCounter = 0;
}
void MyLogo::deinit() {
}
void MyLogo::update() {
	switch (mCounter) {
	case 0:
		CBright::getInstance().SetDrawBright(0, 0, 0);
		mCounter++;
		addToDrawList(mMyLogo);
	case 1:
		if (CBright::getInstance().Fade(255, 255, 255, 60) == 0) {
			mCounter++;
			mWaitCounter = 0;
		}
		break;
	case 2:
		if (++mWaitCounter == 120) {
			mCounter++;
		}
		break;
	case 3:
		if (CBright::getInstance().Fade(0, 0, 0, 60) == 0) {
			mCounter++;
			mSceneChanger.lock()->ChangeScene(typeid(SSLogo));
		}
		break;
	default:
		assert(false);
	}
}


SSLogo::SSLogo(std::weak_ptr<ISceneChanger> sceneChanger) :CObjMgr(sceneChanger) {
}
void SSLogo::init() {
	if (!mSS) {
		mSS = std::make_shared<Object::SpriteStudio>();
	}

	mCounter = 0;
	mSpriteStudioIndex = 0;
}
void SSLogo::deinit() {
}
void SSLogo::update() {
	switch (mCounter) {
	case 0:
		CBright::getInstance().SetDrawBright(0, 0, 0);
		mCounter++;
		mSpriteStudioIndex = 0;
		addToDrawList(mSS);
	case 1:
		if (CBright::getInstance().Fade(255, 255, 255, 30) == 0) {
			mCounter++;
		}
		break;
	case 2:
		if (mSS->update() == Object::CFlipObj::STATUS::END) {
			// ƒV[ƒ“‚Ì•ÏX
			mSceneChanger.lock()->ChangeScene(typeid(Opening::TitleMgr));
			mCounter++;
		}
		break;
	default:
		assert(false);
		break;
	}
}
