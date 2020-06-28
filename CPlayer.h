#ifndef _INCLUDE_GUARD_CPLAYER_
#define _INCLUDE_GUARD_CPLAYER_

#include "CPuyoField.h"

namespace Game {
	// プレイヤークラス
	class CPlayer {
	private:
		enum class SetName {
			current,	// 現在のぷよ
			next,		// ネクストぷよ
			nextnext,	// ネクストネクストぷよ
			length
		};
		struct PuyoSet {
			Point point;
			PuyoType type[2];
			double angle;
		} mPuyoSet[(int)SetName::length];

		// ぷよ領域
		CPuyoField* const mPuyoField;

		// 初期位置
		const std::unordered_map<PointName, Point> mDefaultPoint;

		// 使うぷよの色の数
		const int mColors;

		// 行数（見えない1行は含まない）
		const int mRow;

		// 列数
		const int mCol;

		// ぷよの幅・高さ
		const int mPuyoSize;

		// カウンター
		int mCount;

		// シーン管理
		enum class Scene {
			init,		// 初期化
			next,		// Next ぷよが動く
			fall,		// ぷよ操作時間
			pop,		// ぷよを消す
			gameover	// ゲームオーバー
		} mScene;

		// グラフィック管理
		const CResourceMgr* const mResourceMgr;

		class CFall;
		CFall *mFallMgr;

		// ぷよを座標から算出した位置のぷよ領域にセットする
		void setPuyo(const Puyo* puyo) const;

		// ぷよセットを描く専用の関数
		void DrawPuyoSet(const PuyoSet* puyoset) const;

		void Calc();
		void Draw() const;
	public:
		// colors:色の数, row:行数(見えない1行は含まない), col:列数, puyo_size:ぷよの高さ・幅, point:すべてのPointNameの初期位置
		CPlayer(int colors, int row, int col, int puyo_size, const CResourceMgr *resourceMgr, std::unordered_map<PointName, Point> point);
		~CPlayer();
		void Run();
	};
}

#endif
