#ifndef _LIST_H_
#define _LIST_H_


#include <map>
#include <string>
#include "Buff.h"
#include "Equipment.h"

extern std::map<int, std::string> weaponName;
extern std::map<int, std::string> armorName;
extern std::map<int, std::string> accessoryName;
extern std::map<int, std::string> skillName;
extern std::map<int, std::string> buffName;

std::string getWeaponName(int idx);
std::string getArmorName(int idx);
std::string getAccessoryName(int idx);
std::string getSkillName(int idx);
std::string getBuffName(int idx);

#endif // _LIST_H_