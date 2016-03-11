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
}

void Game::play() {
	while (true) {
		drawBoard();
		if (SDL_PollEvent(_event)) {
			if (_event->type == SDL_QUIT) {
				break;
			} else if (_event->type == SDL_MOUSEBUTTONUP) {
				if (_event->button.button == SDL_BUTTON_LEFT) {
					_board->insert(_event->button.x/(GLOBAL::WIDTH/7), 1);
				} else if (_event->button.button == SDL_BUTTON_RIGHT) {
					_board->insert(_event->button.x/(GLOBAL::WIDTH/7), 2);
				}
			}
		}
	}
}

void Game::drawBoard() {
	_graphics->clear();
	_board->draw(_graphics);
	_graphics->flip();
}