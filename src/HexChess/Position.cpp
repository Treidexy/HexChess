#include "HexChess/Position.h"

using namespace HexChess;

Position Position::Default() {
	Position position = {};

	// pawns
	position.pieces[SquareAt(1, 0)] = Piece::WPawn;
	position.pieces[SquareAt(2, 1)] = Piece::WPawn;
	position.pieces[SquareAt(3, 2)] = Piece::WPawn;
	position.pieces[SquareAt(4, 3)] = Piece::WPawn;
	position.pieces[SquareAt(5, 4)] = Piece::WPawn;
	position.pieces[SquareAt(6, 3)] = Piece::WPawn;
	position.pieces[SquareAt(7, 2)] = Piece::WPawn;
	position.pieces[SquareAt(8, 1)] = Piece::WPawn;
	position.pieces[SquareAt(9, 0)] = Piece::WPawn;

	position.pieces[SquareAt(1, 6)] = Piece::BPawn;
	position.pieces[SquareAt(2, 6)] = Piece::BPawn;
	position.pieces[SquareAt(3, 6)] = Piece::BPawn;
	position.pieces[SquareAt(4, 6)] = Piece::BPawn;
	position.pieces[SquareAt(5, 6)] = Piece::BPawn;
	position.pieces[SquareAt(6, 6)] = Piece::BPawn;
	position.pieces[SquareAt(7, 6)] = Piece::BPawn;
	position.pieces[SquareAt(8, 6)] = Piece::BPawn;
	position.pieces[SquareAt(9, 6)] = Piece::BPawn;

	return position;
}