#ifndef GAME_H
#define GAME_H

union SDL_Event;
class Graphics;
class Board;

class Game {
public:
	Game();
	void drawBoard();
	void play();
	void aiMove();
	// char checkWin(char *b[6]]);
private:
	Graphics* _graphics;
	SDL_Event* _event;
	Board* _board;
	int _state;
};


#endif