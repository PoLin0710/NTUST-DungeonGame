#pragma once
#include <vector>
#include<windows.h>
#include "Shop.h"

using namespace std;

enum ICON_IDX
{
	ROAD = '.',
	WALL = '#'
};

class Map
{
private:
	char board[142][52];
	vector<Shop> Shops;
	//vector<role> roles;  GAME

public:
	char getIcon(int x, int y) const;

	void setBoard();

	void gameStart();

	void showBoard(int viewLeftUpX, int viewLeftUpY, int x, int y);
};

