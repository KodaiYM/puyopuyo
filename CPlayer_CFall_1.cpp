#define _USE_MATH_DEFINES

#include <DxLib.h>

#include "CPlayer_CFall.h"
#include "function.h"
// デバッグ用
#include "key.h"

using namespace PuyoPuyo;
const int CPuyoPuyo::CFall::mRotateFrame = 8;
const int CPuyoPuyo::CFall::mMoveFrame   = 5;
const int CPuyoPuyo::CFall::mLandFrame   = 60;
CPuyoPuyo::CFall::CFall(std::shared_ptr<PuyoSet>    currentPuyoSet,
                        const Point                 fieldPoint,
                        std::shared_ptr<CPuyoField> puyoField, int puyo_size,
                        int row, int col)
    : mCurrentPuyoSet(std::move(currentPuyoSet))
    , mFieldPoint(fieldPoint)
    , mPuyoSize(puyo_size)
    , mRow(row)
    , mCol(col)
    , mPuyoField(std::move(puyoField)) {
	mSpeed            = 1.6f;
	mCount            = 0;
	mLandCount        = 0;
	mDestinationAngle = 1;
	mDestinationJ     = 2;
}

int CPuyoPuyo::CFall::Run() {
	bool not_falled  = (FreeFall() == 0);
	bool not_rotated = (Rotate() == 0);
	bool not_moved   = (Move() == 0);

	// デバッグ用
#if DEBUG | _DEBUG
	if (KeyStateOf(KEY_INPUT_UP)) {
		mCurrentPuyoSet->point.y--;
	}
#endif

	// 自由落下できない状況のとき、着地判定
	if (!movable(Puyo::Direction::bottom, true) ||
	    !movable(getPoint(mDestinationAngle * M_PI_2), Puyo::Direction::bottom)) {
		// 下キーを押していたら、着地カウントを加速
		if (KeyStateOf(KEY_INPUT_DOWN)) {
			mLandCount += 10;
		}
		if (not_rotated && not_moved) {
			mLandCount++;

			// 着地カウントが、ある数以上のとき
			if (mLandCount >= mLandFrame) {
				Puyo p0;
				p0.point.x = p0.point.y = 0;
				p0.type                 = mCurrentPuyoSet->type[0];

				switch (Remainder(mDestinationAngle, 4)) {
				case 0:
					if (geti(mCurrentPuyoSet->point.y) != -2) {
						mPuyoField->set(p0, geti(mCurrentPuyoSet->point.y),
						                getj(mCurrentPuyoSet->point.x) + 1);
					}
					break;
				case 1:
					if (geti(mCurrentPuyoSet->point.y) - 1 != -2) {
						mPuyoField->set(p0, geti(mCurrentPuyoSet->point.y) - 1,
						                getj(mCurrentPuyoSet->point.x));
					}
					break;
				case 2:
					if (geti(mCurrentPuyoSet->point.y) != -2) {
						mPuyoField->set(p0, geti(mCurrentPuyoSet->point.y),
						                getj(mCurrentPuyoSet->point.x) - 1);
					}
					break;
				case 3:
					if (geti(mCurrentPuyoSet->point.y) + 1 != -2) {
						mPuyoField->set(p0, geti(mCurrentPuyoSet->point.y) + 1,
						                getj(mCurrentPuyoSet->point.x));
					}
					break;
				}

				Puyo p1;
				p1.point.x = p1.point.y = 0;
				p1.type                 = mCurrentPuyoSet->type[1];
				if (geti(mCurrentPuyoSet->point.y) != -2) {
					mPuyoField->set(p1, geti(mCurrentPuyoSet->point.y),
					                getj(mCurrentPuyoSet->point.x));
				}

				mCount            = 0;
				mLandCount        = 0;
				mDestinationAngle = 1;
				mDestinationJ     = 2;

				return 0;
			}
		}
	}

	return 1;
}

Point CPuyoPuyo::CFall::getPoint(const Point &point, double angle) const {
	Point p;
	p.x = (int)std::round(point.x + mPuyoSize * std::cos(angle));
	p.y = (int)std::round(point.y - mPuyoSize * std::sin(angle));
	return p;
}
Point CPuyoPuyo::CFall::getPoint(double angle) const {
	Point p = getPoint(mCurrentPuyoSet->point, angle);
	return p;
}
int CPuyoPuyo::CFall::geti(int y) const {
	return Quotient(y - mFieldPoint.y, mPuyoSize);
}
int CPuyoPuyo::CFall::getj(int x) const {
	return Quotient(x - mFieldPoint.x, mPuyoSize);
}
int CPuyoPuyo::CFall::getx(int j) const {
	return mFieldPoint.x + j * mPuyoSize;
}
int CPuyoPuyo::CFall::gety(int i) const {
	return mFieldPoint.y + i * mPuyoSize;
}
bool CPuyoPuyo::CFall::movable(Puyo::Direction direction) const {
	return movable(direction, true) && movable(direction, false);
}
bool CPuyoPuyo::CFall::movable(Puyo::Direction direction, bool axis) const {
	return axis
	           ? movable(mCurrentPuyoSet->point, direction)
	           : movable(getPoint(mCurrentPuyoSet->point, mCurrentPuyoSet->angle),
	                     direction);
}
bool CPuyoPuyo::CFall::movable(const Point &         point,
                               const Puyo::Direction direction) const {
	Point p;
	p.x = point.x;
	p.y = point.y;

	switch (direction) {
	case Puyo::Direction::left:
		p.x--;
		break;
	case Puyo::Direction::right:
		p.x++;
		break;
	case Puyo::Direction::bottom:
		p.y++;
		break;
	case Puyo::Direction::top:
		p.y--;
		break;
	}
	if (overlapped(p)) {
		return false;
	}
	return true;
}
