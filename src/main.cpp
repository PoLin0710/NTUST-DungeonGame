#include <iostream>
#include "Shop.h"

using namespace std;

int main()
{
	Shop shop;
	vector<int> v = shop.intoShop(1000);
	for (auto i : v)
	{
		cout << shop.getItem(i).name << "\n";
	}
}
