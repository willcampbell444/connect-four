#ifndef GAME_H
#define GAME_H

#include <string>

union SDL_Event;
class Graphics;
class Board;

class Game {
public:
	Game();
	void drawBoard();
	void drawBoard(bool noFlip);
	bool play();
	void aiMove();
	int analyze(unsigned long long p0, unsigned long long p1);
	int negamax(unsigned long long p0, unsigned long long p1, int alpha, int beta, int color, int depth);
	int minimax(unsigned long long blue, unsigned long long red, int alpha, int beta, int depth, bool maximize);
	unsigned long long insertIntoBitboard(unsigned long long toAdd, unsigned long long other, int x);
	bool checkWin(unsigned long long b);
	void restart();
	void update();
	void wait(int length);
	void wait(int length, std::string message);
private:
	Graphics* _graphics;
	SDL_Event* _event;
	Board* _board;
	int _state;
	int _mouseColumn;
	int* _mouseX;
	int* _mouseY;
	bool _quit;
	bool _mouseMode;

	// unsigned long long wins[69]; // Contains all possible winning boards
};


#endif