#include "Opening.SSLogo.h"
#include "CTransFadeout.h"
#include "Opening.title.h"

using namespace Opening;

SSLogo::SSLogo(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , m_SpriteStudio(std::make_shared<ImageSpriteStudio>()) {
	addToDrawList(m_SpriteStudio);
}

std::shared_ptr<ITransStart> SSLogo::getTransStart() const noexcept {
	return nullptr;
}

void SSLogo::update() {
	if (m_SpriteStudio->update()) {
		// ƒV[ƒ“‚Ì•ÏX
		m_sceneChanger.lock()->ChangeScene(
		    nullptr, std::make_shared<Opening::Title>(m_sceneChanger));
	}
}
