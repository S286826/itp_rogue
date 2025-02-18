#include "Inventory.h"

void Inventory::CreateRandomItem()
{
	std::uniform_int_distribution<> item_dist(0, ItemType::potion);

	std::uniform_int_distribution<> defense_dist(Item::minDefense, Item::maxDefense);
	std::uniform_int_distribution<> damage_dist(Item::minDamage, Item::maxDamage);
	std::uniform_int_distribution<> range_dist(0, Item::maxRange);
	std::uniform_int_distribution<> heal_dist(1, Item::maxHeal);

	ItemType itemType = (ItemType)item_dist(mt);

	Item* newItem;

	switch (itemType) {
	case ItemType::armour:
		newItem = new ArmourItem(defense_dist(mt));
		std::cout << *(ArmourItem*)newItem << '\n';
		break;

	case ItemType::potion:
		newItem = new PotionItem(heal_dist(mt));
		std::cout << *(PotionItem*)newItem << '\n';
		break;

	default:
	case ItemType::weapon:
		newItem = new WeaponItem(damage_dist(mt), range_dist(mt));
		std::cout << *(WeaponItem*)newItem << '\n';
		break;
	}

	inventory.push_back(newItem);
}

std::vector<int> Inventory::GetInventory()
{
	int armourNumber = 0;
	int weaponNumber = 0;
	int potionNumber = 0;
	for (int i = 0; i < inventory.size(); i++)
	{
		if (inventory[i]->GetType() == ItemType::armour)
			armourNumber++;
		if (inventory[i]->GetType() == ItemType::weapon)
			weaponNumber++;
		if (inventory[i]->GetType() == ItemType::potion)
			potionNumber++;
	}
	return std::vector<int> { armourNumber, weaponNumber, potionNumber };
}

void Inventory::PrintItemsOfType(ItemType type)
{
	int count{ 0 };

	for (auto item : inventory) {
		switch (type)
		{
			case ItemType::weapon:
			{
				WeaponItem* weapon = dynamic_cast<WeaponItem*>(item);
				
				if (weapon != nullptr)
				{
					std::cout << ++count << ' ' << *weapon << '\n';
				}
				break;
			}
			case ItemType::armour:
			{
				ArmourItem* armour = dynamic_cast<ArmourItem*>(item);

				if (armour != nullptr)
				{
					std::cout << ++count << ' ' << *armour << '\n';
				}
				break;
			}
			case ItemType::potion:
			{
				PotionItem* potion = dynamic_cast<PotionItem*>(item);

				if (potion != nullptr)
				{
					std::cout << ++count << ' ' << *potion << '\n';
				}
				break;
			}
		}
	}
}

ArmourItem* Inventory::GetArmourByIndex(int index)
{
	int count{ 0 };

	for (auto item : inventory) {
		ArmourItem* armour = dynamic_cast<ArmourItem*>(item);
		if (armour != nullptr)
		{
			count++;

			if (count == index)
			{
				return armour;
			}
		}
	}

	return nullptr;
}
