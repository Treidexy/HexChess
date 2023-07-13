#include "HexChess/Position.h"

#include <iostream>

#include "HexChess/Directions.h"

using namespace HexChess;

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

	BitBoard InDirection(BitBoard checkersbb, int dir, int x, int y) {
		BitBoard bb;
		int square;
		while (SquareInDir(dir, x, y, &square)) {
			bb.set(square);

			if (checkersbb[square]) {
				break;
			}

			x = FileOf(square);
			y = RankOf(square);
		}

		return bb;
	}

	BitBoard RookEyes(BitBoard checkersbb, int x, int y) {
		BitBoard bb;
		for (int i = 0; i < DirectionHalfCount; i++) {
			bb |= InDirection(checkersbb, i, x, y);
		}

		return bb;
	}

	BitBoard BishopEyes(BitBoard checkersbb, int x, int y) {
		BitBoard bb;
		for (int i = DirectionHalfCount; i < DirectionCount; i++) {
			bb |= InDirection(checkersbb, i, x, y);
		}

		return bb;
	}

	BitBoard QueenEyes(BitBoard checkersbb, int x, int y) {
		BitBoard bb;
		for (int i = 0; i < DirectionCount; i++) {
			bb |= InDirection(checkersbb, i, x, y);
		}

		return bb;
	}

	MoveOptions FromBB(BitBoard enemy, BitBoard ally, BitBoard bb) {
		return MoveOptions { .quites = bb & ~ally & ~enemy, .attacks = bb & ~ally & enemy };
	}
}

MoveOptions Position::PieceMoves(int square) const {
	int color;
	if (colorbb[White][square]) {
		color = White;
	} else if (colorbb[Black][square]) {
		color = Black;
	} else {
		return MoveOptions {};
	}

	BitBoard ally = colorbb[color];
	BitBoard enemy = colorbb[!color];
	int piece = pieces[square];

	int file = FileOf(square);
	int rank = RankOf(square);

	switch (piece) {
	case King:
		return FromBB(enemy, ally, KingEyes(file, rank));
	case Queen:
		return FromBB(enemy, ally, QueenEyes(checkersbb, file, rank));
	case Rook:
		return FromBB(enemy, ally, RookEyes(checkersbb, file, rank));
	case Bishop:
		return FromBB(enemy, ally, BishopEyes(checkersbb, file, rank));
	case Knight:
		return FromBB(enemy, ally, KnightEyes(file, rank));
	}

	return MoveOptions {};
}