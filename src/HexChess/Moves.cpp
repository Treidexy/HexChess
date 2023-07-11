#include "HexChess/Moves.h"
#include "HexChess/Position.h"

#include <iostream>

using namespace HexChess;

BitBoard HexChess::king_eyes[BoardLen];
BitBoard HexChess::knight_eyes[BoardLen];
BitBoard HexChess::pawn_eyes[BoardLen];

BitBoard HexChess::ray_eyes[BoardLen][DirectionCount];

namespace {
	BitBoard BitIfInBounds(int x, int y) {
		if (InBounds(x, y)) {
			return BitBoard(SquareAt(x, y));
		} else {
			return BitBoard();
		}
	}

	BitBoard KnightEyes(int x, int y) {
		BitBoard bb = BitBoard();

		bb |= BitIfInBounds(x - 1, y + 2);
		bb |= BitIfInBounds(x + 1, y + 2);
		bb |= BitIfInBounds(x + 2, y + 1);
		bb |= BitIfInBounds(x + 3, y - 1);
		bb |= BitIfInBounds(x + 3, y - 2);
		bb |= BitIfInBounds(x + 2, y - 3);
		bb |= BitIfInBounds(x + 1, y - 3);
		bb |= BitIfInBounds(x - 1, y - 3);
		bb |= BitIfInBounds(x - 2, y - 3);
		bb |= BitIfInBounds(x - 3, y - 2);
		bb |= BitIfInBounds(x - 3, y - 1);
		bb |= BitIfInBounds(x - 2, y + 1);

		return bb;
	}
}

void HexChess::InitEyes() {
	for (int x = 0; x < FileCount; x++) {
		for (int y = 0; y < RankCounts[x]; y++) {
			knight_eyes[SquareAt(x, y)] = KnightEyes(x, y);
		}
	}

	std::cout << knight_eyes[0].high << knight_eyes[0].low << "\n";
}