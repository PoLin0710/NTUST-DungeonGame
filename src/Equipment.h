#include <string>
#include <vector>
#ifndef _EQUIPMENT_H_
#define _EQUIPMENT_H_

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

enum SKILLTYPE
{
	ATK = 1,
	SP = 2
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

struct skill
{
	int type;
	int skillIDX;
	std::string name;
	bool isPassive;
	int diceNum;
	int cd;
};

class Equipment
{
	int vitality;
	int focus;
	int speed;
	int hitRate;
	int pAttack;
	int mAttack;
	int pDefense;
	int mDefense;

	double mulVitality;
	double mulFocus;
	double mulSpeed;
	double mulhitRate;
	double mulPAttack;
	double mulMAttack;
	double mulPDefense;
	double mulMDefense;

	int weapon = WEAPON_IDX::WEAPON_NONE;
	int armor = ARMOR_IDX::ARMOR_NONE;
	int accessory = ACCESSORY_IDX::ACCESSORY_NONE;

	std::vector<skill> skills;

public:
	int getVitality(int param) const {
		return param;
	}

	int getFocus(int param) const {
		return param;
	}

	int getSpeed(int param) const {
		return param;
	}

	int getHitRate(int param) const {
		return param;
	}

	int getPAttack(int param) const {
		return param;
	}

	int getMAttack(int param) const {
		return param;
	}

	int getPDefense(int param) const {
		return param;
	}

	int getMDefense(int param) const {
		return param;
	}

	std::vector<skill> getSkills()
	{
		std::vector<skill> ans;
		ans.push_back({ SKILLTYPE::ATK,0, "ATTACK", false, 1, 0 });
		ans.push_back({ SKILLTYPE::SP,4, "HEAL", false, 2, 1 });
		ans.push_back({ SKILLTYPE::SP, 1,"FLEE", false, 1, 0 });
		return ans;
	}
	int useSkill(double rate, int i) {
		return 10;
	}

	void setWeapon(int weapon)
	{
		this->weapon = weapon;
	}
	void setArmor(int armor) {
		this->armor = armor;
	}

	void setAccessory(int accessory) {
		this->accessory = accessory;
	}

	int getWeapon() const
	{
		return this->weapon;
	}

	int getArmor() const
	{
		return this->armor;
	}

	int getAccessory() const
	{
		return this->accessory;
	}
};

#endif //_EQUIPMENT_H_
