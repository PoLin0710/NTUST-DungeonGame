#include "Role.h"

int Role::money = 600;
std::vector<Bag> Role::bag = {
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::IWOODEN_SWORD},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::IHAMMER},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::IGIANT_HAMMER},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::IMAGIC_WAND},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::IRITUAL_SWORD},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::IWOODEN_SHIELD},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::IPLATE_ARMOR},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::ILEATHER_ARMOR},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::IROBE},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::ILAUREL_WREATH},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::IHOLY_GRAIL},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::ISHOES},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::IBRACELET},
	{BAG_TYPE::ITEM, ITEM_IDX::IGODSBEARD},
	{BAG_TYPE::ITEM, ITEM_IDX::IGOLDEN_ROOT},
	{BAG_TYPE::ITEM, ITEM_IDX::ITELEPORT_SCROLL},
	{BAG_TYPE::ITEM, ITEM_IDX::ITENT},
	{BAG_TYPE::EQUIPMENT, ITEM_IDX::IElucidator_Dark_Repulser}
};

Role::Role(string name, char icon) :Entity(name, ENTITY_TYPE::ROLE, icon)
{
	this->setWeapon(rand() % WEAPON_IDX::ELUCIDATOR_DARK_REPULSER + 1);
	this->setArmor(rand() % ARMOR_IDX::LAUREL_WREATH + 1);
	this->setAccessory(rand() % ACCESSORY_IDX::BRACELET + 1);

	update();
}

Role::~Role()
{
}

void Role::useItem(int itemIdx, int bagIdx)
{
	bool useState = false;

	if (itemIdx == ITEM_IDX::IGODSBEARD)
	{

		int nowHP = getVitality();
		this->setVitality(nowHP + 25);
		useState = true;
	}
	else if (itemIdx == ITEM_IDX::IGOLDEN_ROOT)
	{
		int nowFocus = getFocus();
		this->setFocus(nowFocus + 3);
		useState = true;
	}
	else if (itemIdx == ITEM_IDX::ITELEPORT_SCROLL)
	{
		useState = true;
	}  //­n¥[
	else if (itemIdx == ITEM_IDX::ITENT)
	{
		useState = true;
	}

	if (useState)
	{
		bag.erase(bag.begin() + bagIdx);
	}
}

void Role::wearEquipment(int equipmentIdx, int bagIdx)
{
	int weapon, armor, accessory;

	switch (equipmentIdx)
	{
		// Weapon
	case ITEM_IDX::IWOODEN_SWORD:
	case ITEM_IDX::IHAMMER:
	case ITEM_IDX::IGIANT_HAMMER:
	case ITEM_IDX::IMAGIC_WAND:
	case ITEM_IDX::IRITUAL_SWORD:
	case ITEM_IDX::IElucidator_Dark_Repulser:
		weapon = this->getWeapon();
		if (weapon != WEAPON_IDX::WEAPON_NONE)
		{
			bag.erase(bag.begin() + bagIdx);

			if (weapon != WEAPON_IDX::ELUCIDATOR_DARK_REPULSER)
			{
				bag.push_back({ BAG_TYPE::EQUIPMENT ,weapon - 1 });
			}
			else
			{
				bag.push_back({ BAG_TYPE::EQUIPMENT ,ITEM_IDX::IElucidator_Dark_Repulser });
			}

			if (equipmentIdx != ITEM_IDX::IElucidator_Dark_Repulser)
			{
				this->setWeapon(equipmentIdx + 1);
			}
			else
			{
				this->setWeapon(WEAPON_IDX::ELUCIDATOR_DARK_REPULSER);
			}
		}

		break;
		// Armor
	case ITEM_IDX::IWOODEN_SHIELD:
	case ITEM_IDX::IPLATE_ARMOR:
	case ITEM_IDX::ILEATHER_ARMOR:
	case ITEM_IDX::IROBE:
	case ITEM_IDX::ILAUREL_WREATH:
		armor = this->getArmor();
		if (armor != ARMOR_IDX::ARMOR_NONE)
		{
			bag.erase(bag.begin() + bagIdx);
			bag.push_back({ BAG_TYPE::EQUIPMENT ,armor + 4 });
		}
		this->setArmor(equipmentIdx - 4);
		break;
		// Accessory
	case ITEM_IDX::IHOLY_GRAIL:
	case ITEM_IDX::ISHOES:
	case ITEM_IDX::IBRACELET:
		accessory = this->getAccessory();
		if (accessory != ACCESSORY_IDX::ACCESSORY_NONE)
		{
			bag.erase(bag.begin() + bagIdx);
			bag.push_back({ BAG_TYPE::EQUIPMENT ,accessory + 9 });
		}
		this->setAccessory(equipmentIdx - 9);
		break;
	default:
		break;
	}

	update();
}

void Role::unWearEquipment(int method)
{
	int weapon, armor, accessory;
	switch (method)
	{
	case METHOD::UNWEAR_WEAPON:
		weapon = this->getWeapon();
		if (weapon != WEAPON_IDX::WEAPON_NONE)
		{
			bag.push_back({ BAG_TYPE::EQUIPMENT ,weapon - 1 });
		}
		this->setWeapon(WEAPON_IDX::WEAPON_NONE);
		break;
	case METHOD::UNWEAR_ARMOR:
		armor = this->getArmor();
		if (armor != ARMOR_IDX::ARMOR_NONE)
		{
			bag.push_back({ BAG_TYPE::EQUIPMENT ,armor + 4 });
		}
		this->setArmor(ARMOR_IDX::ARMOR_NONE);
		break;
	case METHOD::UNWEAR_ACCESSORY:
		accessory = this->getAccessory();
		if (accessory != ACCESSORY_IDX::ACCESSORY_NONE)
		{
			bag.push_back({ BAG_TYPE::EQUIPMENT ,accessory + 9 });
		}
		this->setAccessory(ACCESSORY_IDX::ACCESSORY_NONE);
		break;
	default:
		break;
	}

	update();
}

void Role::addMoney(int amount)
{
	money += amount;
}

void Role::costMoney(int amount)
{
	money -= amount;
}

int& Role::getMoney()
{
	return money;
}

void Role::printBag()
{
	std::cout << "BAG : ";
	for (auto i : bag)
	{
		std::cout << getItemName(i.index) << " ";
	}
	std::cout << std::endl;
}

void Role::insertBag(vector<int> item)
{
	for (auto i : item)
	{
		if (i < 13 || i == 17) //equipment
		{
			bag.push_back({ BAG_TYPE::EQUIPMENT,i });
		}
		else
		{
			bag.push_back({ BAG_TYPE::ITEM,i });
		}
	}
}

vector<Bag> Role::getBag() {
	return bag;
}
