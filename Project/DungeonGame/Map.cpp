#include "Map.h"

void setColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

char Map::getIcon(int x, int y) const
{
	return board[y][x];
}

void Map::setBoard()
{
	for (int i = 0; i <= 141; i++)
	{
		for (int j = 0; j <= 51; j++)
		{
			if (i == 0 || i == 141 || j == 0 || j == 51) {
				board[i][j] = ICON_IDX::WALL;
			}
			else {
				board[i][j] = ICON_IDX::ROAD;
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		int x, y;

		while (true)
		{
			y = rand() % 100 + 1, x = rand() % 40 + 1;

			if (board[y][x] == ICON_IDX::ROAD)
			{
				Shops.push_back(Shop(x, y));
				board[y][x] = Shops.back().getIcon();
				break;
			}
		}
	}
}

void Map::gameStart()
{
	int viewLeftUpX = 0, viewLeftUpY = 0;
	int x = 1, y = 1;
	int money = 1000; // GAME
	setBoard();

	while (true)
	{
		showBoard(viewLeftUpX, viewLeftUpY, x, y);
		char input = _getch();

		if (input == 'W' || input == 'w')
		{
			if (y >= 1) {
				y--;
			}

			if (y < viewLeftUpY) {
				viewLeftUpY--;
			}

			if (y == 0) {
				y++;
			}
		}
		else if (input == 'S' || input == 's')
		{
			if (y <= 140) {
				y++;
			}

			if (y >= viewLeftUpY + 20) {
				viewLeftUpY++;
			}

			if (y == 141) {
				y--;
			}
		}
		else if (input == 'A' || input == 'a')
		{
			if (x >= 1) {
				x--;
			}

			if (x < viewLeftUpX) {
				viewLeftUpX--;
			}

			if (x == 0) {
				x++;
			}
		}
		else if (input == 'D' || input == 'd')
		{
			if (x <= 50) {
				x++;
			}

			if (x >= viewLeftUpX + 40) {
				viewLeftUpX++;
			}

			if (x == 51) {
				x--;
			}
		}
		else if (input == '\r')
		{
			if (board[y][x] == (new Shop)->getIcon()) {
				(new Shop)->intoShop(money);
			}
		}
	}
}

void Map::showBoard(int viewLeftUpX, int viewLeftUpY, int x, int y)
{
	gotoxy(0, 0);

	for (int i = viewLeftUpY; i < viewLeftUpY + 20; i++)
	{
		for (int j = viewLeftUpX; j < viewLeftUpX + 40; j++)
		{
			if (i == y && x == j) {
				setColor(176);
			}
			else if (board[i][j] == (new Shop)->getIcon())
			{
				setColor(14);
			}
			else {
				setColor();
			}

			cout << board[i][j];
		}

		cout << "\n";
	}

	//cout << x << " " << y;
	setColor();
}