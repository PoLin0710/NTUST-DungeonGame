#pragma once
#include "Position.h"

class RandomEvent {
private:
	Position sPos;	// RandomEvent location
	char sIcon = '?';	// RandomEvent icon

public:
	RandomEvent();

	// Set position
	void setPos(Position pos);

	void setPos(int x, int y);

	// Get position
	Position getPos() const;

	// Get Icon
	char getIcon() const;

	void treasure_big();
	void treasure_medium();
	void treasure_little();
	void found_money();

	void update();

	int diceNum;
	int bonusAmount;
	int hitRate;
};