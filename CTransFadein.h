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
   * frame: フェードインするフレーム数
   * mode:  フェードイン方法
   */
  CTransFadein(int frame, Mode mode) noexcept;
#pragma endregion

#pragma region デストラクタ
public:
	~CTransFadein() noexcept = default;
#pragma endregion

#pragma region 非公開
private:
	bool       m_firstUpdate = true; // 初めてのupdate
	int        m_counter     = 0;    // フレームカウンタ
	const int  m_frame;              // フェードインフレーム数
	const Mode m_mode;               // フェードイン方法
#pragma endregion
};
