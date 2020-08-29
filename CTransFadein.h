#pragma once
#include "ITrans.h"

class CTransFadein final : public ITransStart {
public:
	enum class Mode {
		Fix,   // 初期フレームで止めた状態でフェードイン
		Update // 更新しつつフェードイン
	};

private:
	int        mCounter = 0;
	const int  mSpeed;
	const Mode mMode;

public:
	/**
	 * scene: フェードインするシーン
	 * speed: フェードインするフレーム数
	 * mode:  フェードイン方法
	 */
	CTransFadein(int speed, Mode mode);
	// 最後のフレームで true を返す
	virtual bool update(const std::weak_ptr<CScene> &scene) override;
	virtual void draw(const std::weak_ptr<CScene> &scene) const override;
};
