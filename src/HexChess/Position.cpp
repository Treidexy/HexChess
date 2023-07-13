#include "HexChess/Position.h"

using namespace HexChess;

namespace {
	void SetPiece(Position* position, File file, Rank rank, Piece piece, Color color) {
		int square = SquareAt(file, rank);
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