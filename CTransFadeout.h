#pragma once
#include "ITrans.h"

class CTransFadeout final : public ITransEnd {
#pragma region      外部公開
public:
  enum class Mode {
    Fix,   // 最終フレームで止めた状態でフェードアウト
    Update // 更新しつつフェードアウト
  };

public:
  // 最後のフレームで true を返す
  bool update(const std::weak_ptr<CScene> &scene) override;
  void draw(const std::weak_ptr<CScene> &scene) const override;

public:
  /**
   * speed: フェードアウトするフレーム数
   * mode:  フェードアウト方法
   */
  CTransFadeout(int speed, CTransFadeout::Mode mode) noexcept;
#pragma endregion

#pragma region デストラクタ
public:
	~CTransFadeout() noexcept = default;
#pragma endregion

#pragma region 非公開
private:
	bool       mFirstUpdate = true; // 初めての update
	const int  mSpeed;
	const Mode mMode;
#pragma endregion
};
