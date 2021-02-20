#pragma once

#include "BGMMenu.h"
#include "CScene.h"
#include "ImageMenu.h"

namespace Menu {
class SceneMenu final : public CScene {
#pragma region  外部公開
public:
  void                         update() override;
  std::shared_ptr<ITransStart> getTransStart() const override;

public:
  SceneMenu(std::weak_ptr<ISceneChanger> sceneChanger);
#pragma endregion

#pragma region デストラクタ
public:
	~SceneMenu() noexcept = default;
#pragma endregion

#pragma region 非公開
private:
	int mCounter = 0;

	/* 画像 */
	const std::shared_ptr<ImageBackground>      mBackground;
	const std::shared_ptr<ImageBattle>          mBattle;
	const std::shared_ptr<ImageBattleSelected>  mBattle_selected;
	const std::shared_ptr<ImageTokoton>         mTokoton;
	const std::shared_ptr<ImageTokotonSelected> mTokoton_selected;

	/* 音 */
	BGMMenu mBGMMenu;
#pragma endregion
};
} // namespace Menu
