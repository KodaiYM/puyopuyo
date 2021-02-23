#include <DxLib.h>

#include "CTransFadein.h"
#include "Tokoton.h"

using namespace PuyoPuyo;
using namespace Tokoton;

/* ゲームクラスに対する定義 */
SceneTokoton::SceneTokoton(std::weak_ptr<ISceneChanger> changer)
    : CScene(std::move(changer))
    , m_puyopuyo(4, 12, 6, 38,
                 {{PointName::next_field, {276, 17}},
                  {PointName::field, {47, 13}},
                  {PointName::next, {278, 60}},
                  {PointName::nextnext, {291, 141}},
                  {PointName::current, {47 + 2 * 38, -25}}}) {}
void SceneTokoton::update() {
	/*
	const std::unordered_map<int, const char *> SoundPath = {
	    {(int)SoundName::chain1, "sound_effect/chain1.wav"},
	    {(int)SoundName::chain2, "sound_effect/chain2.wav"},
	    {(int)SoundName::chain3, "sound_effect/chain3.wav"},
	    {(int)SoundName::chain4, "sound_effect/chain4.wav"},
	    {(int)SoundName::chain5, "sound_effect/chain5.wav"},
	    {(int)SoundName::chain6, "sound_effect/chain6.wav"},
	    {(int)SoundName::chain7, "sound_effect/chain7.wav"},
	    {(int)SoundName::game_over, "sound_effect/game_over.wav"},
	    {(int)SoundName::land, "sound_effect/land.wav"},
	    {(int)SoundName::move, "sound_effect/move.wav"},
	    {(int)SoundName::rotate, "sound_effect/rotate.wav"},
	};*/
	m_puyopuyo.Run();
}
std::shared_ptr<ITransStart> SceneTokoton::getTransStart() const {
	return std::make_unique<CTransFadein>(60, CTransFadein::Mode::Update);
}
