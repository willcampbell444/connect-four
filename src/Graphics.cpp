#include "Graphics.h"
#include "Globals.h"
#include <SDL.h>

Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(GLOBAL::WIDTH, GLOBAL::HEIGHT, 0, &_window, &_renderer);
	SDL_SetWindowTitle(_window, "Connect Four");
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
}

void Graphics::drawFillRect(int x1, int y1, int x2, int y2, int r, int g, int b) {
	SDL_Rect rect;
	rect.x = x1;
	rect.y = y1;
	rect.w = x2-x1;
	rect.h = y2-y1;

	SDL_SetRenderDrawColor(_renderer, r, g, b, 255);
	SDL_RenderFillRect(_renderer, &rect);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(_renderer, &rect);
}

void Graphics::drawRect(int x1, int y1, int x2, int y2, int r, int g, int b) {
	SDL_Rect rect;
	rect.x = x1;
	rect.y = y1;
	rect.w = x2-x1;
	rect.h = y2-y1;

	SDL_SetRenderDrawColor(_renderer, r, g, b, 255);
	SDL_RenderDrawRect(_renderer, &rect);
}

void Graphics::flip() {
	SDL_RenderPresent(_renderer);
}

void Graphics::clear() {
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);
}