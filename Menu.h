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
	enum class BUTTON { BATTLE, TOKOTON, length } m_selected_button;
	enum class STATE { SELECTING, TRANSITIONING } m_state;

	/* 画像 */
	const std::shared_ptr<IGraphic> m_background;
	const std::shared_ptr<IGraphic> m_battle;
	const std::shared_ptr<IGraphic> m_battle_selected;
	const std::shared_ptr<IGraphic> m_tokoton;
	const std::shared_ptr<IGraphic> m_tokoton_selected;

	/* 音 */
	BGMMenu m_BGMMenu;
#pragma endregion
};
} // namespace Menu
