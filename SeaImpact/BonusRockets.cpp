#include "BonusRockets.h"

BonusRockets::BonusRockets(const Coordinates& pos) : Bonus(pos, { "R" })
{
}

void BonusRockets::use(Player* pl)
{
	pl->addRocket(1);
}