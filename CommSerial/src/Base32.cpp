#include "Base32.h"

namespace comser {
	static const uint8_t ENCODE_ARR[32] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G',
	'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
	'V', 'W', 'X', 'Y', 'Z', '2', '3', '4', '5', '6', '7' };

	static const uint8_t DECODE_ARR[91] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 26, 27, 28, 29, 30, 31, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };

	Base32::Base32()
	{
	}

	void Base32::encode(std::vector<uint8_t>& in, std::vector<uint8_t>& out)
	{
		double outSize = in.size() * (8.0 / 5.0);
		if (outSize > (int)outSize) {
			outSize = ((int)outSize) + 1;
		}
		while (in.size() % 5 != 0) {
			in.push_back(0);
		}
		out.reserve((int)(in.size() * (4.0 / 3.0)));
		for (int i = 0; i < in.size(); i += 5) {
			out.push_back(ENCODE_ARR[in.at(i) & 0x1F]);
			out.push_back(ENCODE_ARR[((in.at(i) & 0xE0) >> 5) | ((in.at(i + 1) & 0x03) << 3)]);
			out.push_back(ENCODE_ARR[(in.at(i + 1) & 0x7C) >> 2]);
			out.push_back(ENCODE_ARR[((in.at(i + 1) & 0x80) >> 7) | ((in.at(i + 2) & 0x0F) << 1)]);
			out.push_back(ENCODE_ARR[((in.at(i + 2) & 0xF0) >> 4) | ((in.at(i + 3) & 0x01) << 4)]);
			out.push_back(ENCODE_ARR[(in.at(i + 3) & 0x3E) >> 1]);
			out.push_back(ENCODE_ARR[((in.at(i + 3) & 0XC0) >> 6) | ((in.at(i + 4) & 0x07) << 2)]);
			out.push_back(ENCODE_ARR[(in.at(i + 4) & 0xF8) >> 3]);
		}
		out.resize((int)outSize);
	}

	void Base32::decode(std::vector<uint8_t>& in, std::vector<uint8_t>& out)
	{
		int outSize = in.size() * (5.0 / 8.0);
		while (in.size() % 8 != 0) {
			in.push_back(0);
		}
		out.reserve(in.size() * (5.0 / 8.0));
		for (int i = 0; i < in.size(); i += 8) {
			out.push_back((DECODE_ARR[in.at(i)] & 0x1F) | ((DECODE_ARR[in.at(i + 1)] & 0x03) << 5));
			out.push_back(((DECODE_ARR[in.at(i + 1)] & 0x18) >> 3) | ((DECODE_ARR[in.at(i + 2)] & 0x1F) << 2) | ((DECODE_ARR[in.at(i + 3)] & 0x01) << 7));
			out.push_back(((DECODE_ARR[in.at(i + 3)] & 0x1E) >> 1) | ((DECODE_ARR[in.at(i + 4)] & 0x0F) << 4));
			out.push_back(((DECODE_ARR[in.at(i + 4)] & 0x10) >> 4) | ((DECODE_ARR[in.at(i + 5)] & 0x1F) << 1) | ((DECODE_ARR[in.at(i + 6)] & 0x03) << 6));
			out.push_back(((DECODE_ARR[in.at(i + 6)] & 0x1C) >> 2) | ((DECODE_ARR[in.at(i + 7)] & 0x1F) << 3));
		}
		out.resize((int)outSize);
	}


	Base32::~Base32()
	{
	}
}
