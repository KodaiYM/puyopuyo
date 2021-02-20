#include "CSceneMgr.h"
#include "CBright.h"
#include "ITrans.h"
#include <cassert>

void CSceneMgr::update() {
	changed = false;

	/* 終了時処理 */
	if (m_howToEnd) {
		if (!m_lasted) {
			// m_howToEnd に値があり、直前が最後のフレームではない場合
			if (m_howToEnd->update(m_currentScene)) {
				// 最後のフレームの時
				m_lasted = true;
			}
			return;
		} else {
			// 直前が最後のフレームだった
			assert(m_lasted);

			m_howToEnd.reset();
			m_currentScene.reset();
			m_lasted = false;
		}
	}

	/* 開始時処理 */
	if (m_howToStart) {
		if (!m_lasted) {
			// m_howToStart に値があり、直前が最後のフレームではない場合
			if (m_howToStart->update(m_nextScene)) {
				// 最後のフレームの時
				m_lasted = true;
			}
			return;
		} else {
			// 直前が最後のフレームだった
			assert(m_lasted);

			m_howToStart.reset();
			m_lasted = false;
		}
	}

	/* next scene の移動 */
	if (m_nextScene) {
		m_currentScene = std::move(m_nextScene);
		m_nextScene.reset();
		CBright::getInstance().SetScreenBright(255, 255, 255);
	}

	m_currentScene->update();
}
void CSceneMgr::draw() const {
	if (changed) {
		m_currentScene->draw();
	} else {
		if (m_howToEnd) {
			m_howToEnd->draw(m_currentScene);
		} else if (m_howToStart) {
			m_howToStart->draw(m_nextScene);
		} else {
			m_currentScene->draw();
		}
	}
}
void CSceneMgr::ChangeScene(std::shared_ptr<ITransEnd> howToEnd,
                            std::shared_ptr<CScene>    nextScene) {
	m_howToEnd   = std::move(howToEnd);
	m_nextScene  = std::move(nextScene);
	m_howToStart = m_nextScene->getTransStart();
	changed      = true;
	m_lasted     = false;
}
