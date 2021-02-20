#if DEBUG | _DEBUG
#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>
#include <cstdio>
#endif

#include "CSceneMgr.h"
#include "CTransFadein.h"
#include "Opening.MyLogo.h"
#include <DxLib.h>
//#include "Game.h" /* デバッグ中 */
#include "key.h"
#include <memory>

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
#if DEBUG | _DEBUG
	AllocConsole();
	(void)std::freopen("CONOUT$", "w", stdout);
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	//ウィンドウ or 全画面
	if (ChangeWindowMode(TRUE) == -1) {
		return -1;
	}

	//ウィンドウがアクティブでないときも処理をするか
	if (SetAlwaysRunFlag(TRUE)) {
		return -1;
	}

	// DXライブラリ初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	//裏画面へ書き込み
	if (SetDrawScreen(DX_SCREEN_BACK) == -1) {
		return -1;
	}

	auto sceneMgr = std::make_shared<CSceneMgr>();
	sceneMgr->ChangeScene(nullptr, std::make_shared<Opening::MyLogo>(sceneMgr));
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		UpdateKey();        // キー情報の更新
		sceneMgr->update(); // シーンの更新
		sceneMgr->draw();   // シーンの実行
	}
	sceneMgr.reset();

	// DXライブラリ終了
	DxLib_End();

#if DEBUG | _DEBUG
	FreeConsole();
#endif
	return 0;
}
