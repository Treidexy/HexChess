#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include "HexChess/HexChess.h"

#include <bitset>

using namespace HexChess;

static constexpr const float tile_width = 60.0f;
static constexpr const float tile_height = 51.9615242271f;

struct Game: public olc::PixelGameEngine {
	Position position;
	olc::Decal* tile_decals[3];
	olc::Decal* sel_tile_decal;
	olc::Decal* stat_tile_decal;

	static const constexpr int tile_colors[FileCount] = {
		0, 1, 2, 0, 1, 2, 1, 0, 2, 1, 0
	};
	static const constexpr float tile_yoffs[FileCount] = {
		2.5f, 2.0f, 1.5f, 1.0f, 0.5f, 0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f,
	};

	olc::Decal* piece_decals[PieceCount * 2];

	Square sel_square;
	Square curr_square;

	Game() {
		sAppName = "Hex Chess";
	}

	bool OnUserCreate() override {
		position = Position::Default();
		sel_square = 69;

		tile_decals[0] = new olc::Decal(new olc::Sprite("res/tile0.png"));
		tile_decals[1] = new olc::Decal(new olc::Sprite("res/tile1.png"));
		tile_decals[2] = new olc::Decal(new olc::Sprite("res/tile2.png"));

		sel_tile_decal = new olc::Decal(new olc::Sprite("res/sel_tile.png"));
		stat_tile_decal = new olc::Decal(new olc::Sprite("res/stat_tile.png"));

		piece_decals[King] = new olc::Decal(new olc::Sprite("res/w_king.png"));
		piece_decals[Queen] = new olc::Decal(new olc::Sprite("res/w_queen.png"));
		piece_decals[Rook] = new olc::Decal(new olc::Sprite("res/w_rook.png"));
		piece_decals[Bishop] = new olc::Decal(new olc::Sprite("res/w_bishop.png"));
		piece_decals[Knight] = new olc::Decal(new olc::Sprite("res/w_knight.png"));
		piece_decals[Pawn] = new olc::Decal(new olc::Sprite("res/w_pawn.png"));
		
		piece_decals[PieceCount + King] = new olc::Decal(new olc::Sprite("res/b_king.png"));
		piece_decals[PieceCount + Queen] = new olc::Decal(new olc::Sprite("res/b_queen.png"));
		piece_decals[PieceCount + Rook] = new olc::Decal(new olc::Sprite("res/b_rook.png"));
		piece_decals[PieceCount + Bishop] = new olc::Decal(new olc::Sprite("res/b_bishop.png"));
		piece_decals[PieceCount + Knight] = new olc::Decal(new olc::Sprite("res/b_knight.png"));
		piece_decals[PieceCount + Pawn] = new olc::Decal(new olc::Sprite("res/b_pawn.png"));

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::PixelF(0.25f, 0.25f, 0.25f));

		File file = int(GetMouseX() / (0.75f * tile_width) - 0.25f * 0.75f);
		if (file < 0) {
			file = 0;
		} else if (file >= FileCount) {
			file = FileCount - 1;
		}

		Rank rank = RankCounts[file] - 1 - int(GetMouseY() / tile_height - tile_yoffs[file]);
		if (rank < 0) {
			rank = 0;
		} else if (rank >= RankCounts[file]) {
			rank = RankCounts[file] - 1;
		}

		curr_square = SquareAt(file, rank);
		if (GetMouse(0).bReleased) {
			position.DoMove(sel_square, curr_square);
		} else if (!GetMouse(0).bHeld) {
			sel_square = curr_square;
		}

		MoveOptions move_options = position.PieceMoves(sel_square);
		
		for (File x = 0; x < FileCount; x++) {
			for (Rank y = 0; y < RankCounts[x]; y++) {
				Rank draw_y = RankCounts[x] - y - 1;

				DrawDecal(olc::vf2d {x * 0.75f * tile_width, (tile_yoffs[x] + draw_y) * tile_height}, tile_decals[(tile_colors[x] + draw_y) % 3]);
			}
		}

		for (File x = 0; x < FileCount; x++) {
			for (Rank y = 0; y < RankCounts[x]; y++) {
				Rank draw_y = RankCounts[x] - y - 1;
				Piece piece = position.pieces[SquareAt(x, y)];
				Square square = SquareAt(x, y);

				if (piece != None) {
					DrawDecal(olc::vf2d {x * 0.75f * tile_width, (tile_yoffs[x] + draw_y) * tile_height}, piece_decals[PieceCount * int(position.colorbb[Black][square]) + int(piece)]);
				}

				if (move_options.quites[square] || move_options.attacks[square]) {
					DrawDecal(olc::vf2d {x * 0.75f * tile_width, (tile_yoffs[x] + draw_y)* tile_height}, stat_tile_decal);
				}
				if (square == sel_square) {
					DrawDecal(olc::vf2d {x * 0.75f * tile_width, (tile_yoffs[x] + draw_y)* tile_height}, sel_tile_decal);
				}
			}
		}
		return true;
	}
};

int main() {
	Game game;
	if (game.Construct(510, 572, 1, 1)) {
		game.Start();
	}
}