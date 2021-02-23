#pragma once

#include <DxLib.h>
#include <Shlwapi.h>
#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "IGraphic.h"

#pragma comment(lib, "shlwapi.lib")
using namespace std::string_literals;

// グラフィックリソースの setXY系の基準位置
enum class ORIGIN { UPPER_LEFT, CENTER };
// 1つのグラフィックリソースのクラス
template <class Derived>
class Image : public IGraphic {
#pragma region 外部公開
public:
	// updateの結果が画像の最後の要素を指す時、true を返す
	bool update() noexcept override;
	void draw() const final;
	void setX(int x, ORIGIN origin = ORIGIN::UPPER_LEFT);
	void setY(int y, ORIGIN origin = ORIGIN::UPPER_LEFT);
	void setXY(int x, int y, ORIGIN origin = ORIGIN::UPPER_LEFT);
	// pair(x, y)
	void setXY(const std::pair<int, int> &point,
	           ORIGIN                     origin = ORIGIN::UPPER_LEFT);

public:
	// 初期描画位置
	Image(int x, int y, ORIGIN origin = ORIGIN::UPPER_LEFT);
#pragma endregion

#pragma region デストラクタ
public:
	virtual ~Image() noexcept = 0;
#pragma endregion

#pragma region 非公開
private:
	// このリソースの利用者数
	inline static unsigned int s_count = 0;

	// このリソースのパスリスト（インデックス順）
	static const std::vector<std::string> s_paths;

	// このリソースのハンドル一覧（インデックス順）
	inline static std::vector<int> s_handles;

private:
	// 現在ハンドル位置のリソースの読み込み完了を待つ
	void wait_until_current_handle_loaded() const;

	// このリソースの現在ハンドル位置
	std::vector<int>::iterator m_current_handle;

	int m_x, m_y; // 描画位置
#pragma endregion
};

template <class Derived>
Image<Derived>::Image(int x, int y, ORIGIN origin) {
	// 初めての利用の時
	if (0 == s_count) {
		// 他にこのリソースの使用をしていた人がいない場合

		assert(s_handles.empty());

		// 領域の予約
		s_handles.reserve(s_paths.size());

		// 非同期読み込み
		SetUseASyncLoadFlag(TRUE);

		for (const auto &path : s_paths) {
			int handle;

			try {
				handle = LoadGraph(path.c_str());
			} catch (const std::ios_base::failure &ios_f) {
				// よく分からないが読み込み失敗

				MessageBox(NULL,
				           ("Error in " __FUNCTION__ "\n"s + ios_f.what()).c_str(),
				           TEXT("File Open Error"), MB_OK | MB_ICONERROR);
				std::exit(EXIT_FAILURE);
			}

			// メモリ不足等で読み込み失敗
			if (handle == -1) {
				MessageBox(NULL,
				           ("Error in " __FUNCTION__ "\n"s +
				            "unable to get handle of: " + path)
				               .c_str(),
				           TEXT("File Open Error"), MB_OK | MB_ICONERROR);
				std::exit(EXIT_FAILURE);
			}

			// 読み込んだリソースハンドラの追加
			s_handles.push_back(handle);
		}

		// 非同期読み込みの解除
		SetUseASyncLoadFlag(FALSE);
	}
	// 利用者数を1増やす
	++s_count;

	m_current_handle = s_handles.end() - 1;
	setXY(x, y, origin);
}

template <class Derived>
Image<Derived>::~Image() noexcept {
	assert(s_count >= 1);
	assert(s_handles.size() == s_paths.size());

	// 利用者数を1減らす
	--s_count;

	// 利用者数が0になった
	if (0 == s_count) {
		// リソースの解放
		for (const auto &handle : s_handles) {
			DeleteGraph(handle);
		}

		// ハンドル一覧の解放
		s_handles.clear();
		s_handles.shrink_to_fit();
	}
}

template <class Derived>
const std::vector<std::string> Image<Derived>::s_paths = []() {
	std::vector<std::string> paths;

	if (PathIsDirectory(Derived::s_path)) {
		// グラフィックのパスがディレクトリの場合、0.* から順に見つかるだけ探す

		if (WIN32_FIND_DATA FindFileData;
		    INVALID_HANDLE_VALUE !=
		    FindFirstFile((Derived::s_path + "/0.*"s).c_str(), &FindFileData)) {
			// 0.* ファイルが見つかった場合

			// ドット付きの拡張子を取得
			const auto extension = FindFileData.cFileName + 1;

			int i = 0;
			while (1) {
				// i.* ファイルを探す（i は 0 以上の10進数値）
				const auto filename =
				    Derived::s_path + "/"s + std::to_string(i) + extension;

				// ファイルが存在しないとき
				if (!PathFileExists(filename.c_str())) {
					break;
				}

				// パス一覧に追加
				paths.push_back(filename);
				++i;
			}
		} else {
			// 0.*　ファイルが見つからない場合
			MessageBox(NULL,
			           ("Error in " __FUNCTION__ "\n"s +
			            "There is no 0.* file in the directory: " + Derived::s_path)
			               .c_str(),
			           TEXT("File Open Error"), MB_OK | MB_ICONERROR);
			std::exit(EXIT_FAILURE);
		}
	} else {
		// グラフィックのパスがファイルの場合

		// ファイルが存在しないとき
		if (!PathFileExists(Derived::s_path)) {
			MessageBox(NULL,
			           ("Error in " __FUNCTION__ "\n"s +
			            "Cannot find file: " + Derived::s_path)
			               .c_str(),
			           TEXT("File Open Error"), MB_OK | MB_ICONERROR);
			std::exit(EXIT_FAILURE);
		}

		// ファイルが存在するとき
		paths.push_back(Derived::s_path);
	}

	assert(!paths.empty());
	return paths;
}();

template <class Derived>
bool Image<Derived>::update() noexcept {
	// ハンドル位置を進める
	++m_current_handle;

	// ハンドル位置が最後の位置を超えたら
	if (s_handles.end() == m_current_handle) {
		// 最初に戻す
		m_current_handle = s_handles.begin();
	}

	// ハンドル位置が最後のとき
	if (s_handles.end() - 1 == m_current_handle) {
		return true;
	}

	return false;
}

template <class Derived>
void Image<Derived>::draw() const {
	wait_until_current_handle_loaded();
	DrawGraph(m_x, m_y, *m_current_handle, TRUE);
}

template <class Derived>
void Image<Derived>::wait_until_current_handle_loaded() const {
	while (CheckHandleASyncLoad(*m_current_handle) == TRUE) {
#if DEBUG || _DEBUG
		std::cout << "loading graphic handle: "
		          << s_paths.at(std::distance(s_handles.begin(), m_current_handle))
		          << "(" << *m_current_handle << ")" << std::endl;
#endif
		ProcessMessage();
		Sleep(1);
	}
}
template <class Derived>
void Image<Derived>::setX(int x, ORIGIN origin) {
	wait_until_current_handle_loaded();

	int width, height;
	if (-1 == GetGraphSize(*m_current_handle, &width, &height)) {
		throw "failed to get graph size!";
	}

	m_x = ORIGIN::UPPER_LEFT == origin ? x : x - (width / 2);
}

template <class Derived>
void Image<Derived>::setY(int y, ORIGIN origin) {
	wait_until_current_handle_loaded();

	int width, height;
	if (-1 == GetGraphSize(*m_current_handle, &width, &height)) {
		throw "failed to get graph size!";
	}

	m_y = ORIGIN::UPPER_LEFT == origin ? y : y - (height / 2);
}

template <class Derived>
void Image<Derived>::setXY(int x, int y, ORIGIN origin) {
	setX(x, origin);
	setY(y, origin);
}

template <class Derived>
void Image<Derived>::setXY(const std::pair<int, int> &point, ORIGIN origin) {
	const auto &[x, y] = point;
	setXY(x, y, origin);
}
