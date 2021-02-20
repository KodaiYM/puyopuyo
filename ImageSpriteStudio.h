#pragma once

#include "Image.h"

class ImageSpriteStudio final : public Image<ImageSpriteStudio> {
public:
	static constexpr const char *s_path = "../puyopuyo/img/Opening/SpriteStudio";

	ImageSpriteStudio()
	    : Image(0, 0) {}
};
