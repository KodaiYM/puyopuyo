#pragma once

#include "Movie.h"

class MovieTitle final : public Movie<MovieTitle> {
public:
	static constexpr const char *path = "../puyopuyo/img/Opening/title.ogv";
};
