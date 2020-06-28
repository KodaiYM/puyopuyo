#pragma once

#include "CResourceMgr.h"
#include <memory>

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
		void Draw(std::shared_ptr<const CResourceMgr> const resourceMgr);
	private:
		bool mConnected[4];
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
}
