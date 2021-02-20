#pragma once

#include "Image.h"

namespace Menu {
class ImageBackground final : public Image<ImageBackground> {
public:
	static constexpr const char *path = "../puyopuyo/img/Menu/background.png";

	ImageBackground()
	    : Image(0, 0) {}
};
class ImageMenu final : public Image<ImageMenu> {
public:
	static constexpr const char *path = "../puyopuyo/img/Menu/menu.png";

	ImageMenu(int x, int y)
	    : Image(x, y) {}
};
class ImageBattle final : public Image<ImageBattle> {
public:
	static constexpr const char *path = "../puyopuyo/img/Menu/battle.png";

	ImageBattle(int x, int y)
	    : Image(x, y) {}
};
class ImageBattleSelected final : public Image<ImageBattleSelected> {
public:
	static constexpr const char *path =
	    "../puyopuyo/img/Menu/battle_selected.png";

	ImageBattleSelected(int x, int y)
	    : Image(x, y) {}
};
class ImageTokoton final : public Image<ImageTokoton> {
public:
	static constexpr const char *path = "../puyopuyo/img/Menu/tokoton.png";

	ImageTokoton(int x, int y)
	    : Image(x, y) {}
};
class ImageTokotonSelected final : public Image<ImageTokotonSelected> {
public:
	static constexpr const char *path =
	    "../puyopuyo/img/Menu/tokoton_selected.png";

	ImageTokotonSelected(int x, int y)
	    : Image(x, y) {}
};
} // namespace Menu
