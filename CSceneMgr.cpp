#include "CSceneMgr.h"

void CSceneMgr::Run() {
	mScene->Run();
}

CSceneMgr::CSceneMgr() {
	mScene = nullptr;
}

// 引数 pNextScene にシーンを変更する
void CSceneMgr::ChangeScene(CBaseScene* pNextScene) {
	//現在のシーンを解放
	delete mScene;

	//次のシーンをセットする
	mScene = pNextScene;
}
