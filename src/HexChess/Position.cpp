#include "HexChess/Position.h"

#include <iostream>

using namespace HexChess;

namespace {
	void SetPiece(Position* position, File file, Rank rank, Piece piece, Color color) {
		Square square = SquareAt(file, rank);
		position->pieces[square] = piece;
		position->colorbb[color].set(square);
		position->checkersbb.set(square);
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

	bool is_attack = false;
	MoveOptions move_options = PieceMoves(from);
	if (move_options.attacks[to]) {
		is_attack = true;
	} else if (move_options.quites[to]) {
	} else {
		//return false; // comment out for dbg
	}


	// maybe eat piece
	Color to_color;
	if (ColorOf(to, &to_color)) {
		colorbb[to_color][to] = 0;
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

	return true;
}