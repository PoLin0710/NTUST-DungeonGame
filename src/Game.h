#pragma once

#include <vector>
#include "Shop.h"
#include "Combat.h"
#include "RandomEvent.h"

enum ICON_IDX
{
	ROAD = '.',
	WALL = '#'
};

class Game
{
public:
	Game();
	//~Game();

	void setBoard();
	void showBoard(int viewLeftUpX, int viewLeftUpY, int x, int y, bool clear, Position delta, bool detect);
	void showAllMap(int viewLeftUpX, int viewLeftUpY, int x, int y);
	void gameStart(Role*);
	void start();
	bool vaildMove(Position, bool alldetect);
	bool useItem();
private:
	std::vector<Role*> roles;
	std::vector<Entity*> enemys;
	vector<Shop*> shops;
	vector<vector<char>> board;
	vector<Role*> order;
	vector<RandomEvent*> events;

	Role* now;
	int maxMove;
};

