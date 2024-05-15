#include "Entity.h"

Entity::Entity(std::string _name, int type = ENTITY_TYPE::ENEMY)
{
	this->name = _name;

	this->initVitality = 30 + rand() % 15; // Range [30,45)
	this->initFocus = 3;
	this->initSpeed = 30 + rand() % 25; // Range [30,55)
	this->initHitRate = 40 + rand() % 20; // Range [40,60)
	this->initPAttack = 5 + rand() % 11; // Range [5,15]
	this->initMAttack = 5 + rand() % 11; // Range [5,15]
	this->initPDefense = rand() % 21; // Range [0,20]
	this->initMDefense = rand() % 21; // Range [0,20]

	this->equipment.setWeapon(WEAPON_IDX::HAMMER);
	this->equipment.setArmor(ARMOR_IDX::PLATE_ARMOR);
	this->equipment.setAccessory(ACCESSORY_IDX::BRACELET);

	this->equipment.updateEquipment();

	this->activeSkills = equipment.getSkills();
	this->passiveSkills = equipment.getPassiveSkills();
	this->activeSkillsCD.clear();
	this->passiveSkillsCD.clear();
	this->activeSkillsCD.resize(activeSkills.size(), 0);
	this->passiveSkillsCD.resize(passiveSkills.size(), 0);

	this->maxVitality = equipment.getVitality(this->initVitality);
	this->maxFocus = equipment.getFocus(this->initFocus);
	this->maxSpeed = equipment.getSpeed(this->initSpeed);
	this->maxHitRate = equipment.getHitRate(this->initHitRate);
	this->maxPAttack = equipment.getPAttack(this->initPAttack);
	this->maxMAttack = equipment.getMAttack(this->initMAttack);
	this->maxPDefense = equipment.getPDefense(this->initPDefense);
	this->maxMDefense = equipment.getMDefense(this->initMDefense);

	this->curVitality = this->maxVitality;
	this->curFocus = this->maxFocus;
	this->curSpeed = this->maxSpeed;
	this->curHitRate = this->maxHitRate;
	this->curPAttack = this->maxPAttack;
	this->curMAttack = this->maxMAttack;
	this->curPDefense = this->maxPDefense;
	this->curMDefense = this->maxMDefense;

	this->isFlee = false;
	this->turn = 0;
	this->type = type;
}

Entity::~Entity()
{
}

void Entity::setVitality(int vitality) {
	this->curVitality = min(vitality, this->maxVitality);
}

void Entity::setFocus(int focus) {
	this->curFocus = min(focus, this->maxFocus);
}

void Entity::setSpeed(int speed) {
	this->curSpeed = speed;
}

void Entity::setHitRate(int hitRate) {
	this->curHitRate = hitRate;
}

void Entity::setPAttack(int pAttack) {
	this->curPAttack = pAttack;
}

void Entity::setMAttack(int mAttack) {
	this->curMAttack = mAttack;
}

void Entity::setPDefense(int pDefense) {
	this->curPDefense = pDefense;
}

void Entity::setMDefense(int mDefense) {
	this->curMDefense = mDefense;
}

void Entity::setWeapon(int weapon) {
	this->equipment.setWeapon(weapon);
}

void Entity::setArmor(int armor) {
	this->equipment.setArmor(armor);
}

void Entity::setAccessory(int accessory) {
	this->equipment.setAccessory(accessory);
}


string Entity::getName() const
{
	return name;
}

int Entity::getVitality() const {
	return curVitality;
}

int Entity::getFocus() const {
	return curFocus;
}

int Entity::getSpeed() {
	if (findBuffs(Buff::BUFF_IDX::BSPEEDUP))
	{
		return curSpeed * 1.5;
	}

	return curSpeed;
}

int Entity::getHitRate() const {
	return curHitRate;
}

int Entity::getPAttack() const {
	return curPAttack;
}

int Entity::getMAttack() const {
	return curMAttack;
}

int Entity::getPDefense() const {
	return curPDefense;
}

int Entity::getMDefense() const {
	return curMDefense;
}


int Entity::getWeapon() const {
	return equipment.getWeapon();
}

int Entity::getArmor() const {
	return equipment.getArmor();
}

int Entity::getAccessory() const {
	return equipment.getAccessory();
}

int Entity::getType() const
{
	return type;
}

int Entity::getActiveSkillSize() const
{
	return activeSkills.size();
}

bool Entity::getIsFlee() const
{
	return isFlee;
}

std::vector<skill> Entity::getActiveSkills() const
{
	return activeSkills;
}

bool Entity::isDizziness()
{
	return findBuffs(Buff::BUFF_IDX::BDIZZINESS);
}

double Entity::RolltheDice(int diceNum, int successNum)
{
	double successRate = 0;
	gotoxy(3, 22);

	for (int i = 0; i < diceNum; i++)
	{
		if (i < successNum || (i == 0 && findSkills(SKILL_IDX::RUN))) //Passtive skill detect
		{
			successRate++;

			SetColor(14);

			std::cout << "*";
			SetColor(7);
		}
		else
		{
			int Roll = rand() % 100 + 1;

			if (Roll < curHitRate) //succes
			{
				successRate++;

				SetColor(14);

				std::cout << "*";
				SetColor(7);
			}
			else //fail
			{
				SetColor(12);

				std::cout << "*";
				SetColor(7);
			}
			Sleep(300);
		}


	}
	std::cout << "\n";

	//Debuff angry check
	if (findBuffs(Buff::BUFF_IDX::BANGRY))
	{
		successRate * 0.7;
	}

	return successRate / diceNum;
}

//戰鬥前觸發
void Entity::update()
{
	this->maxVitality = equipment.getVitality(this->initVitality);
	this->maxFocus = equipment.getFocus(this->initFocus);
	this->maxSpeed = equipment.getSpeed(this->initSpeed);
	this->maxHitRate = equipment.getHitRate(this->initHitRate);
	this->maxPAttack = equipment.getPAttack(this->initPAttack);
	this->maxMAttack = equipment.getMAttack(this->initMAttack);
	this->maxPDefense = equipment.getPDefense(this->initPDefense);
	this->maxMDefense = equipment.getMDefense(this->initMDefense);

	this->curVitality = min(this->curVitality, this->maxVitality);
	this->curFocus = min(this->curFocus, this->maxFocus);
	this->curSpeed = this->maxSpeed;
	this->curHitRate = this->maxHitRate;
	this->curPAttack = this->maxPAttack;
	this->curMAttack = this->maxMAttack;
	this->curPDefense = this->maxPDefense;
	this->curMDefense = this->maxMDefense;

	isFlee = false;
	this->turn = 0;
	activeSkills = equipment.getSkills();
	passiveSkills = equipment.getPassiveSkills();
	activeSkillsCD.clear();
	passiveSkillsCD.clear();
	activeSkillsCD.resize(activeSkills.size(), 0);
	passiveSkillsCD.resize(passiveSkills.size(), 0);
}

bool Entity::useSkill(int skill_IDX, std::vector<Entity*> roles, std::vector<Entity*> enemys)
{
	if (skill_IDX >= activeSkills.size() || activeSkillsCD[skill_IDX] != 0)
	{
		return false;
	}

	skill curSkill = activeSkills[skill_IDX];
	activeSkillsCD[skill_IDX] = curSkill.cd;

	if (curSkill.type == SKILLTYPE::ATK)
	{
		std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, enemys);

		if (getWeapon() == WEAPON_IDX::MAGIC_WAND || getWeapon() == WEAPON_IDX::RITUAL_SWORD)
		{
			this->curHitRate = this->maxHitRate - 5;
			this->curMAttack = this->maxMAttack * RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum)); //之後更改
			attack(curSkill.skillIdx, 0, this->curMAttack, target);

			this->curHitRate = this->maxHitRate;
		}
		else if (getWeapon() == WEAPON_IDX::HAMMER || getWeapon() == WEAPON_IDX::GIANT_HAMMER)
		{
			float rate = RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum));

			std::vector<Entity*> Aoe;

			std::copy_if(enemys.begin(), enemys.end(), std::back_inserter(Aoe),
				[&target](Entity* elem) {
					return std::find(target.begin(), target.end(), elem) == target.end();
				});

			Aoe.erase(
				std::remove_if(Aoe.begin(), Aoe.end(),
					[](const Entity* entity) {
						return entity->getIsFlee() || entity->getVitality() == 0;
					}),
				Aoe.end()
						);

			if (rate == 1)
			{
				target[0]->insertBuff(Buff::BUFF_IDX::BDIZZINESS);
			}

			attack(curSkill.skillIdx, 0, this->curMAttack, target);
			attack(curSkill.skillIdx, 0, this->curMAttack * 0.5, Aoe);

		}
		else
		{
			this->curPAttack = this->maxMAttack * RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum)); //之後更改
			attack(curSkill.skillIdx, this->curPAttack, 0, target);
		}
	}
	else
	{
		if (curSkill.skillIdx == SKILL_IDX::FLEE)
		{
			int rate = double(this->curVitality) / (this->maxVitality + this->curPDefense + this->curMDefense) * this->curSpeed;
			rate = min(rate, 98);

			this->curHitRate = rate;
			double state = RolltheDice(1, useFocus(curSkill.diceNum));
			this->curHitRate = this->maxHitRate;

			if (state >= 1)
			{
				isFlee = true;
			}

		}
		else if (curSkill.skillIdx == SKILL_IDX::PROVOKE)
		{
			int rate = double(this->curVitality) / (this->maxVitality + this->curPDefense + this->curMDefense) * this->curSpeed;

			std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, enemys);
			this->curHitRate = rate;
			double state = RolltheDice(1, useFocus(curSkill.diceNum));
			this->curHitRate = this->maxHitRate;

			if (state >= 1)
			{
				target[0]->insertBuff(Buff::BUFF_IDX::BANGRY);
			}

		}
		else if (curSkill.skillIdx == SKILL_IDX::HEAL)
		{
			std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, roles);
			this->curMAttack = this->maxMAttack * RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum));
			heal(this->curMAttack, target);

		}
		else if (curSkill.skillIdx == SKILL_IDX::SPEEDUP)
		{
			std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, roles);
			double state = RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum));

			if (state >= 1)
			{
				target[0]->insertBuff(Buff::BUFF_IDX::BSPEEDUP);
			}
		}
	}

	if (findBuffs(Buff::BUFF_IDX::BPOISONED))
	{
		this->curVitality -= (this->curVitality * 0.1);
	}

}

int Entity::useFocus(int diceNum)
{
	int useFocus = 0;
	int maxFocus = min(curFocus, diceNum);


	gotoxy(3, 21);
	std::cout << "Focus";

	gotoxy(3, 22);
	SetColor(8);
	for (int i = 0; i < diceNum; i++)
	{
		std::cout << "*";
	}
	SetColor(7);

	if (type == ENTITY_TYPE::ROLE)
	{
		while (true)
		{
			gotoxy(0, 48);
			char command = _getch();

			if (command == 'A' || command == 'a')
			{
				gotoxy(3, 22);

				useFocus = useFocus - 1 < 0 ? 0 : useFocus - 1;

				for (int i = 0; i < diceNum; i++)
				{
					if (i < useFocus)
					{
						SetColor(14);
					}
					else
					{
						SetColor(8);
					}
					std::cout << "*";
				}

				SetColor(7);

			}
			else if (command == 'D' || command == 'd')
			{
				gotoxy(3, 22);
				useFocus = useFocus >= maxFocus ? maxFocus : useFocus + 1;

				for (int i = 0; i < diceNum; i++)
				{
					if (i < useFocus)
					{
						SetColor(14);
					}
					else
					{
						SetColor(8);
					}
					std::cout << "*";
				}

				SetColor(7);

			}
			else if (command == 13)
			{
				break;
			}
		}
	}
	else
	{
		int randomFocus = rand() % maxFocus;

		gotoxy(3, 22);

		for (int i = 0; i < randomFocus; i++)
		{
			if (i < maxFocus)
			{
				SetColor(14);
			}
			else
			{
				SetColor(8);
			}

			std::cout << "*";
		}
		SetColor(7);

		useFocus = randomFocus;
	}



	this->curFocus -= useFocus;
	return useFocus;
}

void Entity::attack(int skillIdx, int pAttack, int mAttack, std::vector<Entity*> enemys)
{
	std::vector<int> oneSelf = { SKILL_IDX::ATTACK ,SKILL_IDX::FLEE,SKILL_IDX::PROVOKE,SKILL_IDX::HEAL,SKILL_IDX::SPEEDUP, };
	std::vector<int> allSelf = { SKILL_IDX::SHOCK_BLAST,-1 };

	for (auto i : enemys)
	{
		double pDefense = 1 - (i->curPDefense / double(i->curPDefense + 50));
		double mDefense = 1 - (i->curMDefense / double(i->curMDefense + 50));

		int realPAttack = pAttack * pDefense;
		int realMAttack = mAttack * mDefense;

		if (i->findSkills(SKILL_IDX::FORTIFY))
		{
			realPAttack *= 0.9;
			realMAttack *= 0.9;
		}

		i->curVitality -= (realPAttack + realMAttack);
		i->curVitality = max(i->curVitality, 0);

		//Passtive skill
		if ((realPAttack + realMAttack) > 0 && findSkills(SKILL_IDX::DESTROY))
		{
			switch (rand() % 3)
			{
			case 0:
				i->setWeapon(WEAPON_IDX::WEAPON_NONE);
				break;
			case 1:
				i->setArmor(ARMOR_IDX::ARMOR_NONE);
				break;
			case 2:
				i->setAccessory(ACCESSORY_IDX::ACCESSORY_NONE);
			default:
				break;
			}
		}
	}
}

void Entity::insertBuff(int buffIdx)
{
	Buff::Buff temp;
	switch (buffIdx)
	{
	case Buff::BUFF_IDX::BANGRY:
		temp = { Buff::BUFF_IDX::BANGRY,3 };
		break;
	case Buff::BUFF_IDX::BDIZZINESS:
		temp = { Buff::BUFF_IDX::BDIZZINESS,1 };
		break;
	case Buff::BUFF_IDX::BPOISONED:
		temp = { Buff::BUFF_IDX::BPOISONED,3 };
		break;
	case Buff::BUFF_IDX::BSPEEDUP:
		temp = { Buff::BUFF_IDX::BSPEEDUP,1 };
		break;
	default:
		break;
	}

	bool find = false;
	for (int i = 0; i < this->buffs.size(); i++)
	{
		if (buffs[i].buffIdx == temp.buffIdx)
		{
			find = true;

			buffs[i].turn = temp.turn;

			break;
		}
	}

	if (!find)
	{
		this->buffs.push_back(temp);
	}

}

void Entity::heal(int mAttack, std::vector<Entity*> enemys)
{
	for (auto i : enemys)
	{
		int realMAttack = mAttack;

		i->curVitality += realMAttack;
		i->curVitality = min(i->curVitality, i->maxVitality);
	}
}

std::vector<Entity*> Entity::chooseEntitys(int skill_IDX, std::vector<Entity*> chooseList)
{
	chooseList.erase(
		std::remove_if(chooseList.begin(), chooseList.end(),
			[](const Entity* entity) {
				return entity->getIsFlee() || entity->getVitality() == 0;
			}),
		chooseList.end()
				);


	int oneSelf[] = { SKILL_IDX::ATTACK ,SKILL_IDX::FLEE,SKILL_IDX::PROVOKE,SKILL_IDX::HEAL,SKILL_IDX::SPEEDUP, };
	int allSelf[] = { SKILL_IDX::SHOCK_BLAST };

	std::vector<Entity*> target;

	for (int i : oneSelf)
	{
		if (i == skill_IDX)
		{
			if (type == ENTITY_TYPE::ROLE)
			{
				gotoxy(6, 15);
				std::cout << "====Target====";

				int pr = 0;
				for (auto j : chooseList)
				{
					gotoxy(6, 16 + pr);

					std::cout << j->getName();

					pr++;
				}

				int index = 0;

				gotoxy(3, 16);
				std::cout << "->";

				while (true)
				{
					gotoxy(0, 48);
					char command = _getch();

					if (command == 'W' || command == 'w')
					{
						gotoxy(3, 16 + index);
						std::cout << "  ";

						index = index - 1 < 0 ? chooseList.size() - 1 : index - 1;

						gotoxy(3, 16 + index);
						std::cout << "->";
					}
					else if (command == 'S' || command == 's')
					{
						gotoxy(3, 16 + index);
						std::cout << "  ";

						index = index + 1 == chooseList.size() ? 0 : index + 1;

						gotoxy(3, 16 + index);
						std::cout << "->";
					}
					else if (command == 13)
					{
						target.push_back(chooseList[index]);
						break;
					}
				}
			}
			else
			{
				int randomChoose = rand() % chooseList.size();

				gotoxy(6, 15);
				std::cout << "====CHOOSE====";

				gotoxy(6, 16);
				std::cout << chooseList[randomChoose]->name;
				target.push_back(chooseList[randomChoose]);
			}


			return target;
		}

	}


	for (auto i : chooseList)
	{
		target.push_back(i);
	}

	return target;

}

//回傳是否開始下一個步驟 否直接到TurnEnd
bool Entity::turnStart()
{
	for (int i = 0; i < activeSkillsCD.size(); i++)
	{
		activeSkillsCD[i] = max(activeSkillsCD[i] - 1, 0);
	}

	for (int i = 0; i < passiveSkillsCD.size(); i++)
	{
		passiveSkillsCD[i] = max(passiveSkillsCD[i] - 1, 0);
	}

	if (findBuffs(Buff::BUFF_IDX::BDIZZINESS))
	{
		return false;
	}

	return true;
}

void Entity::turnEnd()
{
	for (auto i = buffs.begin(); i != buffs.end(); i++)
	{
		if (i->turn > 0)
		{
			i->turn = i->turn - 1;
		}
	}

	buffs.erase(std::remove_if(buffs.begin(), buffs.end(), [](const Buff::Buff& src) {
		return src.turn == 0;
		}), buffs.end());

	int debug = 0;
}

bool Entity::findSkills(SKILL_IDX skillIdx)
{
	auto it = std::find_if(passiveSkills.begin(), passiveSkills.end(), [skillIdx](const skill& skill) {
		return skill.skillIdx == skillIdx;
		});

	if (it != passiveSkills.end())
	{
		return true;
	}

	return false;
}

bool Entity::findBuffs(Buff::BUFF_IDX buffIdx)
{
	auto it = std::find_if(buffs.begin(), buffs.end(), [buffIdx](const Buff::Buff& buff) {
		return buff.buffIdx == buffIdx;
		});

	if (it != buffs.end())
	{
		return true;
	}

	return false;
}

void Entity::printInfo(int x, int y)
{
	gotoxy(x, y);
	std::cout << "Name: " << name << std::endl;

	gotoxy(x, y + 1);
	std::cout << "HP: " << std::left << std::setw(3) << curVitality << "/" << std::left << std::setw(3) << maxVitality << "   ";
	std::cout << "FOCUS: " << curFocus << "/" << maxFocus << std::endl;

	gotoxy(x, y + 2);
	std::cout << "PATK: " << std::left << std::setw(3) << curPAttack << "     ";
	std::cout << "PDEF: " << std::left << std::setw(3) << curPDefense << std::endl;

	gotoxy(x, y + 3);
	std::cout << "MATK: " << std::left << std::setw(3) << curMAttack << "     ";
	std::cout << "MDEF: " << std::left << std::setw(3) << curMDefense << std::endl;

	gotoxy(x, y + 4);
	std::cout << "SPD: " << std::left << std::setw(3) << curSpeed << "      ";
	std::cout << "HIT: " << std::left << std::setw(3) << curHitRate << std::endl;

	gotoxy(x, y + 5);
	std::cout << "Weapon: " << getWeaponName(equipment.getWeapon()) << std::endl;

	gotoxy(x, y + 6);
	std::cout << "Armor: " << getArmorName(equipment.getArmor()) << std::endl;

	gotoxy(x, y + 7);
	std::cout << "Accessory: " << getAccessoryName(equipment.getAccessory()) << std::endl;

	gotoxy(x, y + 8);

	std::cout << "Buff : ";
	for (auto i : buffs)
	{
		std::cout << getBuffName(i.buffIdx) << " , " << i.turn << " ";
	}
	std::cout << std::endl;
}

void Entity::printSkills(int x, int y)
{
	int tempY = y;
	int index = 0;

	gotoxy(x, y);
	std::cout << "|Active Skills , CD";
	for (auto i : activeSkills)
	{
		gotoxy(x, ++y);

		if (activeSkillsCD[index] != 0)
		{
			SetColor(8);
		}
		else
		{
			SetColor(7);
		}
		std::cout << "|" << getSkillName(i.skillIdx) << " , " << activeSkillsCD[index++];

		SetColor(7);
	}

	y = tempY;
	index = 0;
	gotoxy(x + 25, y);
	std::cout << "|Passive Skills , CD";
	for (auto i : passiveSkills)
	{
		gotoxy(x + 25, ++y);

		if (passiveSkillsCD[index] != 0)
		{
			SetColor(8);
		}
		else
		{
			SetColor(7);
		}
		std::cout << "|" << getSkillName(i.skillIdx) << " , " << passiveSkillsCD[index++];

		SetColor(7);
	}

	y = tempY;
	gotoxy(x + 50, y);
	std::cout << "|Buff , CD";
	for (auto i : buffs)
	{
		gotoxy(x + 50, y++);

		if (i.turn != 0)
		{
			SetColor(8);
		}
		else
		{
			SetColor(7);
		}
		std::cout << "|" << getBuffName(i.buffIdx) << " , " << i.turn;

		SetColor(7);
	}

}