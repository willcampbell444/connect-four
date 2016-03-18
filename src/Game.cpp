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
	_board = new Board(0, 0, GLOBAL::WIDTH, GLOBAL::HEIGHT);
	// _state = STATE::AI_MOVE;
	_state = STATE::PLAYER_DECISION;
	_mouseColumn = -1;
	_mouseX = new int(0);
	_mouseY = new int(0);
	_mouseMode = true;
	_currentPlayer = 1;

	_quit = false;
}

void Game::restart() {
	_board->clear();
	_state = STATE::PLAYER_DECISION;
	_currentPlayer = 1;

	_mouseMode = true;
	_mouseColumn = -1;
}

void Game::aiMove() {
	int best = -1000000000;
	int move = 0;
	int alpha = -99999999;
	int beta = 99999999;
	unsigned long long p0 = _board->getBoard(0);
	unsigned long long p1 = _board->getBoard(1);

	int depth;
	if (_difficulty == 1) {
		depth = 1;
	} else if (_difficulty == 2) {
		depth = 2;
	} else {
		depth = 7;
	}

	for (int i = 0; i < 7; i++) {
		unsigned long long y = insertIntoBitboard(p0, p1, i);
		if (y != 0) {
			int x = minimax(y, p1, alpha, beta, depth, false);
			if (x > best) {
				move = i;
				best = x;
			} else if (best == x) {
				if ((move < 3 || move > 3) && i == 3) {
					move = i;
				} else if ((move < 2 || move > 4) && (i > 1 || i < 5)) {
					move = i;
				} else if ((move == 0 || move == 6) && (i > 0 || i < 6)) {
					move = i;
				}
			}
		}
	}
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
				if (x > alpha) {
					alpha = x;
				}
				if (alpha >= beta) {
					return beta;
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
				if (x < beta) {
					beta = x;
				}
				if (alpha >= beta) {
					return beta;
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

void Game::update() {
	if (_state == STATE::AI_MOVE) {
		aiMove();
		_state = STATE::PLAYER_DECISION;
	}
	if (SDL_PollEvent(_event)) {
		if (_event->type == SDL_QUIT) {
			_quit = true;
			return;
		} else if (_state == STATE::PLAYER_DECISION) {
			if (_event->type == SDL_MOUSEBUTTONUP) {
				if (!_mouseMode) {
					_mouseMode = true;
				} else if (_event->button.button == SDL_BUTTON_LEFT) {
					int r = _board->screenToRow(_event->button.x, _event->button.y);
					if (r != -1 && _board->insert(r, _currentPlayer)) {
						if (_players == 1) {
							_state = STATE::AI_MOVE;
						} else {
							_currentPlayer = 1 - _currentPlayer;
						}
						_mouseColumn = -1;
					}
				}
			} else if (_event->type == SDL_KEYUP) {
				_mouseMode = false;
				if (_event->key.keysym.sym == SDLK_LEFT || _event->key.keysym.sym == SDLK_a) {
					if (_mouseColumn < 1) {
						_mouseColumn = 6;
					} else {
						_mouseColumn -= 1;
					}
				} else if (_event->key.keysym.sym == SDLK_RIGHT || _event->key.keysym.sym == SDLK_d) {
					if (_mouseColumn > 5) {
						_mouseColumn = 0;
					} else {
						_mouseColumn += 1;
					}
				} else if (_event->key.keysym.sym == SDLK_RETURN || _event->key.keysym.sym == SDLK_SPACE) {
					if (_mouseColumn != -1 && _board->insert(_mouseColumn, _currentPlayer)) {
						if (_players == 1) {
							_state = STATE::AI_MOVE;
						} else {
							_currentPlayer = 1 - _currentPlayer;
						}
					}
				}
			} else if (_event->type == SDL_MOUSEMOTION) {
				_mouseMode = true;
			}
			if (_mouseMode) {
				SDL_GetMouseState(_mouseX, _mouseY);
				_mouseColumn = _board->screenToRow(*_mouseX, *_mouseY);
			} 
		}
	}
	return;
}

void Game::wait(int length, std::string message) {
	int start = SDL_GetTicks();
	while (start+length > SDL_GetTicks()) {
		drawBoard(true);
		_graphics->drawFontCentered(message, GLOBAL::WIDTH/2, GLOBAL::HEIGHT/2);
		_graphics->flip();
		if (SDL_PollEvent(_event)) {
			if (_event->type == SDL_QUIT) {
				_quit = true;
				return;
			} else if (_event->type == SDL_MOUSEBUTTONUP) {
				return;
			} else if (_event->type == SDL_KEYUP) {
				return;
			}
		}
	}
}

void Game::wait(int length) {
	int start = SDL_GetTicks();
	while (start+length > SDL_GetTicks()) {
		drawBoard();
		if (SDL_PollEvent(_event) && _event->type == SDL_QUIT) {
			_quit = true;
			return;
		}
	}
}

void Game::menu() {
	int r = 0;
	int c = 0;
	float boxHeight = (GLOBAL::HEIGHT-GLOBAL::GAP)/3.0f;
	float boxWidth = (GLOBAL::WIDTH-GLOBAL::GAP)/2.0f;
	float boxThirdWidth = (GLOBAL::WIDTH-GLOBAL::GAP)/3.0f;

	int players = -1;
	int playerHover = -1;
	int difficulty = -1;
	int difficultyHover = -1;
	bool playHover = false;
	while (true) {
		_graphics->clear();
		_graphics->drawFillRect(GLOBAL::GAP, GLOBAL::GAP, GLOBAL::WIDTH-10, boxHeight, COLORS::UNCLAIMED);
		_graphics->drawFontCentered("Connect Four", GLOBAL::WIDTH/2, boxHeight/2+GLOBAL::GAP);
		
		if (players == 1 || (players == -1 && playerHover == 1)) {
			_graphics->drawFillRect(GLOBAL::GAP, GLOBAL::GAP+boxHeight, boxWidth, boxHeight*2, COLORS::HIGHLIGHTED);
		} else {
			_graphics->drawFillRect(GLOBAL::GAP, GLOBAL::GAP+boxHeight, boxWidth, boxHeight*2, COLORS::UNCLAIMED);
		}
		_graphics->drawFontCentered("1 player", boxWidth/2, boxHeight/2+boxHeight+GLOBAL::GAP, 0.6);

		if (players == 2 || (players == -1 && playerHover == 2)) {
			_graphics->drawFillRect(boxWidth+GLOBAL::GAP, GLOBAL::GAP+boxHeight, GLOBAL::WIDTH-GLOBAL::GAP, boxHeight*2, COLORS::HIGHLIGHTED);
		} else {
			_graphics->drawFillRect(boxWidth+GLOBAL::GAP, GLOBAL::GAP+boxHeight, GLOBAL::WIDTH-GLOBAL::GAP, boxHeight*2, COLORS::UNCLAIMED);
		}
		_graphics->drawFontCentered("2 player", boxWidth+boxWidth/2, boxHeight/2+boxHeight+GLOBAL::GAP, 0.6);
		
		if (players == 1) {
			if (difficulty == 1 || (difficulty == -1 && difficultyHover == 1)) {
				_graphics->drawFillRect(GLOBAL::GAP, GLOBAL::GAP+boxHeight*2, boxThirdWidth, boxHeight*3, COLORS::HIGHLIGHTED);
			} else {
				_graphics->drawFillRect(GLOBAL::GAP, GLOBAL::GAP+boxHeight*2, boxThirdWidth, boxHeight*3, COLORS::UNCLAIMED);
			}
			_graphics->drawFontCentered("Easy", boxThirdWidth/2, boxHeight/2+boxHeight*2+GLOBAL::GAP, 0.6);

			if (difficulty == 2 || (difficulty == -1 && difficultyHover == 2)) {
				_graphics->drawFillRect(boxThirdWidth+GLOBAL::GAP, GLOBAL::GAP+boxHeight*2, boxThirdWidth*2, boxHeight*3, COLORS::HIGHLIGHTED);
			} else {
				_graphics->drawFillRect(boxThirdWidth+GLOBAL::GAP, GLOBAL::GAP+boxHeight*2, boxThirdWidth*2, boxHeight*3, COLORS::UNCLAIMED);
			}	
			_graphics->drawFontCentered("Medium", boxThirdWidth+boxThirdWidth/2, boxHeight/2+boxHeight*2+GLOBAL::GAP, 0.6);

			if (difficulty == 3 || (difficulty == -1 && difficultyHover == 3)) {
				_graphics->drawFillRect(boxThirdWidth*2+GLOBAL::GAP, GLOBAL::GAP+boxHeight*2, GLOBAL::WIDTH-GLOBAL::GAP, boxHeight*3, COLORS::HIGHLIGHTED);
			} else {
				_graphics->drawFillRect(boxThirdWidth*2+GLOBAL::GAP, GLOBAL::GAP+boxHeight*2, GLOBAL::WIDTH-GLOBAL::GAP, boxHeight*3, COLORS::UNCLAIMED);
			}
			_graphics->drawFontCentered("Hard", boxThirdWidth*2+boxThirdWidth/2, boxHeight/2+boxHeight*2+GLOBAL::GAP, 0.6);

			if (playHover) {
				_graphics->drawFillRect(GLOBAL::GAP, GLOBAL::GAP+boxHeight*3, GLOBAL::WIDTH-GLOBAL::GAP, boxHeight*4, COLORS::HIGHLIGHTED);
			} else {
				_graphics->drawFillRect(GLOBAL::GAP, GLOBAL::GAP+boxHeight*3, GLOBAL::WIDTH-GLOBAL::GAP, boxHeight*4, COLORS::UNCLAIMED);
			}
			_graphics->drawFontCentered("play", GLOBAL::WIDTH/2, boxHeight/2+boxHeight*3+GLOBAL::GAP);
		} else {
			if (playHover) {
				_graphics->drawFillRect(GLOBAL::GAP, GLOBAL::GAP+boxHeight*2, GLOBAL::WIDTH-GLOBAL::GAP, boxHeight*3, COLORS::HIGHLIGHTED);
			} else {
				_graphics->drawFillRect(GLOBAL::GAP, GLOBAL::GAP+boxHeight*2, GLOBAL::WIDTH-GLOBAL::GAP, boxHeight*3, COLORS::UNCLAIMED);
			}
			_graphics->drawFontCentered("play", GLOBAL::WIDTH/2, boxHeight/2+boxHeight*2+GLOBAL::GAP);
		}
		_graphics->flip();

		if (SDL_PollEvent(_event)) {
			if (_event->type == SDL_QUIT) {
				_quit = true;
				return;
			} else if (_event->type == SDL_MOUSEBUTTONUP) {
				if (!_mouseMode) {
					_mouseMode = true;
				} else if (_event->button.button == SDL_BUTTON_LEFT) {
					if (!_mouseMode) {
						_mouseMode = true;
					} else if (_event->button.x > GLOBAL::GAP && _event->button.x < boxWidth && _event->button.y > GLOBAL::GAP+boxHeight && _event->button.y < boxHeight*2) {
						players = 1;
						difficulty = -1;
						difficultyHover = -1;
						boxHeight = (GLOBAL::HEIGHT-GLOBAL::GAP)/4.0f;
					} else if (_event->button.x > boxWidth+GLOBAL::GAP && _event->button.x < GLOBAL::WIDTH-GLOBAL::GAP && _event->button.y > GLOBAL::GAP+boxHeight && _event->button.y < boxHeight*2) {
						players = 2;
						boxHeight = (GLOBAL::HEIGHT-GLOBAL::GAP)/3.0f;
					} else if (players == 1) {
						if (_event->button.x > GLOBAL::GAP && _event->button.x < boxThirdWidth && _event->button.y > GLOBAL::GAP+boxHeight*2 && _event->button.y < boxHeight*3) {
							difficulty = 1;
						} else if (_event->button.x > boxThirdWidth+GLOBAL::GAP && _event->button.x < boxThirdWidth*2 && _event->button.y > GLOBAL::GAP+boxHeight*2 && _event->button.y < boxHeight*3) {
							difficulty = 2;
						} else if (_event->button.x > boxThirdWidth*2+GLOBAL::GAP && _event->button.x < boxThirdWidth*3 && _event->button.y > GLOBAL::GAP+boxHeight*2 && _event->button.y < boxHeight*3) {
							difficulty = 3;
						} else if (_event->button.x > GLOBAL::GAP && _event->button.x < GLOBAL::WIDTH-GLOBAL::GAP && _event->button.y > GLOBAL::GAP+boxHeight*3 && _event->button.y < boxHeight*4) {
							if (difficulty != -1) {
								_difficulty = difficulty;
								_players = 1;
								return;
							}
						}
					} else if (_event->button.x > GLOBAL::GAP && _event->button.x < GLOBAL::WIDTH-GLOBAL::GAP && _event->button.y > GLOBAL::GAP+boxHeight*2 && _event->button.y < boxHeight*3) {
						if (players == 2) {
							_players = 2;
							return;
						}
					}
				}
			} else if (_event->type == SDL_MOUSEMOTION) {
				_mouseMode = true;
			}
		}
		if (_mouseMode) {
			SDL_GetMouseState(_mouseX, _mouseY);

			if (*_mouseX > GLOBAL::GAP && *_mouseX < boxWidth && *_mouseY > GLOBAL::GAP+boxHeight && *_mouseY < boxHeight*2) {
				playerHover = 1;
			} else if (*_mouseX > boxWidth+GLOBAL::GAP && *_mouseX < GLOBAL::WIDTH-GLOBAL::GAP && *_mouseY > GLOBAL::GAP+boxHeight && *_mouseY < boxHeight*2) {
				playerHover = 2;
			} else {
				playerHover = -1;
			}

			if (players == 1) {
				if (*_mouseX > GLOBAL::GAP && *_mouseX < boxThirdWidth && *_mouseY > GLOBAL::GAP+boxHeight*2 && *_mouseY < boxHeight*3) {
					difficultyHover = 1;
				} else if (*_mouseX > boxThirdWidth+GLOBAL::GAP && *_mouseX < boxThirdWidth*2 && *_mouseY > GLOBAL::GAP+boxHeight*2 && *_mouseY < boxHeight*3) {
					difficultyHover = 2;
				} else if (*_mouseX > boxThirdWidth*2+GLOBAL::GAP && *_mouseX < boxThirdWidth*3 && *_mouseY > GLOBAL::GAP+boxHeight*2 && *_mouseY < boxHeight*3) {
					difficultyHover = 3;
				} else {
					difficultyHover = -1;
				}
			}

			if (players != 1) {
				if (*_mouseX > GLOBAL::GAP && *_mouseX < GLOBAL::WIDTH-10 && *_mouseY > GLOBAL::GAP+boxHeight*2 && *_mouseY < boxHeight*3) {
					playHover = true;
				} else {
					playHover = false;
				}
			} else {
				if (*_mouseX > GLOBAL::GAP && *_mouseX < GLOBAL::WIDTH-10 && *_mouseY > GLOBAL::GAP+boxHeight*3 && *_mouseY < boxHeight*4) {
					playHover = true;
				} else {
					playHover = false;
				}
			}
		}
	}
}

bool Game::play() {
	if (_quit) {
		return false;
	}
	menu();
	while (true) {
		if (_quit) {
			return false;
		}
		drawBoard();
		update();
		if (checkWin(_board->getBoard(0))) {
			if (_players == 1) {
				wait(6000, "You Lose");
			} else {
				wait(6000, "Blue Wins");
			}
			return true;
		} else if (checkWin(_board->getBoard(1))) {
			if (_players == 1) {
				wait(6000, "You Win");
			} else {
				wait(6000, "Red Wins");
			}
			return true;
		} else if (_board->full()) {
			wait(6000, "It's a tie!");
			return true;
		}
	}
}



void Game::drawBoard() {
	_graphics->clear();
	_board->draw(_graphics, _mouseColumn);
	_graphics->flip();
}

void Game::drawBoard(bool noFlip) {
	_graphics->clear();
	_board->draw(_graphics, _mouseColumn);
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