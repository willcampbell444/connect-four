#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <SDL_ttf.h>
#include <map>

struct SDL_Window;
struct SDL_Renderer;
struct Color;
struct Text {
	SDL_Texture* texture;
	int w, h;
};

class Graphics {
public:
	Graphics();
	~Graphics();

	void drawRect(int x1, int y1, int x2, int y2, Color c);
	void drawFillRect(int x1, int y1, int x2, int y2, Color c);
	void drawFont(std::string in, int x, int y);
	void drawFontCentered(std::string in, int x, int y);
	void flip();
	void clear();

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	TTF_Font* _font;
	std::map<std::string, Text> _textTextures;
};

#endif