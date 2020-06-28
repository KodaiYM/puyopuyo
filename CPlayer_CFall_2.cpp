#define _USE_MATH_DEFINES
#include "CPlayer_CFall.h"
#include "function.h"
#include "key.h"

using namespace Game;
int CPlayer::CFall::FreeFall() {
	bool falled = false;
	int quantity = (int)mSpeed;
	const int r = mCount % 10;

	mCount++;
	switch ((int)(mSpeed * 10) % 10) {
	case 1:
		if (r == 0) {
			quantity++;
		}
		break;
	case 2:
		if (r == 0 || r == 5) {
			quantity++;
		}
		break;
	case 3:
		if (r == 3 || r == 6 || r == 9) {
			quantity++;
		}
		break;
	case 4:
		if (r == 2 || r == 4 || r == 7 || r == 9) {
			quantity++;
		}
		break;
	case 5:
		if (r % 2 == 0) {
			quantity++;
		}
		break;
	case 6:
		if (r == 1 || r == 3 || r == 4 || r == 5 || r == 7 || r == 9) {
			quantity++;
		}
		break;
	case 7:
		if (r == 1 || r == 2 || r == 4 || r == 5 || r == 7 || r == 8 || r == 9) {
			quantity++;
		}
		break;
	case 8:
		if ((1 <= r && r <= 4) || (6 <= r && r <= 9)) {
			quantity++;
		}
		break;
	case 9:
		if (r != 0) {
			quantity++;
		}
		break;
	}
	if (KeyStateOf(KEY_INPUT_DOWN)) {
		quantity += 14;
	}

	while (quantity-- && movable(Puyo::Direction::bottom, true) && movable(getPoint(mDestinationAngle*M_PI_2), Puyo::Direction::bottom)) {
		mCurrentPuyoSet->point.y++;
		falled = true;
	}

	return falled ? 1 : 0;
}
int CPlayer::CFall::Rotate() {
	/* 両側埋まっている場合とそうでない場合で、A,B を押したときの 動作を変える必要がある */
	if (KeyStateOf(KEY_INPUT_A) == 1) {
		PlaySoundMem(mResourceMgr->getSoundHandle((int)SoundName::rotate), DX_PLAYTYPE_BACK);
		// 着地状態のとき
		if (!movable(Puyo::Direction::bottom)) {
			// 回転に必要なフレーム数だけ上に移動する
			mCurrentPuyoSet->point.y -= mRotateFrame;
		}
		mDestinationAngle--;
	} else if (KeyStateOf(KEY_INPUT_B) == 1) {
		PlaySoundMem(mResourceMgr->getSoundHandle((int)SoundName::rotate), DX_PLAYTYPE_BACK);
		// 着地状態のとき
		if (!movable(Puyo::Direction::bottom)) {
			// 回転に必要なフレーム数だけ上に移動する
			mCurrentPuyoSet->point.y -= mRotateFrame;
		}
		mDestinationAngle++;
	}
	// まずは、両側埋まっているような例外を除いて考えよう

	// 回転が必要なとき
	if (mCurrentPuyoSet->angle != mDestinationAngle * M_PI_2) {
		const int x = mCurrentPuyoSet->point.x;
		const int y = mCurrentPuyoSet->point.y;

		/* 回転後に何かあるときの調整 */
		if (!rotatable(x, y, mDestinationAngle*M_PI_2)) {
			// 上に行けて、上に行けば回転できるとき
			if (movable(Puyo::Direction::top, true) && rotatable(x, gety(geti(y - 1)), mDestinationAngle*M_PI_2)) {
				// 上のマスに行く
				mCurrentPuyoSet->point.y = gety(geti(y - 1));
			}
			// 右に行けて、右に行けば回転できるとき
			else if (movable(Puyo::Direction::right, true) && rotatable(getx(getj(x) + 1), y, mDestinationAngle*M_PI_2)) {
				// まだ右に行こうとしてなければ
				if (mDestinationJ <= getj(x)) {
					// 右に移動
					mDestinationJ = getj(x) + 1;
				}
			}
			// 左に行けて、左に行けば回転できるとき
			else if (movable(Puyo::Direction::left, true) && rotatable(getx(getj(x - 1)), y, mDestinationAngle*M_PI_2)) {
				// まだ左に行こうとしてなければ
				if (mDestinationJ >= getj(x - 1) + 1) {
					// 左に移動
					mDestinationJ = getj(x - 1);
				}
			}
			// 下に行けて、下に行けば回転できるとき
			else if (movable(Puyo::Direction::bottom, true) && rotatable(x, gety(geti(y) + 1), mDestinationAngle*M_PI_2)) {
				// 下のマスに行く
				mCurrentPuyoSet->point.y = gety(geti(y) + 1);
			}
			// 上下左右の移動でどうにもならないとき
			else {
				// 負の回転をしていた場合
				if (mCurrentPuyoSet->angle > mDestinationAngle*M_PI_2) {
					mDestinationAngle--;
				}
				// 正の回転をしていた場合
				else {
					mDestinationAngle++;
				}
			}
		}

		/* 回転 この回転を手前に持ってくると、movable が false を返すようになっちゃう */
		// 1フレームで移動したい角度
		double anglePerFrame = M_PI_2 / mRotateFrame;
		if (mDestinationAngle*M_PI_2 < mCurrentPuyoSet->angle) {
			// 負の回転
			anglePerFrame = -anglePerFrame;
		}

		mCurrentPuyoSet->angle += anglePerFrame;
		// 目的の角度に近いとき
		if (abs(mCurrentPuyoSet->angle - mDestinationAngle * M_PI_2) < abs(anglePerFrame)) {
			mCurrentPuyoSet->angle = mDestinationAngle * M_PI_2;
		}

		return 1;
	}

	return 0;
}
bool CPlayer::CFall::rotatable(int x, int y, double angle) {
	Point point;
	point.x = x;
	point.y = y;
	point = getPoint(point, angle);

	return !overlapped(point);
}
bool CPlayer::CFall::overlapped(const Point& p) const {
	// 壁に被っている場合
	if (p.x < mFieldPoint.x || p.x + mPuyoSize > mFieldPoint.x + mCol * mPuyoSize || p.y + mPuyoSize > mFieldPoint.y + mRow * mPuyoSize) {
		return true;
	}
	// ちょうど行にいる場合
	if (Remainder(p.y - mFieldPoint.y, mPuyoSize) == 0) {
		// ちょうど行・列にいる場合
		if (Remainder(p.x - mFieldPoint.x, mPuyoSize) == 0) {
			// その位置にぷよがあるか見る
			if (mPuyoField->getPuyoType(geti(p.y), getj(p.x)) == PuyoType::none) {
				return false;
			}
		}
		// ちょうど行にいるが、列に関して微妙な位置にいる場合
		else {
			// 左と右を見る
			if (mPuyoField->getPuyoType(geti(p.y), getj(p.x)) == PuyoType::none && mPuyoField->getPuyoType(geti(p.y), getj(p.x) + 1) == PuyoType::none) {
				return false;
			}
		}
	}
	// 行に関して微妙な位置にいる場合
	else {
		// ちょうど列にいる場合
		if (Remainder(p.x - mFieldPoint.x, mPuyoSize) == 0) {
			// 上と下を見る
			if (mPuyoField->getPuyoType(geti(p.y), getj(p.x)) == PuyoType::none && mPuyoField->getPuyoType(geti(p.y) + 1, getj(p.x)) == PuyoType::none) {
				return false;
			}
		}
		// 行・列に関して微妙な位置にいる場合
		else {
			// 左上、右上、左下、右下を見る
			if (mPuyoField->getPuyoType(geti(p.y), getj(p.x)) == PuyoType::none
				&& mPuyoField->getPuyoType(geti(p.y), getj(p.x) + 1) == PuyoType::none
				&& mPuyoField->getPuyoType(geti(p.y) + 1, getj(p.x)) == PuyoType::none
				&& mPuyoField->getPuyoType(geti(p.y) + 1, getj(p.x) + 1) == PuyoType::none) {
				return false;
			}
		}
	}
	return true;
}
int CPlayer::CFall::Move() {
	Point const axis_destination_point = { getx(mDestinationJ), mCurrentPuyoSet->point.y };
	Point const non_axis_destination_point = getPoint(axis_destination_point, (double)mDestinationAngle*M_PI_2);

	if (KeyStateOf(KEY_INPUT_LEFT) == 1 || (KeyStateOf(KEY_INPUT_LEFT) > 10 && KeyStateOf(KEY_INPUT_LEFT) % 3 == 1)) {
		if (movable(axis_destination_point, Puyo::Direction::left) && movable(non_axis_destination_point, Puyo::Direction::left)) {
			PlaySoundMem(mResourceMgr->getSoundHandle((int)SoundName::move), DX_PLAYTYPE_BACK);
			mDestinationJ--;
		}
	} else if (KeyStateOf(KEY_INPUT_RIGHT) == 1 || (KeyStateOf(KEY_INPUT_RIGHT) > 10 && KeyStateOf(KEY_INPUT_RIGHT) % 3 == 1)) {
		if (movable(axis_destination_point, Puyo::Direction::right) && movable(non_axis_destination_point, Puyo::Direction::right)) {
			PlaySoundMem(mResourceMgr->getSoundHandle((int)SoundName::move), DX_PLAYTYPE_BACK);
			mDestinationJ++;
		}
	}

	if (mCurrentPuyoSet->point.x != getx(mDestinationJ)) {
		// 1フレームで移動したい量
		int quantityPerFrame = mPuyoSize / mMoveFrame;
		printf("%d, %d\n", mCurrentPuyoSet->point.x, getx(mDestinationJ)); // 199, 237

		// 右に移動
		if (mCurrentPuyoSet->point.x < getx(mDestinationJ)) {
			// 移動予定先が移動できないはずの場所であるという異常の場合
			if (overlapped(axis_destination_point) || overlapped(non_axis_destination_point)) {
				mDestinationJ--;
				if (mCurrentPuyoSet->point.x == getx(mDestinationJ))return 0;
			} else {
				mCurrentPuyoSet->point.x += quantityPerFrame;
			}
		}
		// 左に移動
		else {
			// 移動予定先が移動できないはずの場所であるという異常の場合
			if (overlapped(axis_destination_point) || overlapped(non_axis_destination_point)) {
				mDestinationJ++;
				if (mCurrentPuyoSet->point.x == getx(mDestinationJ))return 0;
			} else {
				mCurrentPuyoSet->point.x -= quantityPerFrame;
			}
		}

		// 被っていた場合
		if (overlapped(mCurrentPuyoSet->point) || overlapped(getPoint(mCurrentPuyoSet->angle))) {
			// まず、左方向に調整
			const double angle = mCurrentPuyoSet->angle;
			Point pl = mCurrentPuyoSet->point;
			bool success = false;
			for (int i = 0; i < mPuyoSize; i++) {
				pl.x--;
				if (!overlapped(pl) && !overlapped(getPoint(pl, angle))) {
					success = true;
					break;
				}
			}
			// 左方向の調整が成功した
			if (success) {
				mCurrentPuyoSet->point = pl;
			} else {
				// 右方向に調整してみる
				Point pr = mCurrentPuyoSet->point;
				for (int i = 0; i < mPuyoSize; i++) {
					pr.x++;
					if (!overlapped(pr) && !overlapped(getPoint(pr, angle))) {
						success = true;
						break;
					}
				}
				// 右方向の調整が成功した
				if (success) {
					mCurrentPuyoSet->point = pr;
				} else {
					printf("Move() 左右の方向の調整が失敗\n");
				}
			}
		}

		// 移動先に近いとき
		if (abs(mCurrentPuyoSet->point.x - getx(mDestinationJ)) < abs(quantityPerFrame)) {
			mCurrentPuyoSet->point.x = getx(mDestinationJ);
		}
		return 1;
	}
	return 0;
}
