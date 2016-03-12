#include "Game.h"
#include "Graphics.h"
#include "Board.h"
#include "Globals.h"
#include <SDL.h>

Game::Game() {
	SDL_Init(SDL_INIT_VIDEO);
	_graphics = new Graphics();
	_event = new SDL_Event();
	_board = new Board();
	_state = STATE::AI_MOVE;
}

void Game::aiMove() {
	_board->insert(4, 2);
	_board->getBoard();
}

// char Game::CheckWin(char *b[6]) {
	
// }

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
			}
		}
		if (_state == STATE::AI_MOVE) {
			aiMove();
			_state = STATE::PLAYER_DECISION;
		}
	}
}

void Game::drawBoard() {
	_graphics->clear();
	_board->draw(_graphics);
	_graphics->flip();
}