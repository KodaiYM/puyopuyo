#pragma once
#include "ITrans.h"

class CTransFadein final : public ITransStart {
#pragma region     外部公開
public:
  enum class Mode {
    Fix,   // 初期フレームで止めた状態でフェードイン
    Update // 更新しつつフェードイン
  };

public:
  // 最後のフレームで true を返す
  bool update(const std::weak_ptr<CScene> &scene) override;
  void draw(const std::weak_ptr<CScene> &scene) const override;

public:
  /**
   * speed: フェードインするフレーム数
   * mode:  フェードイン方法
   */
  CTransFadein(int speed, Mode mode) noexcept;
#pragma endregion

#pragma region デストラクタ
public:
	~CTransFadein() noexcept = default;
#pragma endregion

#pragma region 非公開
private:
	bool       mFirstUpdate = true; // 初めてのupdate
	int        mCounter     = 0;
	const int  mSpeed;
	const Mode mMode;
#pragma endregion
};
