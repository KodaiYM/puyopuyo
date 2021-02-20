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
	enum class BUTTON { BATTLE, TOKOTON } m_selected_button = BUTTON::BATTLE;

	/* 画像 */
	const std::shared_ptr<ImageBackground>      m_background;
	const std::shared_ptr<ImageBattle>          m_battle;
	const std::shared_ptr<ImageBattleSelected>  m_battle_selected;
	const std::shared_ptr<ImageTokoton>         m_tokoton;
	const std::shared_ptr<ImageTokotonSelected> m_tokoton_selected;

	/* 音 */
	BGMMenu m_BGMMenu;
#pragma endregion
};
} // namespace Menu
