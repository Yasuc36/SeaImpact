#include "BonusShield.h"

BonusShield::BonusShield(const Coordinates& pos) : Bonus(pos, { "S" })
{
}

void BonusShield::use(Player* pl)
{
	pl->addShield();
}