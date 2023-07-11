#pragma once

#include <cassert>

namespace HexChess {
	static constexpr const int FileCount = 11;

	static constexpr const int RankMinCount = 6;
	static constexpr const int RankMaxCount = 11;
	static constexpr const int RankCounts[FileCount] = {
		6, 7, 8, 9, 10, 11, 10, 9, 8, 7, 6,
	};

	static constexpr const int BoardLen = FileCount * RankMaxCount;


	static constexpr const int LatNorth = 0;
	static constexpr const int LatNorthEast = 1;
	static constexpr const int LatSouthEast = 2;
	static constexpr const int LatSouth = 3;
	static constexpr const int LatSouthWest = 4;
	static constexpr const int LatNorthWest = 5;

	static constexpr const int DiagNorthEast = 6;
	static constexpr const int DiagEast = 7;
	static constexpr const int DiagSouthEast = 8;
	static constexpr const int DiagSouthWest = 9;
	static constexpr const int DiagWest = 10;
	static constexpr const int DiagNorthWest = 11;

	static constexpr const int DirectionCount = 12;

	enum class Piece {
		None,
		WKing,
		WQueen,
		WRook,
		WBishop,
		WKnight,
		WPawn,

		BKing,
		BQueen,
		BRook,
		BBishop,
		BKnight,
		BPawn,
	};

	enum class PieceKind {
		None,
		King,
		Queen,
		Rook,
		Bishop,
		Knight,
		Pawn,
	};

	inline constexpr bool InBounds(int file, int rank) {
		return file >= 0 && file < FileCount && rank >= 0 && rank < RankCounts[file];
	}

	inline constexpr int SquareAt(int file, int rank) {
		assert(InBounds(file, rank));

		return file * FileCount + rank;
	}
}