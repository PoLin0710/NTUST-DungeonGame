#include "Equipment.h"

void Equipment::setWeapon(int idx)
{
	weapon = idx;
}

void Equipment::setArmor(int idx)
{
	armor = idx;
}

void Equipment::setAccessory(int idx)
{
	accessory = idx;
}

void Equipment::updateEquipment()
{
	eVitality = 0;
	eFocus = 0;
	eSpeed = 0;
	eHitRate = 0;
	ePAttack = 0;
	eMAttack = 0;
	ePDefense = 0;
	eMDefense = 0;

	mulVitality = 1;
	mulFocus = 1;
	mulSpeed = 1;
	mulHitRate = 1;
	mulPAttack = 1;
	mulMAttack = 1;
	mulPDefense = 1;
	mulMDefense = 1;

	maxVitality = 100;
	maxFocus = 3;
	maxSpeed = 100;
	maxHitRate = 100;
	maxPAttack = 100;
	maxMAttack = 100;
	maxPDefense = 100;
	maxMDefense = 100;

	//Weapon
	if (weapon == WEAPON_IDX::WOODEN_SWORD)
	{
		skills[SKILL_IDX::ATTACK].diceNum = 3;
		ePAttack += 5;
		eHitRate += 10;
	}
	else if (weapon == WEAPON_IDX::HAMMER)
	{
		skills[SKILL_IDX::ATTACK].diceNum = 4;
		ePAttack += 15;
		eHitRate -= 15;
	}
	else if (weapon == WEAPON_IDX::GIANT_HAMMER)
	{
		skills[SKILL_IDX::ATTACK].diceNum = 5;
		ePAttack += 20;
		eHitRate -= 15;
	}
	else if (weapon == WEAPON_IDX::MAGIC_WAND)
	{
		skills[SKILL_IDX::ATTACK].diceNum = 3;
		eMAttack += 10;
	}
	else if (weapon == WEAPON_IDX::RITUAL_SWORD)
	{
		skills[SKILL_IDX::ATTACK].diceNum = 1;
		eMAttack += 15;
	}

	//Armor
	if (armor == ARMOR_IDX::WOODEN_SHIELD)
	{
		ePDefense += 10;
	}
	else if (armor == ARMOR_IDX::PLATE_ARMOR)
	{
		ePDefense += 20;
		eSpeed -= 10;
	}
	else if (armor == ARMOR_IDX::LEATHER_ARMOR)
	{
		ePDefense += 5;
	}
	else if (armor == ARMOR_IDX::ROBE)
	{
		eMDefense += 10;
	}
	else if (armor == ARMOR_IDX::LAUREL_WREATH)
	{
		mulMDefense = 1.1;
	}

	//Accessory
	if (accessory == ACCESSORY_IDX::HOLY_GRAIL)
	{
		eMDefense += 30;
	}
	else if (accessory == ACCESSORY_IDX::SHOES)
	{
		eSpeed += 5;
	}
	else if (accessory == ACCESSORY_IDX::BRACELET)
	{
		maxFocus++;
	}
}

int Equipment::getWeapon() const
{
	return weapon;
}

int Equipment::getArmor() const
{
	return armor;
}

int Equipment::getAccessory() const
{
	return accessory;
}

int Equipment::getVitality(int vitality) const
{
	return min(int((vitality + eVitality) * mulVitality), maxVitality);
}

int Equipment::getFocus(int focus) const
{
	return min(int((focus + eFocus) * mulFocus), maxFocus);
}

int Equipment::getMaxFocus(int focus) const
{
	return maxFocus;
}

int Equipment::getSpeed(int speed) const
{
	return min(int((speed + eSpeed) * mulSpeed), maxSpeed);
}

int Equipment::getHitRate(int hitRate) const
{
	return min(int((hitRate + eHitRate) * mulHitRate), maxHitRate);
}

int Equipment::getPAttack(int pAttack) const
{
	return min(int((pAttack + ePAttack) * mulPAttack), maxPAttack);
}

int Equipment::getMAttack(int mAttack) const
{
	return min(int((mAttack + eMAttack) * mulMAttack), maxMAttack);
}

int Equipment::getPDefense(int pDefense) const
{
	return min(int((pDefense + ePDefense) * mulPDefense), maxPDefense);
}

int Equipment::getMDefense(int mDefense) const
{
	return min(int((mDefense + eMDefense) * mulMDefense), maxMDefense);
}

skill Equipment::getSkill(int idx) const
{
	return skills[idx];
}

bool compareSkill(const skill& s1, const skill& s2)
{
	return s1.skillIdx < s2.skillIdx;
}

bool equalSkill(const skill& s1, const skill& s2)
{
	return s1.skillIdx == s2.skillIdx;
}

vector<skill> Equipment::getSkills()
{
	vector<skill> vecSkill;
	vecSkill.push_back(skills[SKILL_IDX::ATTACK]);
	vecSkill.push_back(skills[SKILL_IDX::FLEE]);

	//Weapon
	if (weapon == WEAPON_IDX::WOODEN_SWORD) {
		vecSkill.push_back(skills[SKILL_IDX::SPEEDUP]);
	}
	else if (weapon == WEAPON_IDX::HAMMER)
	{
		vecSkill.push_back(skills[SKILL_IDX::PROVOKE]);
	}
	else if (weapon == WEAPON_IDX::MAGIC_WAND)
	{
		vecSkill.push_back(skills[SKILL_IDX::SHOCK_BLAST]);
		vecSkill.push_back(skills[SKILL_IDX::HEAL]);
	}
	else if (weapon == WEAPON_IDX::RITUAL_SWORD)
	{
		vecSkill.push_back(skills[SKILL_IDX::SHOCK_BLAST]);
	}
	else if (weapon == WEAPON_IDX::ELUCIDATOR_DARK_REPULSER)
	{
		vecSkill.push_back(skills[SKILL_IDX::STARBURST_STREAM]);
	}

	//Armor
	if (armor == ARMOR_IDX::WOODEN_SHIELD)
	{
		vecSkill.push_back(skills[SKILL_IDX::PROVOKE]);
	}

	//Accessory
	if (accessory == ACCESSORY_IDX::HOLY_GRAIL)
	{
		vecSkill.push_back(skills[SKILL_IDX::HEAL]);
	}

	sort(vecSkill.begin(), vecSkill.end(), compareSkill);
	auto it = std::unique(vecSkill.begin(), vecSkill.end(), equalSkill);
	vecSkill.erase(it, vecSkill.end());

	return vecSkill;
}

vector<skill> Equipment::getPassiveSkills()
{
	vector<skill> vecSkill;

	//Weapon
	if (weapon == WEAPON_IDX::HAMMER)
	{
		vecSkill.push_back(skills[SKILL_IDX::HAMMER_SPLASH]);
	}
	else if (weapon == WEAPON_IDX::GIANT_HAMMER)
	{
		vecSkill.push_back(skills[SKILL_IDX::HAMMER_SPLASH]);
	}
	else if (weapon == WEAPON_IDX::ELUCIDATOR_DARK_REPULSER)
	{
		vecSkill.push_back(skills[SKILL_IDX::DESTROY]);
	}

	//Armor
	if (armor == ARMOR_IDX::PLATE_ARMOR)
	{
		vecSkill.push_back(skills[SKILL_IDX::FORTIFY]);
	}
	else if (armor == ARMOR_IDX::LEATHER_ARMOR)
	{
		vecSkill.push_back(skills[SKILL_IDX::FORTIFY]);
	}

	//Accessory
	if (accessory == ACCESSORY_IDX::SHOES)
	{
		vecSkill.push_back(skills[SKILL_IDX::RUN]);
	}

	sort(vecSkill.begin(), vecSkill.end(), compareSkill);
	auto it = std::unique(vecSkill.begin(), vecSkill.end(), equalSkill);
	vecSkill.erase(it, vecSkill.end());

	return vecSkill;
}
