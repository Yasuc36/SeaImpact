#pragma once
#include "Enemy.h"

/**
* Class for enemy type: Toucher. Inherited from Enemy
*/

class EnemyToucher : public Enemy
{
public:
	EnemyToucher(const Coordinates& pos, std::vector<Shot>* shots);
};