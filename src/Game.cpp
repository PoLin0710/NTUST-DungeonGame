#include "Game.h"

Game::Game()
{
	srand(time(NULL));

	roles.push_back(new Role("Role 1", '1'));
	roles.push_back(new Role("Role 2", '2'));
	roles.push_back(new Role("Role 3", '3'));

	board.resize(142, vector<char>(52));

	for (int i = 0; i < 100; i++)
	{
		std::string name = "Enemy" + to_string(i);

		enemys.push_back(new Entity(name, ENTITY_TYPE::ENEMY, 'E'));
	}

	setBoard();
}

void Game::setBoard()
{
	for (int i = 0; i <= 141; i++)
	{
		for (int j = 0; j <= 51; j++)
		{
			if (i == 0 || i == 141 || j == 0 || j == 51) {
				board[i][j] = char(ICON_IDX::WALL);
			}
			else {
				board[i][j] = ICON_IDX::ROAD;
			}
		}
	}


	for (int i = 0; i < 50; i++)
	{
		int x, y;

		y = rand() % 140 + 1, x = rand() % 50 + 1;
		board[y][x] = ICON_IDX::WALL;
	}

	for (int i = 0; i < 15; i++)
	{
		int x, y;

		while (true)
		{
			y = rand() % 100 + 1, x = rand() % 40 + 1;

			if (board[y][x] == ICON_IDX::ROAD)
			{
				shops.push_back(new Shop(x, y));
				board[y][x] = shops.back()->getIcon();
				break;
			}
		}

	}

	for (auto i : enemys)
	{
		while (true)
		{
			int x, y;
			y = rand() % 140 + 1, x = rand() % 50 + 1;

			if (board[y][x] == ICON_IDX::ROAD)
			{
				i->ePos = { x,y };
				board[y][x] = i->getIcon();
				break;
			}
		}
	}

	vector<vector<char>> tempBoard = board;

	for (auto i : roles)
	{
		while (true)
		{
			int x, y;
			y = rand() % 100 + 1, x = rand() % 40 + 1;

			if (tempBoard[y][x] == ICON_IDX::ROAD)
			{
				i->ePos = { x,y };
				tempBoard[y][x] = i->getIcon();
				break;
			}
		}
	}

}

void Game::showBoard(int viewLeftUpX, int viewLeftUpY, int x, int y, bool clear, Position delta)
{
	const int gotoX = 0;
	const int gotoY = 0;

	vector<vector<char>> tempBoard = board;

	for (auto i : roles)
	{
		tempBoard[i->ePos.y][i->ePos.x] = i->getIcon();
	}

	if (clear)
	{
		gotoxy(0, 0);


		for (int i = viewLeftUpY; i < viewLeftUpY + 20; i++)
		{
			for (int j = viewLeftUpX; j < viewLeftUpX + 40; j++)
			{
				if (i == y && x == j) {
					SetColor(176);
				}
				else if (tempBoard[i][j] == (new Shop)->getIcon())
				{
					SetColor(14);
				}
				else if (tempBoard[i][j] == 'E')
				{
					SetColor(12);
				}
				else {
					SetColor(7);
				}

				cout << tempBoard[i][j];
			}

			cout << "\n";
		}
		SetColor(7);
	}
	else
	{
		int lastX = x - delta.x - viewLeftUpX;
		int lastY = y - delta.y - viewLeftUpY;

		SetColor(176);
		gotoxy(x - viewLeftUpX, y - viewLeftUpY);
		cout << roles[0]->getIcon();//§ïorder

		gotoxy(lastX, lastY);

		if (tempBoard[lastY + viewLeftUpY][lastX + viewLeftUpX] == (new Shop)->getIcon())
		{
			SetColor(14);
		}
		else if (tempBoard[lastY + viewLeftUpY][lastX + viewLeftUpX] == 'E')
		{
			SetColor(12);
		}
		else {
			SetColor(7);
		}

		cout << tempBoard[lastY + viewLeftUpY][lastX + viewLeftUpX];

		gotoxy(0, 20);

	}

}

void Game::gameStart(Role* target)
{

	int viewLeftUpX = min(max(target->ePos.x - 15, 0), 10);
	int viewLeftUpY = min(max(target->ePos.y - 10, 0), 100);
	showBoard(viewLeftUpX, viewLeftUpY, target->ePos.x, target->ePos.y, true, { 0,0 });

	while (true)
	{
		bool isMove = true;
		bool moveVideo = false;
		Position delta;

		char input = _getch();

		if (input == 'W' || input == 'w')
		{
			if (target->ePos.y >= 1) {
				target->ePos.y--;
			}

			if (target->ePos.y < viewLeftUpY) {
				viewLeftUpY--;
				moveVideo = true;
			}

			if (target->ePos.y == 0) {
				target->ePos.y++;
			}

			delta = { 0,-1 };
		}
		else if (input == 'S' || input == 's')
		{
			if (target->ePos.y <= 140) {
				target->ePos.y++;
			}

			if (target->ePos.y >= viewLeftUpY + 20) {
				viewLeftUpY++;
				moveVideo = true;
			}

			if (target->ePos.y == 141) {
				target->ePos.y--;
			}

			delta = { 0, 1 };
		}
		else if (input == 'A' || input == 'a')
		{
			if (target->ePos.x >= 1) {
				target->ePos.x--;
			}

			if (target->ePos.x < viewLeftUpX) {
				viewLeftUpX--;
				moveVideo = true;
			}

			if (target->ePos.x == 0) {
				target->ePos.x++;
			}

			delta = { -1, 0 };
		}
		else if (input == 'D' || input == 'd')
		{
			if (target->ePos.x <= 50) {
				target->ePos.x++;
			}

			if (target->ePos.x >= viewLeftUpX + 40) {
				viewLeftUpX++;
				moveVideo = true;
			}

			if (target->ePos.x == 51) {
				target->ePos.x--;
			}

			delta = { 1, 0 };
		}
		else
		{
			isMove = false;

			delta = { 0,0 };
		}

		if (isMove)
		{
			showBoard(viewLeftUpX, viewLeftUpY, target->ePos.x, target->ePos.y, moveVideo, delta);
		}
	}
}

void Game::start()
{
	gameStart(roles[0]); //§ïorder
}
