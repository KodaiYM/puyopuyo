#include "Opening.MyLogo.h"
#include "CTransFadein.h"
#include "CTransFadeout.h"
#include "Opening.SSLogo.h"
#include "Opening.title.h"

using namespace Opening;

MyLogo::MyLogo(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , mMyLogo(std::make_shared<ImageLogo>()) {
	addToDrawList(mMyLogo);
}

std::shared_ptr<ITransStart> MyLogo::getTransStart() const {
	return std::make_shared<CTransFadein>(60, CTransFadein::Mode::Fix);
}

void MyLogo::update() {
	if (mCounter <= 120) {
		if (120 == mCounter) {
			// ƒV[ƒ“‚Ì•ÏX
			m_sceneChanger.lock()->ChangeScene(
			    std::make_shared<CTransFadeout>(30, CTransFadeout::Mode::Fix),
			    std::make_shared<SSLogo>(m_sceneChanger));
		}
		++mCounter;
	}
}
