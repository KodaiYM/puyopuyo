#pragma once

#include "CPuyoField.h"
#include "CScene.h"
#include "Game_define.h"

namespace PuyoPuyo {

// ぷよぷよクラス
class CPuyoPuyo {
private:
	enum class SetName {
		current,  // 現在のぷよ
		next,     // ネクストぷよ
		nextnext, // ネクストネクストぷよ
		length
	};
	struct PuyoSet {
		Point    point;
		PuyoType type[2];
		double   angle;
	};
	std::shared_ptr<PuyoSet> mPuyoSet[(int)SetName::length];

	// ぷよ領域
	std::shared_ptr<CPuyoField> mPuyoField;

	// 初期位置
	const std::unordered_map<PointName, const Point> mDefaultPoint;

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
		init,    // 初期化
		next,    // Next ぷよが動く
		fall,    // ぷよ操作時間
		pop,     // ぷよを消す
		gameover // ゲームオーバー
	} mScene;

	class CFall;
	std::unique_ptr<CFall> mFallMgr;

	const std::shared_ptr<IGraphic> m_background;
	const std::shared_ptr<IGraphic> m_frame;
	const std::shared_ptr<IGraphic> m_left_next_frame;

	// ぷよを座標から算出した位置のぷよ領域にセットする
	void setPuyo(std::unique_ptr<const Puyo> puyo) const;

	// ぷよセットを描く専用の関数
	void DrawPuyoSet(PuyoSet puyoset) const;

	void Calc();
	void Draw() const;

public:
	// colors:色の数, row:行数(見えない1行は含まない), col:列数,
	// puyo_size:ぷよの高さ・幅, point:すべてのPointNameの初期位置
	CPuyoPuyo(int colors, int row, int col, int puyo_size,
	          std::unordered_map<PointName, const Point> point);
	~CPuyoPuyo();
	void Run();
};

} // namespace PuyoPuyo
