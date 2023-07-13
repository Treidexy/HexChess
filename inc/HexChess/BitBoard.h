#pragma once

#include <bitset>

#include "HexChess/Board.h"

namespace HexChess {
	using BitBoard = std::bitset<BoardLen>;

	static const BitBoard UsableBoard {"0000011111100001111111000111111110011111111101111111111111111111110111111111100111111111000111111110000111111100000111111"};
}