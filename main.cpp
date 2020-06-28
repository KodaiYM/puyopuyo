//デバッグ用
#define DEBUG_MODE
#define _CRT_SECURE_NO_WARNINGS

#include <DxLib.h>
#include "CSceneMgr.h"
#include "Opening.h"
#include "key.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
#ifdef DEBUG_MODE
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

	//ウィンドウ or 全画面
	if (ChangeWindowMode(TRUE) == -1) {
		return -1;
	}

	//ウィンドウがアクティブでないときも処理をするか
	if (SetAlwaysRunFlag(TRUE)) {
		return -1;
	}

	//DXライブラリ初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	//裏画面へ書き込み
	if (SetDrawScreen(DX_SCREEN_BACK) == -1) {
		return -1;
	}

	CSceneMgr* SceneMgr = new CSceneMgr;
	SceneMgr->ChangeScene(new COpening(SceneMgr));
	//メインループ。画面更新、他アプリケーションとの連携処理、画面消去
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		UpdateKey();		//キー情報の更新
		SceneMgr->Run();	//シーンの実行
	}

	//DXライブラリ終了
	DxLib_End();

#ifdef DEBUG_MODE
	FreeConsole();
#endif
	return 0;
}
