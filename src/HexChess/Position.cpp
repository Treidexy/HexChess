#include "HexChess/Position.h"

#include <iostream>

using namespace HexChess;

namespace {
	void SetPiece(Position* position, File file, Rank rank, Piece piece, Color color) {
		Square square = SquareAt(file, rank);
		position->pieces[square] = piece;
		position->colorbb[color].set(square);
		position->checkersbb.set(square);

		if (piece == King) {
			position->royalties[color].square = square;
		}
	}
}

Position Position::Default() {
	Position position = {};
	Position& p = position;

	// pawns
	SetPiece(&p, 1, 0, Pawn, White);
	SetPiece(&p, 2, 1, Pawn, White);
	SetPiece(&p, 3, 2, Pawn, White);
	SetPiece(&p, 4, 3, Pawn, White);
	SetPiece(&p, 5, 4, Pawn, White);
	SetPiece(&p, 6, 3, Pawn, White);
	SetPiece(&p, 7, 2, Pawn, White);
	SetPiece(&p, 8, 1, Pawn, White);
	SetPiece(&p, 9, 0, Pawn, White);

	SetPiece(&p, 2, 0, Rook, White);
	SetPiece(&p, 3, 0, Knight, White);
	SetPiece(&p, 4, 0, Queen, White);
	SetPiece(&p, 5, 0, Bishop, White);
	SetPiece(&p, 5, 1, Bishop, White);
	SetPiece(&p, 5, 2, Bishop, White);
	SetPiece(&p, 6, 0, King, White);
	SetPiece(&p, 7, 0, Knight, White);
	SetPiece(&p, 8, 0, Rook, White);


	SetPiece(&p, 1, 6, Pawn, Black);
	SetPiece(&p, 2, 6, Pawn, Black);
	SetPiece(&p, 3, 6, Pawn, Black);
	SetPiece(&p, 4, 6, Pawn, Black);
	SetPiece(&p, 5, 6, Pawn, Black);
	SetPiece(&p, 6, 6, Pawn, Black);
	SetPiece(&p, 7, 6, Pawn, Black);
	SetPiece(&p, 8, 6, Pawn, Black);
	SetPiece(&p, 9, 6, Pawn, Black);

	SetPiece(&p, 2, 7, Rook, Black);
	SetPiece(&p, 3, 8, Knight, Black);
	SetPiece(&p, 4, 9, Queen, Black);
	SetPiece(&p, 5, 10, Bishop, Black);
	SetPiece(&p, 5, 9, Bishop, Black);
	SetPiece(&p, 5, 8, Bishop, Black);
	SetPiece(&p, 6, 9, King, Black);
	SetPiece(&p, 7, 8, Knight, Black);
	SetPiece(&p, 8, 7, Rook, Black);

	p.CalcEyes(White);
	p.CalcEyes(Black);

	p.CalcRoyaltySafety(White);
	p.CalcRoyaltySafety(Black);

	p.opp = White;

	return position;
}

bool Position::ColorOf(Square square, Color* out_color) const {
	for (Color i = 0; i < ColorCount; i++) {
		if (colorbb[i][square]) {
			*out_color = i;
			return true;
		}
	}

	return false;
}

bool Position::DoMove(Square from, Square to) {
	if (from == to) {
		return false;
	}

	Color from_color;
	if (!ColorOf(from, &from_color)) {
		return false;
	}

	if (from_color != opp) {
		return false; // comment out for dbg
	}

	Piece from_piece = pieces[from];

	bool is_attack = false;
	MoveOptions move_options = PieceMoves(from);
	if (move_options.attacks[to]) {
		is_attack = true;
	} else if (move_options.quites[to]) {
	} else {
		return false; // comment out for dbg
	}

	Color eat_color;

	if (from_piece == Pawn) {
		if (to == passing_square) {
			assert(is_attack);
			assert(ColorOf(last_move, &eat_color));

			// eat piece
			colorbb[eat_color][last_move] = 0;
			checkersbb[last_move] = 0;
			pieces[last_move] = None;
		}

		if (RankOf(from) - RankOf(to) == 2) {
			passing_square = SquareAt(FileOf(to), RankOf(to) + 1);
		} else if (RankOf(to) - RankOf(from) == 2) {
			passing_square = SquareAt(FileOf(to), RankOf(to) - 1);
		} else {
			passing_square = -1;
		}
	} else {
		passing_square = -1;
	}

	// maybe eat piece
	if (ColorOf(to, &eat_color)) {
		colorbb[eat_color][to] = 0;
		checkersbb[to] = 0;
		pieces[to] = None;
	}

	// place new piece
	colorbb[from_color][to] = 1;
	checkersbb[to] = 1;
	pieces[to] = pieces[from];

	// remove old piece
	colorbb[from_color][from] = 0;
	checkersbb[from] = 0;
	pieces[from] = None;

	last_move = to;

	if (from_piece == King) {
		royalties[from_color].square = to;
	}

	CalcEyes(White);
	CalcEyes(Black);

	CalcRoyaltySafety(White);
	CalcRoyaltySafety(Black);

	opp = !opp;

	return true;
}