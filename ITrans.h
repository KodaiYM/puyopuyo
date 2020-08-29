#pragma once
#include "CScene.h"

// 画面遷移のインターフェース
class ITrans {
protected:
	ITrans() {}
	virtual ~ITrans() {}

public:
	// 最後のフレームで true を返す
	virtual bool update(const std::weak_ptr<CScene> &scene)     = 0;
	virtual void draw(const std::weak_ptr<CScene> &scene) const = 0;
};

// 終了時画面遷移のインターフェース
class ITransEnd : public ITrans {
protected:
	ITransEnd() {}
	virtual ~ITransEnd() {}
};

// 開始時画面遷移のインターフェース
class ITransStart : public ITrans {
protected:
	ITransStart() {}
	virtual ~ITransStart() {}
};
