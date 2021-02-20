#include <cassert>
#include <memory>
#include <vector>

#include "CScene.h"

void CScene::draw() const {
	for (auto &task : m_drawList) {
		task->draw();
	}
}
void CScene::clearDrawList() noexcept {
	m_drawList.clear();
}
void CScene::addToDrawList(std::shared_ptr<const IGraphic> task) {
	if (std::find(m_drawList.begin(), m_drawList.end(), task) !=
	    m_drawList.end()) {
		assert("task is already in DrawList.");
	}
	m_drawList.push_back(task);
}
void CScene::eraseFromDrawList(std::shared_ptr<const IGraphic> task) {
	if (std::find(m_drawList.begin(), m_drawList.end(), task) ==
	    m_drawList.end()) {
		assert("task was not found.");
	}
}

CScene::CScene(std::weak_ptr<ISceneChanger> sceneChanger) noexcept
    : m_sceneChanger(std::move(sceneChanger)) {}
