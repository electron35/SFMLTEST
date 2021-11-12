#include "Boule.h"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

Boule::Boule(int id, int x, int y, int radius, Color color, float Vx, float Vy, float Ax, float Ay) {
	Point::Point(id,x,y);
	this->_radius = radius;
	this->_color = color;
	this->_Vx = Vx;
	this->_Vy = Vy;
	this->_Ax = Ax;
	this->_Ay = Ay;
	
	this->_XP = x;
	this->_YP = y;

	this->projection = CircleShape(this->_radius);
	this->projection.setPosition(Vector2f(this->_XP,this->_YP));
	this->projection.setFillColor(color);
}


void Boule::move() {
	if ((_XP + this->_Vx) > this->borneXMax)
	{
		this->_XP = this->borneXMax - std::abs((this->borneXMax - this->_XP) - this->_Vx);
		this->_Vx = -this->_Vx;
	}
	else if ((_XP + this->_Vx) < borneXMin)
	{
		this->_XP = borneXMin - ((this->_XP) + this->_Vx);
		this->_Vx = -this->_Vx;
	}
	else {
		this->_XP += this->_Vx;
	}

	if ((_YP + this->_Vy) > this->borneYMax)
	{
		this->_YP = this->borneYMax - std::abs(((this->borneYMax - this->_YP) - this->_Vy));
		this->_Vy = -this->_Vy;
	}
	else if ((_YP + this->_Vx) < borneYMin)
	{
		this->_YP = borneYMin - ((this->_YP) + this->_Vy);
		this->_Vy = -this->_Vy;
	}
	else {
		this->_YP += this->_Vy;
	}

	this->projection.setPosition(Vector2f(this->_XP, this->_YP));
}