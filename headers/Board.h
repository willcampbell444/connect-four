#ifndef BOARD_H
#define BOARD_H

class Graphics;

class Board {
public:
	Board();
	void insert(int x, int player);
	int disksInRow(int x);
	// int[7][6] getBoard();
	void draw(Graphics* graphics);
private:
	int _board[7][6];
};

#endif