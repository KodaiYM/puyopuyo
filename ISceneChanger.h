#ifndef _INCLUDE_GUARD_ISCENECHANGER_
#define _INCLUDE_GUARD_ISCENECHANGER_

//シーンを変更するためのインターフェイスクラス
class CBaseScene;
class ISceneChanger {
public:
	virtual ~ISceneChanger() = 0;
	//指定シーンに変更する。引数は delete で解放される。
	virtual void ChangeScene(CBaseScene* pNextScene) = 0;
};

#endif
