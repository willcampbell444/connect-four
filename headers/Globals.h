#ifndef GLOBAL_H
#define GLOBAL_H

namespace GLOBAL {
	const int WIDTH = 955;
	const int HEIGHT = 820;
	const int GAP = 10;
}

namespace STATE {
	const int PLAYER_DECISION = 1;
	const int AI_MOVE = 2;
	const int CHOOSE_DIFFICULTY = 3;
}

struct Color {
	int r, g, b;
};

namespace COLORS {
	const Color PLAYER1 = {175, 36, 11};
	const Color PLAYER2 = {21, 38, 119};
	const Color BACKGROUND = {192, 197, 206};
	// const Color BACKGROUND = {255, 255, 255};
	const Color UNCLAIMED = {151, 155, 162};
	// const Color UNCLAIMED = {227, 151, 72};
	const Color HIGHLIGHTED = {125, 130, 137};
	const Color TEXT = {43, 48, 59};
	const Color TEXTOUTLINE = {0, 0, 0};
}

#endif