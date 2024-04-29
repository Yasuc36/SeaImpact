#include "BonusInvincibility.h"

BonusInvincibility::BonusInvincibility(const Coordinates& pos) : Bonus(pos, { "I" })
{
}

void BonusInvincibility::use(Player* pl)
{
	pl->addInvincibility();
}