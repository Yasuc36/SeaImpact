#pragma once
#include <vector>
#include <string>
#include "Coordinates.h"
#include "BaseObject.h"
#include "curses.h"
#include "GameRender.h"

/**
* Class, that manages shots fired out of ship. Cares about shape, direction of fire, position etc.
*/

class Shot : public BaseObject
{
private:
	int Direction; // (<0 = left; >=0 right)
public:
	Shot(const Coordinates & position, std::vector<std::string> shape, int direction); // Constructor
	void move();	// Move the shot by 1
};