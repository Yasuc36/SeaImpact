#pragma once
#include "Bonus.h"

/**
* Class which manages Bonus, which adds invincibility to the player.
*/

class BonusInvincibility : public Bonus
{
public:
	BonusInvincibility(const Coordinates& pos);
	void use(Player* pl);
};