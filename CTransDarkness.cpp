#include "CTransDarkness.h"
#include "CBright.h"
#include <Windows.h>
#include <cassert>
#include <string>

CTransDarkness::CTransDarkness(int frame, Mode mode) noexcept
    : m_frame(frame)
    , m_mode(mode) {}

bool CTransDarkness::update(const std::weak_ptr<CScene> &scene) {
	// 初めての update の場合
	if (m_firstUpdate) {
		CBright::getInstance().SetScreenBright(255, 255, 255);
		m_firstUpdate = false;
	}

	switch (m_mode) {
	case Mode::Fix:
		break;
	case Mode::Update:
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
	if (m_counter < m_frame) {
		++m_counter;
	}

	// 最後のフレームの時 true
	return m_counter == m_frame;
}
void CTransDarkness::draw(const std::weak_ptr<CScene> &scene) const noexcept {}
