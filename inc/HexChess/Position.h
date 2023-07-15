#pragma once

#include "HexChess/Board.h"
#include "HexChess/BitBoard.h"

namespace HexChess {
	struct MoveOptions {
		BitBoard quites;
		BitBoard attacks; // = eyes & enemy
	};

	struct Royalty {
		Square square;

		bool in_double_check;
		BitBoard check_ray; // includes attacking piece
		BitBoard pin_rays[DirectionCount]; // includes attacking piece
	};

	struct Position {
		Piece pieces[BoardLen];
		BitBoard checkersbb;
		BitBoard colorbb[ColorCount];
		BitBoard eyesbb[ColorCount];

		Square passing_square;
		Square last_move;

		Royalty royalties[ColorCount];

		Color opp;

		static Position Default();

		bool ColorOf(Square, Color* out_color) const;

		// returns true if move was made
		bool DoMove(Square from, Square to);
		MoveOptions PieceMoves(Square) const;

		void CalcRoyaltySafety(Color); // might change name later
		void CalcEyes(Color);
	};
}