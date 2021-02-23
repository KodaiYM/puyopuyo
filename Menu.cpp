#include "Menu.h"
#include "CTransFadein.h"
#include "CTransFadeout.h"
#include "Tokoton.h"
#include "key.h"

using namespace Menu;

SceneMenu::SceneMenu(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , m_background(std::make_shared<ImageBackground>())
    , m_battle(std::make_shared<ImageBattle>(150, 300, ORIGIN::CENTER))
    , m_battle_selected(
          std::make_shared<ImageBattleSelected>(150, 300, ORIGIN::CENTER))
    , m_tokoton(std::make_shared<ImageTokoton>(490, 300, ORIGIN::CENTER))
    , m_tokoton_selected(
          std::make_shared<ImageTokotonSelected>(490, 300, ORIGIN::CENTER))
    , m_selected_button(BUTTON::BATTLE)
    , m_state(STATE::SELECTING) {
	addToDrawList(m_background);
	addToDrawList(m_battle_selected);
	addToDrawList(m_tokoton);
}

void SceneMenu::update() {
	m_BGMMenu.play();

	switch (m_state) {
	case STATE::SELECTING:
		clearDrawList();
		addToDrawList(m_background);
		addToDrawList(BUTTON::BATTLE == m_selected_button ? m_battle_selected
		                                                  : m_battle);
		addToDrawList(BUTTON::TOKOTON == m_selected_button ? m_tokoton_selected
		                                                   : m_tokoton);

		if (KeyStateOf(KEY_INPUT_RIGHT) == 1) {
			m_selected_button =
			    static_cast<BUTTON>((static_cast<int>(m_selected_button) + 1) %
			                        static_cast<int>(BUTTON::length));
		}
		if (KeyStateOf(KEY_INPUT_RETURN) == 1) {
			m_state = STATE::TRANSITIONING;
			m_sceneChanger.lock()->ChangeScene(
			    std::make_shared<CTransFadeout>(60, CTransFadeout::Mode::Update),
			    std::make_shared<Tokoton::SceneTokoton>(m_sceneChanger));
		}
		break;
	case STATE::TRANSITIONING:
		break;
	default:
		assert(!"ñ¢é¿ëïÇÃÉVÅ[Éì");
	}
}

std::shared_ptr<ITransStart> Menu::SceneMenu::getTransStart() const {
	return std::make_shared<CTransFadein>(60, CTransFadein::Mode::Update);
}
