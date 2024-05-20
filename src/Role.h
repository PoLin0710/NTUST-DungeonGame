/***********************************************************************
 * File: Role.h
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
 * Description: Header file for the Role class representing a character in the game.
***********************************************************************/
#ifndef _ROLE_H_
#define _ROLE_H_

#include "Entity.h"

// Define a structure for items in the character's bag
struct Bag {
	int type;   // Type of item (ITEM or EQUIPMENT)
	int index;  // Index of the item
};

// Define enumeration for bag item types
enum BAG_TYPE {
	ITEM = 0,       // Item type
	EQUIPMENT = 1   // Equipment type
};

// Define enumeration for methods related to equipment
enum METHOD {
	UNWEAR_WEAPON = 0,      // Method to unwear weapon
	UNWEAR_ARMOR = 1,       // Method to unwear armor
	UNWEAR_ACCESSORY = 2    // Method to unwear accessory
};

// Role class declaration, inherits from Entity class
class Role :public Entity
{
public:
	//Constructor
	Role(string, char);

	//Desructor
	~Role();

	// Methods for character actions
	void useItem(int, int);	// Use an item from the bag
	void wearEquipment(int, int); // Wear equipment from the bag
	void unWearEquipment(int); // Remove worn equipment
	void addMoney(int); // Add money to character's balance
	void costMoney(int); // Deduct money from character's balance
	int& getMoney(); // Get character's current balance
	void printBag(); // Print contents of character's bag
	void insertBag(vector<int>); // Insert items into character's bag
	vector<Bag> getBag(); //Get Bag

private:
	static int money;  // Static variable to store character's money
	static vector<Bag> bag; // Static vector to represent character's bag
};

#endif // _ROLE_H_