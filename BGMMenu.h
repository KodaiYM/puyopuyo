#pragma once

#include "BGM.h"

class BGMMenu final : public BGM<BGMMenu> {
public:
	static constexpr const char *path = "../puyopuyo/bgm/Menu/menu_title.wav";
};
