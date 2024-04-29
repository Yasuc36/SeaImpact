#include "Coordinates.h"

Coordinates::Coordinates(const int x, const int y)
{
	X = x;
	Y = y;
}

Coordinates::Coordinates(const Coordinates & position)
{
	X = position.X;
	Y = position.Y;
}

bool operator==(const Coordinates & a, const Coordinates & b)
{
	if (a.X == b.X && a.Y == b.Y) return true;
	return false;
}