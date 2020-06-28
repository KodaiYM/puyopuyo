#ifndef _INCLUDE_GUARD_CGRAPHICMGR_
#define _INCLUDE_GUARD_CGRAPHICMGR_

#include <unordered_map>

class CResourceMgr {
private:
	std::unordered_map<int, int> mGraphicHandle;
	std::unordered_map<int, int> mSoundHandle;
public:
	CResourceMgr() {};

	// グラフィック番号に、ファイル名のグラフィックをロードする
	void LoadGraphic(const std::unordered_map<int, const char*> graphiclist);
	// サウンド番号に、ファイル名のサウンドをロードする
	void LoadSound(const std::unordered_map<int, const char*> soundlist);

	// グラフィックハンドルの取得
	int getGraphicHandle(int graphicName) const;
	// サウンドハンドルの取得
	int getSoundHandle(int soundName) const;

	// 全リソースの解放
	~CResourceMgr();
};

#endif
