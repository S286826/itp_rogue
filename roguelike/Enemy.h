#pragma once

#include <vector>
#include <random>

#include "Player.h"

class Enemy {
public:
	Enemy() {}
	Enemy(int xPos, int yPos) : x{ xPos }, y{ yPos } { }
	Enemy(int xPos, int yPos, int hp) : x{ xPos }, y{ yPos }, health{ hp } {}

	void MoveTowardsPlayer(int playerX, int playerY, 
		const std::vector< std::vector<char>>& grid, 
		int colSize, int rowSize);

	int getX() { return x; }
	int getY() { return y; }

	// bool CheckForPlayer(int& playerX, int& playerY);

	int GetAttackDamage();

	void setPosition(int xPos, int yPos) {
		x = xPos;
		y = yPos;
	}

	static const char enemySymbol;

	static void SetPlayerReference(Player* playerPtr) { _player = playerPtr; }

private:
	int x{ 0 }, y{ 0 };
	int health{ 10 };
	int maxDamage{ 5 };

	std::random_device rd;
	std::mt19937 mt;

	static Player* _player;
	
	bool CheckForPlayer(int &playerX, int &playerY);
};