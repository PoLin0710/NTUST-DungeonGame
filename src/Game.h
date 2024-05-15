#pragma once

#include <vector>
#include "Shop.h"
#include "Combat.h"

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
	void showBoard(int viewLeftUpX, int viewLeftUpY, int x, int y, bool clear, Position delta);
	void gameStart(Role*);
	void start();
private:
	std::vector<Role*> roles;
	std::vector<Entity*> enemys;
	vector<Shop*> shops;
	vector<vector<char>> board;
	vector<Role*> order;
};

