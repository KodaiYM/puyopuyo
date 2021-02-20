#pragma once

#include <memory>

#include "ISceneChanger.h"

// シーン管理の基底クラス
class CSceneMgr final : public ISceneChanger,
                        public std::enable_shared_from_this<CSceneMgr> {
#pragma region 外部公開
public:
	void update();
	void draw() const;
	void ChangeScene(std::shared_ptr<ITransEnd> howToEnd,
	                 std::shared_ptr<CScene>    nextScene) override;

public:
	CSceneMgr() noexcept = default;
#pragma endregion

#pragma region デストラクタ
public:
	~CSceneMgr() noexcept = default;
#pragma endregion

#pragma region 非公開
private:
	bool m_lasted = false;
	bool changed  = false; // 直前の update が ChangeScene を呼んだ
	std::shared_ptr<ITransEnd>   m_howToEnd;
	std::shared_ptr<ITransStart> m_howToStart;
	std::shared_ptr<CScene>      m_currentScene;
	std::shared_ptr<CScene>      m_nextScene;
#pragma endregion
};
