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

	olc::Decal* piece_decals[13];

	int sel_square;

	Game() {
		sAppName = "Hex Chess";

		std::bitset<BoardLen> bb;
		for (int x = 0; x < FileCount; x++) {
			for (int y = 0; y < RankCounts[x]; y++) {
				bb.set(SquareAt(x, y), true);
			}
		}

		std::cout << bb << '\n';
	}

	bool OnUserCreate() override {
		InitEyes();
		position = Position::Default();
		sel_square = 69;

		tile_decals[0] = new olc::Decal(new olc::Sprite("res/tile0.png"));
		tile_decals[1] = new olc::Decal(new olc::Sprite("res/tile1.png"));
		tile_decals[2] = new olc::Decal(new olc::Sprite("res/tile2.png"));

		sel_tile_decal = new olc::Decal(new olc::Sprite("res/sel_tile.png"));
		stat_tile_decal = new olc::Decal(new olc::Sprite("res/stat_tile.png"));

		piece_decals[(int) Piece::WKing] = new olc::Decal(new olc::Sprite("res/w_king.png"));
		piece_decals[(int) Piece::WQueen] = new olc::Decal(new olc::Sprite("res/w_queen.png"));
		piece_decals[(int) Piece::WRook] = new olc::Decal(new olc::Sprite("res/w_rook.png"));
		piece_decals[(int) Piece::WBishop] = new olc::Decal(new olc::Sprite("res/w_bishop.png"));
		piece_decals[(int) Piece::WKnight] = new olc::Decal(new olc::Sprite("res/w_knight.png"));
		piece_decals[(int) Piece::WPawn] = new olc::Decal(new olc::Sprite("res/w_pawn.png"));
		
		piece_decals[(int) Piece::BKing] = new olc::Decal(new olc::Sprite("res/b_king.png"));
		piece_decals[(int) Piece::BQueen] = new olc::Decal(new olc::Sprite("res/b_queen.png"));
		piece_decals[(int) Piece::BRook] = new olc::Decal(new olc::Sprite("res/b_rook.png"));
		piece_decals[(int) Piece::BBishop] = new olc::Decal(new olc::Sprite("res/b_bishop.png"));
		piece_decals[(int) Piece::BKnight] = new olc::Decal(new olc::Sprite("res/b_knight.png"));
		piece_decals[(int) Piece::BPawn] = new olc::Decal(new olc::Sprite("res/b_pawn.png"));

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::PixelF(0.25f, 0.25f, 0.25f));

		int file = int(GetMouseX() / (0.75f * tile_width) + 0.0625f);
		if (file < 0) {
			file = 0;
		} else if (file >= FileCount) {
			file = FileCount - 1;
		}

		int rank = RankCounts[file] - 1 - int(GetMouseY() / tile_height - tile_yoffs[file]);
		if (rank < 0) {
			rank = 0;
		} else if (rank >= RankCounts[file]) {
			rank = RankCounts[file] - 1;
		}

		sel_square = SquareAt(file, rank);
		
		for (int x = 0; x < FileCount; x++) {
			for (int y = 0; y < RankCounts[x]; y++) {
				int draw_y = RankCounts[x] - y - 1;

				DrawDecal(olc::vf2d {x * 0.75f * tile_width, (tile_yoffs[x] + draw_y)* tile_height}, tile_decals[(tile_colors[x] + draw_y) % 3]);
			}
		}

		for (int x = 0; x < FileCount; x++) {
			for (int y = 0; y < RankCounts[x]; y++) {
				int draw_y = RankCounts[x] - y - 1;
				Piece piece = position.pieces[SquareAt(x, y)];
				int square = SquareAt(x, y);

				if (piece != Piece::None) {
					DrawDecal(olc::vf2d {x * 0.75f * tile_width, (tile_yoffs[x] + draw_y) * tile_height}, piece_decals[(int) piece]);
				}

				if (knight_eyes[sel_square][square]) {
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