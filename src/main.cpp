#include "Game.h"

int main() {
	Game game;
	while (game.play()) {
		game.restart();
	}

	return 0;
}