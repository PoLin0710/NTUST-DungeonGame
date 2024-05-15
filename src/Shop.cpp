#include "Shop.h"

item Shop::getItem(int idx)
{
	return items[idx];
}

char Shop::getIcon()
{
	return icon;
}

vector<int> Shop::intoShop(int& money)
{
	vector<int> purchaseIdx;
	int idx = 0;

	while (true)
	{
		showShopInfo(idx, money);
		char input = _getch();

		if (input == 'W' || input == 'w')
		{
			if (idx <= 0) {
				idx = 17;
			}
			else {
				idx--;
			}
		}

		if (input == 'S' || input == 's')
		{
			if (idx >= 17) {
				idx = 0;
			}
			else {
				idx++;
			}
		}

		if (input == '\r')
		{
			if (money >= items[idx].price)
			{
				purchaseIdx.push_back(idx);
				money -= items[idx].price;
			}
		}

		if (input == 27)
		{
			system("CLS");
			return purchaseIdx;
		}
	}
}

void Shop::showShopInfo(int idx, int& money)
{
	system("CLS");
	static int upIdx = 0, downIdx = 9;

	if (upIdx > idx)
	{
		upIdx = idx;
		downIdx = idx + 9;
	}

	if (downIdx < idx)
	{
		downIdx = idx;
		upIdx = idx - 9;
	}
	cout << "Money : " << money << "\n";
	cout << "         Item                                                          Price\n";

	for (int i = upIdx; i <= downIdx; i++)
	{
		SetColor(7);
		cout << setw(5) << ((i == idx) ? "-> " : "  ") << setw(30) << left << items[i].name;

		if (items[i].price > money)
		{
			SetColor(12);
		}
		cout << setw(40) << right << items[i].price << "$\n";

		SetColor(7);
	}

	cout << "\n\n";
	cout << items[idx].introduction;
}