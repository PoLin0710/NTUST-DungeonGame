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

	for (int i = 0; i < 100; i++)
	{
		events.push_back(new RandomEvent);
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

	for (auto i : events)
	{
		while (true)
		{
			int x, y;
			y = rand() % 140 + 1, x = rand() % 50 + 1;

			if (board[y][x] == ICON_IDX::ROAD)
			{
				i->setPos({ x,y });
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

void Game::showBoard(int viewLeftUpX, int viewLeftUpY, int x, int y, bool clear, Position delta, bool detect)
{
	int gotoX = 18;
	int gotoY = 5;

	vector<vector<char>> tempBoard = board;

	for (auto i : roles)
	{
		tempBoard[i->ePos.y][i->ePos.x] = i->getIcon();
	}

	if (clear)
	{
		showAllMap(viewLeftUpX, viewLeftUpY, x, y);
	}
	else
	{
		int lastX = x - delta.x - viewLeftUpX + gotoX;
		int lastY = y - delta.y - viewLeftUpY + gotoY;

		int indexX = x - delta.x;
		int indexY = y - delta.y;

		SetColor(176);
		gotoxy(x - viewLeftUpX + gotoX, y - viewLeftUpY + gotoY);

		if (detect)
		{
			cout << now->getIcon();//改order
		}
		else
		{
			cout << " ";
		}

		gotoxy(lastX, lastY);

		if (tempBoard[indexY][indexX] == (new Shop)->getIcon())
		{
			SetColor(14);
		}
		else if (tempBoard[indexY][indexX] == 'E')
		{
			SetColor(12);
		}
		else if (tempBoard[indexY][indexX] == '?')
		{
			SetColor(10);
		}
		else if (tempBoard[indexY][indexX] == 'T')
		{
			SetColor(206);
		}
		else {
			SetColor(7);
		}

		cout << tempBoard[indexY][indexX];

		gotoxy(0, 20);

	}

	SetColor(7);

	if (!detect)
	{
		return;
	}

	if (board[y][x] == (new Shop)->getIcon())
	{
		printFileAtPosition("mainInfo.txt", 77, 2);
		gotoxy(78, 3);
		std::cout << "Welcome OOP Shop!!";

		int index = 0;
		gotoxy(80, 6);
		std::cout << "->";

		gotoxy(82, 6);
		std::cout << " Enter it";

		gotoxy(82, 7);
		std::cout << " Exit";

		while (true)
		{
			char command = _getch();

			if (command == 'W' || command == 'w')
			{
				gotoxy(80, 6 + index);
				std::cout << "  ";

				index = index - 1 < 0 ? 1 : index - 1;

				gotoxy(80, 6 + index);
				std::cout << "->";
			}
			else if (command == 'S' || command == 's')
			{
				gotoxy(80, 6 + index);
				std::cout << "  ";

				index = index + 1 == 2 ? 0 : index + 1;

				gotoxy(80, 6 + index);
				std::cout << "->";
			}
			else if (command == 13)
			{
				if (index == 0)
				{
					now->insertBag((new Shop)->intoShop(now->getMoney()));

					printFileAtPosition("BD2.txt", 0, 0);

					gotoxy(105, 1);
					std::cout << "Money : " << now->getMoney() << " $";

					roles[0]->printInfo(6, 29);
					roles[1]->printInfo(44, 29);
					roles[2]->printInfo(82, 29);

					showAllMap(viewLeftUpX, viewLeftUpY, x, y);

					gotoxy(78, 3);
					std::cout << "Current Player: " << now->getName();
					gotoxy(78, 4);
					cout << "move step: " << maxMove;

					break;
				}
				else if (index == 1)
				{
					printFileAtPosition("mainInfo.txt", 77, 2);
					gotoxy(78, 3);
					std::cout << "Current Player: " << now->getName();
					gotoxy(78, 4);
					cout << "move step: " << maxMove;

					gotoxy(78, 25);
					std::cout << "End(Enter)";
					gotoxy(78, 26);
					std::cout << "Open Bag(i)";
					gotoxy(78, 27);
					std::cout << "W,A,S,D to Move";
					break;
				}
			}
		}
	}
	else if (board[y][x] == 'E')
	{
		int random = rand() % 3 + 1;

		printFileAtPosition("mainInfo.txt", 77, 2);
		gotoxy(78, 3);
		std::cout << "Dangerous!!";
		gotoxy(78, 4);
		std::cout << "Enemy Have :" << random;


		int index = 0;
		gotoxy(80, 6);
		std::cout << "->";

		gotoxy(82, 6);
		std::cout << " Attack!!";

		gotoxy(82, 7);
		std::cout << " Exit";

		while (true)
		{
			gotoxy(78, 25);
			std::cout << "End(Enter)";
			gotoxy(78, 26);
			std::cout << "Choose UP (W), DOWN(S)";
			gotoxy(78, 27);
			std::cout << "Enter to check!";

			char command = _getch();

			if (command == 'W' || command == 'w')
			{
				gotoxy(80, 6 + index);
				std::cout << "  ";

				index = index - 1 < 0 ? 1 : index - 1;

				gotoxy(80, 6 + index);
				std::cout << "->";
			}
			else if (command == 'S' || command == 's')
			{
				gotoxy(80, 6 + index);
				std::cout << "  ";

				index = index + 1 == 2 ? 0 : index + 1;

				gotoxy(80, 6 + index);
				std::cout << "->";
			}
			else if (command == 13)
			{
				if (index == 0)
				{
					vector<Entity*> curEnemys;

					for (int i = 0; i < random; i++)
					{
						std::string name = "Enemy" + to_string(i);

						curEnemys.push_back(new Entity(name, ENTITY_TYPE::ENEMY, 'E'));
					}

					Combat combat(roles, curEnemys);
					combat.start();

					system("cls");
					board[y][x] = ICON_IDX::ROAD;
					printFileAtPosition("BD2.txt", 0, 0);

					gotoxy(105, 1);
					std::cout << "Money : " << now->getMoney() << " $";

					roles[0]->printInfo(6, 29);
					roles[1]->printInfo(44, 29);
					roles[2]->printInfo(82, 29);

					showAllMap(viewLeftUpX, viewLeftUpY, x, y);

					gotoxy(78, 3);
					std::cout << "Current Player: " << now->getName();
					gotoxy(78, 4);
					cout << "move step: " << maxMove;

					break;
				}
				else if (index == 1)
				{
					printFileAtPosition("mainInfo.txt", 77, 2);
					gotoxy(78, 3);
					std::cout << "Current Player: " << now->getName();
					gotoxy(78, 4);
					cout << "move step: " << maxMove;
					break;
				}
			}
		}
	}
	else if (board[y][x] == '?')
	{
		printFileAtPosition("mainInfo.txt", 77, 2);
		gotoxy(78, 3);
		std::cout << "Random Event!!";

		RandomEvent newEvent;
		newEvent.update();

		int index = 0;
		gotoxy(80, 6);
		std::cout << "->";

		gotoxy(82, 6);
		std::cout << " Try!!";

		gotoxy(82, 7);
		std::cout << " Flee";

		while (true)
		{
			gotoxy(78, 26);
			std::cout << "Choose UP (W), DOWN(S)";
			gotoxy(78, 27);
			std::cout << "Enter to check!";
			char command = _getch();

			if (command == 'W' || command == 'w')
			{
				gotoxy(80, 6 + index);
				std::cout << "  ";

				index = index - 1 < 0 ? 1 : index - 1;

				gotoxy(80, 6 + index);
				std::cout << "->";
			}
			else if (command == 'S' || command == 's')
			{
				gotoxy(80, 6 + index);
				std::cout << "  ";

				index = index + 1 == 2 ? 0 : index + 1;

				gotoxy(80, 6 + index);
				std::cout << "->";
			}
			else if (command == 13)
			{
				if (index == 0)
				{
					now->setHitRate(newEvent.hitRate);
					double rate = now->RolltheDice(newEvent.diceNum, 0, 80, 13);
					if (rate == 0)
					{
						now->setVitality(now->getVitality() * 0.9);
					}
					else
					{
						now->addMoney(newEvent.bonusAmount * rate);
					}

					now->setHitRate(now->getHitRate());

					board[y][x] = ICON_IDX::ROAD;
					system("cls");

					printFileAtPosition("BD2.txt", 0, 0);

					gotoxy(105, 1);
					std::cout << "Money : " << now->getMoney() << " $";

					roles[0]->printInfo(6, 29);
					roles[1]->printInfo(44, 29);
					roles[2]->printInfo(82, 29);

					showAllMap(viewLeftUpX, viewLeftUpY, x, y);

					gotoxy(78, 3);
					std::cout << "Current Player: " << now->getName();
					gotoxy(78, 4);
					cout << "move step: " << maxMove;

					break;
				}
				else if (index == 1)
				{
					printFileAtPosition("mainInfo.txt", 77, 2);
					gotoxy(78, 3);
					std::cout << "Random Event!!";

					gotoxy(78, 3);
					std::cout << "Current Player: " << now->getName();
					gotoxy(78, 4);
					cout << "move step: " << maxMove;

					gotoxy(78, 25);
					std::cout << "End(Enter)";
					gotoxy(78, 26);
					std::cout << "Open Bag(i)";
					gotoxy(78, 27);
					std::cout << "W,A,S,D to Move";
					break;
				}
			}
		}
	}
	else if (board[y][x] == 'T')
	{
		printFileAtPosition("mainInfo.txt", 77, 2);
		gotoxy(78, 3);
		std::cout << "Current Player: " << now->getName();
		gotoxy(78, 4);
		cout << "move step: " << maxMove;

		gotoxy(78, 6);
		cout << "In Tent";

		gotoxy(78, 25);
		std::cout << "End(Enter)";
		gotoxy(78, 26);
		std::cout << "Open Bag(i)";
		gotoxy(78, 27);
		std::cout << "W,A,S,D to Move";
	}
	else
	{
		printFileAtPosition("mainInfo.txt", 77, 2);
		gotoxy(78, 3);
		std::cout << "Current Player: " << now->getName();
		gotoxy(78, 4);
		cout << "move step: " << maxMove;

		gotoxy(78, 25);
		std::cout << "End(Enter)";
		gotoxy(78, 26);
		std::cout << "Open Bag(i)";
		gotoxy(78, 27);
		std::cout << "W,A,S,D to Move";
	}

	gotoxy(0, 41);

}

void Game::showAllMap(int viewLeftUpX, int viewLeftUpY, int x, int y)
{
	int gotoX = 18;
	int gotoY = 5;

	gotoxy(78, 25);
	std::cout << "End(Enter)";
	gotoxy(78, 26);
	std::cout << "Open Bag(i)";
	gotoxy(78, 27);
	std::cout << "W,A,S,D to Move";

	gotoxy(8, 1);

	for (auto it = order.begin(); it != order.end(); ++it) {
		if ((*it)->getVitality() == 0)
		{
			SetColor(8);
		}
		cout << (*it)->getName();
		SetColor(7);

		if (it != order.end() - 1) {
			cout << " -> ";
		}
	}

	vector<vector<char>> tempBoard = board;

	for (auto i : roles)
	{
		tempBoard[i->ePos.y][i->ePos.x] = i->getIcon();
	}

	for (int i = min(viewLeftUpY, 122); i < viewLeftUpY + 20; i++)
	{
		gotoxy(gotoX, gotoY++);
		for (int j = min(viewLeftUpX, 12); j < viewLeftUpX + 40; j++)
		{
			if ((i == now->ePos.y && now->ePos.x == j) || (i == y && j == x)) {
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
			else if (tempBoard[i][j] == '?')
			{
				SetColor(10);
			}
			else if (tempBoard[i][j] == 'T')
			{
				SetColor(206);
			}
			else {
				SetColor(7);
			}

			cout << tempBoard[i][j];
		}

		cout << "\n";
	}
	SetColor(7);

	if (now->getName() == "Role 1")
	{
		SetColor(10);
		printFileAtPosition("BD1.txt", 5, 28);
		SetColor(7);
		roles[0]->printInfo(6, 29);
	}
	else if (now->getName() == "Role 2")
	{
		SetColor(10);
		printFileAtPosition("BD1.txt", 43, 28);
		SetColor(7);
		roles[1]->printInfo(44, 29);
	}
	else if (now->getName() == "Role 3")
	{
		SetColor(10);
		printFileAtPosition("BD1.txt", 81, 28);
		SetColor(7);
		roles[2]->printInfo(82, 29);
	}
}

void Game::gameStart(Role* target)
{
	maxMove = 0;

	int viewLeftUpX = min(max(target->ePos.x - 15, 0), 10);
	int viewLeftUpY = min(max(target->ePos.y - 10, 0), 100);
	showBoard(viewLeftUpX, viewLeftUpY, target->ePos.x, target->ePos.y, true, { 0,0 }, true);
	//printFileAtPosition("mainInfo.txt", 77, 2);

	gotoxy(78, 3);
	std::cout << "Current Player: " << now->getName();
	gotoxy(78, 25);
	std::cout << "End(Enter)";
	gotoxy(78, 26);
	std::cout << "Open Bag(i)";
	gotoxy(78, 27);
	std::cout << "W,A,S,D to Move";
	gotoxy(78, 4);
	cout << "move step: ";
	now->setHitRate(min(now->getSpeed(), 90));
	maxMove = (now->getSpeed() / 10) * now->RolltheDice(now->getSpeed() / 10, 0, 78, 5);
	gotoxy(78, 4);
	cout << "move step: " << maxMove;

	char input = ' ';

	while (input != 13 && now->getVitality() > 0)
	{
		bool isMove = true;
		bool moveVideo = false;
		Position delta;

		input = _getch();

		if ((input == 'W' || input == 'w') && maxMove > 0)
		{


			if (vaildMove({ target->ePos.x, target->ePos.y - 1 }, false)) {
				target->ePos.y--;
			}
			else
			{
				isMove = false;

				if (target->ePos.y == 1)
				{
					viewLeftUpY = 0;
					moveVideo = true;
				}

			}

			if (target->ePos.y - 1 < viewLeftUpY) {
				viewLeftUpY--;
				moveVideo = true;
			}

			delta = { 0,-1 };
		}
		else if ((input == 'S' || input == 's') && maxMove > 0)
		{
			if (vaildMove({ target->ePos.x, target->ePos.y + 1 }, false)) {
				target->ePos.y++;
			}
			else
			{
				isMove = false;

				if (target->ePos.y + 1 == 140)
				{
					viewLeftUpY = 122;
					moveVideo = true;
				}
			}

			if (target->ePos.y + 1 >= viewLeftUpY + 20) {
				viewLeftUpY++;
				moveVideo = true;
			}

			delta = { 0, 1 };
		}
		else if ((input == 'A' || input == 'a') && maxMove > 0)
		{

			if (vaildMove({ target->ePos.x - 1, target->ePos.y }, false)) {
				target->ePos.x--;
			}
			else
			{
				isMove = false;

				if (target->ePos.x == 1)
				{
					viewLeftUpX = 0;
					moveVideo = true;
				}
			}

			if (target->ePos.x - 1 < viewLeftUpX) {
				viewLeftUpX--;
				moveVideo = true;
			}

			delta = { -1, 0 };
		}
		else if ((input == 'D' || input == 'd') && maxMove > 0)
		{
			if (vaildMove({ target->ePos.x + 1, target->ePos.y }, false)) {
				target->ePos.x++;
			}
			else
			{
				isMove = false;

				if (target->ePos.x == 50)
				{
					viewLeftUpX = 12;
					moveVideo = true;
				}
			}

			if (target->ePos.x + 1 >= viewLeftUpX + 40) {
				viewLeftUpX++;
				moveVideo = true;
			}

			delta = { 1, 0 };
		}
		else if (input == 'I' || input == 'i')
		{
			isMove = false;
			useItem();

			viewLeftUpX = min(max(target->ePos.x - 15, 0), 10);
			viewLeftUpY = min(max(target->ePos.y - 10, 0), 100);

			moveVideo = true;

		}
		else
		{
			isMove = false;

			delta = { 0,0 };
		}

		if (isMove || moveVideo)
		{
			if (isMove)
			{
				maxMove -= isMove;
			}

			showBoard(viewLeftUpX, viewLeftUpY, target->ePos.x, target->ePos.y, moveVideo, delta, true);
		}
	}

	if (now->getVitality() != 0)
	{
		if (board[now->ePos.y][now->ePos.x] == 'T')
		{
			now->setVitality(now->getVitality() + 50);
			now->setFocus(now->getFocus() + 5);
		}

		now->setVitality(now->getVitality() + maxMove);
	}

}

void Game::start()
{
	const int requiredRows = 70;
	const int requiredCols = 120;

	hideCursor();
	// 重複檢查螢幕大小
	while (true) {
		if (checkConsoleSize(requiredRows, requiredCols)) {
			system("cls");
			printFileAtPosition("start.txt", 0, 0);
			Sleep(2500);


			system("cls");
			printFileAtPosition("BD2.txt", 0, 0);

			gotoxy(105, 1);
			std::cout << "Money : " << now->getMoney() << " $";

			roles[0]->printInfo(6, 29);
			roles[1]->printInfo(44, 29);
			roles[2]->printInfo(82, 29);
			break;
		}
		else {
			system("cls");
			std::cerr << "請調整螢幕大小至至少 " << requiredRows << " 行 " << requiredCols << " 列" << std::endl;
			Sleep(1000); // 等待 3 秒鐘
		}
	}

	for (auto i : roles)
	{
		order.push_back(i);
	}

	std::sort(order.begin(), order.end(), [](Entity* a, Entity* b) {
		return a->getSpeed() > b->getSpeed();
		});

	gotoxy(8, 1);

	for (auto it = order.begin(); it != order.end(); ++it) {
		if ((*it)->getVitality() == 0)
		{
			SetColor(8);
		}
		cout << (*it)->getName();
		SetColor(7);

		if (it != order.end() - 1) {
			cout << " -> ";
		}
	}

	while (true)
	{
		for (auto i : order)
		{
			now = i;

			if (i->getVitality() == 0)
			{
				continue;
			}
			else
			{
				if (i->getName() == "Role 1")
				{
					SetColor(10);
					printFileAtPosition("BD1.txt", 5, 28);
					SetColor(7);
					roles[0]->printInfo(6, 29);
				}
				else if (i->getName() == "Role 2")
				{
					SetColor(10);
					printFileAtPosition("BD1.txt", 43, 28);
					SetColor(7);
					roles[1]->printInfo(44, 29);
				}
				else if (i->getName() == "Role 3")
				{
					SetColor(10);
					printFileAtPosition("BD1.txt", 81, 28);
					SetColor(7);
					roles[2]->printInfo(82, 29);
				}

				gameStart(now);

				if (i->getName() == "Role 1")
				{
					SetColor(7);
					printFileAtPosition("BD1.txt", 5, 28);
					SetColor(7);
					roles[0]->printInfo(6, 29);
				}
				else if (i->getName() == "Role 2")
				{
					SetColor(7);
					printFileAtPosition("BD1.txt", 43, 28);
					SetColor(7);
					roles[1]->printInfo(44, 29);
				}
				else if (i->getName() == "Role 3")
				{
					SetColor(7);
					printFileAtPosition("BD1.txt", 81, 28);
					SetColor(7);
					roles[2]->printInfo(82, 29);
				}
			}

			gotoxy(0, 41);
		}

		bool end = true;

		for (auto i : roles)
		{
			if (i->getVitality() > 0)
			{
				end = false;
			}
		}

		if (end)
		{
			break;
		}
	}

	system("cls");
	printFileAtPosition("gameover.txt", 0, 0);

}

bool Game::vaildMove(Position target, bool alldetect)
{
	if (!alldetect)
	{
		return board[target.y][target.x] != ICON_IDX::WALL;
	}
	else
	{
		return board[target.y][target.x] == ICON_IDX::ROAD;
	}
}

bool Game::useItem()
{
	printFileAtPosition("mainInfo.txt", 77, 2);
	vector<pair<int, int>> temp;//bagIdx,itemIdx
	vector<Bag>tempBag = now->getBag();

	int index = 0;
	for (auto i : tempBag)
	{
		temp.push_back({ index,i.index });
		index++;
	}

	gotoxy(78, 3);
	std::cout << "Item: ";

	int pr = 1;
	for (auto i : temp)
	{
		gotoxy(82, 3 + pr);
		std::cout << getItemName(i.second);

		if (pr == 10)
		{
			break;
		}

		pr++;
	}

	gotoxy(78, 25);
	std::cout << "Back(BackSpace)";
	gotoxy(78, 26);
	std::cout << "Choose UP (W), DOWN(D)  ";
	gotoxy(78, 27);
	std::cout << "Enter to check!         ";


	index = 0;
	int viewLeftUpX = min(max(now->ePos.x - 15, 0), 10);
	int viewLeftUpY = min(max(now->ePos.y - 10, 0), 100);

	while (true)
	{

		gotoxy(78, 4 + (index % 10));
		std::cout << "->";
		gotoxy(0, 48);

		char command = _getch();
		if (command == 8)//back
		{
			printFileAtPosition("mainInfo.txt", 77, 2);
			gotoxy(78, 3);
			std::cout << "Current Player: " << now->getName();
			gotoxy(78, 4);
			cout << "move step: " << maxMove;

			gotoxy(78, 25);
			std::cout << "End(Enter)";
			gotoxy(78, 26);
			std::cout << "Open Bag(i)";
			gotoxy(78, 27);
			std::cout << "W,A,S,D to Move";

			break;
		}
		else if (command == 13)
		{
			if (temp[index].second == ITEM_IDX::ITELEPORT_SCROLL)
			{
				Position temp = now->ePos;
				gotoxy(78, 25);

				std::cout << "                            ";
				gotoxy(78, 26);
				std::cout << "Use W,A,S,D to choose target!";
				gotoxy(78, 27);
				std::cout << "Enter to check!             ";

				while (true)
				{
					bool isMove = true;
					bool moveVideo = false;
					Position delta;

					char input = _getch();

					if (input == 'W' || input == 'w')
					{


						if (vaildMove({ temp.x, temp.y - 1 }, true)) {
							temp.y--;
						}
						else
						{
							isMove = false;

							if (temp.y == 1)
							{
								viewLeftUpY = 0;
								moveVideo = true;
							}

						}

						if (temp.y - 1 < viewLeftUpY) {
							viewLeftUpY--;
							moveVideo = true;
						}

						delta = { 0,-1 };
					}
					else if (input == 'S' || input == 's')
					{
						if (vaildMove({ temp.x, temp.y + 1 }, true)) {
							temp.y++;
						}
						else
						{
							isMove = false;

							if (temp.y + 1 == 140)
							{
								viewLeftUpY = 122;
								moveVideo = true;
							}
						}

						if (temp.y + 1 >= viewLeftUpY + 20) {
							viewLeftUpY++;
							moveVideo = true;
						}

						delta = { 0, 1 };
					}
					else if (input == 'A' || input == 'a')
					{

						if (vaildMove({ temp.x - 1, temp.y }, true)) {
							temp.x--;
						}
						else
						{
							isMove = false;

							if (temp.x == 1)
							{
								viewLeftUpX = 0;
								moveVideo = true;
							}
						}

						if (temp.x - 1 < viewLeftUpX) {
							viewLeftUpX--;
							moveVideo = true;
						}

						delta = { -1, 0 };
					}
					else if (input == 'D' || input == 'd')
					{
						if (vaildMove({ temp.x + 1, temp.y }, true)) {
							temp.x++;
						}
						else
						{
							isMove = false;

							if (temp.x == 50)
							{
								viewLeftUpX = 12;
								moveVideo = true;
							}
						}

						if (temp.x + 1 >= viewLeftUpX + 40) {
							viewLeftUpX++;
							moveVideo = true;
						}

						delta = { 1, 0 };
					}
					else if (input == 13)
					{
						now->ePos.x = temp.x;
						now->ePos.y = temp.y;

						showBoard(viewLeftUpX, viewLeftUpY, temp.x, temp.y, true, delta, true);

						printFileAtPosition("mainInfo.txt", 77, 2);

						gotoxy(78, 3);
						std::cout << "Current Player: " << now->getName();

						gotoxy(78, 25);
						std::cout << "End(Enter)";
						gotoxy(78, 26);
						std::cout << "Open Bag(i)";
						gotoxy(78, 27);
						std::cout << "W,A,S,D to Move";
						gotoxy(78, 4);
						cout << "move step: " << maxMove;
						break;
					}
					else
					{
						isMove = false;

						delta = { 0,0 };
					}

					if (isMove || moveVideo)
					{
						showBoard(viewLeftUpX, viewLeftUpY, temp.x, temp.y, moveVideo, delta, false);
					}


				}
			}
			else if (temp[index].second == ITEM_IDX::ITENT)
			{
				board[now->ePos.y][now->ePos.x] = 'T';
			}

			if (tempBag[index].type == BAG_TYPE::ITEM)
			{
				now->useItem(temp[index].second, temp[index].first);
			}
			else if (tempBag[index].type == BAG_TYPE::EQUIPMENT)
			{
				now->wearEquipment(temp[index].second, temp[index].first);

			}

			if (now->getName() == "Role 1")
			{
				SetColor(10);
				printFileAtPosition("BD1.txt", 5, 28);
				SetColor(7);
				roles[0]->printInfo(6, 29);
			}
			else if (now->getName() == "Role 2")
			{
				SetColor(10);
				printFileAtPosition("BD1.txt", 43, 28);
				SetColor(7);
				roles[1]->printInfo(44, 29);
			}
			else if (now->getName() == "Role 3")
			{
				SetColor(10);
				printFileAtPosition("BD1.txt", 81, 28);
				SetColor(7);
				roles[2]->printInfo(82, 29);
			}

			printFileAtPosition("mainInfo.txt", 77, 2);

			gotoxy(78, 3);
			std::cout << "Current Player: " << now->getName();

			gotoxy(78, 25);
			std::cout << "End(Enter)";
			gotoxy(78, 26);
			std::cout << "Open Bag(i)";
			gotoxy(78, 27);
			std::cout << "W,A,S,D to Move";
			gotoxy(78, 4);
			cout << "move step: " << maxMove;

			return true;
		}
		else if (command == 'W' || command == 'w')
		{
			gotoxy(78, 4 + index % 10);
			std::cout << "  ";


			index = index - 1 < 0 ? temp.size() - 1 : index - 1;

			if (index % 10 == 9 || index == temp.size() - 1)
			{
				for (int i = 0; i < 10; i++)
				{
					gotoxy(82, 4 + i);
					if (index / 10 * 10 + i < temp.size())
					{
						std::cout << left << setw(23) << getItemName(temp[i + index / 10 * 10].second);
					}
					else
					{
						std::cout << "                   ";
					}
				}
			}

			gotoxy(78, 4 + (index % 10));
			std::cout << "->";

		}
		else if (command == 'S' || command == 's')
		{
			gotoxy(78, 4 + index % 10);
			std::cout << "  ";

			index = index + 1 == temp.size() ? 0 : index + 1;

			if (index % 10 == 0)
			{
				for (int i = 0; i < 10; i++)
				{
					gotoxy(82, 4 + i);
					if (index + i < temp.size())
					{
						std::cout << left << setw(23) << getItemName(temp[i + index].second);
					}
					else
					{
						std::cout << "                   ";
					}
				}
			}

			gotoxy(78, 4 + (index % 10));
			std::cout << "->";
		}
	}

	return false;
}

