#include "Graphics.h"
#include "Globals.h"
#include <SDL.h>
// #include <SDL_ttf.h>


Graphics::Graphics() {
	SDL_CreateWindowAndRenderer(GLOBAL::WIDTH, GLOBAL::HEIGHT, 0, &_window, &_renderer);
	SDL_SetWindowTitle(_window, "Connect Four");

	TTF_Init();

	_font = TTF_OpenFont("assets/arial.ttf", 72);
}

Graphics::~Graphics() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	TTF_CloseFont(_font);
	TTF_Quit();
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

void Graphics::drawFont(std::string in, int x, int y) {
	if (_textTextures.find(in) == _textTextures.end()) {
		SDL_Color c = {0, 0, 0, 0};
		SDL_Surface* textSurface = TTF_RenderText_Blended(_font, in.c_str(), c);
		Text text;
		text.texture = SDL_CreateTextureFromSurface(_renderer, textSurface);
		text.w = textSurface->w;
		text.h = textSurface->h;
		_textTextures[in] = text;
		SDL_FreeSurface(textSurface);
	}
	SDL_Rect dest = {x, y, _textTextures[in].w, _textTextures[in].h};
	SDL_RenderCopy(_renderer, _textTextures[in].texture, NULL, &dest);
}

void Graphics::drawFontCentered(std::string in, int x, int y) {
	if (_textTextures.find(in) == _textTextures.end()) {
		SDL_Color c = {0, 0, 0, 0};
		SDL_Surface* textSurface = TTF_RenderText_Blended(_font, in.c_str(), c);
		Text text;
		text.texture = SDL_CreateTextureFromSurface(_renderer, textSurface);
		text.w = textSurface->w;
		text.h = textSurface->h;
		_textTextures[in] = text;
		SDL_FreeSurface(textSurface);
	}
	SDL_Rect dest = {x-(_textTextures[in].w/2), y-(_textTextures[in].h/2), _textTextures[in].w, _textTextures[in].h};
	SDL_RenderCopy(_renderer, _textTextures[in].texture, NULL, &dest);
}

void Graphics::flip() {
	SDL_RenderPresent(_renderer);
}

void Graphics::clear() {
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);
}