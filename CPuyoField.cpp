#include <DxLib.h>
#include <memory>
#include <string>

#include "CPuyoField.h"
#include "ImagePuyoPuyo.h"

using namespace PuyoPuyo;
CPuyoField::CPuyoField(int row, int col, int puyo_size)
    : mRow(row)
    , mCol(col)
    , mPuyoSize(puyo_size)
    , m_left_cross(std::make_shared<ImageCross>(47 + (mCol / 2 - 1) * mPuyoSize,
                                                13, ORIGIN::UPPER_LEFT))
    , m_right_cross(std::make_shared<ImageCross>(47 + (mCol / 2) * mPuyoSize,
                                                 13, ORIGIN::UPPER_LEFT)) {
	mField.resize(mRow + 1);
	mConnectionCount.resize(mRow);
	/* ぷよフィールドの初期化 */
	for (int i = 0; i < mRow + 1; i++) {
		std::vector<Puyo> puyo;
		puyo.resize(mCol);
		mField[i] = puyo;
	}

	// つながっているぷよの数(mConnectionCount)の初期化
	for (int i = 0; i < mRow; i++) {
		mConnectionCount[i].resize(mCol);
		for (int j = 0; j < mCol; j++) {
			mConnectionCount[i][j] = -1;
		}
	}
	mTransparency = 0;
	mChain        = 0;
	mScene        = Scene::drop;
}
void CPuyoField::set(Puyo puyo, int i, int j) {
	mField[i + 1][j] = puyo;
}
PuyoType CPuyoField::getPuyoType(int i, int j) const {
	if (i < -1) {
		return PuyoType::none;
	} else if (j < 0 || j >= mCol || i >= mRow) {
		// 壁の場合
		return PuyoType::block;
	} else {
		return mField[i + 1][j].type;
	}
}
bool CPuyoField::GameOvered() const {
	return getPuyoType(0, mCol / 2 - 1) != PuyoType::none ||
	       getPuyoType(0, mCol / 2) != PuyoType::none;
}
void CPuyoField::Draw(Point field) const {
	// ×を描く
	m_left_cross->draw();
	m_right_cross->draw();
	switch (mScene) {
	case Scene::drop:
	case Scene::judge_popable:
		// 最初の一行は描かない
		for (int i = 0; i < mRow; i++) {
			for (int j = 0; j < mCol; j++) {
				Puyo puyo(mField[i + 1][j]);

				// 相対座標を絶対座標に直してから描く
				puyo.point.x += field.x + mPuyoSize * j;
				puyo.point.y += field.y + mPuyoSize * i;
				puyo.Draw();
			}
		}
		break;
	case Scene::blink_pop_puyo:
	case Scene::pop:
		// 最初の一行は描かない
		for (int i = 0; i < mRow; i++) {
			for (int j = 0; j < mCol; j++) {
				Puyo puyo(mField[i + 1][j]);

				// 相対座標を絶対座標に直してから描く
				puyo.point.x += field.x + mPuyoSize * j;
				puyo.point.y += field.y + mPuyoSize * i;

				if (getConnectionNum(i, j) >= 4) {
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, *mTransparency);
					puyo.Draw();
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				} else {
					puyo.Draw();
				}
			}
		}
		break;
	default:
		throw "CPuyoField にシーン" + std::to_string((int)mScene) +
		    "は実装されていません。";
		break;
	}
}

int CPuyoField::Pop() {
	switch (mScene) {
	case Scene::drop:
		// ぷよ落下が終わったら
		if (Drop() == 0) {
			mScene = Scene::judge_popable;
		}
		break;
	case Scene::judge_popable: {
		// 消せるぷよがあるかどうか判定するとともに、ぷよの結合もチェック
		bool popable = false;
		for (int i = 0; i < mRow; i++) {
			for (int j = 0; j < mCol; j++) {
				// 上下のチェック
				if (i == 0) {
					mField[i + 1][j].setConnectionState(Puyo::Direction::bottom,
					                                    getPuyoType(i + 1, j) ==
					                                        getPuyoType(i, j));
				} else if (i == mRow - 1) {
					mField[i + 1][j].setConnectionState(
					    Puyo::Direction::top, getPuyoType(i - 1, j) == getPuyoType(i, j));
				} else {
					mField[i + 1][j].setConnectionState(Puyo::Direction::bottom,
					                                    getPuyoType(i + 1, j) ==
					                                        getPuyoType(i, j));
					mField[i + 1][j].setConnectionState(
					    Puyo::Direction::top, getPuyoType(i - 1, j) == getPuyoType(i, j));
				}

				// 左右のチェック
				if (j == 0) {
					mField[i + 1][j].setConnectionState(Puyo::Direction::right,
					                                    getPuyoType(i, j + 1) ==
					                                        getPuyoType(i, j));
				} else if (j == mCol - 1) {
					mField[i + 1][j].setConnectionState(Puyo::Direction::left,
					                                    getPuyoType(i, j - 1) ==
					                                        getPuyoType(i, j));
				} else {
					mField[i + 1][j].setConnectionState(Puyo::Direction::right,
					                                    getPuyoType(i, j + 1) ==
					                                        getPuyoType(i, j));
					mField[i + 1][j].setConnectionState(Puyo::Direction::left,
					                                    getPuyoType(i, j - 1) ==
					                                        getPuyoType(i, j));
				}

				if (getPuyoType(i, j) != PuyoType::none && CountConnection(i, j) >= 4) {
					popable = true;
				}
			}
		}
		if (popable) {
			mScene = Scene::init_before_pop;
		} else {
			for (int i = 0; i < mRow; i++) {
				for (int j = 0; j < mCol; j++) {
					mConnectionCount[i][j] = -1;
				}
			}
			mChain = 0;
			mScene = Scene::drop;
			return 0;
		}
	}
	case Scene::init_before_pop:
		for (int i = 0; i < mRow; i++) {
			for (int j = 0; j < mCol; j++) {
				CountConnection(i, j);
			}
		}
		mTransparency = std::make_unique<int>(255);
		mBlinkPopPuyo = std::make_unique<blink_pop_puyo>(mTransparency);
		mScene        = Scene::blink_pop_puyo;
	case Scene::blink_pop_puyo:
		if (mBlinkPopPuyo->blink() == 0) {
			mBlinkPopPuyo.reset();
			mChain++;
			switch (mChain) {
			case 1:
				// PlaySoundMem(mResourceMgr->getSoundHandle((int)SoundName::chain1),
				//             DX_PLAYTYPE_BACK);
				break;
			case 2:
				// PlaySoundMem(mResourceMgr->getSoundHandle((int)SoundName::chain2),
				//             DX_PLAYTYPE_BACK);
				break;
			case 3:
				// PlaySoundMem(mResourceMgr->getSoundHandle((int)SoundName::chain3),
				//             DX_PLAYTYPE_BACK);
				break;
			case 4:
				// PlaySoundMem(mResourceMgr->getSoundHandle((int)SoundName::chain4),
				//             DX_PLAYTYPE_BACK);
				break;
			case 5:
				// PlaySoundMem(mResourceMgr->getSoundHandle((int)SoundName::chain5),
				//             DX_PLAYTYPE_BACK);
				break;
			case 6:
				// PlaySoundMem(mResourceMgr->getSoundHandle((int)SoundName::chain6),
				//             DX_PLAYTYPE_BACK);
				break;
			default:
				// PlaySoundMem(mResourceMgr->getSoundHandle((int)SoundName::chain7),
				//             DX_PLAYTYPE_BACK);
				break;
			}
			mScene = Scene::pop;
		}
		break;
	case Scene::pop:
		*mTransparency -= 15;
		if (*mTransparency <= 0) {
			for (int i = 0; i < mRow; i++) {
				for (int j = 0; j < mCol; j++) {
					if (getConnectionNum(i, j) >= 4) {
						remove(i, j);
					}
					mConnectionCount[i][j] = -1;
				}
			}
			mTransparency.reset();
			mScene = Scene::drop;
		}
		break;
	}
	return 1;
}
CPuyoField::blink_pop_puyo::blink_pop_puyo(std::shared_ptr<int> transparency)
    : mMaxTransparency(*transparency)
    , mMinTransparency(*transparency - 100)
    , mTransparency(std::move(transparency)) {
	mCounter = 0;
}
int CPuyoField::blink_pop_puyo::blink() {
	if (mCounter >= mBlinkNum * 2) {
		return 0;
	}
	if (mCounter % 2) {
		*mTransparency += mSpeed;
		if (*mTransparency >= mMaxTransparency) {
			*mTransparency = mMaxTransparency;
			mCounter++;
		}
	} else {
		*mTransparency -= mSpeed;
		if (*mTransparency <= mMinTransparency) {
			*mTransparency = mMinTransparency;
			mCounter++;
		}
	}
	return 1;
}

int CPuyoField::subCountConnection(int i, int j, PuyoType type,
                                   std::vector<std::vector<bool> > *connected) {
	connected->at(i)[j]    = true;
	mConnectionCount[i][j] = 1;

	/* 隣接しているかチェック */
	// 右
	if (j < mCol - 1 && getPuyoType(i, j + 1) == type &&
	    mConnectionCount[i][j + 1] == -1) {
		mConnectionCount[i][j] += subCountConnection(i, j + 1, type, connected);
	}
	// 上
	if (i >= 1 && getPuyoType(i - 1, j) == type &&
	    mConnectionCount[i - 1][j] == -1) {
		mConnectionCount[i][j] += subCountConnection(i - 1, j, type, connected);
	}
	// 左
	if (j >= 1 && getPuyoType(i, j - 1) == type &&
	    mConnectionCount[i][j - 1] == -1) {
		mConnectionCount[i][j] += subCountConnection(i, j - 1, type, connected);
	}
	// 下
	if (i < mRow - 1 && getPuyoType(i + 1, j) == type &&
	    mConnectionCount[i + 1][j] == -1) {
		mConnectionCount[i][j] += subCountConnection(i + 1, j, type, connected);
	}

	return mConnectionCount[i][j];
}
int CPuyoField::CountConnection(int i, int j) {
	const PuyoType type = getPuyoType(i, j);

	// 調査済みの場合
	if (mConnectionCount[i][j] != -1) {
		return mConnectionCount[i][j];
	}
	// ぷよがなかったり、おじゃまの場合
	if (type == PuyoType::ojama || type == PuyoType::none) {
		mConnectionCount[i][j] = 0;
		return 0;
	}

	// 調査の必要がある場合
	{
		int                             n;
		std::vector<std::vector<bool> > connected;
		connected.resize(mRow);
		for (int l = 0; l < mRow; l++) {
			connected[l].resize(mCol);
			for (int m = 0; m < mCol; m++) {
				connected[l][m] = false;
			}
		}

		n = subCountConnection(i, j, type, &connected);

		for (int l = 0; l < mRow; l++) {
			for (int m = 0; m < mCol; m++) {
				if (connected[l][m]) {
					mConnectionCount[l][m] = n;
				}
			}
		}
		return n;
	}
}
int CPuyoField::getConnectionNum(int i, int j) const {
	if (mConnectionCount[i][j] == -1) {
		throw "与えられた座標の接続ぷよ数はまだカウントされていません。";
	}
	return mConnectionCount[i][j];
}

void CPuyoField::remove(int i, int j) {
	Puyo puyo;
	mField[i + 1][j] = puyo;
}
int CPuyoField::Drop() {
	bool dropping = false;
	for (int j = 0; j < mCol; j++) {
		bool droppable = false;
		for (int i = mRow - 1; i >= -1; i--) {
			Puyo &puyo = mField[i + 1][j];
			if (puyo.type == PuyoType::none) {
				droppable = true;
			} else if (droppable) {
				dropping = true;
				puyo.point.y += 4;
				if (puyo.point.y >= mPuyoSize) {
					puyo.point.y = 0;

					set(puyo, i + 1, j);
					remove(i, j);
				}
			}
		}
	}
	return dropping ? 1 : 0;
}
