#include "HexChess/Moves.h"
#include "HexChess/Position.h"

#include <iostream>

#include "HexChess/Directions.h"

using namespace HexChess;

BitBoard HexChess::king_eyes[BoardLen];
BitBoard HexChess::knight_eyes[BoardLen];
BitBoard HexChess::pawn_eyes[BoardLen];

BitBoard HexChess::ray_eyes[BoardLen][DirectionCount];

namespace {
	BitBoard KingEyes(int x, int y) {
		BitBoard bb = BitBoard();
		int eye_square;

		for (int i = 0; i < DirectionCount; i++) {
			if (SquareInDir(i, x, y, &eye_square)) {
				bb.set(eye_square);
			}
		}

		return bb;
	}

	BitBoard KnightEyes(int x, int y) {
		BitBoard bb = BitBoard();
		int eye_square;

		for (int i = 0; i < DirectionHalfCount; i++) {
			if (SquareInDir(i, x, y, &eye_square) && SquareInDir(i, FileOf(eye_square), RankOf(eye_square), &eye_square)) {
				int p = eye_square;
				if (SquareInDir(positive_modulo(i - 1, DirectionHalfCount), FileOf(p), RankOf(p), &eye_square)) {
					bb.set(eye_square);
				}
				if (SquareInDir((i + 1) % DirectionHalfCount, FileOf(p), RankOf(p), &eye_square)) {
					bb.set(eye_square);
				}
			}
		}

		return bb;
	}
}

void HexChess::InitEyes() {
	for (int x = 0; x < FileCount; x++) {
		for (int y = 0; y < RankCounts[x]; y++) {
			int square = SquareAt(x, y);
			king_eyes[square] = KingEyes(x, y);
			knight_eyes[square] = KnightEyes(x, y);
		}
	}
}