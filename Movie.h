#pragma once

#include "IGraphic.h"
#include <DxLib.h>
#include <Shlwapi.h>
#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#pragma comment(lib, "shlwapi.lib")
using namespace std::string_literals;

// 1つのムービーリソースのクラス
template <class Derived>
class Movie : public IGraphic {
#pragma region 外部公開
public:
	// update が呼ばれたフレームは、動画が進む
	// 動画の最終フレームで、true を返す
	[[nodiscard]] bool update() final;
	// 動画を描画する
	void draw() const final;

public:
	Movie();
#pragma endregion

#pragma region デストラクタ
public:
	virtual ~Movie() noexcept = 0;
#pragma endregion

#pragma region 非公開
private:
	// このリソースの利用者数
	inline static unsigned int s_count = 0;

	// この動画のパス
	static const std::string path;

	// この動画のハンドル
	inline static int handle;

private:
	static int LoadSound_(const char *filename) {
		/* ファイルの存在確認 */
		std::ifstream ifs(filename);
		if (!ifs) {
			throw std::ios_base::failure("cannot open the file: "s + filename);
		}
		ifs.close();

		/* ファイルハンドルの取得 */
		int handle = LoadGraph(filename);
		if (handle == -1) {
			throw std::ios_base::failure("failed to open the file: "s + filename);
		}
		return handle;
	}

private:
	int          m_x = 0, m_y = 0; // 描画位置
	mutable bool updated = false;  // update が呼ばれたかどうか
	bool         lasted  = true; // 直前が最終フレームだった時、true
#pragma endregion
};

template <class Derived>
Movie<Derived>::Movie() {
	// 初めての利用の時
	if (0 == s_count) {
		// 他にこのリソースの使用をしていた人がいない場合

		// 非同期読み込み
		SetUseASyncLoadFlag(TRUE);

		try {
			handle = LoadSound_(path.c_str());
			SeekMovieToGraphToFrame(handle, 0);
		} catch (std::ios_base::failure ios_f) {
			// よく分からないが読み込み失敗

			MessageBox(
			    NULL,
			    (std::string("Error in " __FUNCTION__ "\n") + ios_f.what()).c_str(),
			    TEXT("File Open Error"), MB_OK | MB_ICONERROR);
			std::exit(EXIT_FAILURE);
		}

		// メモリ不足等で読み込み失敗
		if (handle == -1) {
			MessageBox(NULL,
			           (std::string("Error in " __FUNCTION__ "\n") +
			            "unable to get handle of: " + path)
			               .c_str(),
			           TEXT("File Open Error"), MB_OK | MB_ICONERROR);
			std::exit(EXIT_FAILURE);
		}

		// 非同期読み込みの解除
		SetUseASyncLoadFlag(FALSE);
	}
	// 利用者数を1増やす
	++s_count;
}

template <class Derived>
Movie<Derived>::~Movie() noexcept {
	assert(s_count >= 1);

	// 利用者数を1減らす
	--s_count;

	// 利用者数が0になった
	if (0 == s_count) {
		PauseMovieToGraph(handle);
		DeleteGraph(handle);
	}
}

template <class Derived>
const std::string Movie<Derived>::path = []() {
	// ファイルが存在しないとき
	if (auto fs = std::ifstream(Derived::path); !fs.is_open()) {
		MessageBox(NULL,
		           (std::string("Error in " __FUNCTION__ "\n") +
		            "Cannot find file: " + Derived::path)
		               .c_str(),
		           TEXT("File Open Error"), MB_OK | MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}

	// ファイルが存在するとき

	return Derived::path;
}();

template <class Derived>
bool Movie<Derived>::update() {
	updated = true;

	// 停止状態のとき、ムービーを再生状態にする
	if (GetMovieStateToGraph(handle) == 0) {
		PlayMovieToGraph(handle);
	}

	// 直前が最終フレームだった時
	if (lasted) {
		// 最初に戻す
		PauseMovieToGraph(handle);
		SeekMovieToGraphToFrame(handle, 0);
		PlayMovieToGraph(handle);

		lasted = false;
	}

	// 最終フレームのとき
	if (GetMovieTotalFrameToGraph(handle) - 1 ==
	    TellMovieToGraphToFrame(handle)) {
		lasted = true;
	}

	return lasted;
}

template <class Derived>
void Movie<Derived>::draw() const {
	/* 読み込み中なら読み込み完了まで待つ */
	while (CheckHandleASyncLoad(handle) == TRUE) {
#ifdef _DEBUG
		std::cout << "loading movie handle: " << path << "(" << handle << ")"
		          << std::endl;
#endif
		ProcessMessage();
		Sleep(1);
	}

	// 動画の描画
	DrawGraph(m_x, m_y, handle, FALSE);

	// updateが呼ばれなかったフレームは、止める
	if (!updated) {
		PauseMovieToGraph(handle);
	}

	updated = false;
}
