/***********************************************************************
 * File: List.cpp
 * Author:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Create Date: 2024-05-20
 * Editor:
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Update Date: 2024-05-20
 * Description: This file implements functions to retrieve names associated with various game items,
 *				such as weapons, armor, accessories, skills, buffs, and general items.
***********************************************************************/
#include "List.h"


// ==========================Initialize maps storing item names==========================
std::map<int, std::string> weaponName = {
	{WEAPON_IDX::WEAPON_NONE, "NONE"},
	{WEAPON_IDX::WOODEN_SWORD, "WOODEN_SWORD"},
	{WEAPON_IDX::HAMMER, "HAMMER"},
	{WEAPON_IDX::GIANT_HAMMER, "GIANT_HAMMER"},
	{WEAPON_IDX::MAGIC_WAND, "MAGIC_WAND"},
	{WEAPON_IDX::RITUAL_SWORD, "RITUAL_SWORD"},
	{WEAPON_IDX::ELUCIDATOR_DARK_REPULSER,"ELUCIDATOR_REPULSER"}
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
		{ITEM_IDX::ITENT, "TENT"},
		{ITEM_IDX::IElucidator_Dark_Repulser, "ELUCIDATOR_REPULSER"}
};

// ======================================END======================================

/**
 * Intent: Retrieve the name of a weapon based on its index.
 * Pre: The weapon index must be valid.
 * Post: Returns the name of the weapon if found; otherwise, returns "UNKNOWN_WEAPON".
 * \param idx The index of the weapon.
 * \return The name of the weapon corresponding to the provided index.
 */
std::string getWeaponName(int idx)
{
	//Find
	if (weaponName.find(idx) != weaponName.end())
	{
		return weaponName[idx];
	}

	return "UNKNOWN_WEAPON";
}

/**
 * Intent: Retrieve the name of an armor based on its index.
 * Pre: The armor index must be valid.
 * Post: Returns the name of the armor if found; otherwise, returns "UNKNOWN_ARMOR".
 * \param idx The index of the armor.
 * \return The name of the armor corresponding to the provided index.
 */
std::string getArmorName(int idx)
{
	//Find
	if (armorName.find(idx) != armorName.end())
	{
		return armorName[idx];
	}

	return "UNKNOWN_ARMOR";
}

/**
 * Intent: Retrieve the name of an accessory based on its index.
 * Pre: The accessory index must be valid.
 * Post: Returns the name of the accessory if found; otherwise, returns "UNKNOWN_ACCESSORY".
 * \param idx The index of the accessory.
 * \return The name of the accessory corresponding to the provided index.
 */
std::string getAccessoryName(int idx)
{
	//Find
	if (accessoryName.find(idx) != accessoryName.end())
	{
		return accessoryName[idx];
	}

	return "UNKNOWN_ACCESSORY";
}

/**
 * Intent: Retrieve the name of a skill based on its index.
 * Pre: The skill index must be valid.
 * Post: Returns the name of the skill if found; otherwise, returns "UNKNOWN_SKILL".
 * \param idx The index of the skill.
 * \return The name of the skill corresponding to the provided index.
 */
std::string getSkillName(int idx)
{
	//Find
	if (skillName.find(idx) != skillName.end())
	{
		return skillName[idx];
	}

	return "UNKNOWN_SKILL";
}

/**
 * Intent: Retrieve the name of a buff based on its index.
 * Pre: The buff index must be valid.
 * Post: Returns the name of the buff if found; otherwise, returns "UNKNOWN_BUFF".
 * \param idx The index of the buff.
 * \return The name of the buff corresponding to the provided index.
 */
std::string getBuffName(int idx)
{
	//Find
	if (buffName.find(idx) != buffName.end())
	{
		return buffName[idx];
	}

	return "UNKNOWN_BUFF";
}

/**
 * Intent: Retrieve the name of an item based on its index.
 * Pre: The item index must be valid.
 * Post: Returns the name of the item if found; otherwise, returns "UNKNOWN_ITEM".
 * \param idx The index of the item.
 * \return The name of the item corresponding to the provided index.
 */
std::string getItemName(int idx)
{
	//Find
	if (ItemName.find(idx) != ItemName.end())
	{
		return ItemName[idx];
	}

	return "UNKNOWN_ITEM";
}
