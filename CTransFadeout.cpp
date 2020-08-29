#include "CTransFadeout.h"
#include "CBright.h"
#include <Windows.h>
#include <cassert>
#include <string>

CTransFadeout::CTransFadeout(int speed, Mode mode)
    : mSpeed(speed)
    , mMode(mode) {}
CTransFadeout::~CTransFadeout() {
	CBright::getInstance().SetDrawBright(255, 255, 255);
}
bool CTransFadeout::update(const std::weak_ptr<CScene> &scene) {
	switch (mMode) {
	case Mode::Fix:
		break;
	case Mode::Update:
		scene.lock()->update();
		break;
	default:
		MessageBox(NULL,
		           (std::string("Error in " __FUNCTION__ "\n") +
		            "ñ¢é¿ëïÇÃÉÇÅ[ÉhÇ≈åƒÇŒÇÍÇ‹ÇµÇΩ: " + std::to_string((int)mMode))
		               .c_str(),
		           TEXT("ñ¢é¿ëï"), MB_OK | MB_ICONERROR);
		std::exit(EXIT_FAILURE);
		break;
	}
	return CBright::getInstance().Fade(0, 0, 0, mSpeed) == 0;
}
void CTransFadeout::draw(const std::weak_ptr<CScene> &scene) const {
	scene.lock()->draw();
}
