#pragma once
#include "CScene.h"

// 画面遷移のインターフェース
class ITrans {
public:
	// 最後のフレームで true を返す
	virtual bool update(const std::weak_ptr<CScene> &scene)     = 0;
	virtual void draw(const std::weak_ptr<CScene> &scene) const = 0;

public:
	virtual ~ITrans() noexcept = default;
};

// 終了時画面遷移のインターフェース
class ITransEnd : public ITrans {
public:
	virtual ~ITransEnd() noexcept = 0;
};

// 開始時画面遷移のインターフェース
class ITransStart : public ITrans {
public:
	virtual ~ITransStart() noexcept = 0;
};
