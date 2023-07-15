#pragma once

#include <bitset>
#include <cassert>
#include <intrin.h>

#include "Board.h"

namespace HexChess {
	using BitBoard = std::bitset<BoardLen>;
	static const BitBoard UsableBoard {"0000011111100001111111000111111110011111111101111111111111111111110111111111100111111111000111111110000111111100000111111"};

	static const BitBoard PawnBoosts[ColorCount] {
		BitBoard("0000000000000000000001000000000100000000010000000001000000000100000000000100000000000100000000000100000000000100000000000"),
		BitBoard("0000000000000001000000000010000000000100000000001000000000010000000000100000000001000000000010000000000100000000000000000"),
	};

	inline Square WeakBit(BitBoard b) {
		assert(b.any());
		unsigned long idx;
		if (_BitScanForward64((unsigned long*) (&idx), b._Getword(0)) == 0) {
			if (_BitScanForward64((unsigned long*) (&idx), b._Getword(1)) == 0) {
				abort();
			}

			idx += 64; // 64 bits
		}
		return Square(idx);
	}

	inline Square StrongBit(BitBoard b) {
		assert(b.any());
		unsigned long idx;
		if (_BitScanReverse64((unsigned long*) (&idx), b._Getword(1)) == 0) {
			if (_BitScanReverse64((unsigned long*) (&idx), b._Getword(0)) == 0) {
				abort();
			}
		}
		return Square(idx);
	}

	inline Square PopWeak(BitBoard* b) {
		assert(b->any());
		Square s = WeakBit(*b);
		(*b)[s] = 0;
		return s;
	}

	inline Square PopStrong(BitBoard* b) {
		assert(b->any());
		Square s = StrongBit(*b);
		(*b)[s] = 0;
		return s;
	}
}