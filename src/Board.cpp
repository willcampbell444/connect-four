#include "Graphics.h"
#include "Board.h"
#include "Globals.h"

Board::Board() {
	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 6; y++) {
			_board[x][y] = 0;
		}
	}
}

void Board::insert(int x, int player) {
	for (int y = 0; y < 6; y++) {
		if (_board[x][y] == 0) {
			_board[x][y] = player;
			break;
		}
	}
}

int Board::disksInRow(int x) {
	for (int y = 0; y < 6; y++) {
		if (_board[x][y] == 0) {
			return y+1;
		}
	}
	return 6;
}

char (*Board::getBoard())[6] {
	return _board;
}

void  Board::draw(Graphics* graphics) {
	int gridW = GLOBAL::WIDTH/7;
	int gridH = GLOBAL::HEIGHT/6;

	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 6; y++) {
			if (_board[x][5-y] == 0) {
				graphics->drawFillRect(x*gridW, y*gridH, (x+1)*gridW, (y+1)*gridH, 227, 151, 72);
			} else if (_board[x][5-y] == 1) {
				graphics->drawFillRect(x*gridW, y*gridH, (x+1)*gridW, (y+1)*gridH, 175, 36, 11);
			} else if (_board[x][5-y] == 2) {
				graphics->drawFillRect(x*gridW, y*gridH, (x+1)*gridW, (y+1)*gridH, 21, 38, 119);
			}
		}
	}
}
