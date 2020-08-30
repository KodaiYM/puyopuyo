#pragma once

// 1つのグラフィックリソースのインタフェース
class Graphic {
public:
	// 画像や動画を1つ次へ進める（次が無ければ、ループ）
	// updateの結果位置が最後のとき、true を返す
	virtual bool update() = 0;
	// 描画する
	virtual void draw() const = 0;
};
