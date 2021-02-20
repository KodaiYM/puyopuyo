#include "Menu.h"
#include "CTransFadein.h"

using namespace Menu;

SceneMenu::SceneMenu(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , m_background(std::make_shared<ImageBackground>())
    , m_battle(std::make_shared<ImageBattle>(0, 0))
    , m_battle_selected(std::make_shared<ImageBattleSelected>(0, 0))
    , m_tokoton(std::make_shared<ImageTokoton>(0, 0))
    , m_tokoton_selected(std::make_shared<ImageTokotonSelected>(0, 0)) {
	addToDrawList(m_background);
	addToDrawList(m_battle);
}

void SceneMenu::update() {
	m_BGMMenu.play();
}

std::shared_ptr<ITransStart> Menu::SceneMenu::getTransStart() const {
	return std::make_shared<CTransFadein>(60, CTransFadein::Mode::Update);
}
