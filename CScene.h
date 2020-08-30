#pragma once
#include "ISceneChanger.h"
#include "Image.h"
#include <cassert>
#include <memory>
#include <vector>

// オブジェクトを直接操作する基底クラス
class CScene : public std::enable_shared_from_this<CScene> {
private:
	std::vector<std::shared_ptr<const Graphic>> DrawList;

protected:
	std::weak_ptr<ISceneChanger> mSceneChanger;
	CScene(std::weak_ptr<ISceneChanger> sceneChanger)
	    : mSceneChanger(std::move(sceneChanger)) {}

public:
	virtual ~CScene() {}

	virtual void update() = 0;
	virtual void draw() const final {
		for (auto &task : DrawList) {
			task->draw();
		}
	}
	void clearDrawList() {
		DrawList.clear();
	}
	void addToDrawList(std::shared_ptr<const Graphic> task) {
		if (std::find(DrawList.begin(), DrawList.end(), task) != DrawList.end()) {
			assert("task is already in DrawList.");
		}
		DrawList.push_back(task);
	}
	void eraseFromDrawList(std::shared_ptr<const Graphic> task) {
		if (std::find(DrawList.begin(), DrawList.end(), task) == DrawList.end()) {
			assert("task was not found.");
		}
	}
};
