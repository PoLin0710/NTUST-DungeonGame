#pragma once
#include<vector>
#include<string>
using namespace std;

enum WEAPON_IDX
{
	WEAPON_NONE = 0,
	WOODEN_SWORD = 1,
	HAMMER = 2,
	GIANT_HAMMER = 3,
	MAGIC_WAND = 4,
	RITUAL_SWORD = 5
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

enum skillType
{
	atk = 1,
	sp = 2
};

struct skill
{
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
	vector<skill> skills;

public:

	void setWeapon(int);
	void setArmor(int);
	void setAccessory(int);

	int getWeapon() const;
	int getArmor() const;
	int getAccessory() const;

	int getVitality(int vitality) const;
	int getFocus(int Focus) const;
	int getSpeed(int Speed) const;
	int getHitRate(int HitRate) const;
	int getPAttack(int PAttack) const;
	int getMAttack(int MAttack) const;
	int getPDefense(int PDefense) const;
	int getMDefense(int MDefense) const;

	vector<struct skill> getSkills();
	int useSkill(double rate, int index);
};