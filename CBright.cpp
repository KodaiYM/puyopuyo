#include "CBright.h"
#include <iostream>
#include <DxLib.h>

void CBright::SetFader(int RedBright, int GreenBright, int BlueBright, int speed) {
	GetBright(&r, &g, &b);
	mRed = RedBright;
	mGreen = GreenBright;
	mBlue = BlueBright;
	mSpeed = speed;
	frame_per_red = mSpeed * 100 / (mRed - r);
	frame_per_green = mSpeed * 100 / (mGreen - g);
	frame_per_blue = mSpeed * 100 / (mBlue - b);
	mCount = 0;
}
int CBright::Fade() {
	if (mCount == mSpeed) {
		return 0;
	} else {
		// 最終フレーム
		if (mCount == mSpeed - 1) {
			// 計算で少しずれるので、目標値にする
			SetBright(mRed, mGreen, mBlue);
		} else {
			// フェード途中
			SetBright((int)(r + mCount * 100 / frame_per_red), (int)(g + mCount * 100 / frame_per_green), (int)(b + mCount * 100 / frame_per_blue));
		}
		mCount++;
	}
	return mSpeed - mCount;
}

void CBright::GetBright(int* Red, int* Green, int* Blue) {
	if (GetDrawBright(Red, Green, Blue) == -1) {
		std::cerr << "CBright::GetBright(" << Red << ", " << Green << ", " << Blue << ") でエラーが発生しました。" << std::endl;
	}
}
void CBright::SetBright(int RedBright, int GreenBright, int BlueBright) {
	if (SetDrawBright(RedBright, GreenBright, BlueBright) == -1) {
		std::cerr << "CBright::SetBright(" << RedBright << ", " << GreenBright << ", " << BlueBright << ") でエラーが発生しました。" << std::endl;
	}
}
