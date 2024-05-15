#pragma once
#include "Position.h"

class RandomEvent {
private:
	Position sPos;	// RandomEvent location
	char sIcon = 'R';	// RandomEvent icon
	int diceNum;
	int bonusAmount;

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

	void update(Position pos);

};
