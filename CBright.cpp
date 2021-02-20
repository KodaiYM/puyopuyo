#include "CBright.h"
#include <DxLib.h>
#include <iostream>

int CBright::Fade(int red, int green, int blue, int frame) {
	// 前回この関数が呼び出された時の設定と違ったら、初期設定する
	if (red != m_targetRed || green != m_targetGreen || blue != m_targetBlue ||
	    frame != m_frame) {
		GetScreenBright(m_initRed, m_initGreen, m_initBlue);

		m_targetRed       = red;
		m_targetGreen     = green;
		m_targetBlue      = blue;
		m_frame           = frame;
		m_frame_per_red   = m_frame * 100 / (m_targetRed - m_initRed);
		m_frame_per_green = m_frame * 100 / (m_targetGreen - m_initGreen);
		m_frame_per_blue  = m_frame * 100 / (m_targetBlue - m_initBlue);
		m_count           = 0;
	}

	if (m_count == m_frame) {
		return 0;
	} else {
		// 最終フレーム
		if (m_count == m_frame - 1) {
			// 計算で少しずれるので、目標値にする
			SetScreenBright(m_targetRed, m_targetGreen, m_targetBlue);
		} else {
			// フェード途中
			SetScreenBright((int)(m_initRed + m_count * 100 / m_frame_per_red),
			                (int)(m_initGreen + m_count * 100 / m_frame_per_green),
			                (int)(m_initBlue + m_count * 100 / m_frame_per_blue));
		}
		m_count++;
	}

	return m_frame - m_count;
}

void CBright::GetScreenBright(int &red, int &green, int &blue) const {
	if (DxLib::GetDrawBright(&red, &green, &blue) == -1) {
		throw "輝度の取得に失敗しました。";
	}
}
void CBright::SetScreenBright(int red, int green, int blue) const {
	if (DxLib::SetDrawBright(red, green, blue) == -1) {
		throw "輝度設定に失敗しました。";
	}
}
