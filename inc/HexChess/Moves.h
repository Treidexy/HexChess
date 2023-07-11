#pragma once

#include "HexChess/Board.h"
#include "HexChess/BitBoard.h"

namespace HexChess {
	extern BitBoard king_eyes[BoardLen];
	extern BitBoard knight_eyes[BoardLen];
	extern BitBoard pawn_eyes[BoardLen];

	extern BitBoard ray_eyes[BoardLen][DirectionCount];

	void InitEyes();
}