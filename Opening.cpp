#include <DxLib.h>
#include "Opening.h"
#include "Game.h"
#include "key.h"

/* オープニングクラスに対する定義 */
const std::unordered_map<COpening::GrName, const char*> COpening::GrPath = { // GrName と対応
	{GrName::Logo, "./img/Opening/logo.png"},
	{GrName::Title, "./img/Opening/title.ogv"}
};
COpening::COpening(ISceneChanger* changer) : CBaseScene(changer) {
	mScene = Scene::init;
}

void COpening::Run() {
	switch (mScene) {
	case Scene::init:
		for (int i = 0; i < (int)GrName::Length; i++) {
			mGrHandle[i] = LoadGraph(GrPath.at((GrName)i));
		}
		mScene = Scene::logo_init;
	case Scene::logo_init:
		// ロゴの再生クラスの生成
		mLogoPlayer = new CLogoPlayer(mGrHandle[(int)GrName::Logo]);
		mScene = Scene::logo;
	case Scene::logo:
		// ロゴの再生と、終了チェック
		if (mLogoPlayer->Run() == 0) {
			delete mLogoPlayer;
			mScene = Scene::title_init;
		}
		break;
	case Scene::title_init:
		// タイトルの再生クラスの生成
		mTitlePlayer = new CTitlePlayer(mGrHandle[(int)GrName::Title]);
		mScene = Scene::title;
	case Scene::title:
		// タイトルの再生と、終了チェック
		if (mTitlePlayer->Run() == 0) {
			delete mTitlePlayer;
			// ロゴの再生に戻る
			mScene = Scene::logo_init;
			break;
		}
		// ENTERキーを押したとき
		if (KeyStateOf(KEY_INPUT_RETURN) == 1) {
			// シーンの変更を行う
			mScene = Scene::fadeout_init;
			break;
		}
		break;
	case Scene::fadeout_init:
		mFader = new CBright();
		mFader->SetFader(0, 0, 0, 30);
		mScene = Scene::fadeout;
	case Scene::fadeout:
		mTitlePlayer->Run();
		// フェードアウトと終了チェック
		if (mFader->Fade() == 0) {
			// 輝度を元に戻す
			mFader->SetBright(255, 255, 255);
			delete mTitlePlayer;
			for (int i = 0; i < (int)GrName::Length; i++) {
				DeleteGraph(mGrHandle[i]);
			}
			mSceneChanger->ChangeScene(new CGame(mSceneChanger));
			break;
		}
		break;
	}
}

/* ロゴ再生に関する定義 */
COpening::CLogoPlayer::CLogoPlayer(int GrHandle) : mLogoGrHandle(GrHandle) {
	mScene = Scene::init;
}
// 1:実行中, 0:終了
int COpening::CLogoPlayer::Run() {
	switch (mScene) {
	case Scene::init:
		mScene = Scene::fadein_init;
	case Scene::fadein_init:
		//フェードインの設定
		mFader = new CBright;
		SetDrawBright(0, 0, 0);
		mFader->SetFader(255, 255, 255, 60);
		mScene = Scene::fadein;
	case Scene::fadein:
		// ロゴのフェードインの実行と、終了チェック
		if (mFader->Fade() == 0) {
			mScene = Scene::display_init;
		}
		DrawGraph(0, 0, mLogoGrHandle, FALSE);
		break;
	case Scene::display_init:
		mCounter = 0;
		mScene = Scene::display;
	case Scene::display:
		if (mCounter++ == 120) {
			mScene = Scene::fadeout_init;
		}
		DrawGraph(0, 0, mLogoGrHandle, FALSE);
		break;
	case Scene::fadeout_init:
		mFader->SetFader(0, 0, 0, 60);
		mCounter = 0;
		mScene = Scene::fadeout;
	case Scene::fadeout:
		if (mFader->Fade() == 0) {
			delete mFader;
			mScene = Scene::end;
			return 0;
		}
		DrawGraph(0, 0, mLogoGrHandle, FALSE);
		break;
	case Scene::end:
		return 0;
	}
	return 1;
}

/* タイトル再生に関する定義 */
COpening::CTitlePlayer::CTitlePlayer(int GrHandle) : mTitleGrHandle(GrHandle) {
	mScene = Scene::init;
}
COpening::CTitlePlayer::~CTitlePlayer() {
	PauseMovieToGraph(mTitleGrHandle);
}
// 1:実行中, 0:終了
int COpening::CTitlePlayer::Run() {
	switch (mScene) {
	case Scene::init:
		SetDrawBright(255, 255, 255);
		PlayMovieToGraph(mTitleGrHandle);
		mScene = Scene::play;
	case Scene::play:
		DrawExtendGraph(0, 0, 640, 480, mTitleGrHandle, FALSE);
		if (GetMovieStateToGraph(mTitleGrHandle) == 0) {
			SeekMovieToGraph(mTitleGrHandle, 0);
			mScene = Scene::end;
			return 0;
		}
		break;
	case Scene::end:
		return 0;
	}
	return 1;
}
