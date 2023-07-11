#pragma once

#include "HexChess/Board.h"
#include "HexChess/BitBoard.h"

namespace HexChess {
	struct Position {
		Piece pieces[BoardLen];

		static Position Default();

		BitBoard PieceMoves(int square) const;
		BitBoard PieceAttacks(int square) const;
	};
}