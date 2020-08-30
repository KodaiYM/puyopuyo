#include "Opening.SSLogo.h"
#include "CTransFadeout.h"
#include "Opening.title.h"

using namespace Opening;

SSLogo::SSLogo(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , mSS(std::make_shared<ImageSpriteStudio>()) {
	addToDrawList(mSS);
}
void SSLogo::update() {
	if (mSS->update()) {
		// ƒV[ƒ“‚Ì•ÏX
		mSceneChanger.lock()->ChangeScene(
		    nullptr, nullptr, std::make_shared<Opening::Title>(mSceneChanger));
	}
}
