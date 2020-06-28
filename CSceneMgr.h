#pragma once

#include <memory>
#include "CMgr.h"

// シーン管理の基底クラス
class CSceneMgr :public CMgr, public ISceneChanger, public std::enable_shared_from_this<CSceneMgr> {
private:
	std::shared_ptr<CMgr> mCurrentScene;

protected:
	CSceneMgr(std::weak_ptr<ISceneChanger> sceneChanger) :CMgr(sceneChanger) {}
	std::shared_ptr<CMgr> getScene() const {
		return mCurrentScene;
	}
	void setScene(std::shared_ptr<CMgr> nextScene) {
		mCurrentScene = nextScene;
	}

	// シーンがあれば利用し、なければ生成して利用する
	template<typename T>
	void AssignScene(std::shared_ptr<T>& scene) {
		if (!scene) {
			scene = std::make_shared<T>(shared_from_this());
		}
		setScene(scene);
	}

public:
	virtual ~CSceneMgr() {}

	virtual void update() override = 0;
	virtual void draw() const override final {
		getScene()->draw();
	}
	virtual void ChangeScene(const std::type_info& nextScene) override = 0;
};
