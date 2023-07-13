#pragma once

#include "HexChess/Board.h"
#include "HexChess/BitBoard.h"

namespace HexChess {
	struct MoveOptions {
		BitBoard quites;
		BitBoard attacks;
	};

	struct Position {
		int pieces[BoardLen];
		BitBoard checkersbb;
		BitBoard colorbb[ColorCount];

		static Position Default();

		MoveOptions PieceMoves(int square) const;
	};
}