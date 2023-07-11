#pragma once

#include "HexChess/Board.h"

namespace HexChess {
	struct BitBoard {
		unsigned long long low;
		unsigned long long high;

		constexpr BitBoard() : low(0), high(0) {}

		constexpr BitBoard(unsigned long long low, unsigned long long high) : low(low), high(high) {}

		constexpr BitBoard(int square) : low(0), high(0) {
			assert(square >= 0 && square < BoardLen);

			if (square < 64) {
				low = 1ull << square;
			} else {
				high = 1ull << (square - 64);
			}
		}

		constexpr BitBoard operator ~() const {
			return BitBoard {~low, ~high};
		}

		constexpr BitBoard operator &(BitBoard other) const {
			return BitBoard(low & other.low, high & other.high);
		}

		constexpr BitBoard operator |(BitBoard other) const {
			return BitBoard(low | other.low, high | other.high);
		}

		constexpr BitBoard operator ^(BitBoard other) const {
			return BitBoard(low ^ other.low, high ^ other.high);
		}

		constexpr BitBoard& operator &=(BitBoard other) {
			low &= other.low;
			high &= other.high;
			return *this;
		}

		constexpr BitBoard& operator |=(BitBoard other) {
			low |= other.low;
			high |= other.high;
			return *this;
		}

		constexpr BitBoard& operator ^=(BitBoard other) {
			low ^= other.low;
			high ^= other.high;
			return *this;
		}

		constexpr operator bool() const {
			return low || high;
		}
	};

	static constexpr const BitBoard UsableBoard = BitBoard(0xffbff3fe3fc3f83f, 0xfc3f8ff3fefff);
}