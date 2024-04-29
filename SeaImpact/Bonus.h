#pragma once
#include <vector>
#include <string>
#include "BaseObject.h"
#include "Player.h"

/**
* Class for basic behaviour of bonuses.
*/

class Bonus : public BaseObject
{
public:
	Bonus(const Coordinates& pos, const std::vector<std::string> & shape);
	void move();
	virtual void use(Player * pl) = 0;
};