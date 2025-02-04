#include "Enemy.h"

#include "Grid.h"

const char Enemy::enemySymbol = '!';

void Enemy::MoveTowardsPlayer(int playerX, int playerY, 
	const std::vector< std::vector<char>>& grid, int colSize, int rowSize)
{
	// move right towards player
	if (x < playerX)
	{
		this->CheckForPlayer(playerX, playerY);

		if ((x < rowSize - 1) &&
			(grid[x + 1][y] != Grid::wallSymbol))
		{
			x++;
			return;
		}
	}

	if (x > playerX) 
	{	
		this->CheckForPlayer(playerX, playerY);

		if ((x > 1) &&
			(grid[x - 1][y] != Grid::wallSymbol))
		{
			x--;
			return;
		}
	}

	if (y < playerY)
	{
		this->CheckForPlayer(playerX, playerY);

		if ((y < colSize - 1) &&
			(grid[x][y + 1] != Grid::wallSymbol))
		{
			y++;
			return;
		}
	}

	if (y > playerY)
	{
		this->CheckForPlayer(playerX, playerY);

		if ((y > 1) &&
			(grid[x][y - 1] != Grid::wallSymbol))
		{
			y--;
			return;
		}
	}
}

bool Enemy::CheckForPlayer(int &playerX, int &playerY) 
{
	int xDifference = abs(getY() - playerY);
	int yDifference = abs(getX() - playerX);

	return (xDifference == 1 && yDifference == 0) || (xDifference == 0 && yDifference == 1);
}