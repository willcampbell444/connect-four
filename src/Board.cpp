#include "Graphics.h"
#include "Board.h"
#include "Globals.h"

#include <iostream>

Board::Board(int __x, int __y, int __w, int __h) {
	// When you start the game, both bitboards are empty
	// This sets all bits to 0
	_bitboards[0] = 0;
	_bitboards[1] = 0;

	x = __x;
	y = __y;
	w = __w;
	h = __h;

	gridW = (float)(w-GLOBAL::GAP)/7-GLOBAL::GAP;
	gridH = (float)(h-GLOBAL::GAP)/6-GLOBAL::GAP;
}

void Board::clear() {
	_bitboards[0] = 0;
	_bitboards[1] = 0;
}

bool Board::insert(int p, int player) {
	p = p*7; // set x to the index of the bottom of the colomn

	unsigned long long spots = (_bitboards[0] | _bitboards[1]); // combine all peices into one bitboard

	for (int i = p; i < p+6; i++) { // iterate through places in the column
		if ((spots & ((unsigned long long)1 << i)) == 0) { // if the place is empty
			_bitboards[player] = _bitboards[player] | ((unsigned long long)1 << i); // fill it
			return true;
		}
	}
	return false;
}

unsigned long long Board::getBoard(int player) {
	return _bitboards[player];
}

int Board::screenToRow(int screenX, int screenY) {
	if (screenX < x+GLOBAL::GAP || screenX > x+w-GLOBAL::GAP || screenY < y+GLOBAL::GAP || screenY > y+h-GLOBAL::GAP) {
		return -1;
	}
	for (int c = 0; c < 7; c++) {
		if (screenX > x+c*gridW+((c+1)*GLOBAL::GAP) && screenX < x+(c+1)*gridW+((c+1)*GLOBAL::GAP)) {
			return c;
		}
	}
	return -1;
}

void Board::resize(int __x, int __y, int __w, int __h) {
	x = __x;
	y = __y;
	w = __w;
	h = __h;

	gridW = (float)(w-GLOBAL::GAP)/7-GLOBAL::GAP;
	gridH = (float)(h-GLOBAL::GAP)/6-GLOBAL::GAP;
}

void  Board::draw(Graphics* graphics, int hover) {

	for (int c = 0; c < 7; c++) {
		for (int r = 0; r < 6; r++) {
			if ((_bitboards[1] & ((unsigned long long)1 << (c*7+(5-r)))) != 0) {
				graphics->drawFillRect(x+c*gridW+((c+1)*GLOBAL::GAP), y+r*gridH+((r+1)*GLOBAL::GAP), x+(c+1)*gridW+((c+1)*GLOBAL::GAP), y+(r+1)*gridH+((r+1)*GLOBAL::GAP), COLORS::PLAYER1);
			} else if ((_bitboards[0] & ((unsigned long long)1 << (c*7+(5-r)))) != 0) {
				graphics->drawFillRect(x+c*gridW+((c+1)*GLOBAL::GAP), y+r*gridH+((r+1)*GLOBAL::GAP), x+(c+1)*gridW+((c+1)*GLOBAL::GAP), y+(r+1)*gridH+((r+1)*GLOBAL::GAP), COLORS::PLAYER2);
			} else {
				graphics->drawFillRect(x+c*gridW+((c+1)*GLOBAL::GAP), y+r*gridH+((r+1)*GLOBAL::GAP), x+(c+1)*gridW+((c+1)*GLOBAL::GAP), y+(r+1)*gridH+((r+1)*GLOBAL::GAP), COLORS::UNCLAIMED);
			}
		}
	}

	if (hover != -1) {
		for (int r = 0; r < 6; r++) { // iterate through places in the column
			if (((_bitboards[0] | _bitboards[1]) & ((unsigned long long)1 << (hover*7+r))) == 0) { // if the place is empty
				graphics->drawFillRect(x+hover*gridW+((hover+1)*GLOBAL::GAP), y+(5-r)*gridH+(((5-r)+1)*GLOBAL::GAP), x+(hover+1)*gridW+((hover+1)*GLOBAL::GAP), y+((5-r)+1)*gridH+(((5-r)+1)*GLOBAL::GAP), COLORS::HIGHLIGHTED);
				// return;
			}
		}
	}
}