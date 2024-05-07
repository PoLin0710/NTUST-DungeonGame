#pragma once
#include <vector>
#include <string>
using namespace std;

struct item
{
	string name;
	int price;
	string introduction;
};

enum ITEM_IDX
{
    WOODEN_SWORD = 0,
    HAMMER = 1,
    GIANT_HAMMER = 2,
    MAGIC_WAND = 3,
    RITUAL_SWORD = 4,
    WOODEN_SHIELD = 5,
    PLATE_ARMOR = 6,
    LEATHER_ARMOR = 7,
    ROBE = 8,
    LAUREL_WREATH = 9,
    HOLY_GRAIL = 10,
    SHOES = 11,
    BRACELET = 12,
    GODSBEARD = 13,
    GOLDEN_ROOT = 14,
    TELEPORT_SCROLL = 15,
    TENT = 16
};

class Shop
{
private:
	char icon = '$';
	vector<item> items;

public:

	vector<int> intoShop(int money)
	{
		vector<int> purchaseIdx;
		showShopInfo();
	}

	void showShopInfo()
	{

	}
};