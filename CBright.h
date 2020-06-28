#ifndef _INCLUDE_GUARD_CFADER_
#define _INCLUDE_GUARD_CFADER_

class CBright {
private:
	int r, g, b;						// 初期値R、G、B
	int mRed, mGreen, mBlue, mSpeed;	// 目標のR、G、Bと、何フレームでフェードするか
	double frame_per_red, frame_per_green, frame_per_blue; // 各輝度を1増やすのにかかるフレーム数
	int mCount;	//カウンター
public:
	// 指定した輝度へフェードするための初期設定関数。speed はフレーム数を指定する。実際のフェードは、Fade()
	void SetFader(int RedBright, int GreenBright, int BlueBright, int speed);
	// フェードさせる。残りのフレーム数を返す。0でフェード終了。
	int Fade();

	// 輝度を取得する
	void GetBright(int* Red, int* Green, int* Blue);
	// 指定した輝度にセットする
	void SetBright(int RedBright, int GreenBright, int BlueBright);
};

#endif
