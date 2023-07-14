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
		BitBoard bb = BitBoard();
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
		BitBoard bb = BitBoard();
		for (Direction i = 0; i < DirectionHalfCount; i++) {
			bb |= InDirection(checkersbb, i, x, y);
		}

		return bb;
	}

	BitBoard BishopEyes(BitBoard checkersbb, File x, Rank y) {
		BitBoard bb = BitBoard();
		for (Direction i = DirectionHalfCount; i < DirectionCount; i++) {
			bb |= InDirection(checkersbb, i, x, y);
		}

		return bb;
	}

	BitBoard QueenEyes(BitBoard checkersbb, File x, Rank y) {
		BitBoard bb = BitBoard();
		for (Direction i = 0; i < DirectionCount; i++) {
			bb |= InDirection(checkersbb, i, x, y);
		}

		return bb;
	}

	MoveOptions FromBB(BitBoard enemy, BitBoard ally, BitBoard bb) {
		return MoveOptions { .quites = bb & ~ally & ~enemy, .attacks = bb & ~ally & enemy };
	}

	MoveOptions PawnMoves(BitBoard enemy, BitBoard ally, Square square, Color color, Square passing_square) {
		MoveOptions move_options = {};

		File file = FileOf(square);
		Rank rank = RankOf(square);

		Square to;

		Direction eat_east;
		Direction eat_west;
		Direction forward;

		if (color == White) {
			eat_east = LatNorthEast;
			eat_west = LatNorthWest;
			forward = LatNorth;
		} else if (color == Black) {
			eat_east = LatSouthEast;
			eat_west = LatSouthWest;
			forward = LatSouth;
		} else {
			abort();
		}

		if (SquareInDir(eat_east, file, rank, &to)) {
			move_options.attacks[to] = enemy[to] || passing_square == to;
		}
		if (SquareInDir(eat_west, file, rank, &to)) {
			move_options.attacks[to] = enemy[to] || passing_square == to;
		}

		if (SquareInDir(forward, file, rank, &to) && !(enemy | ally)[to]) {
			move_options.quites.set(to);

			if (PawnBoosts[color][square] && SquareInDir(forward, FileOf(to), RankOf(to), &to) && !(enemy | ally)[to]) {
				move_options.quites.set(to);
			}
		}

		return move_options;
	}
}

MoveOptions Position::PieceMoves(Square square) const {
	Color color;
	if (!ColorOf(square, &color)) {
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
	case Pawn:
		return PawnMoves(enemy, ally, square, color, passing_square);
	}

	return MoveOptions {};
}