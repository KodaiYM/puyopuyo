#pragma once

#include "Movie.h"

class MovieTitle final : public Movie<MovieTitle> {
public:
	static constexpr const char *s_path = "../puyopuyo/img/Opening/title.ogv";
};
