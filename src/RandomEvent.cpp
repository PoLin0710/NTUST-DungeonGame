#include "RandomEvent.h"
#include "IO.h"
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
	gotoxy(78, 4);
	std::cout << "You find big treasure";

	gotoxy(92, 5);
	std::cout << "Five (1.024%) 1000$";
	gotoxy(92, 6);
	std::cout << "Four ( 7.68%)  800$";
	gotoxy(92, 7);
	std::cout << "Three(23.04%)  600$";
	gotoxy(92, 8);
	std::cout << "Two  (34.56%)  400$";
	gotoxy(92, 9);
	std::cout << "One  (25.92%)  200$";
	gotoxy(92, 10);
	std::cout << "Zero ( 7.77%)  -10% Heal";

	this->hitRate = 40;
	this->diceNum = 5;
	this->bonusAmount = 1000;
}

void RandomEvent::treasure_medium()
{
	gotoxy(78, 4);
	std::cout << "You find medium treasure";

	gotoxy(92, 5);
	std::cout << "Four ( 6.25%)  800$";
	gotoxy(92, 6);
	std::cout << "Three(25.00%)  600$";
	gotoxy(92, 7);
	std::cout << "Two  (37.50%)  400$";
	gotoxy(92, 8);
	std::cout << "One  (25.00%)  200$";
	gotoxy(92, 9);
	std::cout << "Zero ( 6.25%)  -10% Heal";

	this->hitRate = 50;
	this->diceNum = 4;
	this->bonusAmount = 800;
}

void RandomEvent::treasure_little()
{
	gotoxy(78, 4);
	std::cout << "You find medium treasure";

	gotoxy(92, 5);
	std::cout << "Three ( 21.60%)  500$";
	gotoxy(92, 6);
	std::cout << "Two   ( 43.20%)  333$";
	gotoxy(92, 7);
	std::cout << "One   (28.80%)   166$";
	gotoxy(92, 8);
	std::cout << "Zero ( 6.40%)";

	this->hitRate = 60;
	this->diceNum = 3;
	this->bonusAmount = 500;
}

void RandomEvent::found_money()
{
	gotoxy(78, 4);
	std::cout << "You find 100$";

	this->hitRate = 100;
	this->diceNum = 1;
	this->bonusAmount = 100;
}

void RandomEvent::update()
{

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