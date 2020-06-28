#pragma once

#include "CSceneMgr.h"
#include "Game_define.h"
#include "CPlayer.h"
#include <vector>

//オープニング画面クラス
namespace Game {
	// 子フェーズで共用する関数
	class Functions {
	};
	// フェーズ管理のクラス
	class Scene : public CSceneMgr, public Functions, public std::enable_shared_from_this<Scene> {
	private:
		const std::weak_ptr<ISceneChanger> mSceneChanger;
		const std::shared_ptr<IResourceHandlers> mResourceHandler;
		std::vector<GraphicName> getGraphicNames() const override {
			std::vector<GraphicName> names = {
				GraphicName::background,
				GraphicName::frame,
				GraphicName::ojama,
				GraphicName::cross,
				GraphicName::left_next,
				GraphicName::right_next,
				GraphicName::blue,
				GraphicName::green,
				GraphicName::pink,
				GraphicName::red
			};
			return names;
		}
		std::vector<SoundName> getSoundNames() const override {
			std::vector<SoundName> names = {
				SoundName::chain,
				SoundName::game_over,
				SoundName::land,
				SoundName::move,
				SoundName::rotate
			};
			return names;
		}
		std::unique_ptr<Game::CPlayer> mPlayer;
		std::unique_ptr<CResourceMgr> mResourceMgr;

	public:
		Scene(std::weak_ptr<ISceneChanger> sceneChanger, std::shared_ptr<IResourceHandlers> resourceHanlder);

		virtual void init() override;
	};
}
