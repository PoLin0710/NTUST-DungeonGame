/***********************************************************************
 * File: Shop.h
 * Author:
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Create Date: $YEAR-$MONTH_5-$DAY_OF_MONTH_9
 * Editor:
 *        B11215030 SONG,BING-YU (yehyi817@gmail.com)
 *        B11215040 HUANG,PO-LIN (oliver590617@gmail.com)
 *        B11215014 ¤ýà±´¸ (sunnyching901105@gmail.com)
 *        B11215008 ¬x§B¿o (n590762743@gmail.com)
 * Update Date: $YEAR-$MONTH_5-$DAY_OF_MONTH_19
 * Description: Defines the Shop class and its methods for managing shop interactions.
***********************************************************************/

#pragma once
#include <vector>
#include <string>
#include <conio.h>	
#include <iomanip>
#include "Position.h"
#include "IO.h"
using namespace std;

// Structure to define an item with its name, price, and introduction.
struct item
{
	string name;
	int price;
	string introduction;
};

// Enumeration for item indices to identify different items in the shop.
enum ITEM_IDX
{
	IWOODEN_SWORD = 0,
	IHAMMER = 1,
	IGIANT_HAMMER = 2,
	IMAGIC_WAND = 3,
	IRITUAL_SWORD = 4,
	IWOODEN_SHIELD = 5,
	IPLATE_ARMOR = 6,
	ILEATHER_ARMOR = 7,
	IROBE = 8,
	ILAUREL_WREATH = 9,
	IHOLY_GRAIL = 10,
	ISHOES = 11,
	IBRACELET = 12,
	IGODSBEARD = 13,
	IGOLDEN_ROOT = 14,
	ITELEPORT_SCROLL = 15,
	ITENT = 16,
	IElucidator_Dark_Repulser = 17
};

// Class to manage the shop and its interactions with players.
class Shop
{
private:
	char icon = '$';	// Icon representing the shop
	Position pos;		// Position of the shop
	// List of items available in the shop
	vector<item> items = { {"Wooden Sword", 100, "A basic wooden sword."},
						   {"Hammer", 200, "A Standard Hammer for crafting or combat."},
						   {"Giant hammer", 300, "A Larger, More Powerful Hammer."},
						   {"Magic wand", 100, "A Wand Imbued with Magical Abilities."},
						   {"Ritual sword", 200, "A Ceremonial Sword Used in Rituals."},
						   {"Wooden shield", 100, "A Basic Shield Made of Wood."},
						   {"Plate armor", 300, "Heavy Armor Made of Metal Plates."},
						   {"Leather armor", 300, "Armor Made of Leather, Providing Moderate Protection."},
						   {"Robe", 200, "A Robe Worn for Magical or Ceremonial Purposes."},
						   {"Laurel wreath", 200, "A Decorative Wreath Worn as a Symbol of Honor or Victory."},
						   {"Holy grail", 200, "The Legendary Holy Grail, a Powerful Artifact."},
						   {"Shoes", 200, "A Pair of Shoes or Boots for Protection or Mobility."},
						   {"Bracelet", 100, "A Decorative or Enchanted Bracelet Worn for Various Purposes."},
						   {"Godsbeard", 300, "A rare herb with healing properties."},
						   {"Golden root", 500, "A Valuable and Magical Golden Root."},
						   {"Teleport scroll", 500, "A Scroll Used for Teleportation to Specific Locations."},
						   {"Tent", 500, "A Portable Shelter for Resting or Camping."} ,
						   {"Elucidator & Dark_Repulser", 2000, "A pair of swords comprised of the Black Sword and the White Sword. Can use skill Starburst Stream."} };

public:
	// Default constructor initializing shop position to (0,0)
	Shop() : pos(Position(0, 0)) {}

	// Constructor initializing shop position to given coordinates
	Shop(int x, int y) : pos(Position(x, y)) {}

	// Constructor initializing shop position to given Position object
	Shop(Position pos) :pos(pos) {}

	// Intent: Returns the icon of the shop.
	// Pre: None.
	// Post: The shop icon is returned.
	char getIcon();

	// Intent: Returns the item at the specified index.
	// Pre: idx is a valid index within the items vector.
	// Post: The item at the specified index is returned.
	item getItem(int idx);

	// Intent: Handles the shop interaction where the player can purchase items.
	// Pre: money is the amount of money the player has.
	// Post: Returns a vector of indices representing purchased items.
	vector<int> intoShop(int& money);

	// Intent: Displays the shop information including items and prices.
	// Pre: idx is the current selected item index. money is the player's current amount of money.
	// Post: The shop interface is displayed with the current selection and item details.
	void showShopInfo(int idx, int& money);
};