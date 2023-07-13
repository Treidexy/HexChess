#include "HexChess/Position.h"

#include <iostream>

#include "HexChess/Directions.h"

using namespace HexChess;

namespace {
	BitBoard KingEyes(File x, Rank y) {
		BitBoard bb = BitBoard();
		Square eye_square;

		for (Direction i = 0; i < DirectionCount; i++) {
			if (SquareInDir(i, x, y, &eye_square)) {
				bb.set(eye_square);
			}
		}

		return bb;
	}

	BitBoard KnightEyes(File x, Rank y) {
		BitBoard bb = BitBoard();
		Square eye_square;

		for (Direction i = 0; i < DirectionHalfCount; i++) {
			if (SquareInDir(i, x, y, &eye_square) && SquareInDir(i, FileOf(eye_square), RankOf(eye_square), &eye_square)) {
				Square p = eye_square;
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

	BitBoard InDirection(BitBoard checkersbb, Direction dir, File x, Rank y) {
		BitBoard bb;
		Square square;
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

	BitBoard RookEyes(BitBoard checkersbb, File x, Rank y) {
		BitBoard bb;
		for (Direction i = 0; i < DirectionHalfCount; i++) {
			bb |= InDirection(checkersbb, i, x, y);
		}

		return bb;
	}

	BitBoard BishopEyes(BitBoard checkersbb, File x, Rank y) {
		BitBoard bb;
		for (Direction i = DirectionHalfCount; i < DirectionCount; i++) {
			bb |= InDirection(checkersbb, i, x, y);
		}

		return bb;
	}

	BitBoard QueenEyes(BitBoard checkersbb, File x, Rank y) {
		BitBoard bb;
		for (Direction i = 0; i < DirectionCount; i++) {
			bb |= InDirection(checkersbb, i, x, y);
		}

		return bb;
	}

	MoveOptions FromBB(BitBoard enemy, BitBoard ally, BitBoard bb) {
		return MoveOptions { .quites = bb & ~ally & ~enemy, .attacks = bb & ~ally & enemy };
	}
}

MoveOptions Position::PieceMoves(Square square) const {
	Color color;
	if (colorbb[White][square]) {
		color = White;
	} else if (colorbb[Black][square]) {
		color = Black;
	} else {
		return MoveOptions {};
	}

	BitBoard ally = colorbb[color];
	BitBoard enemy = colorbb[!color];
	Piece piece = pieces[square];

	File file = FileOf(square);
	Rank rank = RankOf(square);

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