#pragma once
#include "Bonus.h"

/**
* Class which manages Bonus, which adds rockets to the player.
*/

class BonusRockets : public Bonus
{
public:
	BonusRockets(const Coordinates& pos);
	void use(Player* pl);
};