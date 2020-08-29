#pragma once

#include <memory>

class ITransEnd;
class ITransStart;
class CScene;
// シーン変更希望のインターフェース
// 変更するかどうか、変更の仕方は Mgr 次第
class ISceneChanger {
public:
	virtual ~ISceneChanger() {}
	// 現在のシーンの終わり方、次のシーンとその始まり方を渡し、シーンの変更をする
	virtual void ChangeScene(std::shared_ptr<ITransEnd> &&,
	                         std::shared_ptr<ITransStart> &&,
	                         std::shared_ptr<CScene> nextScene) = 0;
};
