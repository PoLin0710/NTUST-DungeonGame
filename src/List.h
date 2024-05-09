#ifndef _LIST_H_
#define _LIST_H_


#include <map>
#include <string>
#include "Buff.h"
#include "Equipment.h"
#include "Item.h"

extern std::map<int, std::string> weaponName;
extern std::map<int, std::string> armorName;
extern std::map<int, std::string> accessoryName;
extern std::map<int, std::string> skillName;
extern std::map<int, std::string> buffName;
extern std::map<int, std::string> ItemName;

std::string getWeaponName(int idx);
std::string getArmorName(int idx);
std::string getAccessoryName(int idx);
std::string getSkillName(int idx);
std::string getBuffName(int idx);
std::string getItemName(int idx);

#endif // _LIST_H_