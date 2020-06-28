#ifndef _INCLUDE_GUARD_CPUYOFIELD_
#define _INCLUDE_GUARD_CPUYOFIELD_

#include "Game_define.h"
#include "CResourceMgr.h"
#include <unordered_map>
#include <vector>
#include <memory>

/* ×はここで作成すると良いよ。ゲームオーバーを伝える関数も用意しよう。 */

// ぷよ領域のクラス
namespace Game {
	class CPuyoField {
	public:
		// row:行数(見えない一行は含まない), col:列数, puyo_size:ぷよの高さ、幅
		CPuyoField(int row, int col, int puyo_size, std::shared_ptr<const CResourceMgr> const resourceMgr);

		// 4つ以上つながっているぷよの削除。0で終了、1で実行中
		int Pop();

		// 見える領域で、i+1行 j+1列 に相当する位置にぷよを設置する(i=-1で見えない行)
		// puyo.point は、i+1行 j+1列 に相当する位置から、相対位置で指定
		void set(Puyo puyo, int i, int j);
		// 見える領域で、i+1行 j+1列 に相当する位置のぷよを消す
		void remove(int i, int j);

		// 見える領域で、i+1行 j+1列 に相当するぷよの種類を返す(i=-1で見えない行)
		PuyoType getPuyoType(int i, int j) const;

		// 見える領域で、i+1行 j+1列 はいくつのぷよとつながっているのかを返す(i=-1は不可)
		int CountConnection(int i, int j);
		int getConnectionNum(int i, int j) const;
		
		// ゲームオーバーの判定
		bool GameOvered() const;

		// 基準となる左上の座標を指定することで、その位置を基準として描く
		void Draw(Point field) const;
	private:
		const int mRow;			// 行数
		const int mCol;			// 列数
		const int mPuyoSize;	// ぷよの高さ、幅
		std::shared_ptr<const CResourceMgr> const mResourceMgr;
		std::vector< std::vector<Puyo> > mField;		// ぷよ領域。ぷよの位置は相対保持
		// いくつぷよがつながっているのかのカウント保存用
		// 0:ぷよがない または おじゃまぷよ
		// 1:ぷよは単独
		// -1:まだ調べてない
		std::vector< std::vector<int> > mConnectionCount;
		// CountConnection のサブ関数。
		int subCountConnection(int i, int j, PuyoType type, std::vector< std::vector<bool> >* connected);

		int mChain;	// 連鎖数
		std::shared_ptr<int> mTransparency;	// ぷよが消える時の透明度
		enum class Scene {
			drop,			// ぷよ領域のぷよ落下中
			judge_popable,	// 消せるぷよがあるか判定
			init_before_pop,// 削除対象のぷよを点滅させるクラス等の作成
			blink_pop_puyo,	// 削除対象のぷよを点滅
			pop				// 削除中
		} mScene;

		class blink_pop_puyo {
		private:
			// 点滅回数の管理
			int mCounter;
			const int mBlinkNum = 1;	// 点滅回数
			const int mMaxTransparency;	// 最大透明度
			const int mMinTransparency;	// 最小透明度
			const int mSpeed = 8;		// 透明度の変化量
			std::shared_ptr<int> const mTransparency;	// 透明度の変数
		public:
			blink_pop_puyo(std::shared_ptr<int> transparency);
			// 点滅させる。0で終了。
			int blink();
		};
		std::unique_ptr<blink_pop_puyo> mBlinkPopPuyo;

		int Drop();	// 宙に浮いているぷよを落とす
	};
}

#endif
