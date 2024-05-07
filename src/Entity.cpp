#include "Entity.h"

Entity::Entity()
{
	this->initVitality = 30 + rand() % 15; // Range [30,45)
	this->initFocus = 3;
	this->initSpeed = 30 + rand() % 25; // Range [30,55)
	this->initHitRate = 40 + rand() % 20; // Range [40,60)
	this->initPAttack = 5 + rand() % 11; // Range [5,15]
	this->initMAttack = 5 + rand() % 11; // Range [5,15]
	this->initPDefense = rand() % 21; // Range [0,20]
	this->initMDefense = rand() % 21; // Range [0,20]

	this->equipment.setWeapon(WEAPON_IDX::HAMMER);
	this->equipment.setArmor(ARMOR_IDX::WOODEN_SHIELD);
	this->equipment.setAccessory(ACCESSORY_IDX::ACCESSORY_NONE);

	equipment.updateEquipment();

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
}

Entity::~Entity()
{
}

void Entity::setVitality(int vitality) {
	this->maxVitality = vitality;
}

void Entity::setFocus(int focus) {
	this->maxFocus = focus;
}

void Entity::setSpeed(int speed) {
	this->maxSpeed = speed;
}

void Entity::setHitRate(int hitRate) {
	this->maxHitRate = hitRate;
}

void Entity::setPAttack(int pAttack) {
	this->maxPAttack = pAttack;
}

void Entity::setMAttack(int mAttack) {
	this->maxMAttack = mAttack;
}

void Entity::setPDefense(int pDefense) {
	this->maxPDefense = pDefense;
}

void Entity::setMDefense(int mDefense) {
	this->maxMDefense = mDefense;
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


int Entity::getVitality() const {
	return initVitality;
}

int Entity::getFocus() const {
	return initFocus;
}

int Entity::getSpeed() const {
	return initSpeed;
}

int Entity::getHitRate() const {
	return initHitRate;
}

int Entity::getPAttack() const {
	return initPAttack;
}

int Entity::getMAttack() const {
	return initMAttack;
}

int Entity::getPDefense() const {
	return initPDefense;
}

int Entity::getMDefense() const {
	return initMDefense;
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

double Entity::RolltheDice(int diceNum, int successNum)
{
	double successRate = 0;

	for (int i = 0; i < diceNum; i++)
	{
		if (i < successNum)
		{
			successRate++;

			std::cout << "True ";
		}
		else
		{
			int Roll = rand() % 100 + 1;

			if (Roll < curHitRate)
			{
				successRate++;
				std::cout << "True ";
			}
			else
			{
				std::cout << "False ";
			}
		}
	}
	std::cout << "\n";

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

	isFlee = false;
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
			this->curMAttack = this->maxMAttack * RolltheDice(curSkill.diceNum, useFocus()); //之後更改
			attack(0, this->curMAttack, target);

			this->curHitRate = this->maxHitRate;
		}
		else
		{
			this->curPAttack = this->maxMAttack * RolltheDice(curSkill.diceNum, useFocus()); //之後更改
			attack(this->curPAttack, 0, target);
		}
	}
	else
	{
		if (curSkill.skillIdx == SKILL_IDX::FLEE)
		{
			int rate = double(this->curVitality) / (this->maxVitality + this->curPDefense + this->curMDefense) * this->curSpeed;
			rate = std::min(rate, 98);

			this->curHitRate = rate;
			double state = RolltheDice(1, useFocus());
			this->curHitRate = this->maxHitRate;

			if (state >= 1)
			{
				std::cout << "Flee success\n";
				isFlee = true;
			}

		}
		else if (curSkill.skillIdx == SKILL_IDX::PROVOKE)
		{
			int rate = double(this->curVitality) / (this->maxVitality + this->curPDefense + this->curMDefense) * this->curSpeed;

			std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, enemys);
			this->curHitRate = rate;
			double state = RolltheDice(1, useFocus());
			this->curHitRate = this->maxHitRate;

			if (state >= 1)
			{
				std::cout << "PROVOKE success\n";
				target[0]->insertBuff(Buff::BUFF_IDX::BANGRY);
			}

		}
		else if (curSkill.skillIdx == SKILL_IDX::HEAL)
		{
			std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, roles);
			this->curMAttack = this->maxMAttack * RolltheDice(curSkill.diceNum, useFocus());
			heal(this->curMAttack, target);

		}
		else if (curSkill.skillIdx == SKILL_IDX::SPEEDUP)
		{
			std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, roles);
			double state = RolltheDice(curSkill.diceNum, useFocus());

			if (state >= 1)
			{
				std::cout << "SPEEDUP success\n";
				target[0]->insertBuff(Buff::BUFF_IDX::BSPEEDUP);
			}
		}
	}

}

int Entity::useFocus()
{
	int useFocus = 0;

	std::cout << "Use Focus: ";

	while (std::cin >> useFocus)
	{
		if (useFocus > curFocus)
		{
			std::cout << "Focus not enough !!\n";
			std::cout << "Re-enter: ";
		}
		else
		{
			this->curFocus -= useFocus;
			return useFocus;
		}
	}
}

void Entity::attack(int pAttack, int mAttack, std::vector<Entity*> enemys)
{
	for (auto i : enemys)
	{
		double pDefense = 1 - (i->curPDefense / double(i->curPDefense + 50));
		double mDefense = 1 - (i->curMDefense / double(i->curMDefense + 50));

		int realPAttack = pAttack * pDefense;
		int realMAttack = mAttack * mDefense;

		i->curVitality -= (realPAttack + realMAttack);
		i->curVitality = std::max(i->curVitality, 0);
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
		temp = { Buff::BUFF_IDX::BPOISONED,-1 };
		break;
	case Buff::BUFF_IDX::BSPEEDUP:
		temp = { Buff::BUFF_IDX::BSPEEDUP,-1 };
		break;
	default:
		break;
	}
	buffs.push_back(temp);
}

void Entity::heal(int mAttack, std::vector<Entity*> enemys)
{
	for (auto i : enemys)
	{
		int realMAttack = mAttack;

		i->curVitality += realMAttack;
		i->curVitality = std::min(i->curVitality, i->maxVitality);
	}
}

std::vector<Entity*> Entity::chooseEntitys(int skill_IDX, std::vector<Entity*> chooseList)
{
	int oneSelf[] = { SKILL_IDX::ATTACK ,SKILL_IDX::FLEE,SKILL_IDX::PROVOKE,SKILL_IDX::HEAL,SKILL_IDX::SPEEDUP, };
	int allSelf[] = { SKILL_IDX::SHOCK_BLAST };

	std::vector<Entity*> target;

	for (int i : oneSelf)
	{
		if (i == skill_IDX)
		{
			int pr = 0;
			for (auto j : chooseList)
			{
				std::cout << "Index: " << pr << std::endl;
				j->printInfo();
				pr++;

			}

			int index;

			std::cout << "Choose 1 (0-2):";
			std::cin >> index;

			target.push_back(chooseList[index]);
			return target;
		}
	}


	for (auto i : chooseList)
	{
		target.push_back(i);
	}

	return target;

}

void Entity::printInfo()
{
	std::cout << "Vitality is: " << curVitality << " / " << maxVitality << std::endl;
	std::cout << "Focus is: " << curFocus << " / " << maxFocus << std::endl;
	std::cout << "Speed is: " << curSpeed << " / " << maxSpeed << std::endl;
	std::cout << "HitRate is: " << curHitRate << " / " << maxHitRate << std::endl;
	std::cout << "PAttack is: " << curPAttack << " / " << maxPAttack << std::endl;
	std::cout << "MAttack is: " << curMAttack << " / " << maxMAttack << std::endl;
	std::cout << "PDefense is: " << curPDefense << " / " << maxPDefense << std::endl;
	std::cout << "MDefense is: " << curMDefense << " / " << maxMDefense << std::endl;
	std::cout << "Weapon is: " << equipment.getWeapon() << std::endl;
	std::cout << "Armor is: " << equipment.getArmor() << std::endl;
	std::cout << "Accessory is: " << equipment.getAccessory() << std::endl;
	std::cout << "isFlee : " << isFlee << std::endl;
}

