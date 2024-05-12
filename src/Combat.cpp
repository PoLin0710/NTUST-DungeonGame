#include "Combat.h"



Combat::Combat(vector<Role*> roles, vector<Entity*>enemys)
{
	movingOrder.clear();

	for (auto i : roles)
	{
		i->update();

		if (i->getVitality() != 0)
		{
			movingOrder.push_back(i);
		}

		this->roles.push_back(i);
	}

	for (auto i : enemys)
	{
		i->update();

		if (i->getVitality() != 0)
		{
			movingOrder.push_back(i);
		}

		this->enemys.push_back(i);
	}

	round = 1;

	sort(movingOrder.begin(), movingOrder.end(), [](Entity* a, Entity* b) {
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
	while (!isMove)
	{
		if (curEntity->getType() == ENTITY_TYPE::ROLE)
		{
			system("cls");
			cout << "Round : " << round << std::endl;
			for (auto i : movingOrder)
			{
				cout << i->getName() << "->";
			}
			std::cout << std::endl;
			curEntity->printInfo();
			std::cout << "\nindex: " << index;

			char command = _getch();

			if (command == 'I' || command == 'i')
			{
				isMove = useItem(curEntity);
			}
			else if (command == 'A' || command == 'a')
			{
				index = index - 1 < 0 ? curEntity->getActiveSkillSize() - 1 : index - 1;
			}
			else if (command == 'D' || command == 'd')
			{
				index = index + 1 == curEntity->getActiveSkillSize() ? 0 : index + 1;
			}
			else if (command == 13)
			{
				isMove = true;
				curEntity->useSkill(index, roles, enemys);
			}

		}
	}

	curEntity->turnEnd();

	for (auto i : movingOrder)
	{
		round = i->turn < round ? i->turn : round;
	}

	round++;

	movingOrder.erase(
		std::remove_if(movingOrder.begin(), movingOrder.end(),
			[](const Entity* entity) {
				return entity->getIsFlee() || entity->getVitality() == 0;
			}),
		movingOrder.end()
				);

	sort(movingOrder.begin(), movingOrder.end(), [](Entity* a, Entity* b) {
		return double(a->turn + 1.0) / a->getSpeed() < double(b->turn + 1.0) / b->getSpeed();
		});

	for (auto i : movingOrder)
	{
		cout << i->getName() << "->";
	}

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

	std::cout << "Item: ";

	for (auto i : temp)
	{
		std::cout << getItemName(i.second) << " ";
	}

	index = 0;

	std::cout << "\nindex: " << index;

	while (true)
	{
		char command = _getch();
		if (command == 8)
		{
			break;
		}
		else if (command == 13)
		{
			curRole->useItem(temp[index].second, temp[index].first);
			return true;
		}
		else if (command == 'A' || command == 'a')
		{
			index = index - 1 < 0 ? temp.size() - 1 : index - 1;
		}
		else if (command == 'D' || command == 'd')
		{
			index = index + 1 == temp.size() ? 0 : index + 1;
		}

		system("cls");
		std::cout << "Item: ";
		for (auto i : temp)
		{
			std::cout << getItemName(i.second) << " ";
		}
		std::cout << "\nindex: " << index;
	}

	return false;
}

void Combat::start()
{
	while (true)
	{
		const int requiredRows = 50;
		const int requiredCols = 120;
		// 重複檢查螢幕大小
		while (true) {
			if (checkConsoleSize(requiredRows, requiredCols)) {
				std::cout << "螢幕大小足夠！" << std::endl;
				system("cls");
				printFileAtPosition("combatBoard.txt", 0, 0);
				SetColor(2);
				printFileAtPosition("BD1.txt", 5, 0);
				SetColor();
				break;
			}
			else {
				std::cerr << "請調整螢幕大小至至少 " << requiredRows << " 行 " << requiredCols << " 列" << std::endl;
				Sleep(1000); // 等待 3 秒鐘
			}
		}


		update();
	}
}

