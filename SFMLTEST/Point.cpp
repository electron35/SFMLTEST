#include "point.h"

#include <cmath>

int Point::X()
{
	return this->_X;
}

void Point::X(int X)
{
	this->_X = X;
}

int Point::Y()
{
	return this->_Y;
}

void Point::Y(int Y)
{
	this->_Y = Y;
}

int Point::id()
{
	return this->_id;
}

void Point::id(int id)
{
	this->_id = id;
}

Point::Point()
{
	this->_id = 0;
	this->_X = 0;
	this->_Y = 0;
}

Point::Point(int id)
{
	this->_id = id;
	this->_X = 0;
	this->_Y = 0;
}

Point::Point(int X, int Y)
{
	this->_id = 0;
	this->_X = X;
	this->_Y = Y;
}

Point::Point(int id, int X, int Y)
{
	this->_id = id;
	this->_X = X;
	this->_Y = Y;
}

void Point::move(int xMovement, int yMovement) {
	if ((_X + xMovement) > this->xBorne)
	{
		this->_X = this->xBorne - std::abs((this->xBorne - this->_X) - xMovement);
	}
	else if ((_X + xMovement) < 0)
	{
		this->_X = 0 - ((this->_X) + xMovement);
	}
	else {
		this->_X += xMovement;
	}

	if ((_Y + yMovement) > this->yBorne)
	{
		this->_Y = this->yBorne - std::abs(((this->yBorne - this->_Y) - yMovement));
	}
	else if ((_Y + xMovement) < 0)
	{
		this->_Y = 0 - ((this->_Y) + yMovement);
	}
	else {
		this->_Y += yMovement;
	}
}