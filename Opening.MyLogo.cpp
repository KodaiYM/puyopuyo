#include "Opening.MyLogo.h"
#include "CTransFadeout.h"
#include "Opening.SSLogo.h"
#include "Opening.title.h"

using namespace Opening;

MyLogo::MyLogo(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , mMyLogo(std::make_shared<ImageLogo>()) {
	addToDrawList(mMyLogo);
}
void MyLogo::update() {
	if (mCounter <= 120) {
		if (120 == mCounter) {
			// ƒV[ƒ“‚Ì•ÏX
			mSceneChanger.lock()->ChangeScene(
			    std::make_shared<CTransFadeout>(30, CTransFadeout::Mode::Fix),
			    nullptr, std::make_shared<SSLogo>(mSceneChanger));
		}
		++mCounter;
	}
}
