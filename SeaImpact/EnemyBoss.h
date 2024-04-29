#pragma once
#include "Enemy.h"

/**
* Class for enemy type: Boss. Inherited from Enemy
*/

class EnemyBoss : public Enemy
{
private:
	int MaxShootDelay;
	int ShootDelay;
public:
	EnemyBoss(const Coordinates& pos, std::vector<Shot>* shots);
	void shoot();
};