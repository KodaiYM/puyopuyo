#pragma once

#include "Image.h"

namespace PuyoPuyo {
class ImageBackground final : public Image<ImageBackground> {
public:
	static constexpr const char *s_path = "../puyopuyo/img/Game/background_a.png";

	ImageBackground()
	    : Image(0, 0) {}
};
class ImageFrame final : public Image<ImageFrame> {
public:
	static constexpr const char *s_path = "../puyopuyo/img/Game/frame_a.png";

	ImageFrame()
	    : Image(0, 0) {}
};
class ImageOjama final : public Image<ImageOjama> {
public:
	static constexpr const char *s_path = "../puyopuyo/img/Game/black_a.png";

	ImageOjama(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageCross final : public Image<ImageCross> {
public:
	static constexpr const char *s_path = "../puyopuyo/img/Game/cross_a.png";

	ImageCross(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageLeftNextFrame final : public Image<ImageLeftNextFrame> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/left_next_frame.png";

	ImageLeftNextFrame(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRightNextFrame final : public Image<ImageRightNextFrame> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/right_next_frame.png";

	ImageRightNextFrame(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};

#pragma region      Blue
class ImageBlue0000 final : public Image<ImageBlue0000> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue0000_a.png";

	ImageBlue0000(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue0001 final : public Image<ImageBlue0001> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue0001_a.png";

	ImageBlue0001(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue0010 final : public Image<ImageBlue0010> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue0010_a.png";

	ImageBlue0010(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue0011 final : public Image<ImageBlue0011> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue0011_a.png";

	ImageBlue0011(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue0100 final : public Image<ImageBlue0100> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue0100_a.png";

	ImageBlue0100(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue0101 final : public Image<ImageBlue0101> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue0101_a.png";

	ImageBlue0101(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue0110 final : public Image<ImageBlue0110> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue0110_a.png";

	ImageBlue0110(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue0111 final : public Image<ImageBlue0111> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue0111_a.png";

	ImageBlue0111(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue1000 final : public Image<ImageBlue1000> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue1000_a.png";

	ImageBlue1000(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue1001 final : public Image<ImageBlue1001> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue1001_a.png";

	ImageBlue1001(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue1010 final : public Image<ImageBlue1010> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue1010_a.png";

	ImageBlue1010(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue1011 final : public Image<ImageBlue1011> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue1011_a.png";

	ImageBlue1011(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue1100 final : public Image<ImageBlue1100> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue1100_a.png";

	ImageBlue1100(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue1101 final : public Image<ImageBlue1101> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue1101_a.png";

	ImageBlue1101(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue1110 final : public Image<ImageBlue1110> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue1110_a.png";

	ImageBlue1110(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageBlue1111 final : public Image<ImageBlue1111> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/blue/blue1111_a.png";

	ImageBlue1111(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
#pragma endregion

#pragma region       Green
class ImageGreen0000 final : public Image<ImageGreen0000> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green0000_a.png";

	ImageGreen0000(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen0001 final : public Image<ImageGreen0001> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green0001_a.png";

	ImageGreen0001(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen0010 final : public Image<ImageGreen0010> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green0010_a.png";

	ImageGreen0010(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen0011 final : public Image<ImageGreen0011> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green0011_a.png";

	ImageGreen0011(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen0100 final : public Image<ImageGreen0100> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green0100_a.png";

	ImageGreen0100(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen0101 final : public Image<ImageGreen0101> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green0101_a.png";

	ImageGreen0101(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen0110 final : public Image<ImageGreen0110> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green0110_a.png";

	ImageGreen0110(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen0111 final : public Image<ImageGreen0111> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green0111_a.png";

	ImageGreen0111(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen1000 final : public Image<ImageGreen1000> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green1000_a.png";

	ImageGreen1000(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen1001 final : public Image<ImageGreen1001> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green1001_a.png";

	ImageGreen1001(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen1010 final : public Image<ImageGreen1010> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green1010_a.png";

	ImageGreen1010(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen1011 final : public Image<ImageGreen1011> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green1011_a.png";

	ImageGreen1011(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen1100 final : public Image<ImageGreen1100> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green1100_a.png";

	ImageGreen1100(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen1101 final : public Image<ImageGreen1101> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green1101_a.png";

	ImageGreen1101(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen1110 final : public Image<ImageGreen1110> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green1110_a.png";

	ImageGreen1110(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageGreen1111 final : public Image<ImageGreen1111> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/green/green1111_a.png";

	ImageGreen1111(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
#pragma endregion

#pragma region      Pink
class ImagePink0000 final : public Image<ImagePink0000> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink0000_a.png";

	ImagePink0000(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink0001 final : public Image<ImagePink0001> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink0001_a.png";

	ImagePink0001(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink0010 final : public Image<ImagePink0010> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink0010_a.png";

	ImagePink0010(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink0011 final : public Image<ImagePink0011> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink0011_a.png";

	ImagePink0011(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink0100 final : public Image<ImagePink0100> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink0100_a.png";

	ImagePink0100(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink0101 final : public Image<ImagePink0101> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink0101_a.png";

	ImagePink0101(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink0110 final : public Image<ImagePink0110> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink0110_a.png";

	ImagePink0110(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink0111 final : public Image<ImagePink0111> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink0111_a.png";

	ImagePink0111(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink1000 final : public Image<ImagePink1000> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink1000_a.png";

	ImagePink1000(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink1001 final : public Image<ImagePink1001> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink1001_a.png";

	ImagePink1001(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink1010 final : public Image<ImagePink1010> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink1010_a.png";

	ImagePink1010(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink1011 final : public Image<ImagePink1011> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink1011_a.png";

	ImagePink1011(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink1100 final : public Image<ImagePink1100> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink1100_a.png";

	ImagePink1100(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink1101 final : public Image<ImagePink1101> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink1101_a.png";

	ImagePink1101(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink1110 final : public Image<ImagePink1110> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink1110_a.png";

	ImagePink1110(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImagePink1111 final : public Image<ImagePink1111> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/pink/pink1111_a.png";

	ImagePink1111(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
#pragma endregion

#pragma region     Red
class ImageRed0000 final : public Image<ImageRed0000> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red0000_a.png";

	ImageRed0000(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed0001 final : public Image<ImageRed0001> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red0001_a.png";

	ImageRed0001(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed0010 final : public Image<ImageRed0010> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red0010_a.png";

	ImageRed0010(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed0011 final : public Image<ImageRed0011> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red0011_a.png";

	ImageRed0011(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed0100 final : public Image<ImageRed0100> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red0100_a.png";

	ImageRed0100(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed0101 final : public Image<ImageRed0101> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red0101_a.png";

	ImageRed0101(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed0110 final : public Image<ImageRed0110> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red0110_a.png";

	ImageRed0110(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed0111 final : public Image<ImageRed0111> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red0111_a.png";

	ImageRed0111(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed1000 final : public Image<ImageRed1000> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red1000_a.png";

	ImageRed1000(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed1001 final : public Image<ImageRed1001> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red1001_a.png";

	ImageRed1001(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed1010 final : public Image<ImageRed1010> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red1010_a.png";

	ImageRed1010(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed1011 final : public Image<ImageRed1011> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red1011_a.png";

	ImageRed1011(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed1100 final : public Image<ImageRed1100> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red1100_a.png";

	ImageRed1100(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed1101 final : public Image<ImageRed1101> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red1101_a.png";

	ImageRed1101(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed1110 final : public Image<ImageRed1110> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red1110_a.png";

	ImageRed1110(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
class ImageRed1111 final : public Image<ImageRed1111> {
public:
	static constexpr const char *s_path =
	    "../puyopuyo/img/Game/red/red1111_a.png";

	ImageRed1111(int x, int y, ORIGIN origin)
	    : Image(x, y, origin) {}
};
#pragma endregion
} // namespace PuyoPuyo
