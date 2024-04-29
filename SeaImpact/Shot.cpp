#include "Shot.h"

Shot::Shot(const Coordinates& position, std::vector<std::string> shape, int direction) : BaseObject(position, shape)
{
	Direction = direction;
}

void Shot::move()
{
	if (Direction < 0) --Position.X;
	else ++Position.X;
}