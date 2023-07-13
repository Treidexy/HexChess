#pragma once

#include "HexChess/Board.h"

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

		bool Move(Square from, Square to);
		MoveOptions PieceMoves(Square) const;
	};
}