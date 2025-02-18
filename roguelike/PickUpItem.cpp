#include "Player.h"

#include <stdlib.h>
#include <iostream>

void Player::PickUpItem() {

	_inventory.CreateRandomItem();

}

std::vector<int> Player::GetInventoryStats()
{
	return _inventory.GetInventory();
}

void Player::PrintItems(ItemType toPrint)
{
	_inventory.PrintItemsOfType(toPrint);
}

void Player::EquipArmour(int selection)
{
	_currentArmour = _inventory.GetArmourByIndex(selection);
}

/*
	Checks for symbol below player
	IF treasure symbol
	Call function which calls function to generate random object

*/