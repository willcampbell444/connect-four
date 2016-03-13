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
	_state = STATE::AI_MOVE;

	// // IF A AND WIN == WIN then you win!

	// // Find all winning moves
	// int count = 0;
	// for (int h = 0; int ) // horiontal wins
	// std::sort(wins, wins+69);
}

void Game::aiMove() {
	// _board->insert(4, 0);
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
		if (SDL_PollEvent(_event)) {
			if (_event->type == SDL_QUIT) {
				break;
			} else if (_state == STATE::PLAYER_DECISION && _event->type == SDL_MOUSEBUTTONUP) {
				if (_event->button.button == SDL_BUTTON_LEFT) {
					_board->insert(_event->button.x/(GLOBAL::WIDTH/7), 1);
					_state = STATE::AI_MOVE;
				}
				if (_event->button.button == SDL_BUTTON_RIGHT) {
					_board->insert(_event->button.x/(GLOBAL::WIDTH/7), 0);
					_state = STATE::AI_MOVE;
				}
			}
		}
		if (_state == STATE::AI_MOVE) {
			// aiMove();
			_state = STATE::PLAYER_DECISION;
		}
		if (checkWin(_board->getBoard(0))) {
			std::cout << "0\n";
			drawBoard();
			SDL_Delay(3000);
			return;
		} else if (checkWin(_board->getBoard(1))) {
			std::cout << "1\n";
			drawBoard();
			SDL_Delay(3000);
			return;
		}
	}
}

void Game::drawBoard() {
	_graphics->clear();
	_board->draw(_graphics);
	_graphics->flip();
}