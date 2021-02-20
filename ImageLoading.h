#pragma once

#include "Image.h"

class ImageLoading final : Image<ImageLoading> {
public:
	static constexpr const char *path = "../puyopuyo/img/loading.jpg";

	ImageLoading()
	    : Image(0, 0) {}
};
