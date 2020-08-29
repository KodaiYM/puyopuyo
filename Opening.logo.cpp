#include "Opening.logo.h"
#include "CTransFadeout.h"
#include "Opening.title.h"

using namespace Opening;

MyLogo::MyLogo(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , mMyLogo(std::make_shared<GraphicLogo>()) {
	addToDrawList(mMyLogo);
}
void MyLogo::update() {
	if (mCounter <= 120) {
		if (120 == mCounter) {
			// シーンの変更
			mSceneChanger.lock()->ChangeScene(
			    std::make_shared<CTransFadeout>(30, CTransFadeout::Mode::Fix),
			    nullptr, std::make_shared<SSLogo>(mSceneChanger));
		}
		++mCounter;
	}
}

SSLogo::SSLogo(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , mSS(std::make_shared<GraphicSpriteStudio>()) {
	addToDrawList(mSS);
}
void SSLogo::update() {
	if (mSS->update()) {
		// シーンの変更
		mSceneChanger.lock()->ChangeScene(
		    nullptr, nullptr, std::make_shared<Opening::Title>(mSceneChanger));
	}
}
