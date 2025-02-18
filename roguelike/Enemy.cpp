#include "Enemy.h"

#include "Grid.h"


const char Enemy::enemySymbol = 'E';

void Enemy::MoveTowardsPlayer(int playerX, int playerY, 
	const std::vector< std::vector<char>>& grid, int colSize, int rowSize)
{
	// move right towards player
	if (x < playerX)
	{
		if ((x < rowSize - 1) &&
			(grid[x + 1][y] != Grid::wallSymbol))
		{
			x++;
			return;
		}
	}

	if (x > playerX) 
	{	
		if ((x > 1) &&
			(grid[x - 1][y] != Grid::wallSymbol))
		{
			x--;
			return;
		}
	}

	if (y < playerY)
	{
		if ((y < colSize - 1) &&
			(grid[x][y + 1] != Grid::wallSymbol))
		{
			y++;
			return;
		}
	}

	if (y > playerY)
	{
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

int Enemy::GetAttackDamage() 
{
	// Return random value between 1 and this->maxDamage.
	std::uniform_int_distribution<> attackRange(1, this->maxDamage);

	return attackRange(this->mt);
}