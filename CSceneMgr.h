#ifndef _INCLUDE_GUARD_CSCENEMGR_
#define _INCLUDE_GUARD_CSCENEMGR_

#include "ISceneChanger.h"
#include "CBaseScene.h"

class CSceneMgr : public ISceneChanger, CSceneTask {
private:
	CBaseScene* mScene;		//シーン管理変数
public:
	CSceneMgr();
	// 引数 pNextScene にシーンを変更する
	void ChangeScene(CBaseScene* pNextScene) override;
	void Run() override;
};

#endif
