#pragma once
#include "Bonus.h"

/**
* Class which manages Bonus, which adds shield to the player.
*/

class BonusShield : public Bonus
{
public:
	BonusShield(const Coordinates& pos);
	void use(Player* pl);
};