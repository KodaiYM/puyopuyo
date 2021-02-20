#pragma once

#include "Image.h"

class ImageSpriteStudio final : public Image<ImageSpriteStudio> {
public:
	static constexpr const char *path = "../puyopuyo/img/Opening/SpriteStudio";

	ImageSpriteStudio()
	    : Image(0, 0) {}
};
