#pragma once

#include <cassert>
#include <bitset>

namespace HexChess {
	//static constexpr const int MiddleFile = 5;
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

	static constexpr const int DirectionHalfCount = 6;
	static constexpr const int DirectionCount = 12;


	static constexpr const int White = 0;
	static constexpr const int Black = 1;
	static constexpr const int ColorCount = 2;

	// None is included
	static constexpr const int None = 0;
	static constexpr const int King = 1;
	static constexpr const int Queen = 2;
	static constexpr const int Rook = 3;
	static constexpr const int Bishop = 4;
	static constexpr const int Knight = 5;
	static constexpr const int Pawn = 6;
	static constexpr const int PieceCount = 7;

	inline constexpr bool InBounds(int file, int rank) {
		return file >= 0 && file < FileCount && rank >= 0 && rank < RankCounts[file];
	}

	inline constexpr int FileOf(int square) {
		return square / RankMaxCount;
	}

	inline constexpr int RankOf(int square) {
		return square % RankMaxCount;
	}

	inline constexpr int SquareAt(int file, int rank) {
		assert(InBounds(file, rank));

		return file * RankMaxCount + rank;
	}

	inline constexpr bool MaybeSquareAt(int file, int rank, int* out_square) {
		*out_square = file * RankMaxCount + rank;
		return InBounds(file, rank);
	}
	
	inline int positive_modulo(int i, int n) {
		return (i % n + n) % n;
	}
}