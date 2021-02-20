#include "Menu.h"
#include "CTransFadein.h"

using namespace Menu;

SceneMenu::SceneMenu(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , mBackground(std::make_shared<ImageBackground>())
    , mBattle(std::make_shared<ImageBattle>(0, 0))
    , mBattle_selected(std::make_shared<ImageBattleSelected>(0, 0))
    , mTokoton(std::make_shared<ImageTokoton>(0, 0))
    , mTokoton_selected(std::make_shared<ImageTokotonSelected>(0, 0)) {
	addToDrawList(mBackground);
	addToDrawList(mBattle);
}

void SceneMenu::update() {
	mBGMMenu.play();
	switch (mCounter) {
	case 0:
		break;
	default:
		assert(false);
	}
}

std::shared_ptr<ITransStart> Menu::SceneMenu::getTransStart() const {
	return std::make_shared<CTransFadein>(60, CTransFadein::Mode::Update);
}
