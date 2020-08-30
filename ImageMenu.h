#pragma once

#include "Image.h"

namespace Menu {
class ImageBackground final : public Image<ImageBackground> {
public:
	static constexpr const char *path = "../puyopuyo/img/Menu/background.png";
};
class ImageMenu final : public Image<ImageMenu> {
public:
	static constexpr const char *path = "../puyopuyo/img/Menu/menu.png";
};
class ImageBattle final : public Image<ImageBattle> {
public:
	static constexpr const char *path = "../puyopuyo/img/Menu/battle.png";
};
class ImageBattleSelected final : public Image<ImageBattleSelected> {
public:
	static constexpr const char *path =
	    "../puyopuyo/img/Menu/battle_selected.png";
};
class ImageTokoton final : public Image<ImageTokoton> {
public:
	static constexpr const char *path = "../puyopuyo/img/Menu/tokoton.png";
};
class ImageTokotonSelected final : public Image<ImageTokotonSelected> {
public:
	static constexpr const char *path =
	    "../puyopuyo/img/Menu/tokoton_selected.png";
};
} // namespace Menu
