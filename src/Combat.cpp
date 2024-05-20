/***********************************************************************
 * File: Combat.cpp
 * Author:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 王鈺晴 (sunnyching901105@gmail.com)
 *        B11215008 洪伯穎 (n590762743@gmail.com)
 * Create Date: 2024-05-20
 * Editor:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 王鈺晴 (sunnyching901105@gmail.com)
 *        B11215008 洪伯穎 (n590762743@gmail.com)
 * Update Date: 2024-05-20
 * Description: The Combat class facilitates the management and execution of combat scenarios within the game,
 *				handling interactions between roles and enemies during battles.
***********************************************************************/
#include "Combat.h"

/**
 * Intent: To set up the combat system, initializing the movement order and positions of roles and enemies
 * Pre: roles and enemys must be valid lists of role and enemy pointers
 * Post: Initializes the combat system, setting up the movement order and positions of roles and enemies
 * \param roles List of role pointers
 * \param enemys List of enemy pointers
 */
Combat::Combat(vector<Role*> roles, vector<Entity*>enemys)
{
	//init
	movingOrder.clear();

	//Declare
	int index = 0;

	//Init Role to combat
	for (auto i : roles)
	{
		i->update();

		//Detect is live
		if (i->getVitality() != 0)
		{
			movingOrder.push_back(i);
		}

		this->roles.push_back(i);
		outputXY[i] = { 6 + index * 38 ,1 };

		index++;
	}

	index = 0;

	//Init enemys to combat
	for (auto i : enemys)
	{
		i->update();

		//Detect is live
		if (i->getVitality() != 0)
		{
			movingOrder.push_back(i);
		}

		this->enemys.push_back(i);

		outputXY[i] = { 6 + index * 38 ,36 };

		index++;
	}

	round = 1;

	//Sort combat turns
	std::sort(movingOrder.begin(), movingOrder.end(), [](Entity* a, Entity* b) {
		return double(a->turn + 1.0) / a->getSpeed() < double(b->turn + 1.0) / b->getSpeed();
		});

}

/**
 * Intent: To properly clean up the combat system by updating all roles before destruction
 * Pre: The roles list must be initialized
 * Post: Updates all roles before the Combat object is destroyed
 */
Combat::~Combat()
{
	// End for update role state
	for (auto i : roles)
	{
		i->update();
	}
}

/**
 * Intent: To update the current state of the combat system and process the turn of the current entity
 * Pre: The combat system must be initialized and movingOrder must not be empty
 * Post: Processes the current entity's turn, updates the state of the combat, and returns whether both enemies and roles are still alive
 */
bool Combat::update()
{
	//Declare
	Entity* curEntity = movingOrder[0];

	//TurnStart
	curEntity->turn++;
	curEntity->turnStart();
	bool isMove = false;
	int index = 0;

	//==Output==
	SetColor(2);
	printFileAtPosition("BD1.txt", outputXY[curEntity].x - 1, outputXY[curEntity].y - 1);
	SetColor(7);
	//==========

	//Output Roles info
	for (auto i : roles)
	{
		if (i->getVitality() == 0 || i->getIsFlee() == true) //Detect Die or Flee
		{
			SetColor(8);
			printFileAtPosition("BD1.txt", outputXY[i].x - 1, outputXY[i].y - 1);
		}

		i->printInfo(outputXY[i].x, outputXY[i].y);

		SetColor(7);
	}
	//===============


	//Output Enemys info
	for (auto i : enemys)
	{
		if (i->getVitality() == 0 || i->getIsFlee() == true) //Detect Die or Flee
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
	//==========

	//==Output==
	gotoxy(2, 14);
	cout << "Round : " << round;

	gotoxy(2, 15);
	cout << "Turns : ";
	//=========

	//Output turns info
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

	//Output Role Skills
	if (curEntity->getType() == ENTITY_TYPE::ROLE)
	{
		curEntity->printSkills(9, 17);
	}

	//Output
	gotoxy(2, 26);
	std::cout << "Open Bag (I)";

	//Check the Entity can turn for Battle 
	while (!isMove && !curEntity->isDizziness())
	{
		// if now Entity is Role
		if (curEntity->getType() == ENTITY_TYPE::ROLE)
		{
			//output
			gotoxy(6, 18 + index);
			std::cout << "->";
			gotoxy(0, 48);

			//Get
			char command = _getch();

			//openBag
			if (command == 'I' || command == 'i')
			{
				//Output
				printFileAtPosition("interfemce.txt", 0, 13);
				isMove = useItem(curEntity);

				//if cancel output to choose mode
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
					std::cout << "Choose UP (W), DOWN(S)";
					gotoxy(2, 28);
					std::cout << "Enter to check!";
				}
			}
			else if (command == 'W' || command == 'w') // select index (up)
			{
				gotoxy(6, 18 + index);
				std::cout << "  ";

				index = index - 1 < 0 ? curEntity->getActiveSkillSize() - 1 : index - 1;

				gotoxy(6, 18 + index);
				std::cout << "->";
			}
			else if (command == 'S' || command == 's')// select index (down)
			{
				gotoxy(6, 18 + index);
				std::cout << "  ";

				index = index + 1 == curEntity->getActiveSkillSize() ? 0 : index + 1;

				gotoxy(6, 18 + index);
				std::cout << "->";
			}
			else if (command == 13)//Enter Check
			{
				printFileAtPosition("interfemce.txt", 0, 13);

				if (curEntity->useSkill(index, roles, enemys)) //useSkill can use
				{
					isMove = true;
				}
				else // CD is not really
				{
					//output
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
		else // is Enemy
		{
			int randomSkill = rand() % curEntity->getActiveSkillSize(); //random skill
			printFileAtPosition("interfemce.txt", 0, 13);

			while (true)
			{
				randomSkill = rand() % curEntity->getActiveSkillSize();

				if (randomSkill == SKILL_IDX::FLEE) //Could not use Flee
				{
					continue;
				}
				else if (curEntity->useSkill(index, enemys, roles))//Useskill can cast
				{
					//output
					gotoxy(3, 27);
					std::cout << "Use Skills " << getSkillName(curEntity->getActiveSkills()[index].skillIdx);
					isMove = true;

					Sleep(500);

					break;
				}
			}
		}
	}

	curEntity->turnEnd(); // turnEnd


	//update flee
	movingOrder.erase(
		std::remove_if(movingOrder.begin(), movingOrder.end(),
			[](const Entity* entity) {
				return entity->getIsFlee() || entity->getVitality() == 0;
			}),
		movingOrder.end()
				);

	//update turns
	std::sort(movingOrder.begin(), movingOrder.end(), [](Entity* a, Entity* b) {
		return double(a->turn + 1.0) / a->getSpeed() < double(b->turn + 1.0) / b->getSpeed();
		});

	//update Round
	for (auto i : movingOrder)
	{
		round = i->turn < round ? i->turn : round;
	}

	round++;

	//Check enemys are alive
	bool enemysalive = false;

	for (auto i : enemys)
	{
		if (i->getVitality() != 0)
		{
			enemysalive = true;
			break;
		}
	}

	//Check roles are alive
	bool rolesAlive = false;

	for (auto i : roles)
	{
		if (i->getVitality() != 0 && i->getIsFlee() == false)
		{
			rolesAlive = true;
			break;
		}
	}

	//Output
	SetColor(7);
	printFileAtPosition("BD1.txt", outputXY[curEntity].x - 1, outputXY[curEntity].y - 1);

	//return if all kind have one alive
	return enemysalive && rolesAlive;


}

/**
 * Intent: To handle the usage of items from the role's inventory
 * Pre: role must be a valid Entity pointer, and must be dynamically castable to a Role pointer
 * Post: Allows the player to navigate through the items, and use one if selected
 * \param role A pointer to the role using the item
 */
bool Combat::useItem(Entity* role)
{
	//Declare
	Role* curRole = dynamic_cast<Role*>(role);
	vector<pair<int, int>> temp;	//bagIdx,itemIdx
	vector<Bag>tempBag = curRole->getBag();

	//Push bag to tempBag
	int index = 0;
	for (auto i : tempBag)
	{
		if (i.type == BAG_TYPE::ITEM && i.index < 15)
		{
			temp.push_back({ index,i.index });
		}

		index++;
	}

	//Output
	gotoxy(1, 14);
	std::cout << "Item: ";

	//Output bag 
	int pr = 1;
	for (auto i : temp)
	{
		gotoxy(4, 14 + pr);
		std::cout << getItemName(i.second);

		pr++;
	}

	//Output
	gotoxy(2, 26);
	std::cout << "Back(BackSpace)";
	gotoxy(2, 27);
	std::cout << "Choose UP (W), DOWN(S)";
	gotoxy(2, 28);
	std::cout << "Enter to check!";

	//Declare select
	index = 0;

	while (true)
	{
		//Output 
		gotoxy(1, 15 + index);
		std::cout << "->";
		gotoxy(0, 48);

		//input
		char command = _getch();

		//Choose
		if (command == 8) //backspace
		{
			//output
			printFileAtPosition("interfemce.txt", 0, 13);
			role->printSkills(9, 17);

			break;
		}
		else if (command == 13) //Enter
		{
			curRole->useItem(temp[index].second, temp[index].first);
			return true;
		}
		else if (command == 'W' || command == 'w') //select up
		{
			gotoxy(1, 15 + index);
			std::cout << "  ";


			index = index - 1 < 0 ? temp.size() - 1 : index - 1;

			gotoxy(1, 15 + index);
			std::cout << "->";

		}
		else if (command == 'S' || command == 's') //select down
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

/**
 * Intent: To start and manage the combat loop, ensuring the screen size is appropriate and updating the combat state continuously
 * Pre: The combat system must be initialized, and the console window must be checked for the required size
 * Post: Manages the combat loop, updates the state, and exits when combat ends
 */
void Combat::start()
{
	//Declare
	const int requiredRows = 50;
	const int requiredCols = 120;

	// Check screen size
	while (true) {

		//Check if legel output info
		if (checkConsoleSize(requiredRows, requiredCols)) {
			system("cls");
			printFileAtPosition("combatBoard.txt", 0, 0);
			break;
		}
		else {
			std::cerr << "請調整螢幕大小至至少 " << requiredRows << " 行 " << requiredCols << " 列" << std::endl;
			Sleep(1000); // wait for three sec.
		}
	}
	while (true)
	{
		//output
		printFileAtPosition("interfemce.txt", 0, 13);

		//entity is alive
		if (!update())
		{
			//output
			printFileAtPosition("endCombat.txt", 0, 13);

			//output roles info
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

			//output enemys info
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

			Sleep(1000);
			break;
		}
	}
}

