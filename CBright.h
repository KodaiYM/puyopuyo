#pragma once

#include <memory>

// 輝度設定のクラス
class CBright final {
private:
	CBright() = default;	// Singleton
	~CBright() = default;	// Singleton

	int r, g, b;						// 初期値R、G、B
	int mRed, mGreen, mBlue, mSpeed;	// 目標のR、G、Bと、何フレームでフェードするか
	double frame_per_red, frame_per_green, frame_per_blue; // 各輝度を1増やすのにかかるフレーム数
	int mCount;	//カウンター

public:
	CBright(const CBright&) = delete;				// Singleton
	CBright& operator=(const CBright&) = delete;	// Singleton
	CBright(CBright&&) = delete;					// Singleton
	CBright& operator=(CBright&&) = delete;			// Singleton
	static CBright& getInstance() {					// Singleton
		static CBright instance;
		return instance;
	}

	// 指定した輝度へフェード。同じ引数で speed 回呼ぶと、フェードが完了。戻り値は残りのフレーム数。0でフェード終了。
	int Fade(int RedBright, int GreenBright, int BlueBright, int speed);
	// 輝度を取得する
	void GetDrawBright(std::shared_ptr<int> Red, std::shared_ptr<int> Green, std::shared_ptr<int> Blue) const;
	// 指定した輝度にセットする
	void SetDrawBright(int RedBright, int GreenBright, int BlueBright) const;
};
