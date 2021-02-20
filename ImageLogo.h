#pragma once

#include "Image.h"

class ImageLogo final : public Image<ImageLogo> {
public:
	static constexpr const char *path = "../puyopuyo/img/Opening/logo.png";

	ImageLogo()
	    : Image(0, 0) {}
};
