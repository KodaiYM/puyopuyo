#include "CTransFadein.h"
#include "CBright.h"
#include <Windows.h>
#include <cassert>
#include <string>

CTransFadein::CTransFadein(int frame, Mode mode) noexcept
    : m_frame(frame)
    , m_mode(mode) {}

bool CTransFadein::update(const std::weak_ptr<CScene> &scene) {
	switch (m_mode) {
	case Mode::Fix: // update せず固定の時
		if (m_firstUpdate) {
			scene.lock()->update();
			++m_counter;
		}
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

	// 初めての update の時
	if (m_firstUpdate) {
		CBright::getInstance().SetScreenBright(0, 0, 0);
		m_firstUpdate = false;
	}

	// フェードする。
	// フェード終了時 true
	return CBright::getInstance().Fade(255, 255, 255, m_frame) == 0;
}
void CTransFadein::draw(const std::weak_ptr<CScene> &scene) const {
	scene.lock()->draw();
}
