#ifndef BOARD_H
#define BOARD_H

class Graphics;

class Board {
public:
	Board();
	void insert(int x, int player);
	int disksInRow(int x);
	char (*getBoard())[6];
	void draw(Graphics* graphics);
private:
	char _board[7][6];
	// unsigned long long _p1;
	// unsigned long long _p2;
};

#endif