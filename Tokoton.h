#pragma once

#include <memory>

#include "CPuyoPuyo.h"
#include "CScene.h"

namespace Tokoton {

class SceneTokoton final : public CScene {
#pragma region     外部公開
public:
  void                         update() override;
  std::shared_ptr<ITransStart> getTransStart() const override;

public:
  SceneTokoton(std::weak_ptr<ISceneChanger> sceneChanger);
#pragma endregion

#pragma region デストラクタ
public:
	~SceneTokoton() noexcept = default;
#pragma endregion

#pragma region 非公開
private:
	/* ぷよぷよ盤面 */
	PuyoPuyo::CPuyoPuyo m_puyopuyo;
#pragma endregion
};

} // namespace Tokoton
