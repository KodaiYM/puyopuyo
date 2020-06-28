#include "ResMgr.h"
#include <DxLib.h>
#include <string>
#include <assert.h>
#include <fstream>
#include <Shlwapi.h>
#include <exception>
#include <iostream>
#pragma comment(lib, "shlwapi.lib")

static int _LoadGraph(const TCHAR* filename) {
	std::ifstream ifs(filename);
	if (!ifs) {
		throw std::ios_base::failure("cannot open the file: " + std::string(filename));
	}
	ifs.close();

	int handle = LoadGraph(filename);
	if (handle == -1) {
		throw std::ios_base::failure("failed to open the file: " + std::string(filename));
	}
	return handle;
}
static int _LoadSoundMem(const TCHAR* filename) {
	std::ifstream ifs(filename);
	if (!ifs) {
		throw std::ios_base::failure("cannot open the file: " + std::string(filename));
	}
	ifs.close();

	int handle = LoadSoundMem(filename);
	if (handle == -1) {
		throw std::ios_base::failure("failed to open the file: " + std::string(filename));
	}
	return handle;
}

#define LoadGraph _LoadGraph
#define LoadSoundMem _LoadSoundMem

static const std::unordered_map<GrName, const TCHAR* const> GraphicPath = {
	{GrName::Loading, "../puyopuyo/img/loading.jpg"},
	{GrName::Logo, "../puyopuyo/img/Opening/logo.png"},
	{GrName::Title, "../puyopuyo/img/Opening/title.ogv"},
	{GrName::SpriteStudio, "../puyopuyo/img/Opening/SpriteStudio"}
};
static const std::unordered_map<SndName, const TCHAR* const> SoundPath = {
	{SndName::Sample, "../puyopuyo/sound_effect/chain1.wav"}
};

ResMgr::ResMgr() {
}
ResMgr::~ResMgr() {
	for (auto itr = mGrHandle.begin(); itr != mGrHandle.end(); itr++) {
		std::vector<int>* handleList = &itr->second;
		for (auto itr2 = handleList->begin(); itr2 != handleList->end(); itr2++) {
			DeleteGraph(*itr2);
		}
	}
	for (auto itr = mSndHandle.begin(); itr != mSndHandle.end(); itr++) {
		std::vector<int>* handleList = &itr->second;
		for (auto itr2 = handleList->begin(); itr2 != handleList->end(); itr2++) {
			DeleteSoundMem(*itr2);
		}
	}
}

void ResMgr::push_profile(const std::unordered_set<GrName>& profile) {
	mGrProf.push_back(&profile);
}
void ResMgr::pop_profile(const std::unordered_set<GrName>& profile) {
	for (auto itr = mGrProf.rbegin(); itr != mGrProf.rend(); itr++) {
		if (*itr == &profile) {
			mGrProf.erase(itr.base());
			break;
		}
	}
}
int ResMgr::getHandle(GrName name, unsigned int index) const {
	if (mGrHandle.count(name) == 0) {
		MessageBox(NULL, (std::string("Error in ResMgr::getHandle\n") + "GrName::" + std::to_string((int)name) + " is not ready to load").c_str(), TEXT("getHandle Error"), MB_OK | MB_ICONERROR);
		std::abort();
	}
	if (mGrHandle.at(name).size() <= index) {
		MessageBox(NULL, (std::string("Error in ResMgr::getHandle\n") + 
			"out of range\n" + 
			"size of GrName::" + std::to_string((int)name) + " " + std::to_string(mGrHandle.at(name).size()) + " <= " + std::to_string(index)).c_str()
			, TEXT("getHandle Error"), MB_OK | MB_ICONERROR);
		std::abort();
	}

	int handle = mGrHandle.at(name).at(index);
	// 読み込み中なら読み込み継続
	while (CheckHandleASyncLoad(handle) == TRUE) {
		std::cout << "loading handle: " << handle << std::endl;
		ProcessMessage();
		Sleep(1);
	}
	return handle;
}
int ResMgr::getHandle(SndName name, unsigned int index) const {
	if (mSndHandle.count(name) == 0) {
		MessageBox(NULL, (std::string("Error in ResMgr::getHandle\n") + "SndName::" + std::to_string((int)name) + " is not ready to load").c_str(), TEXT("getHandle Error"), MB_OK | MB_ICONERROR);
		std::abort();
	}
	if (mSndHandle.at(name).size() <= index) {
		MessageBox(NULL, (std::string("Error in ResMgr::getHandle\n") +
			"out of range\n" +
			"size of SndName::" + std::to_string((int)name) + " " + std::to_string(mSndHandle.at(name).size()) + " <= " + std::to_string(index)).c_str()
			, TEXT("getHandle Error"), MB_OK | MB_ICONERROR);
		std::abort();
	}

	int handle = mSndHandle.at(name).at(index);
	// 読み込み中なら読み込み継続
	while (CheckHandleASyncLoad(handle) == TRUE) {
		ProcessMessage();
		Sleep(1);
	}
	return handle;
}
void ResMgr::load() {
	// アンロード処理
	{
		auto itr = mGrHandle.begin();
		while (itr != mGrHandle.end()) {
			bool unload = true;

			// アンロード対象かチェック
			for (auto& profile : mGrProf) {
				for (auto& grName : *profile) {
					if (itr->first == grName) {
						unload = false;
						break;
					}
				}
				if (!unload) {
					break;
				}
			}

			// アンロード対象の場合
			if (unload) {
				std::vector<int>* handleList = &itr->second;
				for (auto itr2 = handleList->begin(); itr2 != handleList->end(); itr2++) {
					DeleteGraph(*itr2);
				}

				mGrHandle.erase(itr++);
			} else ++itr;
		}
	}

	/*
	for (auto itr = mSndHandle.begin(); itr != mSndHandle.end(); itr++) {
				auto find_itr = std::find(mNextSndNames.begin(), mNextSndNames.end(), itr->first);
				// ロード済みのサウンドが、次必要ない場合
				if (find_itr == mNextSndNames.end()) {
					std::vector<int>* handleList = &itr->second;
					for (auto itr2 = handleList->begin(); itr2 != handleList->end(); itr2++) {
						DeleteSoundMem(*itr2);
					}

					mSndHandle.erase(itr->first);
				}
			}

			mDestroyed = true;
	*/
	// ロード処理

	SetUseASyncLoadFlag(TRUE);
	for (auto& profile : mGrProf) {
		for (auto& grName : *profile) {
			// ロードが必要な場合
			if (mGrHandle.count(grName) == 0) {
				WIN32_FIND_DATA FindFileData;
				HANDLE hFind;

				// パスがディレクトリの場合、0.* から順に読み込む
				if (PathIsDirectory(GraphicPath.at(grName))) {
					hFind = FindFirstFile(((std::string)GraphicPath.at(grName) + "/0.*").c_str(), &FindFileData);
					if (hFind != INVALID_HANDLE_VALUE) {
						// ドット付きの拡張子を取得
						std::string extension = FindFileData.cFileName;
						extension.erase(extension.begin());

						std::ifstream ifs;
						std::string filename;
						int i = 0;
						while (1) {
							filename = (std::string)GraphicPath.at(grName) + "/" + std::to_string(i) + extension;

							// ファイルが存在しない（と考えられる）
							ifs.open(filename);
							if (!ifs) {
								break;
							}
							ifs.close();

							int handle;
							try {
								handle = LoadGraph(filename.c_str());
							} catch (std::ios_base::failure ios_f) {
								MessageBox(NULL, (std::string("Error in ResMgr::load()\n") + ios_f.what()).c_str(), TEXT("File Open Error"), MB_OK | MB_ICONERROR);
								std::abort();
							}
							if (handle == -1) {
								MessageBox(NULL, (std::string("Error in ResMgr::load()\n") + "unable to get handle of: " + filename).c_str(), TEXT("File Open Error"), MB_OK | MB_ICONERROR);
								std::abort();
							} else {
								mGrHandle[grName].push_back(handle);
							}

							i++;
						}
					} else {
						MessageBox(NULL, (std::string("Error in ResMgr::load()\n") + "no 0.* file in the directory: " + (std::string)GraphicPath.at(grName)).c_str(), TEXT("File Open Error"), MB_OK | MB_ICONERROR);
						std::abort();
					}
				} else {
					int handle;
					try {
						handle = LoadGraph(GraphicPath.at(grName));
					} catch (std::ios_base::failure ios_f) {
						MessageBox(NULL, (std::string("Error in ResMgr::load()\n") + ios_f.what()).c_str(), TEXT("File Open Error"), MB_OK | MB_ICONERROR);
						std::abort();
					}
					if (handle == -1) {
						MessageBox(NULL, (std::string("Error in ResMgr::load()\n") + "unable to get handle of: " + GraphicPath.at(grName)).c_str(), TEXT("File Open Error"), MB_OK | MB_ICONERROR);
						std::abort();
					} else {
						mGrHandle[grName].push_back(handle);
					}
				}
			}
		}
	}
	SetUseASyncLoadFlag(FALSE);
}
