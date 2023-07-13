#pragma once

#include "HexChess/Board.h"

namespace HexChess {
	template<int dir>
	inline constexpr bool SquareInDir(File, Rank, Square* out_square);

	template<> inline constexpr bool SquareInDir<LatNorth>(File file, Rank rank, Square* out_square) {
		return MaybeSquareAt(file, rank + 1, out_square);
	}
	template<> inline constexpr bool SquareInDir<LatNorthEast>(File file, Rank rank, Square* out_square) {
		if (file >= 5) {
			return MaybeSquareAt(file + 1, rank, out_square);
		} else {
			return MaybeSquareAt(file + 1, rank + 1, out_square);
		}
	}
	template<> inline constexpr bool SquareInDir<LatSouthEast>(File file, Rank rank, Square* out_square) {
		if (file >= 5) {
			return MaybeSquareAt(file + 1, rank - 1, out_square);
		} else {
			return MaybeSquareAt(file + 1, rank, out_square);
		}
	}
	template<> inline constexpr bool SquareInDir<LatSouth>(File file, Rank rank, Square* out_square) {
		return MaybeSquareAt(file, rank - 1, out_square);
	}
	template<> inline constexpr bool SquareInDir<LatSouthWest>(File file, Rank rank, Square* out_square) {
		if (file <= 5) {
			return MaybeSquareAt(file - 1, rank - 1, out_square);
		} else {
			return MaybeSquareAt(file - 1, rank, out_square);
		}
	}
	template<> inline constexpr bool SquareInDir<LatNorthWest>(File file, Rank rank, Square* out_square) {
		if (file <= 5) {
			return MaybeSquareAt(file - 1, rank, out_square);
		} else {
			return MaybeSquareAt(file - 1, rank + 1, out_square);
		}
	}

	template<> inline constexpr bool SquareInDir<DiagNorthEast>(File file, Rank rank, Square* out_square) {
		if (file >= 5) {
			return MaybeSquareAt(file + 1, rank + 1, out_square);
		} else {
			return MaybeSquareAt(file + 1, rank + 2, out_square);
		}
	}
	template<> inline constexpr bool SquareInDir<DiagEast>(File file, Rank rank, Square* out_square) {
		if (file >= 5) {
			return MaybeSquareAt(file + 2, rank - 1, out_square);
		} else if (file == 4) {
			return MaybeSquareAt(file + 2, rank, out_square);
		} else {
			return MaybeSquareAt(file + 2, rank + 1, out_square);
		}
	}
	template<> inline constexpr bool SquareInDir<DiagSouthEast>(File file, Rank rank, Square* out_square) {
		if (file >= 5) {
			return MaybeSquareAt(file + 1, rank - 2, out_square);
		} else {
			return MaybeSquareAt(file + 1, rank - 1, out_square);
		}
	}
	template<> inline constexpr bool SquareInDir<DiagSouthWest>(File file, Rank rank, Square* out_square) {
		if (file <= 5) {
			return MaybeSquareAt(file - 1, rank - 2, out_square);
		} else {
			return MaybeSquareAt(file - 1, rank - 1, out_square);
		}
	}
	template<> inline constexpr bool SquareInDir<DiagWest>(File file, Rank rank, Square* out_square) {
		if (file <= 5) {
			return MaybeSquareAt(file - 2, rank - 1, out_square);
		} else if (file == 6) {
			return MaybeSquareAt(file - 2, rank, out_square);
		} else {
			return MaybeSquareAt(file - 2, rank + 1, out_square);
		}
	}
	template<> inline constexpr bool SquareInDir<DiagNorthWest>(File file, Rank rank, Square* out_square) {
		if (file <= 5) {
			return MaybeSquareAt(file - 1, rank + 1, out_square);
		} else {
			return MaybeSquareAt(file - 1, rank + 2, out_square);
		}
	}

	inline constexpr bool SquareInDir(int dir, File file, Rank rank, Square* out_square) {
		switch (dir) {
		case 0: return SquareInDir<0>(file, rank, out_square);
		case 1: return SquareInDir<1>(file, rank, out_square);
		case 2: return SquareInDir<2>(file, rank, out_square);
		case 3: return SquareInDir<3>(file, rank, out_square);
		case 4: return SquareInDir<4>(file, rank, out_square);
		case 5: return SquareInDir<5>(file, rank, out_square);
		case 6: return SquareInDir<6>(file, rank, out_square);
		case 7: return SquareInDir<7>(file, rank, out_square);
		case 8: return SquareInDir<8>(file, rank, out_square);
		case 9: return SquareInDir<9>(file, rank, out_square);
		case 10: return SquareInDir<10>(file, rank, out_square);
		case 11: return SquareInDir<11>(file, rank, out_square);

		default:
			abort();
		}
	}
}