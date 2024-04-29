#include "BaseObject.h"

BaseObject::BaseObject(const Coordinates& position, std::vector<std::string> shape) : Position(position)
{
	Shape = shape;
}

std::vector<std::string> BaseObject::getShape()
{
	return Shape;
}

Coordinates BaseObject::getPosition()
{
	return Position;
}

bool BaseObject::outOfBounds()
{
	if (Position.X < 0 || Position.X >= GameRender::Width) return true;
	return false;
}