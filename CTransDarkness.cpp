#include "CTransDarkness.h"
#include "CBright.h"
#include <Windows.h>
#include <cassert>
#include <string>

CTransDarkness::CTransDarkness(int frame, Mode mode)
    : mFrame(frame)
    , mMode(mode) {}
CTransDarkness::~CTransDarkness() {}
bool CTransDarkness::update(const std::weak_ptr<CScene> &scene) {
	// 初めての update の場合
	if (mFirstUpdate) {
		CBright::getInstance().SetDrawBright(255, 255, 255);
		mFirstUpdate = false;
	}

	switch (mMode) {
	case Mode::Fix:
		break;
	case Mode::Update:
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
	if (mCounter < mFrame) {
		++mCounter;
	}

	// 最後のフレームの時 true
	return mCounter == mFrame;
}
void CTransDarkness::draw(const std::weak_ptr<CScene> &scene) const {}
