#pragma once

#include <cassert>
#include <bitset>

namespace HexChess {
	using Square = int;
	using File = int;
	using Rank = int;
	using Direction = int;
	using Color = int;
	using Piece = int;


	//static constexpr const int MiddleFile = 5;
	static constexpr const int FileCount = 11;

	static constexpr const int RankMinCount = 6;
	static constexpr const int RankMaxCount = 11;
	static constexpr const int RankCounts[FileCount] = {
		6, 7, 8, 9, 10, 11, 10, 9, 8, 7, 6,
	};

	static constexpr const int BoardLen = FileCount * RankMaxCount;

	using BitBoard = std::bitset<BoardLen>;
	static const BitBoard UsableBoard {"0000011111100001111111000111111110011111111101111111111111111111110111111111100111111111000111111110000111111100000111111"};



	static constexpr const Direction LatNorth = 0;
	static constexpr const Direction LatNorthEast = 1;
	static constexpr const Direction LatSouthEast = 2;
	static constexpr const Direction LatSouth = 3;
	static constexpr const Direction LatSouthWest = 4;
	static constexpr const Direction LatNorthWest = 5;

	static constexpr const Direction DiagNorthEast = 6;
	static constexpr const Direction DiagEast = 7;
	static constexpr const Direction DiagSouthEast = 8;
	static constexpr const Direction DiagSouthWest = 9;
	static constexpr const Direction DiagWest = 10;
	static constexpr const Direction DiagNorthWest = 11;

	static constexpr const int DirectionHalfCount = 6;
	static constexpr const int DirectionCount = 12;


	static constexpr const Color White = 0;
	static constexpr const Color Black = 1;
	static constexpr const int ColorCount = 2;

	static const BitBoard PawnBoosts[ColorCount] {
		BitBoard("0000000000000000000001000000000100000000010000000001000000000100000000000100000000000100000000000100000000000100000000000"),
		BitBoard("0000000000000001000000000010000000000100000000001000000000010000000000100000000001000000000010000000000100000000000000000"),
	};

	// None is included
	static constexpr const Piece None = 0;
	static constexpr const Piece King = 1;
	static constexpr const Piece Queen = 2;
	static constexpr const Piece Rook = 3;
	static constexpr const Piece Bishop = 4;
	static constexpr const Piece Knight = 5;
	static constexpr const Piece Pawn = 6;
	static constexpr const int PieceCount = 7;

	inline constexpr bool InBounds(File file, Rank rank) {
		return file >= 0 && file < FileCount && rank >= 0 && rank < RankCounts[file];
	}

	inline constexpr File FileOf(Square square) {
		return square / RankMaxCount;
	}

	inline constexpr Rank RankOf(Square square) {
		return square % RankMaxCount;
	}

	inline constexpr Square SquareAt(File file, Rank rank) {
		assert(InBounds(file, rank));

		return file * RankMaxCount + rank;
	}

	inline constexpr bool MaybeSquareAt(File file, Rank rank, Square* out_square) {
		*out_square = file * RankMaxCount + rank;
		return InBounds(file, rank);
	}
	
	inline int positive_modulo(int i, int n) {
		return (i % n + n) % n;
	}
}