#pragma once

#include "BGMMenu.h"
#include "CScene.h"
#include "ImageMenu.h"

namespace Menu {
class SceneMenu final : public CScene {
private:
	int mCounter = 0;

	/* ‰æ‘œ */
	const std::shared_ptr<ImageBackground>      mBackground;
	const std::shared_ptr<ImageBattle>          mBattle;
	const std::shared_ptr<ImageBattleSelected>  mBattle_selected;
	const std::shared_ptr<ImageTokoton>         mTokoton;
	const std::shared_ptr<ImageTokotonSelected> mTokoton_selected;

	/* ‰¹ */
	BGMMenu mBGMMenu;

public:
	SceneMenu(std::weak_ptr<ISceneChanger> sceneChanger);

	virtual void update() override;
};
} // namespace Menu
