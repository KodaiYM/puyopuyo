#include "Game_define.h"
#include "ImagePuyoPuyo.h"

using namespace PuyoPuyo;
// ‚Õ‚æƒNƒ‰ƒX‚Ì’è‹`
void Puyo::setConnectionState(Direction direction, bool connected) {
	mConnected[(int)direction] = connected;
}
void Puyo::Draw() const {
	if (mConnected[(int)Direction::right]) {
		if (mConnected[(int)Direction::top]) {
			if (mConnected[(int)Direction::left]) {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue1111>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed1111>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen1111>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink1111>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue1110>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
						;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed1110>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
						;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen1110>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink1110>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				}
			} else {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue1101>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed1101>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen1101>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink1101>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue1100>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed1100>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen1100>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink1100>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				}
			}
		} else {
			if (mConnected[(int)Direction::left]) {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
						m_puyo = std::make_unique<ImageBlue1011>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed1011>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen1011>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink1011>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue1010>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed1010>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen1010>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink1010>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				}
			} else {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue1001>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed1001>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen1001>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink1001>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue1000>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed1000>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen1000>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink1000>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				}
			}
		}
	} else {
		if (mConnected[(int)Direction::top]) {
			if (mConnected[(int)Direction::left]) {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue0111>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed0111>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen0111>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink0111>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue0110>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed0110>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen0110>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink0110>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				}
			} else {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue0101>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed0101>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen0101>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink0101>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue0100>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed0100>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen0100>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink0100>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				}
			}
		} else {
			if (mConnected[(int)Direction::left]) {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue0011>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed0011>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen0011>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink0011>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue0010>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed0010>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen0010>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink0010>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				}
			} else {
				if (mConnected[(int)Direction::bottom]) {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue0001>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed0001>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen0001>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink0001>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				} else {
					switch (type) {
					case PuyoType::blue:
						m_puyo = std::make_unique<ImageBlue0000>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::red:
						m_puyo = std::make_unique<ImageRed0000>(point.x, point.y,
						                                        ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::green:
						m_puyo = std::make_unique<ImageGreen0000>(point.x, point.y,
						                                          ORIGIN::UPPER_LEFT);
						break;
					case PuyoType::pink:
						m_puyo = std::make_unique<ImagePink0000>(point.x, point.y,
						                                         ORIGIN::UPPER_LEFT);
						break;
					}
				}
			}
		}
	}
}
