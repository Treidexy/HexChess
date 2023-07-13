#pragma once

#include "HexChess/Board.h"

namespace HexChess {
	struct MoveOptions {
		BitBoard quites;
		BitBoard attacks;
	};

	struct Position {
		Piece pieces[BoardLen];
		BitBoard checkersbb;
		BitBoard colorbb[ColorCount];

		Square passing_square;

		static Position Default();

		bool ColorOf(Square, Color* out_color) const;

		// returns true if move was made
		bool DoMove(Square from, Square to);
		MoveOptions PieceMoves(Square) const;
	};
}