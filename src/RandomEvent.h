/***********************************************************************
 * File: RandomEvent.h
 * Author:
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Create Date: 2024-05-21
 * Editor:
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Update Date: 2024-05-21
 * Description: Implementation of the RandomEvent class, managing random in-game events
***********************************************************************/
#pragma once
#include "Position.h"

class RandomEvent {
private:
	Position sPos;	// RandomEvent location
	char sIcon = '?';	// RandomEvent icon

public:
	//Constructer
	RandomEvent();

	// Set position
	void setPos(Position pos);

	void setPos(int x, int y);

	// Get position
	Position getPos() const;

	// Get Icon
	char getIcon() const;

	//Event function
	void treasure_big();
	void treasure_medium();
	void treasure_little();
	void found_money();

	//Update
	void update();

	//Declare
	int diceNum;
	int bonusAmount;
	int hitRate;
};