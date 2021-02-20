#include "Opening.SSLogo.h"
#include "CTransFadeout.h"
#include "Opening.title.h"

using namespace Opening;

SSLogo::SSLogo(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , mSS(std::make_shared<ImageSpriteStudio>()) {
	addToDrawList(mSS);
}

std::shared_ptr<ITransStart> SSLogo::getTransStart() const {
	return nullptr;
}

void SSLogo::update() {
	if (mSS->update()) {
		// ƒV[ƒ“‚Ì•ÏX
		m_sceneChanger.lock()->ChangeScene(
		    nullptr, std::make_shared<Opening::Title>(m_sceneChanger));
	}
}
