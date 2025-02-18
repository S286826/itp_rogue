#include <iostream>
#include <array>

#include <random>

#include <Windows.h>

#include "Grid.h"
#include "Item.h"
#include "Player.h"

const char Item::itemSymbol = '$';

const int Item::minDamage = 1;
const int Item::maxDamage = 10;

const int Item::maxRange = 2;

const int Item::minDefense = 1;
const int Item::maxDefense = 5;

const int Item::maxHeal = 10;

std::string Item::getTypeString(ItemType type)
{
	switch (type)
	{
	case ItemType::armour:
		return "Armour";
	case ItemType::potion:
		return "Potion";
	default:
	case ItemType::weapon:
		return "Weapon";
	}
}

ItemType Item::getTypeFromString(std::string type)
{
	if (type == "Armour")
		return ItemType::armour;
	if (type == "Potion")
		return ItemType::potion;

	return ItemType::weapon;
}

std::ostream& operator<<(std::ostream& os, const PotionItem& item)
{
	os << Item::getTypeString(item._type) << " heal amount: " << item._healthHealed;

	return os;
}

std::ostream& operator<<(std::ostream& os, const ArmourItem& item)
{
	os << Item::getTypeString(item._type) << " defense: " << item._defense;
	return os;
}

std::ostream& operator<<(std::ostream& os, const WeaponItem& item)
{
	os << Item::getTypeString(item._type) << " damage: " << item._attack << " range: " << item._range;
	return os;
}

//void PotionItem::UsePotion(Player* player)
//{
//	player->GetHealth() += _healthHealed;
//}
