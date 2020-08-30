#pragma once

#include "Resource.h"
#include <DxLib.h>
#include <Shlwapi.h>
#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#pragma comment(lib, "shlwapi.lib")
using namespace std::string_literals;

// 1つのグラフィックリソースのクラス
template <class Derived>
class Graphic : public Resource {
protected:
	Graphic();
	~Graphic();

private:
	// このリソースの利用者数
	inline static unsigned int count = 0;

	// このリソースのパスリスト（インデックス順）
	static const std::vector<std::string> paths;

	// このリソースのハンドル一覧（インデックス順）
	inline static std::vector<int> handles;

	// このリソースの現在ハンドル位置
	std::vector<int>::iterator current_handle;

private:
	int x = 0, y = 0; // 描画位置

public:
	// updateの結果が画像の最後の要素を指す時、true を返す
	virtual bool update() override final;
	virtual void draw() const override final;
};

template <class Derived>
Graphic<Derived>::Graphic() {
	// 初めての利用の時
	if (0 == count) {
		// 他にこのリソースの使用をしていた人がいない場合

		assert(handles.empty());

		// 領域の予約
		handles.reserve(paths.size());

		// 非同期読み込み
		SetUseASyncLoadFlag(TRUE);

		for (const auto &path : paths) {
			int handle;

			try {
				handle = LoadGraph(path.c_str());
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

			// 読み込んだリソースハンドラの追加
			handles.push_back(handle);
		}

		// 非同期読み込みの解除
		SetUseASyncLoadFlag(FALSE);
	}
	// 利用者数を1増やす
	++count;

	current_handle = handles.end() - 1;
}

template <class Derived>
Graphic<Derived>::~Graphic() {
	assert(count >= 1);
	assert(handles.size() == paths.size());

	// 利用者数を1減らす
	--count;

	// 利用者数が0になった
	if (0 == count) {
		// リソースの解放
		for (const auto &handle : handles) {
			DeleteGraph(handle);
		}

		// ハンドル一覧の解放
		handles.clear();
		handles.shrink_to_fit();
	}
}

template <class Derived>
const std::vector<std::string> Graphic<Derived>::paths = []() {
	std::vector<std::string> paths;

	if (PathIsDirectory(Derived::path)) {
		// グラフィックのパスがディレクトリの場合、0.* から順に見つかるだけ探す

		if (WIN32_FIND_DATA FindFileData;
		    INVALID_HANDLE_VALUE !=
		    FindFirstFile((Derived::path + "/0.*"s).c_str(), &FindFileData)) {
			// 0.* ファイルが見つかった場合

			// ドット付きの拡張子を取得
			const auto extension = FindFileData.cFileName + 1;

			int i = 0;
			while (1) {
				// i.* ファイルを探す（i は 0 以上の10進数値）
				const auto filename =
				    Derived::path + "/"s + std::to_string(i) + extension;

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
			           (std::string("Error in " __FUNCTION__ "\n") +
			            "There is no 0.* file in the directory: " + Derived::path)
			               .c_str(),
			           TEXT("File Open Error"), MB_OK | MB_ICONERROR);
			std::exit(EXIT_FAILURE);
		}
	} else {
		// グラフィックのパスがファイルの場合

		// ファイルが存在しないとき
		if (!PathFileExists(Derived::path)) {
			MessageBox(NULL,
			           (std::string("Error in " __FUNCTION__ "\n") +
			            "Cannot find file: " + Derived::path)
			               .c_str(),
			           TEXT("File Open Error"), MB_OK | MB_ICONERROR);
			std::exit(EXIT_FAILURE);
		}

		// ファイルが存在するとき
		paths.push_back(Derived::path);
	}

	assert(!paths.empty());
	return paths;
}();

template <class Derived>
bool Graphic<Derived>::update() {
	// ハンドル位置を進める
	++current_handle;

	// ハンドル位置が最後の位置を超えたら
	if (handles.end() == current_handle) {
		// 最初に戻す
		current_handle = handles.begin();
	}

	// ハンドル位置が最後のとき
	if (handles.end() - 1 == current_handle) {
		return true;
	}

	return false;
}

template <class Derived>
void Graphic<Derived>::draw() const {
	/* 読み込み中なら読み込み完了まで待つ */
	while (CheckHandleASyncLoad(*current_handle) == TRUE) {
#ifdef _DEBUG
		std::cout << "loading graphic handle: "
		          << paths.at(std::distance(handles.begin(), current_handle)) << "("
		          << *current_handle << ")" << std::endl;
#endif
		ProcessMessage();
		Sleep(1);
	}

	DrawGraph(x, y, *current_handle, TRUE);
}
