#include "CTransFadein.h"
#include "CBright.h"
#include <Windows.h>
#include <cassert>
#include <string>

CTransFadein::CTransFadein(int speed, Mode mode)
    : mSpeed(speed)
    , mMode(mode) {
	CBright::getInstance().SetDrawBright(0, 0, 0);
}
bool CTransFadein::update(const std::weak_ptr<CScene> &scene) {
	switch (mMode) {
	case Mode::Fix:
		if (0 == mCounter) {
			scene.lock()->update();
			++mCounter;
		}
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
	return CBright::getInstance().Fade(255, 255, 255, mSpeed) == 0;
}
void CTransFadein::draw(const std::weak_ptr<CScene> &scene) const {
	scene.lock()->draw();
}
