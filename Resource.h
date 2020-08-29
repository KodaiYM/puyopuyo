#pragma once

// 1つのリソースのインタフェース
class Resource {
public:
	// 画像や音声、動画を1つ次へ進める（次が無ければ、ループ）
	// updateの結果位置が最後のとき、true を返す
	virtual bool update() = 0;
	// 描画する、（音声を）再生する　など
	virtual void draw() const = 0;
};
