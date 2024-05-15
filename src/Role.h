#ifndef _ROLE_H_
#define _ROLE_H_

#include "Entity.h"

struct Bag {
	int type;
	int index;
};

enum BAG_TYPE {
	ITEM = 0,
	EQUIPMENT = 1
};

enum METHOD {
	UNWEAR_WEAPON = 0,
	UNWEAR_ARMOR = 1,
	UNWEAR_ACCESSORY = 2
};

class Role :public Entity
{
public:
	Role(string, char);
	~Role();

	void useItem(int, int);
	void wearEquipment(int, int);
	void unWearEquipment(int);
	void addMoney(int);
	void costMoney(int);
	int& getMoney();
	void printBag();
	void insertBag(vector<int>);
	vector<Bag> getBag();

private:
	static int money;
	static vector<Bag> bag;
};



#endif // _ROLE_H_