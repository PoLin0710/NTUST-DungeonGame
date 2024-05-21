/***********************************************************************
 * File: Entity.cpp
 * Author:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Create Date: 2024-05-21
 * Editor:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Update Date: 2024-05-21
 * Description: Implementation of the Entity class, representing characters and enemies in the game.
***********************************************************************/
#include "Entity.h"

// Intent: To initialize an Entity object with specified name, type, and icon
// Pre: The name must be a valid string, type must be a valid ENTITY_TYPE, and icon must be a character
// Post: Initializes the entity with random attributes and equipment, setting up initial and maximum values
Entity::Entity(std::string _name, int type = ENTITY_TYPE::ENEMY, char icon = 'E')
{
	this->name = _name;
	this->eicon = icon;

	this->initVitality = 30 + rand() % 15;	// Range [30,45)
	this->initFocus = 3;
	this->initSpeed = 30 + rand() % 25;		// Range [30,55)
	this->initHitRate = 40 + rand() % 20;	// Range [40,60)
	this->initPAttack = 5 + rand() % 11;	// Range [5,15]
	this->initMAttack = 5 + rand() % 11;	// Range [5,15]
	this->initPDefense = rand() % 21;		// Range [0,20]
	this->initMDefense = rand() % 21;		// Range [0,20]

	//Set equipment
	this->equipment.setWeapon(WEAPON_IDX::HAMMER);
	this->equipment.setArmor(ARMOR_IDX::PLATE_ARMOR);
	this->equipment.setAccessory(ACCESSORY_IDX::SHOES);

	//Update equipment attribute
	this->equipment.updateEquipment();

	//init skills
	this->activeSkills = equipment.getSkills();
	this->passiveSkills = equipment.getPassiveSkills();
	this->activeSkillsCD.clear();
	this->passiveSkillsCD.clear();
	this->activeSkillsCD.resize(activeSkills.size(), 0);
	this->passiveSkillsCD.resize(passiveSkills.size(), 0);

	//Set have equipment ,update entity attribute
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
	//==================================================

	//init attribute
	this->isFlee = false;
	this->turn = 0;
	this->type = type;
}

// Intent: To destruct the Entity object
// Pre: None
// Post: Properly destructs the Entity object, freeing any allocated resources
Entity::~Entity()
{
}

// Intent: To set the current vitality of the entity
// Pre: vitality must be a non-negative integer
// Post: Sets the current vitality, ensuring it does not exceed the maximum vitality
void Entity::setVitality(int vitality) {
	this->curVitality = min(vitality, this->maxVitality);
}

// Intent: To set the current focus of the entity
// Pre: focus must be a non-negative integer
// Post: Sets the current focus, ensuring it does not exceed the maximum focus
void Entity::setFocus(int focus) {
	this->curFocus = min(focus, this->maxFocus);
}

// Intent: To set the current speed of the entity
// Pre: speed must be a non-negative integer
// Post: Sets the current speed
void Entity::setSpeed(int speed) {
	this->curSpeed = speed;
}

// Intent: To set the current hit rate of the entity
// Pre: hitRate must be a non-negative integer
// Post: Sets the current hit rate
void Entity::setHitRate(int hitRate) {
	this->curHitRate = hitRate;
}

// Intent: To set the current physical attack of the entity
// Pre: pAttack must be a non-negative integer
// Post: Sets the current physical attack
void Entity::setPAttack(int pAttack) {
	this->curPAttack = pAttack;
}

// Intent: To set the current magical attack of the entity
// Pre: mAttack must be a non-negative integer
// Post: Sets the current magical attack
void Entity::setMAttack(int mAttack) {
	this->curMAttack = mAttack;
}

// Intent: To set the current physical defense of the entity
// Pre: pDefense must be a non-negative integer
// Post: Sets the current physical defense
void Entity::setPDefense(int pDefense) {
	this->curPDefense = pDefense;
}

// Intent: To set the current magical defense of the entity
// Pre: mDefense must be a non-negative integer
// Post: Sets the current magical defense
void Entity::setMDefense(int mDefense) {
	this->curMDefense = mDefense;
}

// Intent: To set the weapon of the entity
// Pre: weapon must be a valid weapon index
// Post: Sets the weapon of the entity
void Entity::setWeapon(int weapon) {
	this->equipment.setWeapon(weapon);
}

// Intent: To set the armor of the entity
// Pre: armor must be a valid armor index
// Post: Sets the armor of the entity
void Entity::setArmor(int armor) {
	this->equipment.setArmor(armor);
}

// Intent: To set the accessory of the entity
// Pre: accessory must be a valid accessory index
// Post: Sets the accessory of the entity
void Entity::setAccessory(int accessory) {
	this->equipment.setAccessory(accessory);
}

// Intent: To set the icon of the entity
// Pre: _icon must be a character
// Post: Sets the icon of the entity
void Entity::setIcon(char _icon)
{
	this->eicon = _icon;
}

// Intent: To get the name of the entity
// Pre: None
// Post: Returns the name of the entity
string Entity::getName() const
{
	return name;
}

// Intent: To get the current vitality of the entity
// Pre: None
// Post: Returns the current vitality of the entity
int Entity::getVitality() const {
	return curVitality;
}

// Intent: To get the current focus of the entity
// Pre: None
// Post: Returns the current focus of the entity
int Entity::getFocus() const {
	return curFocus;
}

// Intent: To get the current speed of the entity, considering buffs
// Pre: None
// Post: Returns the current speed of the entity
int Entity::getSpeed() {
	if (findBuffs(Buff::BUFF_IDX::BSPEEDUP))
	{
		return curSpeed * 1.5;
	}

	return curSpeed;
}

// Intent: To get the hit rate of the entity
// Pre: None
// Post: Returns the hit rate of the entity
int Entity::getHitRate() const {
	return maxHitRate;
}

// Intent: To get the current physical attack of the entity
// Pre: None
// Post: Returns the current physical attack of the entity
int Entity::getPAttack() const {
	return curPAttack;
}

// Intent: To get the current magical attack of the entity
// Pre: None
// Post: Returns the current magical attack of the entity
int Entity::getMAttack() const {
	return curMAttack;
}

// Intent: To get the current physical defense of the entity
// Pre: None
// Post: Returns the current physical defense of the entity
int Entity::getPDefense() const {
	return curPDefense;
}

// Intent: To get the current magical defense of the entity
// Pre: None
// Post: Returns the current magical defense of the entity
int Entity::getMDefense() const {
	return curMDefense;
}

// Intent: To get the weapon of the entity
// Pre: None
// Post: Returns the weapon of the entity
int Entity::getWeapon() const {
	return equipment.getWeapon();
}

// Intent: To get the armor of the entity
// Pre: None
// Post: Returns the armor of the entity
int Entity::getArmor() const {
	return equipment.getArmor();
}

// Intent: To get the accessory of the entity
// Pre: None
// Post: Returns the accessory of the entity
int Entity::getAccessory() const {
	return equipment.getAccessory();
}

// Intent: To get the type of the entity
// Pre: None
// Post: Returns the type of the entity
int Entity::getType() const
{
	return type;
}

// Intent: To get the size of the active skills list
// Pre: None
// Post: Returns the size of the active skills list
int Entity::getActiveSkillSize() const
{
	return activeSkills.size();
}

// Intent: To get the flee status of the entity
// Pre: None
// Post: Returns whether the entity is fleeing
bool Entity::getIsFlee() const
{
	return isFlee;
}

// Intent: To get the active skills of the entity
// Pre: None
// Post: Returns the active skills of the entity
std::vector<skill> Entity::getActiveSkills() const
{
	return activeSkills;
}

// Intent: To check if the entity is dizzy
// Pre: None
// Post: Returns true if the entity is affected by dizziness, otherwise false
bool Entity::isDizziness()
{
	return findBuffs(Buff::BUFF_IDX::BDIZZINESS);
}

// Intent: To get the icon of the entity
// Pre: None
// Post: Returns the icon of the entity
char Entity::getIcon() const
{
	return eicon;
}

// Intent: To roll the dice for an action and calculate the success rate
// Pre: diceNum, successNum, x, and y must be non-negative integers
// Post: Rolls the dice and returns the success rate
double Entity::RolltheDice(int diceNum, int successNum, int  x, int y)
{
	//Declare
	double successRate = 0;
	double mul = 1;

	//Debuff angry check
	if (findBuffs(Buff::BUFF_IDX::BANGRY))
	{
		mul = 0.7;
	}


	//Output pos
	gotoxy(x, y);

	//Roll
	for (int i = 0; i < diceNum; i++)
	{
		if (i < successNum + findSkills(SKILL_IDX::RUN)) //Passtive skill detect
		{
			successRate++;

			SetColor(14);

			std::cout << "*";
			SetColor(7);
		}
		else
		{
			int Roll = rand() % 100 + 1;

			if (Roll < curHitRate * mul) //succes
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



	return successRate / diceNum;
}

// Intent: To update the entity's attributes and equipment before combat
// Pre: None
// Post: Updates the entity's attributes and equipment to their initial and maximum values
void Entity::update()
{
	//update equipment state
	equipment.updateEquipment();

	//Set attribute
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

	//==init==
	isFlee = false;
	this->turn = 0;
	buffs.clear();

	activeSkills = equipment.getSkills();
	passiveSkills = equipment.getPassiveSkills();
	activeSkillsCD.clear();
	passiveSkillsCD.clear();
	activeSkillsCD.resize(activeSkills.size(), 0);
	passiveSkillsCD.resize(passiveSkills.size(), 0);
	//================
}

// Intent: To update the entity's attributes and equipment during combat
// Pre: None
// Post: Updates the entity's attributes and equipment, including skill cooldowns
void Entity::combatUpdate()
{
	//update equipment attribute
	equipment.updateEquipment();

	//Set state
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

	//Declare temp
	std::map<int, int> activeSkillsCDTemp;
	std::map<int, int> passiveSkillsCDTemp;

	//==Get skills ID==
	int index = 0;
	for (auto i : activeSkills)
	{
		activeSkillsCDTemp[i.skillIdx] = activeSkillsCD[index++];
	}

	index = 0;
	for (auto i : passiveSkills)
	{
		passiveSkillsCDTemp[i.skillIdx] = passiveSkillsCD[index++];
	}
	//==================

	//get skills
	activeSkills = equipment.getSkills();
	passiveSkills = equipment.getPassiveSkills();

	activeSkillsCD.clear();
	passiveSkillsCD.clear();
	activeSkillsCD.resize(activeSkills.size(), 0);
	passiveSkillsCD.resize(passiveSkills.size(), 0);
	//============

	//map skill to CD
	index = 0;
	for (auto i : activeSkills)
	{
		activeSkillsCD[index++] = activeSkillsCDTemp[i.skillIdx];
	}

	index = 0;
	for (auto i : passiveSkills)
	{
		passiveSkillsCD[index++] = passiveSkillsCDTemp[i.skillIdx];
	}
}

// Intent: To use a skill from the entity's active skill list
// Pre: skill_IDX must be a valid index within the active skills list,
//		roles and enemys must be valid vectors of entity pointers.
// Post: Uses the specified skill, applying its effects and updating skill cooldowns
bool Entity::useSkill(int skill_IDX, std::vector<Entity*> roles, std::vector<Entity*> enemys)
{
	//Check skill can cast
	if (skill_IDX >= activeSkills.size() || activeSkillsCD[skill_IDX] != 0)
	{
		return false;
	}

	//Get current skill
	skill curSkill = activeSkills[skill_IDX];
	activeSkillsCD[skill_IDX] = curSkill.cd;

	//if skill type is attack
	if (curSkill.type == SKILLTYPE::ATK)
	{
		//Choose attack target
		std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, enemys);

		//Choose weapon
		if (getWeapon() == WEAPON_IDX::MAGIC_WAND || getWeapon() == WEAPON_IDX::RITUAL_SWORD) //magic attack
		{
			//cal attack info
			this->curHitRate = this->maxHitRate - 5;
			this->curMAttack = this->maxMAttack * RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum), 3, 22);

			attack(curSkill.skillIdx, 0, this->curMAttack, target);

			this->curHitRate = this->maxHitRate;
		}
		else if (getWeapon() == WEAPON_IDX::HAMMER || getWeapon() == WEAPON_IDX::GIANT_HAMMER) //physical attack (Have AOE)
		{
			//cal attack info
			float rate = RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum), 3, 22);
			this->curMAttack = this->maxMAttack * rate;

			std::vector<Entity*> Aoe;

			//remove target choose other
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
				target[0]->insertBuff(Buff::BUFF_IDX::BDIZZINESS); //give target Debuff
			}

			attack(curSkill.skillIdx, 0, this->curMAttack, target);
			attack(curSkill.skillIdx, 0, this->curMAttack * 0.5, Aoe);

		}
		else if (getWeapon() == WEAPON_IDX::ELUCIDATOR_DARK_REPULSER) // new weapon
		{
			//cal attack info
			float rate = RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum), 3, 22);
			this->curPAttack = this->maxMAttack * rate;

			if (rate == 1)
			{
				target[0]->insertBuff(Buff::BUFF_IDX::BPOISONED); //give target Debuff
			}

			attack(curSkill.skillIdx, 0, this->curMAttack, target);
		}
		else // normal attack
		{
			this->curPAttack = this->maxMAttack * RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum), 3, 22);
			attack(curSkill.skillIdx, this->curPAttack, 0, target);
		}
	}
	else //skill type is SP
	{
		if (curSkill.skillIdx == SKILL_IDX::FLEE) //Flee
		{
			//cal attribute
			int rate = double(this->curVitality) / (this->maxVitality + this->curPDefense + this->curMDefense) * this->curSpeed;
			rate = min(rate, 98);

			//Set
			this->curHitRate = rate;
			double state = RolltheDice(1, useFocus(curSkill.diceNum), 3, 22);
			this->curHitRate = this->maxHitRate;

			//Detect
			if (state >= 1)
			{
				isFlee = true;
			}

		}
		else if (curSkill.skillIdx == SKILL_IDX::PROVOKE) //give target Debuff(angry)
		{
			//cal
			int rate = double(this->curVitality) / (this->maxVitality + this->curPDefense + this->curMDefense) * this->curSpeed;

			//Choose
			std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, enemys);

			//Set
			this->curHitRate = rate;
			double state = RolltheDice(1, useFocus(curSkill.diceNum), 3, 22);
			this->curHitRate = this->maxHitRate;

			//Detect
			if (state >= 1)
			{
				target[0]->insertBuff(Buff::BUFF_IDX::BANGRY);
			}

		}
		else if (curSkill.skillIdx == SKILL_IDX::HEAL) //Heal
		{
			//Choose
			std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, roles);

			//Cal
			this->curMAttack = this->maxMAttack * RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum), 3, 22);

			//Cast skill
			heal(this->curMAttack, target);

		}
		else if (curSkill.skillIdx == SKILL_IDX::SPEEDUP) //Speedup
		{
			//Choose
			std::vector<Entity*> target = chooseEntitys(curSkill.skillIdx, roles);

			//Set
			double state = RolltheDice(curSkill.diceNum, useFocus(curSkill.diceNum), 3, 22);

			//Detect
			if (state >= 1)
			{
				target[0]->insertBuff(Buff::BUFF_IDX::BSPEEDUP);
			}
		}
	}

	if (findBuffs(Buff::BUFF_IDX::BPOISONED)) //Debuff cast poisoned
	{
		this->curVitality -= (this->curVitality * 0.1);
	}

}

/**
 * Intent: To determine and adjust the focus used during an action
 * Pre: diceNum must be a non-negative integer
 * Post: Adjusts the focus used based on player input or random choice, returns the amount of focus used
 */
int Entity::useFocus(int diceNum)
{
	//Declare
	int useFocus = 0;
	int maxFocus = max(0, min(curFocus + findSkills(SKILL_IDX::RUN), diceNum - findSkills(SKILL_IDX::RUN)));

	//==Output==
	gotoxy(3, 21);
	std::cout << "Focus (A :Reduce Focus D :ADD Focus)";

	gotoxy(3, 22);
	for (int i = 0; i < diceNum; i++)
	{
		if (i == 0 && findSkills(SKILL_IDX::RUN))
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
	//======================

	if (type == ENTITY_TYPE::ROLE) //If Entity is Role
	{
		while (true)
		{
			//Output
			gotoxy(0, 48);

			//Input
			char command = _getch();

			//Select up
			if (command == 'A' || command == 'a')
			{
				gotoxy(3, 22);

				useFocus = useFocus - 1 < 0 ? 0 : useFocus - 1;

				for (int i = 0; i < diceNum; i++)
				{
					if (i < useFocus || (findSkills(SKILL_IDX::RUN) && i < useFocus + 1)) //Buff
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
			else if (command == 'D' || command == 'd') //Select down
			{
				gotoxy(3, 22);
				useFocus = useFocus >= maxFocus ? maxFocus : useFocus + 1;

				for (int i = 0; i < diceNum; i++)
				{
					if (i < useFocus || (findSkills(SKILL_IDX::RUN) && i < useFocus + 1))
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
			else if (command == 13) //Enter
			{
				break;
			}
		}
	}
	else // Entity is enemy
	{
		int randomFocus = maxFocus == 0 ? 0 : rand() % maxFocus; //Random focus

		//output
		gotoxy(3, 22);

		for (int i = 0; i < maxFocus; i++)
		{
			if (i < randomFocus + findSkills(SKILL_IDX::RUN)) //Buff
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

	//Set
	this->curFocus -= useFocus;

	return useFocus;
}

/**
 * Intent: To perform an attack on a list of enemy entities, applying physical and magical damage
 * Pre: skillIdx must be a valid skill index, pAttack and mAttack must be non-negative integers, and enemys must be a valid vector of Entity pointers
 * Post: Calculates and applies damage to each enemy, considering their defenses and any passive skills
 */
void Entity::attack(int skillIdx, int pAttack, int mAttack, std::vector<Entity*> enemys)
{
	//Declare attack is to one or Aoe
	std::vector<int> oneSelf = { SKILL_IDX::ATTACK ,SKILL_IDX::FLEE,SKILL_IDX::PROVOKE,SKILL_IDX::HEAL,SKILL_IDX::SPEEDUP, };
	std::vector<int> allSelf = { SKILL_IDX::SHOCK_BLAST,-1 };

	//Attack enemys
	for (auto i : enemys)
	{
		//==cal==
		double pDefense = 1 - (i->curPDefense / double(i->curPDefense + 50));
		double mDefense = 1 - (i->curMDefense / double(i->curMDefense + 50));

		int realPAttack = pAttack * pDefense;
		int realMAttack = mAttack * mDefense;
		//=======

		//Buff detect
		if (i->findSkills(SKILL_IDX::FORTIFY))
		{
			realPAttack *= 0.9;
			realMAttack *= 0.9;
		}

		//Set value
		i->curVitality -= (realPAttack + realMAttack);
		i->curVitality = max(i->curVitality, 0);

		//Passtive skill
		if ((realPAttack + realMAttack) > 0 && findSkills(SKILL_IDX::DESTROY) && enemys.size() == 1)
		{
			std::vector<int> equipmentTemp;

			if (i->getWeapon() != WEAPON_IDX::WEAPON_NONE)
			{
				equipmentTemp.push_back(0);
			}

			if (i->getArmor() != ARMOR_IDX::ARMOR_NONE)
			{
				equipmentTemp.push_back(1);
			}

			if (i->getAccessory() != ACCESSORY_IDX::ACCESSORY_NONE)
			{
				equipmentTemp.push_back(2);
			}

			if (equipmentTemp.size() == 0)
			{
				continue;
			}

			//Random destroy equipment
			switch (equipmentTemp[rand() % equipmentTemp.size()])
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

			i->combatUpdate();
		}

	}
}

/**
 * Intent: To insert a buff into the entity's list of active buffs, updating its duration if it already exists
 * Pre: buffIdx must be a valid buff index
 * Post: Adds the buff to the entity's list or updates the duration if the buff is already present
 * \param buffIdx Index of the buff to be added or updated
 */
void Entity::insertBuff(int buffIdx)
{
	//Declare
	Buff::Buff temp;

	//Choose Buff
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

	//Check buff not repeat if repeat add cd to this buff
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

	//if not push this
	if (!find)
	{
		this->buffs.push_back(temp);
	}
}

/**
 * Intent: To heal a list of entities by a specified amount of magical attack (mAttack)
 * Pre: mAttack must be a non-negative integer, and enemys must be a valid vector of Entity pointers
 * Post: Increases the vitality of each entity in the list by the specified amount, up to their maximum vitality
 * \param mAttack The amount of magical attack to heal
 * \param enemys The list of entities to heal
 */
void Entity::heal(int mAttack, std::vector<Entity*> enemys)
{
	//Heal target
	for (auto i : enemys)
	{
		int realMAttack = mAttack;

		i->curVitality += realMAttack;
		i->curVitality = min(i->curVitality, i->maxVitality);
	}
}

/**
 * Intent: To select target entities based on the skill being used
 * Pre: skill_IDX must be a valid skill index, and chooseList must be a valid vector of Entity pointers
 * Post: Returns a vector of selected target entities based on the skill and entity type
 * \param skill_IDX The index of the skill being used
 * \param chooseList The list of entities to choose from
 * \return A vector of selected target entities
 */
std::vector<Entity*> Entity::chooseEntitys(int skill_IDX, std::vector<Entity*> chooseList)
{
	// Set target list and remove died or isflee
	chooseList.erase(
		std::remove_if(chooseList.begin(), chooseList.end(),
			[](const Entity* entity) {
				return entity->getIsFlee() || entity->getVitality() == 0;
			}),
		chooseList.end()
				);

	// Choose attack is to one or all
	int oneSelf[] = { SKILL_IDX::ATTACK ,SKILL_IDX::FLEE,SKILL_IDX::PROVOKE,SKILL_IDX::HEAL,SKILL_IDX::SPEEDUP,SKILL_IDX::STARBURST_STREAM };
	int allSelf[] = { SKILL_IDX::SHOCK_BLAST };

	//Declare target
	std::vector<Entity*> target;

	//Check the skill is to one
	for (int i : oneSelf)
	{
		if (i == skill_IDX) //if find
		{
			if (type == ENTITY_TYPE::ROLE) //if entity is  role
			{
				//==Output==
				gotoxy(6, 15);
				std::cout << "====Target====";

				int pr = 0;
				for (auto j : chooseList) //Choose list
				{
					gotoxy(6, 16 + pr);

					std::cout << j->getName();

					pr++;
				}

				int index = 0;

				//Select indicater
				gotoxy(3, 16);
				std::cout << "->";

				while (true)
				{
					gotoxy(0, 48);

					//input command
					char command = _getch();

					if (command == 'W' || command == 'w') //Select up
					{
						gotoxy(3, 16 + index);
						std::cout << "  ";

						index = index - 1 < 0 ? chooseList.size() - 1 : index - 1;

						gotoxy(3, 16 + index);
						std::cout << "->";
					}
					else if (command == 'S' || command == 's') //Select down
					{
						gotoxy(3, 16 + index);
						std::cout << "  ";

						index = index + 1 == chooseList.size() ? 0 : index + 1;

						gotoxy(3, 16 + index);
						std::cout << "->";
					}
					else if (command == 13) //Enter
					{
						target.push_back(chooseList[index]);
						break;
					}
				}
				//===================
			}
			else //entity is Enemy
			{
				int randomChoose = rand() % chooseList.size(); //Random choose

				//Output
				gotoxy(6, 15);
				std::cout << "====CHOOSE====";

				gotoxy(6, 16);
				std::cout << chooseList[randomChoose]->name;
				target.push_back(chooseList[randomChoose]);
			}

			//Return target
			return target;
		}

	}

	// choose all enemy
	for (auto i : chooseList)
	{
		target.push_back(i);
	}

	//Return targer
	return target;

}

/**
 * Intent: To manage the start of the entity's turn, updating skill cooldowns and checking for dizziness
 * Pre: None
 * Post: Updates the cooldowns of active and passive skills, returns false if the entity is dizzy, otherwise true
 * \return False if the entity is affected by dizziness, otherwise true
 */
bool Entity::turnStart()
{
	//==CD reduce==
	for (int i = 0; i < activeSkillsCD.size(); i++)
	{
		activeSkillsCD[i] = max(activeSkillsCD[i] - 1, 0);
	}

	for (int i = 0; i < passiveSkillsCD.size(); i++)
	{
		passiveSkillsCD[i] = max(passiveSkillsCD[i] - 1, 0);
	}
	//=============

	//Detect have debuff Dissiness
	if (findBuffs(Buff::BUFF_IDX::BDIZZINESS))
	{
		return false; //couldn't start this turn
	}

	return true;
}

/**
 * Intent: To manage the end of the entity's turn, updating the duration of buffs and removing expired buffs
 * Pre: None
 * Post: Decreases the duration of each active buff, removes buffs that have expired
 */
void Entity::turnEnd()
{
	//Buff cd reduce
	for (auto i = buffs.begin(); i != buffs.end(); i++)
	{
		if (i->turn > 0)
		{
			i->turn = i->turn - 1;
		}
	}

	//if buff turn end remove this
	buffs.erase(std::remove_if(buffs.begin(), buffs.end(), [](const Buff::Buff& src) {
		return src.turn == 0;
		}), buffs.end());
}

/**
 * Intent: To check if a specific skill exists in the entity's passive skills
 * Pre: skillIdx must be a valid skill index
 * Post: Returns true if the skill exists in the entity's passive skills, otherwise false
 * \param skillIdx The index of the skill to find
 * \return True if the skill exists, otherwise false
 */
bool Entity::findSkills(SKILL_IDX skillIdx)
{
	//Find
	auto it = std::find_if(passiveSkills.begin(), passiveSkills.end(), [skillIdx](const skill& skill) {
		return skill.skillIdx == skillIdx;
		});

	//find it
	if (it != passiveSkills.end())
	{
		return true;
	}

	return false;
}

/**
 * Intent: To check if a specific buff exists in the entity's active buffs
 * Pre: buffIdx must be a valid buff index
 * Post: Returns true if the buff exists in the entity's active buffs, otherwise false
 * \param buffIdx The index of the buff to find
 * \return True if the buff exists, otherwise false
 */
bool Entity::findBuffs(Buff::BUFF_IDX buffIdx)
{
	//Find
	auto it = std::find_if(buffs.begin(), buffs.end(), [buffIdx](const Buff::Buff& buff) {
		return buff.buffIdx == buffIdx;
		});

	//find it
	if (it != buffs.end())
	{
		return true;
	}

	return false;
}

/**
 * Intent: To print the detailed information of the entity at a specified position on the console
 * Pre: x and y must be non-negative integers representing the position on the console
 * Post: Displays the entity's name, current and max attributes, equipment, and active buffs at the specified position
 * \param x The x-coordinate on the console
 * \param y The y-coordinate on the console
 */
void Entity::printInfo(int x, int y)
{
	//==Output==
	gotoxy(x, y);
	std::cout << "Name: " << name << std::endl;

	gotoxy(x, y + 1);
	std::cout << "HP: " << std::left << std::setw(3) << curVitality << "/" << std::left << std::setw(3) << maxVitality << "   ";
	std::cout << "FOCUS: " << curFocus << "/" << maxFocus << std::endl;

	gotoxy(x, y + 2);
	std::cout << "PATK: " << std::left << std::setw(3) << maxPAttack << "     ";
	std::cout << "PDEF: " << std::left << std::setw(3) << maxPDefense << std::endl;

	gotoxy(x, y + 3);
	std::cout << "MATK: " << std::left << std::setw(3) << maxMAttack << "     ";
	std::cout << "MDEF: " << std::left << std::setw(3) << maxMDefense << std::endl;

	gotoxy(x, y + 4);
	std::cout << "SPD: " << std::left << std::setw(3) << maxSpeed << "      ";
	std::cout << "HIT: " << std::left << std::setw(3) << maxHitRate << std::endl;

	gotoxy(x, y + 5);
	std::cout << "Weapon: " << std::left << std::setw(20) << getWeaponName(equipment.getWeapon()) << std::endl;

	gotoxy(x, y + 6);
	std::cout << "Armor: " << std::left << std::setw(20) << getArmorName(equipment.getArmor()) << std::endl;

	gotoxy(x, y + 7);
	std::cout << "Accessory: " << std::left << std::setw(20) << getAccessoryName(equipment.getAccessory()) << std::endl;

	gotoxy(x, y + 8);

	std::cout << "Buff : ";
	for (auto i : buffs)
	{
		std::cout << getBuffName(i.buffIdx) << " , " << i.turn << " ";
	}
	std::cout << std::endl;
	//================
}

/**
 * Intent: To print the entity's active skills, passive skills, and buffs along with their cooldowns and durations
 * Pre: x and y must be non-negative integers representing the position on the console
 * Post: Displays the entity's active skills, passive skills, and buffs with their cooldowns and durations at the specified position
 * \param x The x-coordinate on the console
 * \param y The y-coordinate on the console
 */
void Entity::printSkills(int x, int y)
{
	//Declare output pos
	int tempY = y;
	int index = 0;

	//Output
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
	//=============
}