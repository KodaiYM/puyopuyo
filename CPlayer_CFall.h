#pragma once

#include "CPuyoPuyo.h"

namespace PuyoPuyo {
class CPuyoPuyo::CFall {
private:
	float mSpeed; // 自由落下の速度。大きいほどすぐ落ちる。小数点以下第1位まで反映
	int   mCount;
	int   mLandCount; // 着地判定のカウント

	static const int mRotateFrame; // 回転にかかるフレーム数
	static const int mMoveFrame;   // 左右移動にかかるフレーム数
	static const int mLandFrame; // 何フレーム着地していたら、着地となるか

	// 移動先の情報
	int mDestinationAngle; // 角度 : mDestinationAngle * M_PI_2 (= pi/2)
	int mDestinationJ;     // J+1列

	std::shared_ptr<PuyoSet> const mCurrentPuyoSet; // 現在操作中のぷよのセット
	const int                      mPuyoSize; // 1つのぷよの幅・高さ
	const int                      mRow;      // 見える領域の行数
	const int                      mCol;      // 見える領域の列数

	std::shared_ptr<CPuyoField> const mPuyoField;  // ぷよ領域
	const Point                       mFieldPoint; // フィールド初期位置

	// p の位置にあるぷよが、他のぷよや壁と被っているか判定する
	bool overlapped(const Point &p) const;
	// 現在のぷよが direction の方向に少しでも移動できるかどうか
	bool movable(Puyo::Direction direction) const;
	// ぷよ(axis=true:軸, false:そうでない方)が direction
	// の方向に少しでも移動できるかどうか
	bool movable(Puyo::Direction direction, bool axis) const;
	// point の位置にあるぷよが direction の方向に少しでも移動できるかどうか
	bool movable(const Point &point, Puyo::Direction direction) const;
	// x, y を中心として、angle 回転させた先の座標を得る
	Point getPoint(const Point &point, double angle) const;
	// 現在のぷよの座標を中心として、angle 回転させた先の座標を得る
	Point getPoint(double angle) const;
	// y 座標から i (見える領域の行番号)を得る。
	int geti(int y) const;
	// x 座標から j (見える領域の列番号)を得る。
	int getj(int x) const;
	// j (見える領域の行番号)から x 座標を得る。
	int getx(int j) const;
	// i (見える領域の行番号)から y 座標を得る。
	int gety(int i) const;

	int Rotate(); // 回転に関する処理。0 = 回転終了
	// (x, y) の位置にあるぷよが、angle 回転したときに他のぷよと被らないか判定する
	bool rotatable(int x, int y, double angle);
	int  Move();    // 左右の移動に関する処理。0 = 移動終了
	int FreeFall(); // 自由落下。自由落下しなかったとき、0を返す
public:
	CFall(std::shared_ptr<PuyoSet> currentPuyoSet, const Point fieldPoint,
	      std::shared_ptr<CPuyoField> puyoField, int puyo_size, int row, int col);
	int Run();
};
} // namespace PuyoPuyo
