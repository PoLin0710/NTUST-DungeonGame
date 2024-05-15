#include "RandomEvent.h"
#include <iostream>
#include <cstdlib> 
using namespace std;


RandomEvent::RandomEvent()
{

}

// Set position
void RandomEvent::setPos(Position pos) {
	this->sPos = pos;
}

void RandomEvent::setPos(int x, int y) {
	this->sPos.x = x;
	this->sPos.y = y;
}

// Get position
Position RandomEvent::getPos() const { return this->sPos; }

// Get Icon
char RandomEvent::getIcon() const { return this->sIcon; }

void RandomEvent::treasure_big()
{
	this->diceNum = 5;
	this->bonusAmount = 1000;
}

void RandomEvent::treasure_medium()
{
	this->diceNum = 4;
	this->bonusAmount = 800;
}

void RandomEvent::treasure_little()
{
	this->diceNum = 3;
	this->bonusAmount = 500;
}

void RandomEvent::found_money()
{
	this->diceNum = 0;
	this->bonusAmount = 100;
}

void RandomEvent::update(Position rolePos)
{
	if (this->sPos == rolePos) {
		srand(time(NULL));
		int num = rand() % 4;

		switch (num)
		{
		case 0:
			treasure_big();
			break;
		case 1:
			treasure_medium();
			break;
		case 2:
			treasure_little();
			break;
		case 3:
			found_money();
			break;

		default:
			found_money();
			break;
		}

	}
}
