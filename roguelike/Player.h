#pragma once
#include "Inventory.h"

class Enemy;

class Player
{
private:
	int _x{ 0 };
	int _y{ 0 };

	int _lastDamage{ 0 };
	bool _isDamaged{ false };
	
	int _health{ 20 };
public:
	// Position
	int GetX() const { return _x; }
	int GetY() const { return _y; }

	void SetX(int newX) { _x = newX; }
	void SetY(int newY) { _y = newY; }

	void SetPosition(int x, int y) { _x = x; _y = y; }

	// Health
	int GetHealth() const { return _health; }
	bool IsDamaged() const { return _isDamaged; }
	int GetLastDamageAmount() const { return _lastDamage; }

	// Attacking
	void DoAttack(int x, int y);

	// Receiving attack
	void ReceiveAttack(Enemy& enemy);

	void ResetDamageState();

	int damageDelt = 0;
	int health{ 100 };

	void PickUpItem();
	std::vector<int>  GetInventoryStats();

	void PrintItems(ItemType toPrint);

	void EquipArmour(int selection);
private:
	Inventory _inventory;
	ArmourItem* _currentArmour{ nullptr };
};

