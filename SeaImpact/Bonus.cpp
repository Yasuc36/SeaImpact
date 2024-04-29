#include "Bonus.h"

Bonus::Bonus(const Coordinates & pos, const std::vector<std::string> & shape) : BaseObject(pos, shape)
{
}

void Bonus::move()
{
	--Position.X;
}