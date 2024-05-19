/***********************************************************************
 * File: Shop.cpp
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
 * Description: Implements the methods defined in the Shop class for managing shop interactions.
***********************************************************************/
#include "Shop.h"

// Intent: Returns the item at the specified index.
// Pre: idx is a valid index within the items vector.
// Post: The item at the specified index is returned.
item Shop::getItem(int idx)
{
	return items[idx];
}

// Intent: Returns the icon of the shop.
// Pre: None.
// Post: The shop icon is returned.
char Shop::getIcon()
{
	return icon;
}

// Intent: Handles the shop interaction where the player can purchase items.
// Pre: money is the amount of money the player has.
// Post: Returns a vector of indices representing purchased items.
vector<int> Shop::intoShop(int& money)
{
	vector<int> purchaseIdx;	// Vector to store purchased item indices
	int idx = 0;	// Index to track the current selected item

	while (true)
	{
		showShopInfo(idx, money);	// Show the shop information
		char input = _getch();		// Get user input

		if (input == 'W' || input == 'w')
		{
			if (idx <= 0)
			{
				idx = 17;	// Wrap around to the last item
			}
			else
			{
				idx--;	// Move up the list
			}
		}

		if (input == 'S' || input == 's')
		{
			if (idx >= 17)
			{
				idx = 0;	// Wrap around to the first item
			}
			else
			{
				idx++;	// Move down the list
			}
		}

		if (input == '\r')
		{
			if (money >= items[idx].price)
			{
				purchaseIdx.push_back(idx);	// Add item to purchased list
				money -= items[idx].price;	// Deduct money
			}
		}

		if (input == 27)	// Escape key to exit the shop
		{
			system("CLS");
			return purchaseIdx;	// Return the list of purchased items
		}
	}
}

// Intent: Displays the shop information including items and prices.
// Pre: idx is the current selected item index. money is the player's current amount of money.
// Post: The shop interface is displayed with the current selection and item details.
void Shop::showShopInfo(int idx, int& money)
{
	system("CLS");	// Clear the screen
	static int upIdx = 0, downIdx = 9;	// Indices to track the display window

	if (upIdx > idx)
	{
		upIdx = idx;	// Adjust the display window upwards
		downIdx = idx + 9;
	}

	if (downIdx < idx)
	{
		downIdx = idx;	// Adjust the display window downwards
		upIdx = idx - 9;
	}

	cout << "Money : " << money << "\n";
	cout << "         Item                                                          Price\n";

	for (int i = upIdx; i <= downIdx; i++)
	{
		SetColor(7);	// Reset color to default
		cout << setw(5) << ((i == idx) ? "-> " : "  ") << setw(30) << left << items[i].name;

		if (items[i].price > money)
		{
			SetColor(12);	// Change color to red if the player cannot afford the item
		}

		cout << setw(40) << right << items[i].price << "$\n";
		SetColor(7);	// Reset color to default
	}

	cout << "\n\n";
	cout << items[idx].introduction << std::endl << std::endl;
	std::cout << "Back(Esc)\n";
	std::cout << "Choose UP (W), DOWN(D)\n";
	std::cout << "Enter to check!\n";
}