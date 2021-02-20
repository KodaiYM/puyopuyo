#pragma once

#include <memory>

// 輝度設定のクラス
class CBright  final {
#pragma region 公開関数
public:
	// 指定した輝度へフェード。同じ引数で frame
	// 回呼ぶと、フェードが完了。戻り値は残りのフレーム数。0でフェード終了。
	int Fade(int red, int green, int blue, int frame);
	// 輝度を取得する
	void GetScreenBright(int &red, int &green, int &blue) const;
	// 指定した輝度にセットする
	void SetScreenBright(int red, int green, int blue) const;

public:
	static CBright &getInstance() noexcept { // Singleton
		static CBright instance;
		return instance;
	}
	CBright(const CBright &) = delete;            // Singleton
	CBright &operator=(const CBright &) = delete; // Singleton
	CBright(CBright &&)                 = delete; // Singleton
	CBright &operator=(CBright &&) = delete;      // Singleton
#pragma endregion

#pragma region 非公開関数
private:
	CBright() noexcept  = default; // Singleton
	~CBright() noexcept = default; // Singleton

private:
	int    m_initRed, m_initGreen, m_initBlue;       // 初期値R、G、B
	int    m_targetRed, m_targetGreen, m_targetBlue; // 目標のR、G、B
	int    m_frame; // 何フレームでフェードするか
	double m_frame_per_red, m_frame_per_green,
	    m_frame_per_blue; // 各輝度を1増やすのにかかるフレーム数
	int m_count;          //カウンター
#pragma endregion
};
