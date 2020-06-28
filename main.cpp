#if DEBUG|_DEBUG
#define _CRT_SECURE_NO_WARNINGS
#include <crtdbg.h>
#include <stdio.h>
#include <string>
#endif

#include <DxLib.h>
#include "CSceneMgr.h"
#include "ResMgr.h"
#include "Opening.h"
//#include "Game.h" /* デバッグ中 */
#include "key.h"
#include <memory>
#include <iostream>

namespace Main {
	class CMainMgr final :public CSceneMgr {
	private:
		std::shared_ptr<Opening::OpeningMgr> mOpeningScene;
		virtual void ChangeScene(const std::type_info& nextScene) override {
			if (nextScene == typeid(Opening::OpeningMgr)) {
				AssignScene(mOpeningScene);
			}
		}
	public:
		CMainMgr() :CSceneMgr(std::weak_ptr<ISceneChanger>()) {}
		~CMainMgr() {}

		void init() {
			AssignScene(mOpeningScene);
			getScene()->init();
		}
		void deinit() {
			getScene()->deinit();
		}
		void update() {
			getScene()->update();
		}
	};
}

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
#if DEBUG|_DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
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

	//DXライブラリ初期化
	if (DxLib_Init() == -1) {
		return -1;
	}

	//裏画面へ書き込み
	if (SetDrawScreen(DX_SCREEN_BACK) == -1) {
		return -1;
	}

	auto MainMgr = std::make_shared<Main::CMainMgr>();
	MainMgr->init();
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		UpdateKey();		// キー情報の更新
		MainMgr->update();	// シーンの更新
		MainMgr->draw();		// シーンの実行
	}
	MainMgr->deinit();

	MainMgr.reset();

	//DXライブラリ終了
	DxLib_End();

#if DEBUG|_DEBUG
	FreeConsole();
#endif
	return 0;
}
