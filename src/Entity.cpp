#include "Entity.h"

Entity::Entity(std::string _name)
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
	this->equipment.setAccessory(ACCESSORY_IDX::ACCESSORY_NONE);

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

double Entity::RolltheDice(int diceNum, int successNum)
{
	double successRate = 0;

	for (int i = 0; i < diceNum; i++)
	{
		if (i < successNum || (i == 0 && findSkills(SKILL_IDX::RUN))) //Passtive skill detect
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
			rate = std::min(rate, 98);

			this->curHitRate = rate;
			double state = RolltheDice(1, useFocus(curSkill.diceNum));
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
			double state = RolltheDice(1, useFocus(curSkill.diceNum));
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
			this->curMAttack = this->maxMAttack * RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum));
			heal(this->curMAttack, target);

		}
		else if (curSkill.skillIdx == SKILL_IDX::SPEEDUP)
		{
			std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, roles);
			double state = RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum));

			if (state >= 1)
			{
				std::cout << "SPEEDUP success\n";
				target[0]->insertBuff(Buff::BUFF_IDX::BSPEEDUP);
			}
		}
	}

	if (findBuffs(Buff::BUFF_IDX::BPOISONED))
	{
		std::cout << "Launch Debuff Poisoned!\n";
		this->curVitality -= (this->curVitality * 0.1);
	}

	turnEnd();
}

int Entity::useFocus(int diceNum)
{
	int useFocus = 0;

	std::cout << "Use Focus(0-" << std::min(curFocus, diceNum) << "): ";

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

		i->curVitality -= (realPAttack + realMAttack);
		i->curVitality = std::max(i->curVitality, 0);

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
	this;
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
	this->buffs.push_back(temp);
	int x = 0;
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
				std::cout << "Index: " << pr << std::endl << std::endl;
				j->printInfo();
				pr++;
			}

			int index;

			std::cout << "Choose 1 (0-" << chooseList.size() - 1 << "):";
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

//回傳是否開始下一個步驟 否直接到TurnEnd
bool Entity::turnStart()
{
	for (int i = 0; i < activeSkillsCD.size(); i++)
	{
		activeSkillsCD[i] = std::max(activeSkillsCD[i] - 1, 0);
	}

	for (int i = 0; i < passiveSkillsCD.size(); i++)
	{
		passiveSkillsCD[i] = std::max(passiveSkillsCD[i] - 1, 0);
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

void Entity::printInfo()
{
	std::cout << "===================================================" << std::endl;
	std::cout << "|Name is :" << name << std::endl;
	std::cout << "|Vitality is: " << curVitality << " / " << maxVitality << std::endl;
	std::cout << "|Focus is: " << curFocus << " / " << maxFocus << std::endl;
	std::cout << "|Speed is: " << curSpeed << " / " << maxSpeed << std::endl;
	std::cout << "|HitRate is: " << curHitRate << " / " << maxHitRate << std::endl;
	std::cout << "|PAttack is: " << curPAttack << " / " << maxPAttack << std::endl;
	std::cout << "|MAttack is: " << curMAttack << " / " << maxMAttack << std::endl;
	std::cout << "|PDefense is: " << curPDefense << " / " << maxPDefense << std::endl;
	std::cout << "|MDefense is: " << curMDefense << " / " << maxMDefense << std::endl;
	std::cout << "|Weapon is: " << getWeaponName(equipment.getWeapon()) << std::endl;
	std::cout << "|Armor is: " << getArmorName(equipment.getArmor()) << std::endl;
	std::cout << "|Accessory is: " << getAccessoryName(equipment.getAccessory()) << std::endl;
	std::cout << "|isFlee : " << isFlee << std::endl;

	std::cout << "|Active Skills : ";
	for (auto i : activeSkills)
	{
		std::cout << getSkillName(i.skillIdx) << " ";
	}
	std::cout << std::endl;
	std::cout << "|Passive Skills : ";
	for (auto i : passiveSkills)
	{
		std::cout << getSkillName(i.skillIdx) << " ";
	}
	std::cout << std::endl;
	std::cout << "|Buff : ";
	for (auto i : buffs)
	{
		std::cout << getBuffName(i.buffIdx) << " , " << i.turn << " ";
	}
	std::cout << std::endl;
	std::cout << "===================================================" << std::endl;
}

