#include "CBright.h"
#include <iostream>
#include <DxLib.h>

int CBright::Fade(int RedBright, int GreenBright, int BlueBright, int speed) {
	// 前回この関数が呼び出された時の設定と違ったら、初期設定する
	if (RedBright != mRed || GreenBright != mGreen || BlueBright != mBlue || speed != mSpeed) {
		auto red = std::make_shared<int>();
		auto green = std::make_shared<int>();
		auto blue = std::make_shared<int>();

		GetDrawBright(red, green, blue);
		r = *red; g = *green; b = *blue;

		mRed = RedBright;
		mGreen = GreenBright;
		mBlue = BlueBright;
		mSpeed = speed;
		frame_per_red = mSpeed * 100 / (mRed - r);
		frame_per_green = mSpeed * 100 / (mGreen - g);
		frame_per_blue = mSpeed * 100 / (mBlue - b);
		mCount = 0;
	}

	if (mCount == mSpeed) {
		return 0;
	} else {
		// 最終フレーム
		if (mCount == mSpeed - 1) {
			// 計算で少しずれるので、目標値にする
			SetDrawBright(mRed, mGreen, mBlue);
		} else {
			// フェード途中
			SetDrawBright((int)(r + mCount * 100 / frame_per_red), (int)(g + mCount * 100 / frame_per_green), (int)(b + mCount * 100 / frame_per_blue));
		}
		mCount++;
	}

	return mSpeed - mCount;
}

void CBright::GetDrawBright(std::shared_ptr<int> Red, std::shared_ptr<int> Green, std::shared_ptr<int> Blue) const {
	int red, green, blue;
	if (DxLib::GetDrawBright(&red, &green, &blue) == -1) {
		throw "輝度の取得に失敗しました。";
	}

	*Red = red;
	*Green = green;
	*Blue = blue;
}
void CBright::SetDrawBright(int RedBright, int GreenBright, int BlueBright) const {
	if (DxLib::SetDrawBright(RedBright, GreenBright, BlueBright) == -1) {
		throw "輝度設定に失敗しました。";
	}
}
