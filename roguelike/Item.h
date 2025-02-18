#pragma once
#include <random>
#include <vector>
#include <iostream>

class Player;

enum ItemType
{
	armour,
	weapon,
	potion
};

class Item
{
public:
	static const char itemSymbol;

	static const int minDamage;
	static const int maxDamage;

	static const int maxRange;

	static const int minDefense;
	static const int maxDefense;

	static const int maxHeal;

	static std::string getTypeString(ItemType type);
	static ItemType getTypeFromString(std::string type);

	ItemType GetType() {
		return _type;
	}

	Item() {}
	virtual ~Item() {};
protected:
	ItemType _type{ ItemType::weapon };
};

class PotionItem : public Item
{
public:
	PotionItem(int heal)
	{
		_type = ItemType::potion;
		_healthHealed = heal;
	}

	void UsePotion(Player* player);

	friend std::ostream& operator<<(std::ostream& os, const PotionItem& item);

private:
	int _healthHealed;
};

class ArmourItem : public Item
{
public:
	ArmourItem(int def)
	{
		_type = ItemType::armour;
		_defense = def;
	}

	friend std::ostream& operator<<(std::ostream& os, const ArmourItem& item);

private:
	int _defense;
};

class WeaponItem : public Item
{
public:
	WeaponItem(int attack, int range)
	{
		_type = ItemType::weapon;
		_attack = attack;
		_range = range;
	}

	friend std::ostream& operator<<(std::ostream& os, const WeaponItem& item);

private:
	int _attack;
	int _range;
};
