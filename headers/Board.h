#ifndef BOARD_H
#define BOARD_H

class Graphics;

// BOARD CLASS

// Uses bitboards to store the peices:
// a bitboard is stored in a 64 bit integer, each bit is either 1 for full or 0 for empty
// one bitboard is used for each player
// the table below shows the position of each bit

// 6 13 20 27 34 41 48 - This row can never have a peice in it, it's above the top, always all 0
// 5 12 19 26 33 40 47 - Top row
// 4 11 18 25 32 39 46
// 3 10 17 24 31 38 45
// 2 9  16 23 30 37 44
// 1 8  15 22 29 36 43
// 0 7  14 21 28 35 42 - Bottom row

class Board {
public:
	Board();
	void insert(int x, int player);
	// int disksInRow(int x);
	void draw(Graphics* graphics);
	unsigned long long getBoard(int player);
private:
	unsigned long long _bitboards[2];
};

#endif

