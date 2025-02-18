#pragma once

#include "Item.h"

class Inventory {
public:
	Inventory() : mt{ rd() } {}
	void CreateRandomItem();
	std::vector<int> GetInventory();
	void PrintItemsOfType(ItemType type);

	ArmourItem* GetArmourByIndex(int index);

private:

	std::vector<Item*> inventory;
	std::random_device rd;
	std::mt19937 mt;
};