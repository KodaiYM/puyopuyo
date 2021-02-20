#include "CTransFadein.h"
#include "CBright.h"
#include <Windows.h>
#include <cassert>
#include <string>

CTransFadein::CTransFadein(int speed, Mode mode) noexcept
    : mSpeed(speed)
    , mMode(mode) {}

bool CTransFadein::update(const std::weak_ptr<CScene> &scene) {
	// 初めての update の時
	if (mFirstUpdate) {
		CBright::getInstance().SetDrawBright(0, 0, 0);
		mFirstUpdate = false;
	}

	switch (mMode) {
	case Mode::Fix: // update せず固定の時
		if (0 == mCounter) {
			scene.lock()->update();
			++mCounter;
		}
		break;
	case Mode::Update: // update する時
		scene.lock()->update();
		break;
	default:
		MessageBox(NULL,
		           (std::string("Error in " __FUNCTION__ "\n") +
		            "未実装のモードで呼ばれました: " + std::to_string((int)mMode))
		               .c_str(),
		           TEXT("未実装"), MB_OK | MB_ICONERROR);
		std::exit(EXIT_FAILURE);
		break;
	}

	// フェードする。
	// フェード終了時 true
	return CBright::getInstance().Fade(255, 255, 255, mSpeed) == 0;
}
void CTransFadein::draw(const std::weak_ptr<CScene> &scene) const {
	scene.lock()->draw();
}
