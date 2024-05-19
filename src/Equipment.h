/***********************************************************************
 * File: Equipment.h
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
 * Description: Defines data structures and methods for the equipment and skill system.
				This file contains several enumerations for identifying various weapons, armors, accessories, and skills.
				It also defines the "skill" struct and the "Equipment" class for managing character equipment and skills.
***********************************************************************/

#pragma once
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Enumeration for weapon indices to identify different types of weapons.
enum WEAPON_IDX
{
	WEAPON_NONE = 0,
	WOODEN_SWORD = 1,
	HAMMER = 2,
	GIANT_HAMMER = 3,
	MAGIC_WAND = 4,
	RITUAL_SWORD = 5,
	ELUCIDATOR_DARK_REPULSER = 6
};

// Enumeration for armor indices to identify different types of armors.
enum ARMOR_IDX
{
	ARMOR_NONE = 0,
	WOODEN_SHIELD = 1,
	PLATE_ARMOR = 2,
	LEATHER_ARMOR = 3,
	ROBE = 4,
	LAUREL_WREATH = 5
};

// Enumeration for accessory indices to identify different types of accessories.
enum ACCESSORY_IDX
{
	ACCESSORY_NONE = 0,
	HOLY_GRAIL = 1,
	SHOES = 2,
	BRACELET = 3
};

// Enumeration for skill indices to identify different types of skills.
enum SKILL_IDX
{
	ATTACK = 0,
	FLEE = 1,
	PROVOKE = 2,
	SHOCK_BLAST = 3,
	HEAL = 4,
	SPEEDUP = 5,
	RUN = 6,
	HAMMER_SPLASH = 7,
	DESTROY = 8,
	FORTIFY = 9,
	STARBURST_STREAM = 10
};

// Enumeration for skill types to identify whether the skill is attack or special.
enum SKILLTYPE
{
	ATK = 1,
	SP = 2
};

// Structure to define a skill.
struct skill
{
	int skillIdx;   //skill idx
	int type;		//sp,atk
	string name;	//skill name
	bool isPassive; //T passive  F active
	int diceNum;	//number of dice 
	int cd;			//cool down time
};

// Class to manage character equipment and their attributes.
class Equipment
{
private:
	int weapon = WEAPON_IDX::WEAPON_NONE;
	int armor = ARMOR_IDX::ARMOR_NONE;
	int accessory = ACCESSORY_IDX::ACCESSORY_NONE;

	int eVitality = 0;
	int eFocus = 0;
	int eSpeed = 0;
	int eHitRate = 0;
	int ePAttack = 0;
	int eMAttack = 0;
	int ePDefense = 0;
	int eMDefense = 0;

	double mulVitality = 1;
	double mulFocus = 1;
	double mulSpeed = 1;
	double mulHitRate = 1;
	double mulPAttack = 1;
	double mulMAttack = 1;
	double mulPDefense = 1;
	double mulMDefense = 1;

	int maxVitality = 100;
	int maxFocus = 3;
	int maxSpeed = 100;
	int maxHitRate = 100;
	int maxPAttack = 100;
	int maxMAttack = 100;
	int maxPDefense = 100;
	int maxMDefense = 100;

	vector<skill> skills = { {SKILL_IDX::ATTACK, SKILLTYPE::ATK, "ATTACK", false, 1, 0},
						 {SKILL_IDX::FLEE, SKILLTYPE::SP, "FLEE", false, 1, 0},
						 {SKILL_IDX::PROVOKE, SKILLTYPE::SP, "PROVOKE", false, 1, 2},
						 {SKILL_IDX::SHOCK_BLAST, SKILLTYPE::ATK, "SHOCK_BLAST", false, 3, 1},
						 {SKILL_IDX::HEAL, SKILLTYPE::SP, "HEAL", false, 2, 1},
						 {SKILL_IDX::SPEEDUP, SKILLTYPE::SP, "SPEEDUP", false, 2, 3},
						 {SKILL_IDX::RUN, SKILLTYPE::SP, "RUN", true, 0, 0},
						 {SKILL_IDX::HAMMER_SPLASH, SKILLTYPE::ATK, "HAMMER_SPLASH", true, 0, 0},
						 {SKILL_IDX::DESTROY, SKILLTYPE::SP, "DESTROY", true, 0, 0},
						 {SKILL_IDX::FORTIFY, SKILLTYPE::SP, "FORTIFY", true, 0, 5},
						 {SKILL_IDX::STARBURST_STREAM, SKILLTYPE::ATK, "STARBURST_STREAM", false, 16, 10} };

	int diceNum;	//number of dice 
	int cd;			//cool down time

	vector<skill> weaponSkills;
	vector<skill> armorSkills;
	vector<skill> accessorySkills;

public:
	// Intent: Sets the weapon index to the given value.
	// Pre: None.
	// Post: The weapon index is updated to the specified value.
	void setWeapon(int idx);

	// Intent: Sets the armor index to the given value.
	// Pre: None.
	// Post: The armor index is updated to the specified value.
	void setArmor(int idx);

	// Intent: Sets the accessory index to the given value.
	// Pre: None.
	// Post: The accessory index is updated to the specified value.
	void setAccessory(int idx);

	// Intent: Recalculates and updates all equipment attributes.
	// Pre: Weapon, armor, and accessory indices are set.
	// Post: Equipment attributes and multipliers are updated accordingly.
	void updateEquipment();


	// Intent: Returns the currently equipped weapon index.
	// Pre: None.
	// Post: The current weapon index is returned.
	int getWeapon() const;

	// Intent: Returns the currently equipped armor index.
	// Pre: None.
	// Post: The current armor index is returned.
	int getArmor() const;

	// Intent: Returns the currently equipped accessory index.
	// Pre: None.
	// Post: The current accessory index is returned.
	int getAccessory() const;


	// Intent: Calculates and returns the adjusted vitality.
	// Pre: Base vitality value is provided.
	// Post: The adjusted vitality is returned, capped at maxVitality.
	int getVitality(int vitality) const;

	// Intent: Returns the maximum focus value.
	// Pre: Base focus value is provided.
	// Post: The maximum focus value is returned.
	int getFocus(int Focus) const;

	// Intent: Returns the maximum focus value.
	// Pre: Base focus value is provided.
	// Post: The maximum focus value is returned.
	int getMaxFocus(int Focus) const;

	// Intent: Calculates and returns the adjusted speed.
	// Pre: Base speed value is provided.
	// Post: The adjusted speed is returned, capped at maxSpeed.
	int getSpeed(int Speed) const;

	// Intent: Calculates and returns the adjusted hit rate.
	// Pre: Base hit rate value is provided.
	// Post: The adjusted hit rate is returned, capped at maxHitRate.
	int getHitRate(int HitRate) const;

	// Intent: Calculates and returns the adjusted physical attack.
	// Pre: Base physical attack value is provided.
	// Post: The adjusted physical attack is returned, capped at maxPAttack.
	int getPAttack(int PAttack) const;

	// Intent: Calculates and returns the adjusted magic attack.
	// Pre: Base magic attack value is provided.
	// Post: The adjusted magic attack is returned, capped at maxMAttack.
	int getMAttack(int MAttack) const;

	// Intent: Calculates and returns the adjusted physical defense.
	// Pre: Base physical defense value is provided.
	// Post: The adjusted physical defense is returned, capped at maxPDefense.
	int getPDefense(int PDefense) const;

	// Intent: Calculates and returns the adjusted magic defense.
	// Pre: Base magic defense value is provided.
	// Post: The adjusted magic defense is returned, capped at maxMDefense.
	int getMDefense(int MDefense) const;


	// Intent:
	// Pre:
	// Post:
	skill getSkill(int idx) const;

	// Intent: Returns a list of active skills based on equipped items.
	// Pre: None.
	// Post: The vector of active skills is returned.
	vector<skill> getSkills();

	// Intent: Returns a list of passive skills based on equipped items.
	// Pre: None.
	// Post: The vector of passive skills is returned.
	vector<skill> getPassiveSkills();
};