#pragma once

using namespace std;

enum WEAPON_IDX
{
	NONE = 0,
	WOODEN_SWORD = 1,
	HAMMER = 2,
	GIANT_HAMMER = 3,
	MAGIC_WAND = 4,
	RITUAL_SWORD = 5
};

enum ARMOR_IDX
{
	NONE = 0,
	WOODEN_SHIELD = 1,
	PLATE_ARMOR = 2,
	LEATHER_ARMOR = 3,
	ROBE = 4,
	LAUREL_WREATH = 5
};

enum ACCESSORYIDX
{
	NONE = 0,
	HOLY_GRAIL = 1,
	SHOES = 2,
	BRACELET = 3
};

class Equipment
{
	int weapon = WEAPON_IDX::NONE;
	int armor = ARMOR_IDX::NONE;
	int accessory = ACCESSORYIDX::NONE;
	int weaponAtk = 0;
	int armorDef = 0;

};