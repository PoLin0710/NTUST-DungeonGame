#pragma once
#include <vector>
#include <string>
#include <conio.h>	
#include <iomanip>
#include "Position.h"
#include "IO.h"
using namespace std;

struct item
{
	string name;
	int price;
	string introduction;
};

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

class Shop
{
private:
	char icon = '$';
	Position pos;
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

	Shop() : pos(Position(0, 0)) {}

	Shop(int x, int y) : pos(Position(x, y)) {}

	Shop(Position pos) :pos(pos) {}

	char getIcon();

	item getItem(int idx);

	vector<int> intoShop(int& money);

	void showShopInfo(int idx, int& money);

};