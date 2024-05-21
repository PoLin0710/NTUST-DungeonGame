/***********************************************************************
 * File: Game.h
 * Author:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Create Date: 2024-05-21
 * Editor:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Update Date: 2024-05-21
 * Description: Declaration of the Game class, managing the overall game state and flow.
***********************************************************************/
#pragma once

#include <vector>
#include "Shop.h"
#include "Combat.h"
#include "RandomEvent.h"

//Declare Icon
enum ICON_IDX
{
	ROAD = '.',
	WALL = '#'
};

class Game
{
public:
	//Constructer
	Game();

	//Destructer
	//~Game();

	//Function
	void setBoard();
	void showBoard(int viewLeftUpX, int viewLeftUpY, int x, int y, bool clear, Position delta, bool detect);
	void showAllMap(int viewLeftUpX, int viewLeftUpY, int x, int y);
	void gameStart(Role*);
	void start();
	bool vaildMove(Position, bool alldetect);
	bool useItem();

private:
	//Declare attribute
	std::vector<Role*> roles;
	std::vector<Entity*> enemys;
	vector<Shop*> shops;
	vector<vector<char>> board;
	vector<Role*> order;
	vector<RandomEvent*> events;

	//Declare now player
	Role* now;

	//can Move step
	int maxMove;
};

