#include "CResourceMgr.h"
#include <DxLib.h>

void CResourceMgr::LoadGraphic(const std::unordered_map<int, const char*> graphiclist) {
	for (std::unordered_map<int, const char*>::const_iterator itr = graphiclist.begin(); itr != graphiclist.end(); itr++) {
		mGraphicHandle[itr->first] = LoadGraph(itr->second);
	}
}
void CResourceMgr::LoadSound(const std::unordered_map<int, const char*> soundlist) {
	for (std::unordered_map<int, const char*>::const_iterator itr = soundlist.begin(); itr != soundlist.end(); itr++) {
		mSoundHandle[itr->first] = LoadSoundMem(itr->second);
	}
}

int CResourceMgr::getGraphicHandle(int graphicName) const {
	return mGraphicHandle.at(graphicName);
}
int CResourceMgr::getSoundHandle(int graphicName) const {
	return mSoundHandle.at(graphicName);
}

CResourceMgr::~CResourceMgr() {
	for (std::unordered_map<int, int>::const_iterator itr = mGraphicHandle.begin(); itr != mGraphicHandle.end(); itr++) {
		DeleteGraph(itr->second);
	}
	for (std::unordered_map<int, int>::const_iterator itr = mSoundHandle.begin(); itr != mSoundHandle.end(); itr++) {
		DeleteSoundMem(itr->second);
	}
}
