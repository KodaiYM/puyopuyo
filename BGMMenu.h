#pragma once

#include "BGM.h"

class BGMMenu final : public BGM<BGMMenu> {
public:
	static constexpr const char *s_path = "../puyopuyo/bgm/Menu/menu_title.wav";
};
