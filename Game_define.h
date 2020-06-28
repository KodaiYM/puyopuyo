#ifndef _INCLUDE_GUARD_GAME_DEFINE_
#define _INCLUDE_GUARD_GAME_DEFINE_

#include <unordered_map>
#include <DxLib.h>
#include "CResourceMgr.h"

namespace Game {
	// 点・座標のクラス
	class Point {
	public:
		int x;
		int y;
	};
	// ぷよの種類。上の方は、ふつうのぷよにすること
	enum class PuyoType {
		blue,
		red,
		green,
		pink,
		ojama,
		block,	// 壁、消えないぷよ
		none	// 何もないことを表す
	};
	class Puyo {
	public:
		Puyo() {
			type = PuyoType::none;
			point.x = 0;
			point.y = 0;
			mConnected[0] = mConnected[1] = mConnected[2] = mConnected[3] = false;
		};
		PuyoType type;
		Point point;
		// 普通の状態、くっついている状態などの管理
		enum class Direction {
			right,
			top,
			left,
			bottom
		};
		void setConnectionState(Direction direction, bool connected);
		void Draw(const CResourceMgr* const resourceMgr);
	private:
		bool mConnected[4];
	};
	// グラフィック名
	enum class GraphicName {
		background,
		frame,
		blue0000,
		blue0001,
		blue0010,
		blue0011,
		blue0100,
		blue0101,
		blue0110,
		blue0111,
		blue1000,
		blue1001,
		blue1010,
		blue1011,
		blue1100,
		blue1101,
		blue1110,
		blue1111,
		red0000,
		red0001,
		red0010,
		red0011,
		red0100,
		red0101,
		red0110,
		red0111,
		red1000,
		red1001,
		red1010,
		red1011,
		red1100,
		red1101,
		red1110,
		red1111,
		green0000,
		green0001,
		green0010,
		green0011,
		green0100,
		green0101,
		green0110,
		green0111,
		green1000,
		green1001,
		green1010,
		green1011,
		green1100,
		green1101,
		green1110,
		green1111,
		pink0000,
		pink0001,
		pink0010,
		pink0011,
		pink0100,
		pink0101,
		pink0110,
		pink0111,
		pink1000,
		pink1001,
		pink1010,
		pink1011,
		pink1100,
		pink1101,
		pink1110,
		pink1111,
		ojama,
		cross,
		left_next,
		right_next,
		length
	};
	// 1プレイヤーごとに、必ず必要となる座標情報の名前
	enum class PointName {
		field,
		next_field,
		next,
		nextnext,
		current,
		length
	};
	// サウンド名
	enum class SoundName {
		chain1,
		chain2,
		chain3,
		chain4,
		chain5,
		chain6,
		chain7,
		game_over,
		land,
		move,
		rotate
	};
}

#endif
