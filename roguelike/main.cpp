#include <iostream>
#include <array>
#include <random>
#include <Windows.h>
#include "Grid.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
	const int ColumnSize = 100;
	const int RowSize = 20;

	Player player;
	Grid grid(RowSize, ColumnSize, &player);

	// Set the player reference for the Enemy class.
	

	bool isRunning{ true };

	while (isRunning)
	{
		system("cls");
		grid.print_dungeon();

		if (player.IsDamaged()) {
			std::cout << "You were hit for " << player.GetLastDamageAmount() << '\n'; 
		}

		if (player.GetHealth() <= 0)
		{ 
			std::cout << "You are dead!";
			isRunning = false;
			break;
		}

		char ch;
		std::cin >> ch;

		switch (ch)
		{
		case 'w':
			grid.moveUp();
			break;
		case 'a':
			grid.moveLeft();
			break;
		case 's':
			grid.moveDown();
			break;
		case 'd':
			grid.moveRight();
			break;
		case 'q':
			isRunning = false;
			break;
		case 'c':
			grid.clearTreasure();
			break;
		case 'i':
			grid.checkInventory();
			break;
		default:
			std::cout << ch << " is not a valid command\n";
		}

		grid.checkForTreasure();
		
		if (grid.checkForExit() && grid.getRemainingTreasureCount() == 0)
		{
			grid.create_new_dungeon();
		}
	}

	return 0;
}