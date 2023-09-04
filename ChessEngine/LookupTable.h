#pragma once
#include <cstdint>

namespace ChessTables {



	/* ROW MAJOR ORDER,
	*
	* a1 (square 0) -> b1 (square 1) -> c1 (square 2) -> ... -> h1 (square 7)
	a2 (square 8) -> b2 (square 9) -> c2 (square 10) -> ... -> h2 (square 15)
	...
	a8 (square 56) -> b8 (square 57) -> c8 (square 58) -> ... -> h8 (square 63)

	*/
	static enum rankIndex {
		RANK_1 = 7,
		RANK_2 = 6,
		RANK_3 = 5,
		RANK_4 = 4,
		RANK_5 = 3,
		RANK_6 = 2,
		RANK_7 = 1,
		RANK_8 = 0
	};

	static enum fileIndex {
		RANK_1 = 7,
		RANK_2 = 6,
		RANK_3 = 5,
		RANK_4 = 4,
		RANK_5 = 3,
		RANK_6 = 2,
		RANK_7 = 1,
		RANK_8 = 0
	};


	static const std::uint64_t maskRank[8] = {
		0b0000000000000000000000000000000000000000000000000000000011111111,
		0b0000000000000000000000000000000000000000000000001111111100000000,
		0b0000000000000000000000000000000000000000111111110000000000000000,
		0b0000000000000000000000000000000011111111000000000000000000000000,
		0b0000000000000000000000001111111100000000000000000000000000000000,
		0b0000000000000000111111110000000000000000000000000000000000000000,
		0b0000000011111111000000000000000000000000000000000000000000000000,
		0b1111111100000000000000000000000000000000000000000000000000000000,
	};


	static const std::uint64_t maskFile[8] = {
		0b0000000100000001000000010000000100000001000000010000000100000001,
		0b0000001000000010000000100000001000000010000000100000001000000010,
		0b0000010000000100000001000000010000000100000001000000010000000100,
		0b0000100000001000000010000000100000001000000010000000100000001000,
		0b0001000000010000000100000001000000010000000100000001000000010000,
		0b0010000000100000001000000010000000100000001000000010000000100000,
		0b0100000001000000010000000100000001000000010000000100000001000000,
		0b1000000010000000100000001000000010000000100000001000000010000000,
	};


	static const std::uint64_t knightMoveTable[64] = {
		0b0000000000000000000000000000000000000000000000100000010000000000,
		0b0000000000000000000000000000000000000000000001010000100000000000,
		0b0000000000000000000000000000000000000000000010100001000100000000,
		0b0000000000000000000000000000000000000000000101000010001000000000,
		0b0000000000000000000000000000000000000000001010000100010000000000,
		0b0000000000000000000000000000000000000000010100001000100000000000,
		0b0000000000000000000000000000000000000000101000000001000000000000,
		0b0000000000000000000000000000000000000000010000000010000000000000,
		0b0000000000000000000000000000000000000010000001000000000000000100,
		0b0000000000000000000000000000000000000101000010000000000000001000,
		0b0000000000000000000000000000000000001010000100010000000000010001,
		0b0000000000000000000000000000000000010100001000100000000000100010,
		0b0000000000000000000000000000000000101000010001000000000001000100,
		0b0000000000000000000000000000000001010000100010000000000010001000,
		0b0000000000000000000000000000000010100000000100000000000000010000,
		0b0000000000000000000000000000000001000000001000000000000000100000,
		0b0000000000000000000000000000001000000100000000000000010000000010,
		0b0000000000000000000000000000010100001000000000000000100000000101,
		0b0000000000000000000000000000101000010001000000000001000100001010,
		0b0000000000000000000000000001010000100010000000000010001000010100,
		0b0000000000000000000000000010100001000100000000000100010000101000,
		0b0000000000000000000000000101000010001000000000001000100001010000,
		0b0000000000000000000000001010000000010000000000000001000010100000,
		0b0000000000000000000000000100000000100000000000000010000001000000,
		0b0000000000000000000000100000010000000000000001000000001000000000,
		0b0000000000000000000001010000100000000000000010000000010100000000,
		0b0000000000000000000010100001000100000000000100010000101000000000,
		0b0000000000000000000101000010001000000000001000100001010000000000,
		0b0000000000000000001010000100010000000000010001000010100000000000,
		0b0000000000000000010100001000100000000000100010000101000000000000,
		0b0000000000000000101000000001000000000000000100001010000000000000,
		0b0000000000000000010000000010000000000000001000000100000000000000,
		0b0000000000000010000001000000000000000100000000100000000000000000,
		0b0000000000000101000010000000000000001000000001010000000000000000,
		0b0000000000001010000100010000000000010001000010100000000000000000,
		0b0000000000010100001000100000000000100010000101000000000000000000,
		0b0000000000101000010001000000000001000100001010000000000000000000,
		0b0000000001010000100010000000000010001000010100000000000000000000,
		0b0000000010100000000100000000000000010000101000000000000000000000,
		0b0000000001000000001000000000000000100000010000000000000000000000,
		0b0000001000000100000000000000010000000010000000000000000000000000,
		0b0000010100001000000000000000100000000101000000000000000000000000,
		0b0000101000010001000000000001000100001010000000000000000000000000,
		0b0001010000100010000000000010001000010100000000000000000000000000,
		0b0010100001000100000000000100010000101000000000000000000000000000,
		0b0101000010001000000000001000100001010000000000000000000000000000,
		0b1010000000010000000000000001000010100000000000000000000000000000,
		0b0100000000100000000000000010000001000000000000000000000000000000,
		0b0000010000000000000001000000001000000000000000000000000000000000,
		0b0000100000000000000010000000010100000000000000000000000000000000,
		0b0001000100000000000100010000101000000000000000000000000000000000,
		0b0010001000000000001000100001010000000000000000000000000000000000,
		0b0100010000000000010001000010100000000000000000000000000000000000,
		0b1000100000000000100010000101000000000000000000000000000000000000,
		0b0001000000000000000100001010000000000000000000000000000000000000,
		0b0010000000000000001000000100000000000000000000000000000000000000,
		0b0000000000000100000000100000000000000000000000000000000000000000,
		0b0000000000001000000001010000000000000000000000000000000000000000,
		0b0000000000010001000010100000000000000000000000000000000000000000,
		0b0000000000100010000101000000000000000000000000000000000000000000,
		0b0000000001000100001010000000000000000000000000000000000000000000,
		0b0000000010001000010100000000000000000000000000000000000000000000,
		0b0000000000010000101000000000000000000000000000000000000000000000,
		0b0000000000100000010000000000000000000000000000000000000000000000
	};


	static const std::uint64_t kingMoveTable[64] = {
		0b0000000000000000000000000000000000000000000000000000001100000010,
		0b0000000000000000000000000000000000000000000000000000011100000101,
		0b0000000000000000000000000000000000000000000000000000111000001010,
		0b0000000000000000000000000000000000000000000000000001110000010100,
		0b0000000000000000000000000000000000000000000000000011100000101000,
		0b0000000000000000000000000000000000000000000000000111000001010000,
		0b0000000000000000000000000000000000000000000000001110000010100000,
		0b0000000000000000000000000000000000000000000000001100000001000000,
		0b0000000000000000000000000000000000000000000000110000001000000011,
		0b0000000000000000000000000000000000000000000001110000010100000111,
		0b0000000000000000000000000000000000000000000011100000101000001110,
		0b0000000000000000000000000000000000000000000111000001010000011100,
		0b0000000000000000000000000000000000000000001110000010100000111000,
		0b0000000000000000000000000000000000000000011100000101000001110000,
		0b0000000000000000000000000000000000000000111000001010000011100000,
		0b0000000000000000000000000000000000000000110000000100000011000000,
		0b0000000000000000000000000000000000000011000000100000001100000000,
		0b0000000000000000000000000000000000000111000001010000011100000000,
		0b0000000000000000000000000000000000001110000010100000111000000000,
		0b0000000000000000000000000000000000011100000101000001110000000000,
		0b0000000000000000000000000000000000111000001010000011100000000000,
		0b0000000000000000000000000000000001110000010100000111000000000000,
		0b0000000000000000000000000000000011100000101000001110000000000000,
		0b0000000000000000000000000000000011000000010000001100000000000000,
		0b0000000000000000000000000000001100000010000000110000000000000000,
		0b0000000000000000000000000000011100000101000001110000000000000000,
		0b0000000000000000000000000000111000001010000011100000000000000000,
		0b0000000000000000000000000001110000010100000111000000000000000000,
		0b0000000000000000000000000011100000101000001110000000000000000000,
		0b0000000000000000000000000111000001010000011100000000000000000000,
		0b0000000000000000000000001110000010100000111000000000000000000000,
		0b0000000000000000000000001100000001000000110000000000000000000000,
		0b0000000000000000000000110000001000000011000000000000000000000000,
		0b0000000000000000000001110000010100000111000000000000000000000000,
		0b0000000000000000000011100000101000001110000000000000000000000000,
		0b0000000000000000000111000001010000011100000000000000000000000000,
		0b0000000000000000001110000010100000111000000000000000000000000000,
		0b0000000000000000011100000101000001110000000000000000000000000000,
		0b0000000000000000111000001010000011100000000000000000000000000000,
		0b0000000000000000110000000100000011000000000000000000000000000000,
		0b0000000000000011000000100000001100000000000000000000000000000000,
		0b0000000000000111000001010000011100000000000000000000000000000000,
		0b0000000000001110000010100000111000000000000000000000000000000000,
		0b0000000000011100000101000001110000000000000000000000000000000000,
		0b0000000000111000001010000011100000000000000000000000000000000000,
		0b0000000001110000010100000111000000000000000000000000000000000000,
		0b0000000011100000101000001110000000000000000000000000000000000000,
		0b0000000011000000010000001100000000000000000000000000000000000000,
		0b0000001100000010000000110000000000000000000000000000000000000000,
		0b0000011100000101000001110000000000000000000000000000000000000000,
		0b0000111000001010000011100000000000000000000000000000000000000000,
		0b0001110000010100000111000000000000000000000000000000000000000000,
		0b0011100000101000001110000000000000000000000000000000000000000000,
		0b0111000001010000011100000000000000000000000000000000000000000000,
		0b1110000010100000111000000000000000000000000000000000000000000000,
		0b1100000001000000110000000000000000000000000000000000000000000000,
		0b0000001000000011000000000000000000000000000000000000000000000000,
		0b0000010100000111000000000000000000000000000000000000000000000000,
		0b0000101000001110000000000000000000000000000000000000000000000000,
		0b0001010000011100000000000000000000000000000000000000000000000000,
		0b0010100000111000000000000000000000000000000000000000000000000000,
		0b0101000001110000000000000000000000000000000000000000000000000000,
		0b1010000011100000000000000000000000000000000000000000000000000000,
		0b0100000011000000000000000000000000000000000000000000000000000000
	}

}