#include "Menu.h"

using namespace Menu;

SceneMenu::SceneMenu(std::weak_ptr<ISceneChanger> sceneChanger)
    : CScene(sceneChanger)
    , mBackground(std::make_shared<ImageBackground>())
    , mBattle(std::make_shared<ImageBattle>())
    , mBattle_selected(std::make_shared<ImageBattleSelected>())
    , mTokoton(std::make_shared<ImageTokoton>())
    , mTokoton_selected(std::make_shared<ImageTokotonSelected>()) {
	addToDrawList(mBackground);
	addToDrawList(mBattle);
}
void SceneMenu::update() {
	switch (mCounter) {
	case 0:
		mBGMMenu.play();
		break;
	default:
		assert(false);
	}
}
