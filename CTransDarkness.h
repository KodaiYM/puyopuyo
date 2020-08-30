#pragma once
#include "ITrans.h"

class CTransDarkness final : virtual public ITransStart,
                             virtual public ITransEnd {
public:
	enum class Mode {
		Fix,   // 暗転状態で固定
		Update // 暗転状態でも、更新はする
	};

private:
	bool       mFirstUpdate = true; // 初めての update
	int        mCounter     = 0;
	const int  mFrame;
	const Mode mMode;

public:
	/**
	 * frame: 暗転状態のフレーム長さ
	 * mode:  暗転状態での、シーンの動作方法
	 */
	CTransDarkness(int frame, Mode mode);
	~CTransDarkness();
	// 最後のフレームで true を返す
	virtual bool update(const std::weak_ptr<CScene> &scene) override;
	virtual void draw(const std::weak_ptr<CScene> &scene) const override;
};
