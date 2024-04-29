#pragma once
#include "Bonus.h"

/**
* Class which manages Bonus, which adds health to the player.
*/

class BonusHealth : public Bonus
{
public:
	BonusHealth(const Coordinates & pos);
	void use(Player * pl);
};