#pragma once
#include <memory>
#include <vector>

#include "IGraphic.h"
#include "ISceneChanger.h"

// オブジェクトを直接操作する基底クラス
class CScene {
#pragma region 外部公開
public:
	virtual void                         update()              = 0;
	virtual std::shared_ptr<ITransStart> getTransStart() const = 0;

public:
	void draw() const;
	void clearDrawList() noexcept;
	void addToDrawList(std::shared_ptr<const IGraphic> task);
	void eraseFromDrawList(std::shared_ptr<const IGraphic> task);

public:
	CScene(std::weak_ptr<ISceneChanger> sceneChanger) noexcept;
#pragma endregion

#pragma region デストラクタ
public:
	virtual ~CScene() noexcept = default;
#pragma endregion

#pragma region 継承先のみ公開
protected:
	std::weak_ptr<ISceneChanger> m_sceneChanger;
#pragma endregion

#pragma region 非公開
private:
	std::vector<std::shared_ptr<const IGraphic>> m_drawList;
#pragma endregion
};
