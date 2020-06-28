#include "Opening.h"
#include "Opening.logo.h"
#include "ResMgr.h"
#include <iostream>

/* オープニングクラスに対する定義 */
using namespace Opening;

OpeningMgr::OpeningMgr(std::weak_ptr<ISceneChanger> sceneChanger) :CSceneMgr(sceneChanger) {
}
void OpeningMgr::ChangeScene(const std::type_info& nextScene) {
	if (nextScene == typeid(LogoMgr)) {
		AssignScene(mLogoScene);
	} else if (nextScene == typeid(TitleMgr)) {
		AssignScene(mTitleScene);
	}
}
void OpeningMgr::init() {
	if (!mLogoScene) {
		mLogoScene = std::make_shared<LogoMgr>(shared_from_this());
	}
	if (!mTitleScene) {
		mTitleScene = std::make_shared<TitleMgr>(shared_from_this());
	}

	mLogoScene->init();
	mTitleScene->init();
	ResMgr::getInstance().load();

	ChangeScene(typeid(LogoMgr));
}
void OpeningMgr::deinit() {
	mLogoScene->deinit();
	mTitleScene->deinit();
}
void OpeningMgr::update() {
	getScene()->update();
}
