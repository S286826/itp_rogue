#include "Player.h"

#include <stdlib.h>
#include <iostream>

#include "Enemy.h"

// Attack an enemy.
void Player::DoAttack(int x, int y) {
	int damageDelt = rand() % 11;

	std::cout << damageDelt;
}

// TODO: Move this to the enemy class.
//void Player::CheckForPlayer(Enemy& enemy)
//{
//	_isDamaged = enemy.CheckForPlayer(_x, _y);
//
//	if (_isDamaged)
//	{
//		ReceiveAttack(enemy);
//	}
//}

// Receive an attack from an enemy. 
// TODO: Replace 'Enemy &enemy' with an integer damage value. An enemy should call this if it can attack the player.
void Player::ReceiveAttack(Enemy& enemy)
{
	// We've just taken damage from an enemy.
	_isDamaged = true;

	_lastDamage = enemy.GetAttackDamage();
	_health -= _lastDamage;
}

void Player::ResetDamageState()
{
	_isDamaged = false;
	_lastDamage = 0;
}

