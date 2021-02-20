#include <Windows.h>
#include <cassert>
#include <string>

#include "CBright.h"
#include "CTransFadeout.h"

CTransFadeout::CTransFadeout(int speed, Mode mode) noexcept
    : m_frame(speed)
    , m_mode(mode) {}

bool CTransFadeout::update(const std::weak_ptr<CScene> &scene) {
	switch (m_mode) {
	case Mode::Fix: // update せず固定の時
		break;
	case Mode::Update: // update する時
		scene.lock()->update();
		break;
	default:
		MessageBox(NULL,
		           (std::string("Error in " __FUNCTION__ "\n") +
		            "未実装のモードで呼ばれました: " + std::to_string((int)m_mode))
		               .c_str(),
		           TEXT("未実装"), MB_OK | MB_ICONERROR);
		std::exit(EXIT_FAILURE);
		break;
	}

	// フェード処理をする。
	// フェード終了時 true
	return CBright::getInstance().Fade(0, 0, 0, m_frame) == 0;
}
void CTransFadeout::draw(const std::weak_ptr<CScene> &scene) const {
	scene.lock()->draw();
}
