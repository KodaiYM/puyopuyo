#pragma once

#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <vector>
#include <memory>
#include "names.h"

class ResMgr final {
private:
	ResMgr();	// Singleton
	~ResMgr();	// Singleton

	std::unordered_map<GrName, std::vector<int>> mGrHandle;
	std::unordered_map<SndName, std::vector<int>> mSndHandle;

	std::list<const std::unordered_set<GrName>*> mGrProf;

public:
	ResMgr(const ResMgr&) = delete;				// Singleton
	ResMgr& operator=(const ResMgr&) = delete;	// Singleton
	ResMgr(ResMgr&&) = delete;					// Singleton
	ResMgr& operator=(ResMgr&&) = delete;		// Singleton
	static ResMgr& getInstance() {				// Singleton
		static ResMgr instance;
		return instance;
	}

	int getHandle(GrName name, unsigned int index = 0) const;
	int getHandle(SndName name, unsigned int index = 0) const;

	// アンロードとロードを行う
	void load();
	// スタックの末尾に指定プロファイルを追加する
	void push_profile(const std::unordered_set<GrName>& profile);
	// 指定プロファイル以上のプロファイルを取り除く
	void pop_profile(const std::unordered_set<GrName>& profile);
};
