#pragma once
#include "ITrans.h"

class CTransFadeout final : public ITransEnd {
public:
	enum class Mode {
		Fix,   // 最終フレームで止めた状態でフェードアウト
		Update // 更新しつつフェードアウト
	};

private:
	const int  mSpeed;
	const Mode mMode;

public:
	/**
	 * scene: フェードアウトするシーン
	 * speed: フェードアウトするフレーム数
	 * mode:  フェードアウト方法
	 */
	CTransFadeout(int speed, Mode mode);
	~CTransFadeout();
	// 最後のフレームで true を返す
	virtual bool update(const std::weak_ptr<CScene> &scene) override;
	virtual void draw(const std::weak_ptr<CScene> &scene) const override;
};
