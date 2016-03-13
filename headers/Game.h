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
	bool checkWin(unsigned long long b);
private:
	Graphics* _graphics;
	SDL_Event* _event;
	Board* _board;
	int _state;

	// unsigned long long wins[69]; // Contains all possible winning boards
};


#endif