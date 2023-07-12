#pragma once

#include <bitset>

#include "HexChess/Board.h"

namespace HexChess {
	struct BitBoard: public std::bitset<BoardLen> {
		constexpr BitBoard() : std::bitset<BoardLen>() {}
		BitBoard(int square) : std::bitset<BoardLen>() {
			set(square, true);
		}
		explicit BitBoard(const char*p) : std::bitset<BoardLen>(p) {}

		BitBoard& click(int file, int rank) {
			if (InBounds(file, rank)) {
				return (BitBoard&) set(SquareAt(file, rank));
			} else {
				return *this;
			}
		}
	};

	static const BitBoard UsableBoard {"0000011111100001111111000111111110011111111101111111111111111111110111111111100111111111000111111110000111111100000111111"};
}