#include "Combat.h"



Combat::Combat(vector<Role*> roles, vector<Entity*>enemys)
{
	movingOrder.clear();

	int index = 0;

	for (auto i : roles)
	{
		i->update();

		if (i->getVitality() != 0)
		{
			movingOrder.push_back(i);
		}

		this->roles.push_back(i);
		outputXY[i] = { 6 + index * 38 ,1 };

		index++;
	}

	index = 0;

	for (auto i : enemys)
	{
		i->update();

		if (i->getVitality() != 0)
		{
			movingOrder.push_back(i);
		}

		this->enemys.push_back(i);

		outputXY[i] = { 6 + index * 38 ,36 };

		index++;
	}

	round = 1;

	std::sort(movingOrder.begin(), movingOrder.end(), [](Entity* a, Entity* b) {
		return double(a->turn + 1.0) / a->getSpeed() < double(b->turn + 1.0) / b->getSpeed();
		});

}

Combat::~Combat()
{
}

bool Combat::update()
{

	Entity* curEntity = movingOrder[0];
	curEntity->turn++;
	bool isMove = false;
	int index = 0;

	SetColor(2);
	printFileAtPosition("BD1.txt", outputXY[curEntity].x - 1, outputXY[curEntity].y - 1);
	SetColor(7);

	for (auto i : roles)
	{
		if (i->getVitality() == 0 || i->getIsFlee() == true)
		{
			SetColor(8);
			printFileAtPosition("BD1.txt", outputXY[i].x - 1, outputXY[i].y - 1);
		}

		i->printInfo(outputXY[i].x, outputXY[i].y);

		SetColor(7);
	}

	for (auto i : enemys)
	{
		if (i->getVitality() == 0 || i->getIsFlee() == true)
		{
			SetColor(8);
			printFileAtPosition("BD1.txt", outputXY[i].x - 1, outputXY[i].y - 1);
		}
		else
		{
			SetColor(12);
		}

		i->printInfo(outputXY[i].x, outputXY[i].y);

		SetColor(7);
	}

	gotoxy(2, 14);
	cout << "Round : " << round;

	gotoxy(2, 15);
	cout << "Turns : ";
	for (auto it = movingOrder.begin(); it != movingOrder.end(); ++it) {
		if ((*it)->isDizziness())
		{
			SetColor(8);
		}
		cout << (*it)->getName();

		SetColor(7);

		if (it != movingOrder.end() - 1) {
			cout << "->";
		}
	}
	if (curEntity->getType() == ENTITY_TYPE::ROLE)
	{
		curEntity->printSkills(9, 17);
	}

	gotoxy(2, 26);
	std::cout << "Open Bag (I)";

	while (!isMove && !curEntity->isDizziness())
	{
		if (curEntity->getType() == ENTITY_TYPE::ROLE)
		{
			gotoxy(6, 18 + index);
			std::cout << "->";
			gotoxy(0, 48);

			char command = _getch();

			if (command == 'I' || command == 'i')
			{
				printFileAtPosition("interfemce.txt", 0, 13);
				isMove = useItem(curEntity);

				if (!isMove)
				{
					gotoxy(2, 14);
					cout << "Round : " << round;

					gotoxy(2, 15);
					cout << "Turns : ";
					for (auto it = movingOrder.begin(); it != movingOrder.end(); ++it) {
						cout << (*it)->getName();
						if (it != movingOrder.end() - 1) {
							cout << "->";
						}
					}

					gotoxy(2, 26);
					std::cout << "Open Bag (I)";
					gotoxy(2, 27);
					std::cout << "Choose UP (W), DOWN(D)";
					gotoxy(2, 28);
					std::cout << "Enter to check!";
				}
			}
			else if (command == 'W' || command == 'w')
			{
				gotoxy(6, 18 + index);
				std::cout << "  ";

				index = index - 1 < 0 ? curEntity->getActiveSkillSize() - 1 : index - 1;

				gotoxy(6, 18 + index);
				std::cout << "->";
			}
			else if (command == 'S' || command == 's')
			{
				gotoxy(6, 18 + index);
				std::cout << "  ";

				index = index + 1 == curEntity->getActiveSkillSize() ? 0 : index + 1;

				gotoxy(6, 18 + index);
				std::cout << "->";
			}
			else if (command == 13)
			{
				printFileAtPosition("interfemce.txt", 0, 13);

				if (curEntity->useSkill(index, roles, enemys))
				{
					isMove = true;
				}
				else
				{
					gotoxy(2, 14);
					cout << "Round : " << round;

					gotoxy(2, 15);
					cout << "Turns : ";
					for (auto it = movingOrder.begin(); it != movingOrder.end(); ++it) {
						if ((*it)->isDizziness())
						{
							SetColor(8);
						}
						cout << (*it)->getName();

						SetColor(7);

						if (it != movingOrder.end() - 1) {
							cout << "->";
						}
					}

					curEntity->printSkills(9, 17);

					gotoxy(9, 16);
					std::cout << "Skill Not Ready";
				}


			}
		}
		else
		{
			int randomSkill = rand() % curEntity->getActiveSkillSize();
			printFileAtPosition("interfemce.txt", 0, 13);

			while (true)
			{
				randomSkill = rand() % curEntity->getActiveSkillSize();

				if (randomSkill == SKILL_IDX::FLEE)
				{
					continue;
				}
				else if (curEntity->useSkill(index, enemys, roles))
				{
					gotoxy(3, 27);
					std::cout << "Use Skills " << getSkillName(curEntity->getActiveSkills()[index].skillIdx);
					isMove = true;

					Sleep(500);

					break;
				}
			}


		}
	}

	curEntity->turnEnd();


	//update flee
	movingOrder.erase(
		std::remove_if(movingOrder.begin(), movingOrder.end(),
			[](const Entity* entity) {
				return entity->getIsFlee() || entity->getVitality() == 0;
			}),
		movingOrder.end()
				);

	std::sort(movingOrder.begin(), movingOrder.end(), [](Entity* a, Entity* b) {
		return double(a->turn + 1.0) / a->getSpeed() < double(b->turn + 1.0) / b->getSpeed();
		});

	for (auto i : movingOrder)
	{
		round = i->turn < round ? i->turn : round;
	}

	round++;

	bool enemysalive = false;

	for (auto i : enemys)
	{
		if (i->getVitality() != 0)
		{
			enemysalive = true;
			break;
		}
	}

	bool rolesAlive = false;

	for (auto i : roles)
	{
		if (i->getVitality() != 0 && i->getIsFlee() == false)
		{
			rolesAlive = true;
			break;
		}
	}

	SetColor(7);
	printFileAtPosition("BD1.txt", outputXY[curEntity].x - 1, outputXY[curEntity].y - 1);


	return enemysalive && rolesAlive;


}

bool Combat::useItem(Entity* role)
{
	Role* curRole = dynamic_cast<Role*>(role);

	vector<pair<int, int>> temp;//bagIdx,itemIdx
	vector<Bag>tempBag = curRole->getBag();

	int index = 0;
	for (auto i : tempBag)
	{
		if (i.type == BAG_TYPE::ITEM && i.index < 15)
		{
			temp.push_back({ index,i.index });
		}

		index++;
	}

	gotoxy(1, 14);
	std::cout << "Item: ";

	int pr = 1;
	for (auto i : temp)
	{
		gotoxy(4, 14 + pr);
		std::cout << getItemName(i.second);

		pr++;
	}
	gotoxy(2, 26);
	std::cout << "Back(BackSpace)";
	gotoxy(2, 27);
	std::cout << "Choose UP (W), DOWN(D)";
	gotoxy(2, 28);
	std::cout << "Enter to check!";


	index = 0;

	while (true)
	{

		gotoxy(1, 15 + index);
		std::cout << "->";
		gotoxy(0, 48);

		char command = _getch();
		if (command == 8)
		{
			printFileAtPosition("interfemce.txt", 0, 13);
			role->printSkills(9, 17);

			break;
		}
		else if (command == 13)
		{
			curRole->useItem(temp[index].second, temp[index].first);
			return true;
		}
		else if (command == 'W' || command == 'w')
		{
			gotoxy(1, 15 + index);
			std::cout << "  ";


			index = index - 1 < 0 ? temp.size() - 1 : index - 1;

			gotoxy(1, 15 + index);
			std::cout << "->";

		}
		else if (command == 'S' || command == 's')
		{
			gotoxy(1, 15 + index);
			std::cout << "  ";

			index = index + 1 == temp.size() ? 0 : index + 1;

			gotoxy(1, 15 + index);
			std::cout << "->";
		}
	}

	return false;
}

void Combat::start()
{
	const int requiredRows = 50;
	const int requiredCols = 120;
	// 重複檢查螢幕大小
	while (true) {
		if (checkConsoleSize(requiredRows, requiredCols)) {
			printFileAtPosition("combatBoard.txt", 0, 0);
			break;
		}
		else {
			std::cerr << "請調整螢幕大小至至少 " << requiredRows << " 行 " << requiredCols << " 列" << std::endl;
			Sleep(1000); // 等待 3 秒鐘
		}
	}
	while (true)
	{
		printFileAtPosition("interfemce.txt", 0, 13);
		if (!update())
		{
			printFileAtPosition("endCombat.txt", 0, 13);
			for (auto i : roles)
			{
				if (i->getVitality() == 0 || i->getIsFlee() == true)
				{
					SetColor(8);
					printFileAtPosition("BD1.txt", outputXY[i].x - 1, outputXY[i].y - 1);
				}

				i->printInfo(outputXY[i].x, outputXY[i].y);

				SetColor(7);
			}

			for (auto i : enemys)
			{
				if (i->getVitality() == 0 || i->getIsFlee() == true)
				{
					SetColor(8);
					printFileAtPosition("BD1.txt", outputXY[i].x - 1, outputXY[i].y - 1);
				}
				else
				{
					SetColor(12);
				}

				i->printInfo(outputXY[i].x, outputXY[i].y);

				SetColor(7);
			}

			gotoxy(0, 48);
			break;
		}
	}

}

