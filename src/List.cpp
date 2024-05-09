#include "List.h"

std::map<int, std::string> weaponName = {
	{WEAPON_IDX::WEAPON_NONE, "NONE"},
	{WEAPON_IDX::WOODEN_SWORD, "WOODEN_SWORD"},
	{WEAPON_IDX::HAMMER, "HAMMER"},
	{WEAPON_IDX::GIANT_HAMMER, "GIANT_HAMMER"},
	{WEAPON_IDX::MAGIC_WAND, "MAGIC_WAND"},
	{WEAPON_IDX::RITUAL_SWORD, "RITUAL_SWORD"}
};

std::map<int, std::string> armorName = {
	{ARMOR_IDX::ARMOR_NONE, "NONE"},
	{ARMOR_IDX::WOODEN_SHIELD, "WOODEN_SHIELD"},
	{ARMOR_IDX::PLATE_ARMOR, "PLATE_ARMOR"},
	{ARMOR_IDX::LEATHER_ARMOR, "LEATHER_ARMOR"},
	{ARMOR_IDX::ROBE, "ROBE"},
	{ARMOR_IDX::LAUREL_WREATH, "LAUREL_WREATH"}
};

std::map<int, std::string> accessoryName = {
	{ACCESSORY_IDX::ACCESSORY_NONE, "NONE"},
	{ACCESSORY_IDX::HOLY_GRAIL, "HOLY_GRAIL"},
	{ACCESSORY_IDX::SHOES, "SHOES"},
	{ACCESSORY_IDX::BRACELET, "BRACELET"}
};

std::map<int, std::string> skillName = {
	{SKILL_IDX::ATTACK, "ATTACK"},
	{SKILL_IDX::FLEE, "FLEE"},
	{SKILL_IDX::PROVOKE, "PROVOKE"},
	{SKILL_IDX::SHOCK_BLAST, "SHOCK_BLAST"},
	{SKILL_IDX::HEAL, "HEAL"},
	{SKILL_IDX::SPEEDUP, "SPEEDUP"},
	{SKILL_IDX::RUN, "RUN"},
	{SKILL_IDX::HAMMER_SPLASH, "HAMMER_SPLASH"},
	{SKILL_IDX::DESTROY, "DESTROY"},
	{SKILL_IDX::FORTIFY, "FORTIFY"},
	{SKILL_IDX::STARBURST_STREAM, "STARBURST_STREAM"}
};

std::map<int, std::string> buffName = {
	{Buff::BUFF_IDX::BANGRY, "ANGRY"},
	{Buff::BUFF_IDX::BDIZZINESS, "DIZZINESS"},
	{Buff::BUFF_IDX::BPOISONED, "POISONED"},
	{Buff::BUFF_IDX::BSPEEDUP, "SPEEDUP"}
};

std::map<int, string> ItemName = {
	{ITEM_IDX::IWOODEN_SWORD, "WOODEN_SWORD"},
		{ITEM_IDX::IHAMMER, "HAMMER"},
		{ITEM_IDX::IGIANT_HAMMER, "GIANT_HAMMER"},
		{ITEM_IDX::IMAGIC_WAND, "MAGIC_WAND"},
		{ITEM_IDX::IRITUAL_SWORD, "RITUAL_SWORD"},
		{ITEM_IDX::IWOODEN_SHIELD, "WOODEN_SHIELD"},
		{ITEM_IDX::IPLATE_ARMOR, "PLATE_ARMOR"},
		{ITEM_IDX::ILEATHER_ARMOR, "LEATHER_ARMOR"},
		{ITEM_IDX::IROBE, "ROBE"},
		{ITEM_IDX::ILAUREL_WREATH, "LAUREL_WREATH"},
		{ITEM_IDX::IHOLY_GRAIL, "HOLY_GRAIL"},
		{ITEM_IDX::ISHOES, "SHOES"},
		{ITEM_IDX::IBRACELET, "BRACELET"},
		{ITEM_IDX::IGODSBEARD, "GODSBEARD"},
		{ITEM_IDX::IGOLDEN_ROOT, "GOLDEN_ROOT"},
		{ITEM_IDX::ITELEPORT_SCROLL, "TELEPORT_SCROLL"},
		{ITEM_IDX::ITENT, "TENT"}
};

std::string getWeaponName(int idx)
{
	if (weaponName.find(idx) != weaponName.end())
	{
		return weaponName[idx];
	}
	return "UNKNOWN_WEAPON";
}

std::string getArmorName(int idx)
{
	if (armorName.find(idx) != armorName.end())
	{
		return armorName[idx];
	}
	return "UNKNOWN_ARMOR";
}

std::string getAccessoryName(int idx)
{
	if (accessoryName.find(idx) != accessoryName.end())
	{
		return accessoryName[idx];
	}
	return "UNKNOWN_ACCESSORY";
}

std::string getSkillName(int idx)
{
	if (skillName.find(idx) != skillName.end())
	{
		return skillName[idx];
	}
	return "UNKNOWN_SKILL";
}

std::string getBuffName(int idx)
{
	if (buffName.find(idx) != buffName.end())
	{
		return buffName[idx];
	}
	return "UNKNOWN_BUFF";
}

std::string getItemName(int idx)
{
	if (ItemName.find(idx) != ItemName.end())
	{
		return ItemName[idx];
	}

	return "UNKNOWN_ITEM";
}
