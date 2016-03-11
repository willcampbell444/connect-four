#ifndef GAME_H
#define GAME_H

union SDL_Event;
class Graphics;

class Game {
public:
	Game();
	void drawBoard();
	void play();
private:
	Graphics* _graphics;
	SDL_Event* _event;
};


#endif