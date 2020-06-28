#ifndef _INCLUDE_GUARD_OPENING_
#define _INCLUDE_GUARD_OPENING_

#include "CSceneMgr.h"
#include "CBright.h"
#include <unordered_map>

//オープニング画面クラス
class COpening : public CBaseScene {
private:
	enum class Scene {
		init,
		logo_init,
		logo,
		title_init,
		title,
		fadeout_init,
		fadeout
	};
	enum class GrName {	// GrPath と対応
		Logo,
		Title,

		Length // Length は必ず最後
	};
	static const std::unordered_map<GrName, const char*> GrPath;
	class CLogoPlayer;
	class CTitlePlayer;
	CLogoPlayer* mLogoPlayer;
	CTitlePlayer* mTitlePlayer;
	Scene mScene;
	CBright* mFader;
	int mGrHandle[(int)GrName::Length];
public:
	COpening(ISceneChanger* changer);
	void Run() override;
};

//ロゴ再生クラス
class COpening::CLogoPlayer {
private:
	enum class Scene {
		init,
		fadein_init,
		fadein,
		display_init,
		display,
		fadeout_init,
		fadeout,
		end
	};
	Scene mScene;
	CBright* mFader;
	int mCounter;
	const int mLogoGrHandle;
public:
	CLogoPlayer(int GrHandle);
	int Run();
};

//タイトル再生クラス
class COpening::CTitlePlayer {
private:
	enum class Scene {
		init,
		play,
		end
	};
	Scene mScene;
	const int mTitleGrHandle;
public:
	CTitlePlayer(int GrHandle);
	~CTitlePlayer();
	int Run();
};

#endif
