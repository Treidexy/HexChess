#include "HexChess/Position.h"

#include <iostream>

#include "HexChess/Directions.h"

using namespace HexChess;

// MAYBE: maybe move to separate file
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

	BitBoard PawnEyes(File file, Rank rank, Color color) {
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

		Square to;
		BitBoard out = BitBoard();

		if (SquareInDir(eat_east, file, rank, &to)) {
			out[to] = 1;
		}
		if (SquareInDir(eat_west, file, rank, &to)) {
			out[to] = 1;
		}

		return out;
	}

	MoveOptions PawnMoves(BitBoard enemy, BitBoard ally, Square square, Color color, Square passing_square) {
		MoveOptions move_options = {};

		File file = FileOf(square);
		Rank rank = RankOf(square);

		Square to;

		Direction forward;
		if (color == White) {
			forward = LatNorth;
		} else if (color == Black) {
			forward = LatSouth;
		} else {
			abort();
		}

		move_options.attacks |= PawnEyes(file, rank, color);

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

	if (piece == King) {
		return FromBB(enemy, ally, KingEyes(file, rank) & ~eyesbb[!color]);
	}

	if (royalties[color].in_double_check) {
		return MoveOptions {};
	}

	MoveOptions move_options;

	switch (piece) {
	case Queen:
		move_options = FromBB(enemy, ally, QueenEyes(checkersbb, file, rank));
		break;
	case Rook:
		move_options = FromBB(enemy, ally, RookEyes(checkersbb, file, rank));
		break;
	case Bishop:
		move_options = FromBB(enemy, ally, BishopEyes(checkersbb, file, rank));
		break;
	case Knight:
		move_options = FromBB(enemy, ally, KnightEyes(file, rank));
		break;
	case Pawn:
		move_options = PawnMoves(enemy, ally, square, color, passing_square);
		break;

	default:
		return MoveOptions {};
	}

	if (royalties[color].check_ray.any()) {
		move_options.quites &= royalties[color].check_ray;
		move_options.attacks &= royalties[color].check_ray;
	}

	for (Direction i = 0; i < DirectionCount; i++) {
		if (royalties[color].pin_rays[i][square]) {
			move_options.quites &= royalties[color].pin_rays[i];
			move_options.attacks &= royalties[color].pin_rays[i];
		}
	}

	return move_options;
}

void Position::CalcEyes(Color color) {
	BitBoard& eyes = eyesbb[color];
	eyes.reset();

	BitBoard it = colorbb[color];
	while (it.any()) {
		Square square = PopWeak(&it);

		BitBoard ally = colorbb[color];
		BitBoard enemy = colorbb[!color];
		Piece piece = pieces[square];

		File file = FileOf(square);
		Rank rank = RankOf(square);

		switch (piece) {
		case King:
			eyes |= KingEyes(file, rank);
			break;
		case Queen:
			eyes |= QueenEyes(checkersbb, file, rank);
			break;
		case Rook:
			eyes |= RookEyes(checkersbb, file, rank);
			break;
		case Bishop:
			eyes |= BishopEyes(checkersbb, file, rank);
			break;
		case Knight:
			eyes |= KnightEyes(file, rank);
			break;
		case Pawn:
			eyes |= PawnEyes(file, rank, color);
			break;
		}
	}
}

void Position::CalcRoyaltySafety(Color color) {
	int check_count = 0;

	const Square square = royalties[color].square;
	const File file = FileOf(square);
	const Rank rank = RankOf(square);
	
	const BitBoard ally = colorbb[color];
	const BitBoard enemy = colorbb[!color];

	BitBoard &check_ray = royalties[color].check_ray;
	BitBoard (&pin_rays)[DirectionCount] = royalties[color].pin_rays;

	// knights
	BitBoard knight_potential_attackers = KnightEyes(file, rank) & enemy;
	while (knight_potential_attackers.any()) {
		Square knight_square = PopWeak(&knight_potential_attackers);
		if (pieces[knight_square] == Knight) {
			check_ray = BitBoard().set(knight_square);
			check_count++;
		}
	}

	// sliding
	for (Direction i = 0; i < DirectionCount; i++) {
		BitBoard ray = InDirection(enemy, i, file, rank);
		if ((ray & enemy).none()) {
			continue;
		}
		if (!PieceCanSlideInDir(pieces[WeakBit(ray & enemy)], i)) {
			continue;
		}

		BitBoard pinned = ray & ally;
		if (pinned.count() == 0) {
			check_ray = ray;
			check_count++;
		} else if (pinned.count() == 1) {
			pin_rays[i] = check_ray;
		}
	}
	
	// pawns
	BitBoard pawn_potential_attackers = PawnEyes(file, rank, !color) & enemy;
	while (pawn_potential_attackers.any()) {
		Square pawn_square = PopWeak(&pawn_potential_attackers);
		if (pieces[pawn_square] == Pawn) {
			check_ray = BitBoard().set(pawn_square);
			check_count++;
		}
	}

	royalties[color].in_double_check = check_count > 1;
}