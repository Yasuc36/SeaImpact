#pragma once
#include <vector>
#include <string>
#include "Coordinates.h"
#include "GameRender.h"

/**
* Takes care of basic behaviour of graphical objects like ships and bullets.
*/

class BaseObject
{
protected:
	std::vector<std::string> Shape;
	Coordinates Position;
public:
	BaseObject(const Coordinates & position, std::vector<std::string> shape);
	std::vector<std::string> getShape();
	Coordinates getPosition();
	bool outOfBounds();
};