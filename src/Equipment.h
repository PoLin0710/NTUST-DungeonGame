#pragma once
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

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

enum ARMOR_IDX
{
	ARMOR_NONE = 0,
	WOODEN_SHIELD = 1,
	PLATE_ARMOR = 2,
	LEATHER_ARMOR = 3,
	ROBE = 4,
	LAUREL_WREATH = 5
};

enum ACCESSORY_IDX
{
	ACCESSORY_NONE = 0,
	HOLY_GRAIL = 1,
	SHOES = 2,
	BRACELET = 3
};

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

enum SKILLTYPE
{
	ATK = 1,
	SP = 2
};

struct skill
{
	int skillIdx;   //skill idx
	int type;		//sp,atk
	string name;	//skill name
	bool isPassive; //T passive  F active
	int diceNum;	//number of dice 
	int cd;			//cool down time
};

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

	void setWeapon(int idx);
	void setArmor(int idx);
	void setAccessory(int idx);
	void updateEquipment();

	int getWeapon() const;
	int getArmor() const;
	int getAccessory() const;

	int getVitality(int vitality) const;
	int getFocus(int Focus) const;
	int getMaxFocus(int Focus) const;
	int getSpeed(int Speed) const;
	int getHitRate(int HitRate) const;
	int getPAttack(int PAttack) const;
	int getMAttack(int MAttack) const;
	int getPDefense(int PDefense) const;
	int getMDefense(int MDefense) const;
	skill getSkill(int idx) const;

	vector<skill> getSkills();
	vector<skill> getPassiveSkills();
};