#ifndef GRAPHICS_H
#define GRAPHICS_H

struct SDL_Window;
struct SDL_Renderer;

class Graphics {
public:
	Graphics();
	~Graphics();

	void drawRect(int x1, int y1, int x2, int y2, int, int g, int b);
	void drawFillRect(int x1, int y1, int x2, int y2, int r, int g, int b);
	void flip();
	void clear();

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};


#endif