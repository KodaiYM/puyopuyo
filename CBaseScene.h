#ifndef _INCLUDE_GUARD_CBASESCENE_
#define _INCLUDE_GUARD_CBASESCENE_

#include "CSceneTask.h"

//シーンの基底クラス。
class ISceneChanger;
class CBaseScene : public CSceneTask {
protected:
	ISceneChanger* mSceneChanger;	// クラス所有元にシーン切り替えを伝えるインターフェイス
public:
	CBaseScene(ISceneChanger* changer);
	virtual ~CBaseScene() {};
	virtual void Run() {};
};

#endif
