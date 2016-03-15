#include "Graphics.h"
#include "Board.h"
#include "Globals.h"

#include <iostream>

Board::Board() {
	// When you start the game, both bitboards are empty
	// This sets all bits to 0
	_bitboards[0] = 0;
	_bitboards[1] = 0;
}

void Board::insert(int x, int player) {
	x = x*7; // set x to the index of the bottom of the colomn

	unsigned long long spots = (_bitboards[0] | _bitboards[1]); // combine all peices into one bitboard

	for (int i = x; i < x+6; i++) { // iterate through places in the column
		if ((spots & ((unsigned long long)1 << i)) == 0) { // if the place is empty
			_bitboards[player] = _bitboards[player] | ((unsigned long long)1 << i); // fill it
			return;
		}
	}
}

unsigned long long Board::getBoard(int player) {
	return _bitboards[player];
}

void  Board::draw(Graphics* graphics) {
	int gridW = GLOBAL::WIDTH/7;
	int gridH = GLOBAL::HEIGHT/6;

	for (int x = 0; x < 7; x++) {
		for (int y = 0; y < 6; y++) {
			if ((_bitboards[1] & ((unsigned long long)1 << (x*7+y))) != 0) {
				graphics->drawFillRect(x*gridW, GLOBAL::HEIGHT-y*gridH, (x+1)*gridW, GLOBAL::HEIGHT-(y+1)*gridH, 175, 36, 11);
			} else if ((_bitboards[0] & ((unsigned long long)1 << (x*7+y))) != 0) {
				graphics->drawFillRect(x*gridW, GLOBAL::HEIGHT-y*gridH, (x+1)*gridW, GLOBAL::HEIGHT-(y+1)*gridH, 21, 38, 119);
			} else {
				graphics->drawFillRect(x*gridW, GLOBAL::HEIGHT-y*gridH, (x+1)*gridW, GLOBAL::HEIGHT-(y+1)*gridH, 227, 151, 72);
			}
		}
	}
}