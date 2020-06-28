#include <DxLib.h>
#include "Game.h"
#include "key.h"

using namespace Game;
/* ゲームクラスに対する定義 */
CGame::CGame(ISceneChanger* changer) : CBaseScene(changer) {
	mScene = Scene::init;
}
void CGame::Run() {
	switch (mScene) {
	case Scene::init:
		{
			const std::unordered_map<PointName, Point> point = {
				{ PointName::next_field, { 276, 17 } },
				{ PointName::field, { 47, 13 } },
				{ PointName::next, { 278, 60 } },
				{ PointName::nextnext, { 291, 141 } },
				{ PointName::current, { 47 + 2 * 38, -25 } }
			};
			const std::unordered_map<int, const char*> GraphicPath = {
				{ (int)GraphicName::background, "img/Game/background_a.png" },
				{ (int)GraphicName::frame, "img/Game/frame_a.png" },
				{ (int)GraphicName::ojama, "img/Game/black_a.png" },
				{ (int)GraphicName::cross, "img/Game/cross_a.png" },
				{ (int)GraphicName::blue0000, "img/Game/blue0000_a.png" },
				{ (int)GraphicName::blue0001, "img/Game/blue0001_a.png" },
				{ (int)GraphicName::blue0010, "img/Game/blue0010_a.png" },
				{ (int)GraphicName::blue0011, "img/Game/blue0011_a.png" },
				{ (int)GraphicName::blue0100, "img/Game/blue0100_a.png" },
				{ (int)GraphicName::blue0101, "img/Game/blue0101_a.png" },
				{ (int)GraphicName::blue0110, "img/Game/blue0110_a.png" },
				{ (int)GraphicName::blue0111, "img/Game/blue0111_a.png" },
				{ (int)GraphicName::blue1000, "img/Game/blue1000_a.png" },
				{ (int)GraphicName::blue1001, "img/Game/blue1001_a.png" },
				{ (int)GraphicName::blue1010, "img/Game/blue1010_a.png" },
				{ (int)GraphicName::blue1011, "img/Game/blue1011_a.png" },
				{ (int)GraphicName::blue1100, "img/Game/blue1100_a.png" },
				{ (int)GraphicName::blue1101, "img/Game/blue1101_a.png" },
				{ (int)GraphicName::blue1110, "img/Game/blue1110_a.png" },
				{ (int)GraphicName::blue1111, "img/Game/blue1111_a.png" },
				{ (int)GraphicName::green0000, "img/Game/green0000_a.png" },
				{ (int)GraphicName::green0001, "img/Game/green0001_a.png" },
				{ (int)GraphicName::green0010, "img/Game/green0010_a.png" },
				{ (int)GraphicName::green0011, "img/Game/green0011_a.png" },
				{ (int)GraphicName::green0100, "img/Game/green0100_a.png" },
				{ (int)GraphicName::green0101, "img/Game/green0101_a.png" },
				{ (int)GraphicName::green0110, "img/Game/green0110_a.png" },
				{ (int)GraphicName::green0111, "img/Game/green0111_a.png" },
				{ (int)GraphicName::green1000, "img/Game/green1000_a.png" },
				{ (int)GraphicName::green1001, "img/Game/green1001_a.png" },
				{ (int)GraphicName::green1010, "img/Game/green1010_a.png" },
				{ (int)GraphicName::green1011, "img/Game/green1011_a.png" },
				{ (int)GraphicName::green1100, "img/Game/green1100_a.png" },
				{ (int)GraphicName::green1101, "img/Game/green1101_a.png" },
				{ (int)GraphicName::green1110, "img/Game/green1110_a.png" },
				{ (int)GraphicName::green1111, "img/Game/green1111_a.png" },
				{ (int)GraphicName::pink0000, "img/Game/pink0000_a.png" },
				{ (int)GraphicName::pink0001, "img/Game/pink0001_a.png" },
				{ (int)GraphicName::pink0010, "img/Game/pink0010_a.png" },
				{ (int)GraphicName::pink0011, "img/Game/pink0011_a.png" },
				{ (int)GraphicName::pink0100, "img/Game/pink0100_a.png" },
				{ (int)GraphicName::pink0101, "img/Game/pink0101_a.png" },
				{ (int)GraphicName::pink0110, "img/Game/pink0110_a.png" },
				{ (int)GraphicName::pink0111, "img/Game/pink0111_a.png" },
				{ (int)GraphicName::pink1000, "img/Game/pink1000_a.png" },
				{ (int)GraphicName::pink1001, "img/Game/pink1001_a.png" },
				{ (int)GraphicName::pink1010, "img/Game/pink1010_a.png" },
				{ (int)GraphicName::pink1011, "img/Game/pink1011_a.png" },
				{ (int)GraphicName::pink1100, "img/Game/pink1100_a.png" },
				{ (int)GraphicName::pink1101, "img/Game/pink1101_a.png" },
				{ (int)GraphicName::pink1110, "img/Game/pink1110_a.png" },
				{ (int)GraphicName::pink1111, "img/Game/pink1111_a.png" },
				{ (int)GraphicName::red0000, "img/Game/red0000_a.png" },
				{ (int)GraphicName::red0001, "img/Game/red0001_a.png" },
				{ (int)GraphicName::red0010, "img/Game/red0010_a.png" },
				{ (int)GraphicName::red0011, "img/Game/red0011_a.png" },
				{ (int)GraphicName::red0100, "img/Game/red0100_a.png" },
				{ (int)GraphicName::red0101, "img/Game/red0101_a.png" },
				{ (int)GraphicName::red0110, "img/Game/red0110_a.png" },
				{ (int)GraphicName::red0111, "img/Game/red0111_a.png" },
				{ (int)GraphicName::red1000, "img/Game/red1000_a.png" },
				{ (int)GraphicName::red1001, "img/Game/red1001_a.png" },
				{ (int)GraphicName::red1010, "img/Game/red1010_a.png" },
				{ (int)GraphicName::red1011, "img/Game/red1011_a.png" },
				{ (int)GraphicName::red1100, "img/Game/red1100_a.png" },
				{ (int)GraphicName::red1101, "img/Game/red1101_a.png" },
				{ (int)GraphicName::red1110, "img/Game/red1110_a.png" },
				{ (int)GraphicName::red1111, "img/Game/red1111_a.png" },
				{ (int)GraphicName::left_next, "img/Game/left_next.png" },
				{ (int)GraphicName::right_next, "img/Game/right_next.png" },
			};
			const std::unordered_map<int, const char*> SoundPath = {
				{ (int)SoundName::chain1, "sound_effect/chain1.wav" },
				{ (int)SoundName::chain2, "sound_effect/chain2.wav" },
				{ (int)SoundName::chain3, "sound_effect/chain3.wav" },
				{ (int)SoundName::chain4, "sound_effect/chain4.wav" },
				{ (int)SoundName::chain5, "sound_effect/chain5.wav" },
				{ (int)SoundName::chain6, "sound_effect/chain6.wav" },
				{ (int)SoundName::chain7, "sound_effect/chain7.wav" },
				{ (int)SoundName::game_over, "sound_effect/game_over.wav" },
				{ (int)SoundName::land, "sound_effect/land.wav" },
				{ (int)SoundName::move, "sound_effect/move.wav" },
				{ (int)SoundName::rotate, "sound_effect/rotate.wav" },
			};
			mResourceMgr = new CResourceMgr();
			mResourceMgr->LoadGraphic(GraphicPath);
			mResourceMgr->LoadSound(SoundPath);

			mPlayer = new CPlayer(4, 12, 6, 38, mResourceMgr, point);
		}
		mScene = Scene::run;
	case Scene::run:
		mPlayer->Run();
		break;
	}
}
// ぷよクラスの定義
void Puyo::setConnectionState(Direction direction, bool connected) {
	mConnected[(int)direction] = connected;
}
void Puyo::Draw(const CResourceMgr* const resourceMgr) {
	if (mConnected[(int)Direction::right]) {
		if (mConnected[(int)Direction::top]) {
			if (mConnected[(int)Direction::left]) {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue1111), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red1111), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green1111), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink1111), TRUE);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue1110), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red1110), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green1110), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink1110), TRUE);
						break;
					}
				}
			} else {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue1101), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red1101), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green1101), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink1101), TRUE);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue1100), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red1100), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green1100), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink1100), TRUE);
						break;
					}
				}
			}
		} else {
			if (mConnected[(int)Direction::left]) {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue1011), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red1011), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green1011), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink1011), TRUE);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue1010), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red1010), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green1010), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink1010), TRUE);
						break;
					}
				}
			} else {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue1001), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red1001), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green1001), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink1001), TRUE);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue1000), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red1000), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green1000), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink1000), TRUE);
						break;
					}
				}
			}
		}
	} else {
		if (mConnected[(int)Direction::top]) {
			if (mConnected[(int)Direction::left]) {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue0111), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red0111), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green0111), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink0111), TRUE);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue0110), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red0110), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green0110), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink0110), TRUE);
						break;
					}
				}
			} else {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue0101), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red0101), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green0101), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink0101), TRUE);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue0100), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red0100), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green0100), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink0100), TRUE);
						break;
					}
				}
			}
		} else {
			if (mConnected[(int)Direction::left]) {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue0011), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red0011), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green0011), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink0011), TRUE);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue0010), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red0010), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green0010), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink0010), TRUE);
						break;
					}
				}
			} else {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue0001), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red0001), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green0001), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink0001), TRUE);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::blue0000), TRUE);
						return;
					case PuyoType::red:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::red0000), TRUE);
						return;
					case PuyoType::green:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::green0000), TRUE);
						break;
					case PuyoType::pink:
						DrawGraph(point.x, point.y, resourceMgr->getGraphicHandle((int)GraphicName::pink0000), TRUE);
						break;
					}
				}
			}
		}
	}
}
