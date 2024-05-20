/***********************************************************************
 * File: Role.cpp
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
 * Description: Implementation file for the Role class, which represents a character in the game.
***********************************************************************/
#include "Role.h"

//init money
int Role::money = 600;

//Declare Role Bag
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

/**
 * Intent : Initializes a new role with the given name and icon, and randomly assigns starting equipment.
 * Pre : None.
 * Post : The role is created with the specified name, icon, and starting equipment.
 * \param name The name of the role.
 * \param icon The icon representing the role.
 */
Role::Role(string name, char icon) :Entity(name, ENTITY_TYPE::ROLE, icon)
{
	//Random set Equipment
	this->setWeapon(rand() % WEAPON_IDX::ELUCIDATOR_DARK_REPULSER + 1);
	this->setArmor(rand() % ARMOR_IDX::LAUREL_WREATH + 1);
	this->setAccessory(rand() % ACCESSORY_IDX::BRACELET + 1);

	//upload attribute(state)
	update();
}

// Destructor
Role::~Role()
{
}

/**
 * Uses the specified item from the bag.
 *
 * @param itemIdx The index of the item to use.
 * @param bagIdx The index of the item in the bag.
 * Intent : Uses the item with the given index from the bag and updates the role's state accordingly.
 * Pre : The itemIdx and bagIdx parameters must be valid indices.
 * Post : If the item is usable, its effects are applied to the role, and the item is removed from the bag.
 */
void Role::useItem(int itemIdx, int bagIdx)
{
	//Declare
	bool useState = false;

	//Check Item
	if (itemIdx == ITEM_IDX::IGODSBEARD)
	{
		// Heal
		int nowHP = getVitality();
		this->setVitality(nowHP + 25);
		useState = true;
	}
	else if (itemIdx == ITEM_IDX::IGOLDEN_ROOT)
	{
		// Foucs
		int nowFocus = getFocus();
		this->setFocus(nowFocus + 3);
		useState = true;
	}
	else if (itemIdx == ITEM_IDX::ITELEPORT_SCROLL)
	{
		useState = true;
	}
	else if (itemIdx == ITEM_IDX::ITENT)
	{
		useState = true;
	}

	//Delete Bag Item
	if (useState)
	{
		bag.erase(bag.begin() + bagIdx);
	}
}

/**
 * Equips the specified equipment from the bag.
 *
 * @param equipmentIdx The index of the equipment to equip.
 * @param bagIdx The index of the equipment in the bag.
 * Intent : Equips the equipment with the given index from the bag and updates the role's state accordingly.
 * Pre : The equipmentIdx and bagIdx parameters must be valid indices.
 * Post : If the equipment is equippable, it is equipped, and the previous equipment (if any) is moved back to the bag.
 */
void Role::wearEquipment(int equipmentIdx, int bagIdx)
{
	//Declare
	int weapon, armor, accessory;

	//Choose equipment type
	switch (equipmentIdx)
	{
		// Weapon
	case ITEM_IDX::IWOODEN_SWORD:
	case ITEM_IDX::IHAMMER:
	case ITEM_IDX::IGIANT_HAMMER:
	case ITEM_IDX::IMAGIC_WAND:
	case ITEM_IDX::IRITUAL_SWORD:
	case ITEM_IDX::IElucidator_Dark_Repulser:

		//Get now weapon
		weapon = this->getWeapon();

		//If didnt none
		if (weapon != WEAPON_IDX::WEAPON_NONE)
		{
			//erase item
			bag.erase(bag.begin() + bagIdx);

			//push bag
			if (weapon != WEAPON_IDX::ELUCIDATOR_DARK_REPULSER)
			{
				bag.push_back({ BAG_TYPE::EQUIPMENT ,weapon - 1 });
			}
			else
			{
				bag.push_back({ BAG_TYPE::EQUIPMENT ,ITEM_IDX::IElucidator_Dark_Repulser });
			}

			//set weapon
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

		//Get now Armor
		armor = this->getArmor();

		//If didnt none
		if (armor != ARMOR_IDX::ARMOR_NONE)
		{
			//erase item
			bag.erase(bag.begin() + bagIdx);

			//push bag
			bag.push_back({ BAG_TYPE::EQUIPMENT ,armor + 4 });
		}

		//set Armor
		this->setArmor(equipmentIdx - 4);
		break;

		// Accessory
	case ITEM_IDX::IHOLY_GRAIL:
	case ITEM_IDX::ISHOES:
	case ITEM_IDX::IBRACELET:

		//Get now Acceessory
		accessory = this->getAccessory();

		//if None
		if (accessory != ACCESSORY_IDX::ACCESSORY_NONE)
		{
			//erase bag
			bag.erase(bag.begin() + bagIdx);

			//push bag
			bag.push_back({ BAG_TYPE::EQUIPMENT ,accessory + 9 });
		}

		//set Accessory
		this->setAccessory(equipmentIdx - 9);
		break;

	default:
		break;
	}

	update();
}

/**
 * Removes the equipped equipment based on the specified method.
 *
 * @param method The method of removing equipment.
 * Intent : Removes the equipped equipment based on the specified method and moves it back to the bag.
 * Pre : The method parameter must be a valid method for removing equipment.
 * Post : If equipment is removed successfully, it is moved back to the bag and the corresponding slot is set to empty.
 */
void Role::unWearEquipment(int method)
{
	//Declare
	int weapon, armor, accessory;

	//Choose unwear
	switch (method)
	{
	case METHOD::UNWEAR_WEAPON: //Weapon
		//Get
		weapon = this->getWeapon();

		//Detect is exist
		if (weapon != WEAPON_IDX::WEAPON_NONE)
		{
			//push bag
			bag.push_back({ BAG_TYPE::EQUIPMENT ,weapon - 1 });
		}

		//Set none
		this->setWeapon(WEAPON_IDX::WEAPON_NONE);

		break;

	case METHOD::UNWEAR_ARMOR: //Armor
		//Get
		armor = this->getArmor();

		//Detect is exist
		if (armor != ARMOR_IDX::ARMOR_NONE)
		{
			//push bag
			bag.push_back({ BAG_TYPE::EQUIPMENT ,armor + 4 });
		}

		//set none
		this->setArmor(ARMOR_IDX::ARMOR_NONE);

		break;

	case METHOD::UNWEAR_ACCESSORY: //Accessory
		//Get
		accessory = this->getAccessory();

		//Detect is exist
		if (accessory != ACCESSORY_IDX::ACCESSORY_NONE)
		{
			//push bag
			bag.push_back({ BAG_TYPE::EQUIPMENT ,accessory + 9 });
		}

		//set none
		this->setAccessory(ACCESSORY_IDX::ACCESSORY_NONE);

		break;
	default:
		break;
	}

	//update attribute
	update();
}

/**
 * Adds the specified amount of money to the role's money.
 *
 * @param amount The amount of money to add.
 * Intent : Adds the specified amount of money to the role's money.
 * Pre : None.
 * Post : The specified amount of money is added to the role's money.
 */
void Role::addMoney(int amount)
{
	money += amount;
}

/**
 * Subtracts the specified amount of money from the role's money.
 *
 * @param amount The amount of money to subtract.
 * Intent : Subtracts the specified amount of money from the role's money.
 * Pre : The role must have sufficient money to subtract the specified amount.
 * Post : The specified amount of money is subtracted from the role's money.
 */
void Role::costMoney(int amount)
{
	money -= amount;
}

/**
 * Returns a reference to the role's money.
 *
 * @return A reference to the role's money.
 * Intent : Returns a reference to the role's money.
 * Pre : None.
 * Post : A reference to the role's money is returned.
 */
int& Role::getMoney()
{
	return money;
}

/**
 * Prints the contents of the role's bag.
 *
 * Intent : Prints the contents of the role's bag.
 * Pre : None.
 * Post : The contents of the role's bag are printed.
 */

void Role::printBag()
{
	//Output
	std::cout << "BAG : ";

	for (auto i : bag)
	{
		std::cout << getItemName(i.index) << " ";
	}

	std::cout << std::endl;
}

/**
 * Inserts items into the role's bag.
 *
 * Intent : Inserts items into the role's bag.
 * Pre : None.
 * Post : Items are inserted into the role's bag.
 * \param item A vector containing the indices of the items to be inserted.
 */
void Role::insertBag(vector<int> item)
{
	for (auto i : item)
	{
		if (i < 13 || i == 17) //equipment
		{
			bag.push_back({ BAG_TYPE::EQUIPMENT,i });
		}
		else // Item
		{
			bag.push_back({ BAG_TYPE::ITEM,i });
		}
	}
}

/**
 * Retrieves the role's bag.
 *
 * Intent : Retrieves the role's bag.
 * Pre : None.
 * Post : The role's bag is returned.
 * \return A vector containing the contents of the role's bag.
 */
vector<Bag> Role::getBag() {
	return bag;
}
