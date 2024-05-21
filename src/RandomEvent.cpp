/***********************************************************************
 * File: RandomEvent.cpp
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
#include "RandomEvent.h"
#include "IO.h"
#include <iostream>
#include <cstdlib> 
using namespace std;

// Intent: To initialize a RandomEvent object
// Pre: None
// Post: Constructs a RandomEvent object
RandomEvent::RandomEvent()
{
}

/**
 * Intent: To set the position of the random event using a Position object
 * Pre: pos must be a valid Position object
 * Post: Sets the position of the random event
 * \param pos A Position object representing the position of the random event
 */
void RandomEvent::setPos(Position pos) {
	this->sPos = pos;
}

/**
 * Intent: To set the position of the random event using x and y coordinates
 * Pre: x and y must be non-negative integers
 * Post: Sets the position of the random event
 * \param x The x-coordinate of the random event
 * \param y The y-coordinate of the random event
 */
void RandomEvent::setPos(int x, int y) {
	this->sPos.x = x;
	this->sPos.y = y;
}

/**
 * Intent: To get the position of the random event
 * Pre: None
 * Post: Returns the position of the random event
 * \return The position of the random event
 */
Position RandomEvent::getPos() const { return this->sPos; }

/**
 * Intent: To get the icon of the random event
 * Pre: None
 * Post: Returns the icon of the random event
 * \return The icon of the random event
 */
char RandomEvent::getIcon() const { return this->sIcon; }

/**
 * Intent: To handle a big treasure event
 * Pre: None
 * Post: Displays the big treasure event details and sets the hit rate, dice number, and bonus amount
 */
void RandomEvent::treasure_big()
{
	//==Output==
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
	//=============

	//Set
	this->hitRate = 40;
	this->diceNum = 5;
	this->bonusAmount = 1000;
}

/**
 * Intent: To handle a medium treasure event
 * Pre: None
 * Post: Displays the medium treasure event details and sets the hit rate, dice number, and bonus amount
 */
void RandomEvent::treasure_medium()
{
	//==Output==
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
	//===========

	//Set
	this->hitRate = 50;
	this->diceNum = 4;
	this->bonusAmount = 800;
}

/**
 * Intent: To handle a little treasure event
 * Pre: None
 * Post: Displays the little treasure event details and sets the hit rate, dice number, and bonus amount
 */
void RandomEvent::treasure_little()
{
	//==Output==
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
	//============

	//Set
	this->hitRate = 60;
	this->diceNum = 3;
	this->bonusAmount = 500;
}

/**
 * Intent: To handle a found money event
 * Pre: None
 * Post: Displays the found money event details and sets the hit rate, dice number, and bonus amount
 */
void RandomEvent::found_money()
{
	//Output
	gotoxy(78, 4);
	std::cout << "You find 100$";

	//Set
	this->hitRate = 100;
	this->diceNum = 1;
	this->bonusAmount = 100;
}

/**
 * Intent: To update the random event to a new random event
 * Pre: None
 * Post: Sets the random event to one of the predefined events
 */
void RandomEvent::update()
{
	int num = rand() % 4; //Random Event

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