#include "FishBot/Zero.h"

#include <random>

using namespace FishBot;

using namespace HexChess;

bool Zero::MakeMove(Position* position) {
	BitBoard pieces = position->colorbb[position->opp];

	BitBoard it;
	int a;

	while (pieces.any()) {
		it = pieces;

		a = rand() % it.count();
		for (; a > 0; a--) {
			PopWeak(&it);
		}

		Square from = WeakBit(it);
		pieces[from] = 0;

		MoveOptions move_options = position->PieceMoves(from);
		it = move_options.quites | move_options.attacks;

		if (it.count() == 0) {
			continue;
		}

		a = rand() % it.count();
		for (; a > 0; a--) {
			PopWeak(&it);
		}

		Square to = WeakBit(it);
		return position->DoMove(from, to);
	}

	return false;
}