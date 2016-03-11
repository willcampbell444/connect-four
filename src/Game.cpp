#include "Game.h"
#include "Graphics.h"
#include <SDL.h>

Game::Game() {
	SDL_Init(SDL_INIT_VIDEO);
	_graphics = new Graphics();
	_event = new SDL_Event();
}

void Game::play() {
	while (true) {
		drawBoard();
		if (SDL_PollEvent(_event)) {
			if (_event->type == SDL_QUIT) {
				break;
			}
		}
	}
}

void Game::drawBoard() {
	_graphics->clear();
	_graphics->drawFillRect(100, 100, 700, 700, 255, 0, 255);
	_graphics->drawRect(100, 100, 700, 700, 0, 0, 0);
	_graphics->flip();
}