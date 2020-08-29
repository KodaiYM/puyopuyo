#pragma once
#include "ISceneChanger.h"
#include <memory>

// シーン管理の基底クラス
class CSceneMgr final : public ISceneChanger,
                        public std::enable_shared_from_this<CSceneMgr> {
private:
	bool lasted  = false;
	bool changed = false; // 直前の update が ChangeScene を呼んだ
	std::shared_ptr<ITransEnd>   mHowToEnd;
	std::shared_ptr<ITransStart> mHowToStart;
	std::shared_ptr<CScene>      mCurrentScene;
	std::shared_ptr<CScene>      mNextScene;

public:
	void         update();
	void         draw() const;
	virtual void ChangeScene(std::shared_ptr<ITransEnd> &&,
	                         std::shared_ptr<ITransStart> &&,
	                         std::shared_ptr<CScene> nextScene) override;
};
