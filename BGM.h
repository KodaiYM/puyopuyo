#pragma once

#include <DxLib.h>
#include <Shlwapi.h>
#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

#pragma comment(lib, "shlwapi.lib")
using namespace std::string_literals;

// 1つのサウンドリソースのクラス
template <class Derived>
class BGM {
#pragma region 外部公開
public:
	// サウンドを再生する
	bool play();
	// サウンドの停止
	void stop() const;

public:
	BGM();
#pragma endregion

#pragma region デストラクタ
public:
	virtual ~BGM() noexcept = 0;
#pragma endregion

#pragma region 非公開
private:
	// このリソースの利用者数
	inline static unsigned int s_count = 0;

	// このサウンドのパス
	static const std::string s_path;

	// このサウンドのハンドル
	inline static int s_handle;

private:
	bool m_lasted = true; // 直前が最後の再生位置だった時、true

private:
	static int LoadSound_(const char *filename) {
		/* ファイルの存在確認 */
		std::ifstream ifs(filename);
		if (!ifs) {
			throw std::ios_base::failure("cannot open the file: "s + filename);
		}
		ifs.close();

		/* ファイルハンドルの取得 */
		const int handle = LoadSoundMem(filename, 1); // 同時再生可能数 1
		if (handle == -1) {
			throw std::ios_base::failure("failed to open the file: "s + filename);
		}
		return handle;
	}
#pragma endregion
};

template <class Derived>
BGM<Derived>::BGM() {
	// 初めての利用の時
	if (0 == s_count) {
		// 他にこのリソースの使用をしていた人がいない場合

		// 非同期読み込み
		SetUseASyncLoadFlag(TRUE);

		try {
			SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
			s_handle = LoadSound_(s_path.c_str());
			SetSoundCurrentPosition(0, s_handle);
		} catch (const std::ios_base::failure &ios_f) {
			// よく分からないが読み込み失敗

			MessageBox(
			    NULL,
			    (std::string("Error in " __FUNCTION__ "\n") + ios_f.what()).c_str(),
			    TEXT("File Open Error"), MB_OK | MB_ICONERROR);
			std::exit(EXIT_FAILURE);
		}

		// メモリ不足等で読み込み失敗
		if (s_handle == -1) {
			MessageBox(NULL,
			           (std::string("Error in " __FUNCTION__ "\n") +
			            "unable to get handle of: " + s_path)
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
BGM<Derived>::~BGM() noexcept {
	assert(s_count >= 1);

	// 利用者数を1減らす
	--s_count;

	// 利用者数が0になった
	if (0 == s_count) {
		StopSoundMem(s_handle);
		DeleteSoundMem(s_handle);
	}
}

template <class Derived>
const std::string BGM<Derived>::s_path = []() {
	// ファイルが存在しないとき
	if (auto fs = std::ifstream(Derived::s_path); !fs.is_open()) {
		MessageBox(NULL,
		           (std::string("Error in " __FUNCTION__ "\n") +
		            "Cannot find file: " + Derived::s_path)
		               .c_str(),
		           TEXT("File Open Error"), MB_OK | MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}

	// ファイルが存在するとき

	// wav, ogg 以外の拡張子の場合は未対応
	if (const auto path_sv = std::string_view(Derived::s_path);
	    !path_sv.ends_with(".wav") && !path_sv.ends_with(".ogg")) {
		MessageBox(NULL,
		           (std::string("Error in " __FUNCTION__ "\n") +
		            "The extension must be ogg or wav: " + Derived::s_path)
		               .c_str(),
		           TEXT("File Open Error"), MB_OK | MB_ICONERROR);
		std::exit(EXIT_FAILURE);
	}

	return Derived::s_path;
}();

template <class Derived>
bool BGM<Derived>::play() {
	/* 読み込み中なら読み込み完了まで待つ */
	while (CheckHandleASyncLoad(s_handle) == TRUE) {
#ifdef _DEBUG
		std::cout << "loading BGM handle: " << s_path << "(" << s_handle << ")"
		          << std::endl;
#endif
		ProcessMessage();
		Sleep(1);
	}

	// 停止状態のとき、サウンドを再生状態にする
	if (CheckSoundMem(s_handle) == 0) {
		PlaySoundMem(s_handle, DX_PLAYTYPE_BACK, FALSE);
	}

	// 直前が最終位置だった時
	if (m_lasted) {
		// 最初に戻す
		StopSoundMem(s_handle);
		PlaySoundMem(s_handle, DX_PLAYTYPE_BACK, TRUE);

		m_lasted = false;
	}

	// 最終位置のとき
	if (GetSoundTotalTime(s_handle) - 1 <= GetSoundCurrentTime(s_handle)) {
		m_lasted = true;
	}

	return m_lasted;
}

template <class Derived>
void BGM<Derived>::stop() const {
	StopSoundMem(s_handle);
}
