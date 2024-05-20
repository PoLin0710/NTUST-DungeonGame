/***********************************************************************
 * File: List.h
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
 * Description: This header file defines functions to retrieve names associated with various game items,
 *				such as weapons, armor, accessories, skills, buffs, and general items.
***********************************************************************/
#ifndef _LIST_H_
#define _LIST_H_


#include <map>
#include <string>
#include "Buff.h"
#include "Equipment.h"
#include "Shop.h"

// Declare Map for Type index to English Name(string)
extern std::map<int, std::string> weaponName;
extern std::map<int, std::string> armorName;
extern std::map<int, std::string> accessoryName;
extern std::map<int, std::string> skillName;
extern std::map<int, std::string> buffName;
extern std::map<int, std::string> ItemName;

// Declare get Name function
std::string getWeaponName(int idx);
std::string getArmorName(int idx);
std::string getAccessoryName(int idx);
std::string getSkillName(int idx);
std::string getBuffName(int idx);
std::string getItemName(int idx);

#endif // _LIST_H_