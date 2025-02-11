#include "Grid.h"
#include "Player.h"
#include "Item.h"

#include <iostream>
#include <random>

#include <fstream>

const char Grid::playerSymbol = '@';
const char Grid::treasureSymbol = '*';
const char Grid::wallSymbol = '#';
const char Grid::emptySymbol = ' ';
const char Grid::exitSymbol = '^';

void Grid::print_dungeon()
{
	// loop the grid and print each row of characters
	for (int i = 0; i < _rowSize; ++i)
	{
		for (int j = 0; j < _colSize; ++j)
		{
			if (i == playerX && j == playerY)
			{
				std::cout << playerSymbol;
			}
			else if (enemy.getX() == i && enemy.getY() == j) {
				std::cout << Enemy::enemySymbol;
			}
			else {
				std::cout << grid[i][j];
			}
		}
		std::cout << '\n';
	}
	if (shouldPrintInv)
	{
		printInventory();
		shouldPrintInv = false;
	}
	else if (shouldPrintFullMessage)
	{
		std::cout << "Can't hold more of item!";
		shouldPrintFullMessage = false;
	}

}

int Grid::GetPlayerX() 
{
	return this->playerX;
}

int Grid::GetPlayerY() 
{
	return this->playerY;
}

void Grid::moveUp()
{
	if ((playerX > 1) && 
		(grid[playerX - 1][playerY] != wallSymbol))
	{
		int enemyX = enemy.getX();
		int enemyY = enemy.getY();

		if (playerX - 1 == enemyX && playerY == enemyY)
		{
			//player.DoAttack();
		}
		playerX--;
		enemy.MoveTowardsPlayer(playerX, playerY, grid, _colSize, _rowSize);
	}

	this->isDamaged = enemy.CheckForPlayer(playerX, playerY);

	if (isDamaged) 
	{
		ReceiveAttack();
	}
}

void Grid::moveDown()
{
	if ((playerX < _rowSize - 1) &&
		(grid[playerX + 1][playerY] != wallSymbol))
	{

		int enemyX = enemy.getX();
		int enemyY = enemy.getY();

		if (playerX + 1 == enemyX && playerY == enemyY)
		{
			//player.DoAttack();
		}
		playerX++;
		enemy.MoveTowardsPlayer(playerX, playerY, grid, _colSize, _rowSize);
	}
	
	this->isDamaged = enemy.CheckForPlayer(playerX, playerY);

	if (isDamaged)
	{
		ReceiveAttack();
	}
}

void Grid::moveLeft()
{
	if ((playerY > 1) &&
		(grid[playerX][playerY - 1] != wallSymbol))
	{
		int enemyX = enemy.getX();
		int enemyY = enemy.getY();

		if (playerX == enemyX && playerY - 1 == enemyY)
		{
			//player.DoAttack();
		}
		playerY--;
		enemy.MoveTowardsPlayer(playerX, playerY, grid, _colSize, _rowSize);
	}

	this->isDamaged = enemy.CheckForPlayer(playerX, playerY);

	if (isDamaged)
	{
		ReceiveAttack();
	}
}

void Grid::moveRight()
{
	if ((playerY < _colSize - 1) &&
		(grid[playerX][playerY + 1] != wallSymbol))
	{
		int enemyX = enemy.getX();
		int enemyY = enemy.getY();

		if (playerX == enemyX && playerY + 1 == enemyY)
		{
			//player.DoAttack();
		}
		playerY++;
		enemy.MoveTowardsPlayer(playerX, playerY, grid, _colSize, _rowSize);
	}

	this->isDamaged = enemy.CheckForPlayer(playerX, playerY);

	if (isDamaged)
	{
		ReceiveAttack();
	}
}

bool Grid::checkForTreasure()
{
	ItemCollected(0, 0, 0);

	if (grid[playerX][playerY] == treasureSymbol)
	{
		collectItem(invEnum::treasure);
		return true;
	}

	return false;
}

bool Grid::checkForExit()
{
	if (grid[playerX][playerY] == exitSymbol)
	{
		return true;
	}

	return false;
}

void Grid::ItemCollected(int defense, int damage, int healthHealed)
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

//void Grid::collectTreasure()
//{
//	grid[playerX][playerY] = emptySymbol;
//	treasureRemaining--;
//}

//void Grid::collectItem(int item)
//{
//	if (inventory[item] < itemLimit[item])
//	{
//		grid[playerX][playerY] = emptySymbol;
//		if (item == invEnum::treasure)
//			treasureRemaining--;
//		updateInventory(item, 1);
//	}
//	else
//		shouldPrintFullMessage = true;
//}

void Grid::printInventory()
{
	std::cout << "Treasure = " << inventory[invEnum::treasure] << 
		" Potions = " << inventory[invEnum::potion] <<
		" Weapons = " << inventory[invEnum::weapon] <<
		" Armour = " << inventory[invEnum::armour] << '\n';
}

void Grid::checkInventory()
{
	shouldPrintInv = true;
}

void Grid::updateInventory(int itemNumber, int amount)
{
	inventory[itemNumber] += amount;
}

void Grid::initialize_cells()
{
	grid.clear();
	grid.resize(_rowSize);
	
	for (int i = 0; i < _rowSize; ++i)
	{
		grid[i].resize(_colSize, wallSymbol);
	}

	generate_dungeon();
}

void Grid::generate_dungeon()
{
	const int MaxWalkableCells = (_colSize * _rowSize) / 2;
	const int MaxNumberSteps = MaxWalkableCells * 10;

	int stepsTaken{ 0 };
	int cellsConverted{ 0 };

	treasureRemaining = 0;

	std::uniform_int_distribution<> column_dist(1, _colSize-1);
	std::uniform_int_distribution<> row_dist(1, _rowSize-1);
	std::uniform_int_distribution<> enemy_amount(1, enemyMax-1);

	int enemyCount = enemy_amount(mt);
	int x = row_dist(mt);
	int y = column_dist(mt);

	int enemiesSpawned = 1;

	playerX = x;
	playerY = y;

	while (stepsTaken < MaxNumberSteps
		&& cellsConverted < MaxWalkableCells)
	{
		if (grid[x][y] == wallSymbol)
		{
			grid[x][y] = emptySymbol;
			cellsConverted++;
		}

		if (stepsTaken > 0 && stepsTaken % 250 == 0)
		{
			grid[x][y] = treasureSymbol;
			treasureRemaining++;
		}

		std::uniform_int_distribution<> direction_dist(0, 3);

		int direction = direction_dist(mt);

		// 0 = up, 1 = right, 2 = down, 3 = left
		switch (direction)
		{
		case 0:
			if (y <= 1) continue;
			y--;
			break;
		case 1:
			if (x <= 1) continue;
			x--;
			break;
		case 2:
			if (y >= _colSize - 2) continue;
			y++;
			break;
		case 3:
		default:
			if (x >= _rowSize - 2) continue;
			x++;
			break;
		}

		stepsTaken++;

		if (stepsTaken = (MaxNumberSteps/enemyCount) * enemiesSpawned 
			&& (x > playerX + enemySpawnDistance || x < playerX - enemySpawnDistance || y > playerY + enemySpawnDistance || y < playerY - enemySpawnDistance)
			&& enemyCount > 0)
		{
			Enemy newEnemy;
			newEnemy.setPosition(x, y);
			enemiesSpawned++;
			enemyCount--;
		}
	}
	grid[x][y] = exitSymbol;
}

// This needs to be moved into a player class.
void Grid::ReceiveAttack()
{
	// We've just taken damage from an enemy.
	isDamaged = true; 

	lastDamage = enemy.GetAttackDamage();
	health -= lastDamage;
}

void Grid::ResetDamageState() 
{
	isDamaged = false;
	lastDamage = 0;
}