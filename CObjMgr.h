#pragma once
#include "CMgr.h"
#include "CObj.h"

// オブジェクトを直接操作する基底クラス
class CObjMgr :public CMgr {
private:
	std::vector<std::shared_ptr<const CObj>> DrawList;

protected:
	CObjMgr(std::weak_ptr<ISceneChanger> sceneChanger) :CMgr(sceneChanger) {}

public:
	virtual ~CObjMgr() {}

	virtual void init() override {}
	virtual void deinit() override {}
	virtual void update() override = 0;
	virtual void draw() const override final {
		for (auto& task : DrawList) {
			task->draw();
		}
	}
	void clearDrawList() {
		DrawList.clear();
	}
	void addToDrawList(std::shared_ptr<const CObj> task) {
		if (std::find(DrawList.begin(), DrawList.end(), task) != DrawList.end()) {
			assert("task is already in DrawList.");
		}
		DrawList.push_back(task);
	}
	void eraseFromDrawList(std::shared_ptr<const CObj> task) {
		if (std::find(DrawList.begin(), DrawList.end(), task) == DrawList.end()) {
			assert("task was not found.");
		}
	}
};
