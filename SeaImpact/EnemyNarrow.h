#pragma once
#include "Enemy.h"

/**
* Class for enemy type: Narrow. Inherited from Enemy
*/

class EnemyNarrow : public Enemy
{
public:
	EnemyNarrow(const Coordinates& pos, std::vector<Shot>* shots);
};