#pragma once

/**
* Simple class representing position in 2D space.
*/

class Coordinates
{
public:
	int X;
	int Y;
	Coordinates(const int x, const int y);
	Coordinates(const Coordinates & position);
	friend bool operator==(const Coordinates& a, const Coordinates& b);
};

bool operator==(const Coordinates& a, const Coordinates& b);