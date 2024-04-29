#include "BonusHealth.h"

BonusHealth::BonusHealth(const Coordinates& pos) : Bonus(pos, {"H"})
{
}

void BonusHealth::use(Player * pl)
{
	pl->addHp(1);
}