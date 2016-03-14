#include "Game.h"
#include "Graphics.h"
#include "Board.h"
#include "Globals.h"
#include <SDL.h>
#include <iostream>

Game::Game() {
	SDL_Init(SDL_INIT_VIDEO);
	_graphics = new Graphics();
	_event = new SDL_Event();
	_board = new Board();
	_state = STATE::PLAYER_DECISION;
	_board->insert(3, 0);
}

void Game::aiMove() {
	int best = -1000000000;
	int move = 0;
	unsigned long long p0 = _board->getBoard(0);
	unsigned long long p1 = _board->getBoard(1);
	for (int i = 0; i < 7; i++) {
		unsigned long long y = insertIntoBitboard(p0, p1, i);
		if (y != 0) {
			int x = minimax(y, p1, -100, 100, 2, false);
			std::cout << i << ": " << x << "\n";
			if (x > best) {
				move = i;
				best = x;
			}
		}
	}
	std::cout << "\n\n";
	_board->insert(move, 0);
}

int Game::minimax(unsigned long long blue, unsigned long long red, int alpha, int beta, int depth, bool maximize) {
	if (checkWin(red) | checkWin(blue)) {
		if (checkWin(blue)) {
			return  99999999;
		} else {
			return -99999999;
		}
	} else if ((red | blue) == 562949953421312) { // if it is a tie
		return 0;
	} else if (depth <= 0) {
		return analyze(blue, red);
	}

	if (maximize) {
		int max = -1000000000;

		for (int i = 0; i < 7; i++) {
			unsigned long long y = insertIntoBitboard(blue, red, i); // add a blue peice

			if (y != 0) {
				int x = minimax(y, red, alpha, beta, depth-1, false);
				if (x > max) {
					max = x;
				}
			}
		}

		return max;

	} else {
		int min = 1000000000;

		for (int i = 0; i < 7; i++) {
			unsigned long long y = insertIntoBitboard(red, blue, i); // add a red peice

			if (y != 0) {
				int x = minimax(blue, y, alpha, beta, depth-1, true);
				if (x < min) {
					min = x;
				}
			}

		}

		return min;
	}
}

int Game::analyze(unsigned long long p0, unsigned long long p1) {
	int score = 1;
	int loss = 1;
    unsigned long long tmp;
    int n;

    // Check diagonal /
    tmp = p0 & (p0 >> 8); // shift everything diagonally upwards and and that with the board
    n = 1;
    while (tmp != 0) {
    	if (tmp & 1 == 1) {
    		n = n += 1;
    	}
    	tmp = tmp >> 1;
    }
    score = score * n;

    // Check horizontal -
    tmp = p0 & (p0 >> 7); 
    n = 1;
    while (tmp != 0) {
    	if (tmp & 1 == 1) {
    		n = n += 1;
    	}
    	tmp = tmp >> 1;
    }
    score = score * n;

    // Check diagonal
    tmp = p0 & (p0 >> 6); 
    n = 1;
    while (tmp != 0) {
    	if (tmp & 1 == 1) {
    		n = n += 1;
    	}
    	tmp = tmp >> 1;
    }
    score = score * n;

    // Check vertical |
    tmp = p0 & (p0 >> 1);
    n = 1;
    while (tmp != 0) {
    	if (tmp & 1 == 1) {
    		n = n += 1;
    	}
    	tmp = tmp >> 1;
    }
    score = score * n;

    // other player

    // Check diagonal /
    tmp = p1 & (p1 >> 8); // shift everything diagonally upwards and and that with the board
    n = 1;
    while (tmp != 0) {
    	if (tmp & 1 == 1) {
    		n = n += 1;
    	}
    	tmp = tmp >> 1;
    }
    loss = loss * n;
    // Check horizontal -
    n = 1;
    while (tmp != 0) {
    	if (tmp & 1 == 1) {
    		n = n += 1;
    	}
    	tmp = tmp >> 1;
    }
    loss = loss * n;
    // Check diagonal
    n = 1;
    while (tmp != 0) {
    	if (tmp & 1 == 1) {
    		n = n += 1;
    	}
    	tmp = tmp >> 1;
    }
    loss = loss * n;
    // Check vertical |
    n = 1;
    while (tmp != 0) {
    	if (tmp & 1 == 1) {
    		n = n += 1;
    	}
    	tmp = tmp >> 1;
    }
    loss = loss * n;

    return score-loss;
}

unsigned long long Game::insertIntoBitboard(unsigned long long toAdd, unsigned long long other, int x) {
	x = x*7; // set x to the index of the bottom of the colomn

	unsigned long long allPeices = (toAdd | other); // combine all peices into one bitboard

	for (int i = x; i < x+6; i++) { // iterate through places in the column
		if ((allPeices & ((unsigned long long)1 << i)) == 0) { // if the place is empty
			toAdd = (toAdd | ((unsigned long long)1 << i)); // fill it
			return toAdd;
		}
	}
	return 0;
}

bool Game::checkWin(unsigned long long b) {
    unsigned long long tmp;

    // Check diagonal /
    tmp = b & (b >> 8); // shift everything diagonally upwards and and that with the board
    if (tmp & (tmp >> 16)) {
    	return true;
    }
    // Check horizontal -
    tmp = b & (b >> 7); 
    if (tmp & (tmp >> 14)) {
    	return true;
    }
    // Check diagonal
    tmp = b & (b >> 6); 
    if (tmp & (tmp >> 12)) {
    	return true;
    }
    // Check vertical |
    tmp = b & (b >> 1);
    if (tmp & (tmp >> 2)) {
    	return true;
    }
    return false;
}

void Game::play() {
	while (true) {
		drawBoard();
		if (_state == STATE::AI_MOVE) {
			aiMove();
			_state = STATE::PLAYER_DECISION;
		}
		if (SDL_PollEvent(_event)) {
			if (_event->type == SDL_QUIT) {
				break;
			} else if (_state == STATE::PLAYER_DECISION && _event->type == SDL_MOUSEBUTTONUP) {
				if (_event->button.button == SDL_BUTTON_LEFT) {
					_board->insert(_event->button.x/(GLOBAL::WIDTH/7), 1);
					_state = STATE::AI_MOVE;\
				}
			}
		}
		if (checkWin(_board->getBoard(0))) {
			std::cout << "0\n";
			drawBoard();
			SDL_Delay(1000);
			return;
		} else if (checkWin(_board->getBoard(1))) {
			std::cout << "1\n";
			drawBoard();
			SDL_Delay(1000);
			return;
		}
	}
}

void Game::drawBoard() {
	_graphics->clear();
	_board->draw(_graphics);
	_graphics->flip();
}





//             ...
//    /---------|---------\
//   o..       .o.       ..o
//  /   \     /   \     /   \
// ox. o.x   xo. .ox   x.o .xo
//  |   |     |   |     |   |
// oxo oox   xoo oox   xoo oxo

//             ...
//    /---------|---------\     MAX
//   o..       .o.       ..o
//  / 0 \     / 1 \     / 0 \   MIN
// ox. o.x   xo. .ox   x.o .xo
//  0   1     1   1     1   0
//  |   |     |   |     |   |   MAX
// oxo oox   xoo oox   xoo oxo
//  0   1     1   1     1   0