#pragma once

#include "CSceneMgr.h"
#include "Opening.logo.h"
#include "Opening.title.h"

//オープニング画面クラス
namespace Opening {
	class OpeningMgr final : public CSceneMgr {
	private:
		std::shared_ptr<LogoMgr> mLogoScene;
		std::shared_ptr<TitleMgr> mTitleScene;

	public:
		OpeningMgr(std::weak_ptr<ISceneChanger> sceneChanger);

		virtual void ChangeScene(const std::type_info& nextScene) override;
		virtual void update() override final;
		virtual void init() override;
		virtual void deinit() override;
	};
}
