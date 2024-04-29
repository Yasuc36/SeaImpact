#pragma once
#include "Enemy.h"

/**
* Class for enemy type: Wiggler. Inherited from Enemy
*/

class EnemyWiggler : public Enemy
{
public:
	EnemyWiggler(const Coordinates& pos, std::vector<Shot>* shots);
};