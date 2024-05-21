/***********************************************************************
 * File: Equipment.cpp
 * Author:
 *		  B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Create Date: $YEAR-$MONTH_5-$DAY_OF_MONTH_9
 * Editor:
 *		  B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Update Date: $YEAR-$MONTH_5-$DAY_OF_MONTH_19
 * Description: Implements the methods defined in the Equipment class for managing character equipment and skills.
***********************************************************************/

#include "Equipment.h"

// Intent: Sets the weapon index to the given value.
// Pre: None.
// Post: The weapon index is updated to the specified value.
void Equipment::setWeapon(int idx)
{
	weapon = idx;
}

// Intent: Sets the armor index to the given value.
// Pre: None.
// Post: The armor index is updated to the specified value.
void Equipment::setArmor(int idx)
{
	armor = idx;
}

// Intent: Sets the accessory index to the given value.
// Pre: None.
// Post: The accessory index is updated to the specified value.
void Equipment::setAccessory(int idx)
{
	accessory = idx;
}

// Intent: Recalculates and updates all equipment attributes.
// Pre: Weapon, armor, and accessory indices are set.
// Post: Equipment attributes and multipliers are updated accordingly.
void Equipment::updateEquipment()
{
	// Reset attributes
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

	// Update attributes based on the weapon
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
	else if (weapon == WEAPON_IDX::ELUCIDATOR_DARK_REPULSER)
	{
		skills[SKILL_IDX::ATTACK].diceNum = 3;
		ePAttack += 30;
	}

	// Update attributes based on the armor
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

	// Update attributes based on the accessory
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

// Intent: Returns the currently equipped weapon index.
// Pre: None.
// Post: The current weapon index is returned.
int Equipment::getWeapon() const
{
	return weapon;
}

// Intent: Returns the currently equipped armor index.
// Pre: None.
// Post: The current armor index is returned.
int Equipment::getArmor() const
{
	return armor;
}

// Intent: Returns the currently equipped accessory index.
// Pre: None.
// Post: The current accessory index is returned.
int Equipment::getAccessory() const
{
	return accessory;
}

// Intent: Calculates and returns the adjusted vitality.
// Pre: Base vitality value is provided.
// Post: The adjusted vitality is returned, capped at maxVitality.
int Equipment::getVitality(int vitality) const
{
	return min(int((vitality + eVitality) * mulVitality), maxVitality);
}

// Intent: Returns the maximum focus value.
// Pre: Base focus value is provided.
// Post: The maximum focus value is returned.
int Equipment::getFocus(int focus) const
{
	return maxFocus;
}

// Intent: Returns the maximum focus value.
// Pre: Base focus value is provided.
// Post: The maximum focus value is returned.
int Equipment::getMaxFocus(int focus) const
{
	return maxFocus;
}

// Intent: Calculates and returns the adjusted speed.
// Pre: Base speed value is provided.
// Post: The adjusted speed is returned, capped at maxSpeed.
int Equipment::getSpeed(int speed) const
{
	return min(int((speed + eSpeed) * mulSpeed), maxSpeed);
}

// Intent: Calculates and returns the adjusted hit rate.
// Pre: Base hit rate value is provided.
// Post: The adjusted hit rate is returned, capped at maxHitRate.
int Equipment::getHitRate(int hitRate) const
{
	return min(int((hitRate + eHitRate) * mulHitRate), maxHitRate);
}

// Intent: Calculates and returns the adjusted physical attack.
// Pre: Base physical attack value is provided.
// Post: The adjusted physical attack is returned, capped at maxPAttack.
int Equipment::getPAttack(int pAttack) const
{
	return min(int((pAttack + ePAttack) * mulPAttack), maxPAttack);
}

// Intent: Calculates and returns the adjusted magic attack.
// Pre: Base magic attack value is provided.
// Post: The adjusted magic attack is returned, capped at maxMAttack.
int Equipment::getMAttack(int mAttack) const
{
	return min(int((mAttack + eMAttack) * mulMAttack), maxMAttack);
}

// Intent: Calculates and returns the adjusted physical defense.
// Pre: Base physical defense value is provided.
// Post: The adjusted physical defense is returned, capped at maxPDefense.
int Equipment::getPDefense(int pDefense) const
{
	return min(int((pDefense + ePDefense) * mulPDefense), maxPDefense);
}

// Intent: Calculates and returns the adjusted magic defense.
// Pre: Base magic defense value is provided.
// Post: The adjusted magic defense is returned, capped at maxMDefense.
int Equipment::getMDefense(int mDefense) const
{
	return min(int((mDefense + eMDefense) * mulMDefense), maxMDefense);
}

// Intent: Returns the skill at the specified index.
// Pre: Skill index is provided.
// Post: The skill corresponding to the index is returned.
skill Equipment::getSkill(int idx) const
{
	return skills[idx];
}

// Intent: Compares two skills by their indices.
// Pre: Two skill objects are provided.
// Post: Returns true if the first skill's index is less than the second's.
bool compareSkill(const skill& s1, const skill& s2)
{
	return s1.skillIdx < s2.skillIdx;
}

// Intent: Checks equality of two skills by their indices.
// Pre: Two skill objects are provided.
// Post: Returns true if the skills' indices are equal.
bool equalSkill(const skill& s1, const skill& s2)
{
	return s1.skillIdx == s2.skillIdx;
}

// Intent: Returns a list of active skills based on equipped items.
// Pre: None.
// Post: The vector of active skills is returned.
vector<skill> Equipment::getSkills()
{
	vector<skill> vecSkill;
	vecSkill.push_back(skills[SKILL_IDX::ATTACK]);
	vecSkill.push_back(skills[SKILL_IDX::FLEE]);

	// Add weapon-specific skills
	if (weapon == WEAPON_IDX::WOODEN_SWORD)
	{
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

	// Add armor-specific skills
	if (armor == ARMOR_IDX::WOODEN_SHIELD)
	{
		vecSkill.push_back(skills[SKILL_IDX::PROVOKE]);
	}

	// Add accessory-specific skills
	if (accessory == ACCESSORY_IDX::HOLY_GRAIL)
	{
		vecSkill.push_back(skills[SKILL_IDX::HEAL]);
	}

	// Remove duplicate skills
	sort(vecSkill.begin(), vecSkill.end(), compareSkill);
	auto it = std::unique(vecSkill.begin(), vecSkill.end(), equalSkill);
	vecSkill.erase(it, vecSkill.end());

	return vecSkill;
}

// Intent: Returns a list of passive skills based on equipped items.
// Pre: None.
// Post: The vector of passive skills is returned.
vector<skill> Equipment::getPassiveSkills()
{
	vector<skill> vecSkill;

	// Add weapon-specific passive skills
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

	// Add armor-specific passive skills
	if (armor == ARMOR_IDX::PLATE_ARMOR)
	{
		vecSkill.push_back(skills[SKILL_IDX::FORTIFY]);
	}
	else if (armor == ARMOR_IDX::LEATHER_ARMOR)
	{
		vecSkill.push_back(skills[SKILL_IDX::FORTIFY]);
	}

	// Add accessory-specific passive skills
	if (accessory == ACCESSORY_IDX::SHOES)
	{
		vecSkill.push_back(skills[SKILL_IDX::RUN]);
	}

	// Remove duplicate skills
	sort(vecSkill.begin(), vecSkill.end(), compareSkill);
	auto it = std::unique(vecSkill.begin(), vecSkill.end(), equalSkill);
	vecSkill.erase(it, vecSkill.end());

	return vecSkill;
}