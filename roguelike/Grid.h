#pragma once

#include <vector>
#include <random>

#include "Enemy.h"
#include "Player.h"
#include "Item.h"

class Grid {
public:
	Grid(int rowSize, int columnSize, Player *playerPtr) 
		: _rowSize{rowSize},
		  _colSize{columnSize},
		_player{playerPtr},
			mt{rd()}
	{
		initialize_cells();
	};

	void clearTreasure() {
		treasureRemaining = 0;
	}

	void create_new_dungeon() {
		initialize_cells();
	}

	void print_dungeon();

	void set_row_size(int newRowSize) {
		resize_grid(newRowSize, _colSize);
	}

	void set_column_size(int newColSize) {
		resize_grid(_rowSize, newColSize);
	}

	void resize_grid(int rowSize, int columnSize)
	{
		_rowSize = rowSize;
		_colSize = columnSize;
		initialize_cells();
	}

	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	bool checkForTreasure();
	bool checkForExit();

	void printInventory();
	void checkInventory();
	void freeEnemies();

	int getRemainingTreasureCount() { return treasureRemaining; }

	static const char playerSymbol;
	static const char treasureSymbol;
	static const char wallSymbol;
	static const char emptySymbol;
	static const char exitSymbol;

private:
	//Inventory variables
	// std::vector<int> inventory = { 0, 0, 0, 0 };
	std::vector<int> itemLimit = { 100, 100, 100, 100 };
	enum invEnum { treasure, potion, weapon, armour };

	bool shouldPrintInv{ false };
	bool shouldPrintFullMessage{ false };

	int treasureRemaining{ 0 };

	void initialize_cells();
	void generate_dungeon();

	std::vector< std::vector<char>> grid;

	std::random_device rd;
	std::mt19937 mt;

	int _rowSize;
	int _colSize;

	Player *_player;

	int enemySpawnDistance{ 2 };
	int enemyMax{ 10 };
	int enemyMin{ 5 };

	std::vector<Enemy*> enemies;
	std::vector<Item*> inventory;
};