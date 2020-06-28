#pragma once
#include <memory>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <typeinfo>

class CMgr;

// シーン変更希望のインターフェース
// 変更するかどうか、変更の仕方は Mgr 次第
class ISceneChanger {
public:
	virtual ~ISceneChanger() {}
	virtual void ChangeScene(const std::type_info& nextScene) = 0;
};

class CMgr {
protected:
	const std::weak_ptr<ISceneChanger> mSceneChanger;

public:
	CMgr(std::weak_ptr<ISceneChanger> sceneChanger) :mSceneChanger(sceneChanger) {}
	virtual ~CMgr() {}
	virtual void init() {}
	virtual void deinit() {}
	virtual void update() = 0;
	virtual void draw() const = 0;
};
