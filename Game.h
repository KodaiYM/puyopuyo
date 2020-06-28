#ifndef _INCLUDE_GUARD_GAME_
#define _INCLUDE_GUARD_GAME_

#include "CBaseScene.h"
#include "CResourceMgr.h"
#include "Game_define.h"
#include "CPlayer.h"

//ÉQÅ[ÉÄâÊñ ÉNÉâÉX
class CGame : public CBaseScene, CResourceMgr {
public:
	CGame(ISceneChanger* changer);
	void Run() override;
private:
	enum class Scene {
		init,
		run
	};
	static const std::unordered_map <Game::GraphicName, const char*> GraphicPath;
	static const std::unordered_map <Game::SoundName, const char*> SoundPath;

	Scene mScene;
	Game::CPlayer* mPlayer;
	CResourceMgr* mResourceMgr;
};

#endif
