#include <DxLib.h>
#include <cassert>

#include "CTransDarkness.h"
#include "CTransFadein.h"
#include "CTransFadeout.h"
#include "Menu.h"
#include "Opening.MyLogo.h"
#include "Opening.Title.h"
#include "key.h"

using namespace Opening;

Title::Title(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , m_TitleMovie(std::make_shared<MovieTitle>()) {
	addToDrawList(m_TitleMovie);
}

std::shared_ptr<ITransStart> Title::getTransStart() const noexcept {
	return nullptr;
}

void Title::update() {
	// まだムービーが終了していなければ
	if (!m_movieFinished) {
		// 再生する。
		// ムービー終了なら
		if (m_TitleMovie->update()) {
			// ムービー終了とする
			m_movieFinished = true;
		}
	}

	switch (m_counter) {
	case 0: // まだエンターを押していない
		if (m_movieFinished) {
			// ムービー終了
			m_sceneChanger.lock()->ChangeScene(
			    std::make_shared<CTransDarkness>(60, CTransDarkness::Mode::Fix),
			    std::make_shared<Opening::MyLogo>(m_sceneChanger));
		} else if (KeyStateOf(KEY_INPUT_RETURN) == 1) {
			m_sceneChanger.lock()->ChangeScene(
			    std::make_shared<CTransFadeout>(60, CTransFadeout::Mode::Update),
			    std::make_shared<Menu::SceneMenu>(m_sceneChanger));
			++m_counter;
		}
		break;
	case 1: // エンターを押して、遷移中
		break;
	default:
		assert(false);
		break;
	}
}
