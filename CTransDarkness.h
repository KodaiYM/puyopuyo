#pragma once
#include "ITrans.h"

class CTransDarkness final : virtual public ITransStart,
                             virtual public ITransEnd {
#pragma region 外部公開
public:
	enum class Mode {
		Fix,   // 暗転状態で固定
		Update // 暗転状態でも、更新はする
	};

public:
	// 最後のフレームで true を返す
	bool update(const std::weak_ptr<CScene> &scene) override;
	void draw(const std::weak_ptr<CScene> &scene) const noexcept override;

public:
	/**
	 * frame: 暗転状態のフレーム長さ
	 * mode:  暗転状態での、シーンの動作方法
	 */
	CTransDarkness(int frame, Mode mode) noexcept;
#pragma endregion

#pragma region デストラクタ
public:
	~CTransDarkness() noexcept = default;
#pragma endregion

#pragma region 非公開
private:
	bool       m_firstUpdate = true; // 初めての update
	int        m_counter     = 0;    // フレームカウンタ
	const int  m_frame;              // 暗転フレーム長さ
	const Mode m_mode; // 暗転状態での、シーンの動作方法
#pragma endregion
};
