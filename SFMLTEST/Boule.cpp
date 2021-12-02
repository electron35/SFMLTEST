#include "Boule.h"
#include <SFML/Graphics.hpp>
#include <iostream>
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

	/*if (this->_XP > this->borneXMax+100 || this->_XP < this->borneXMin-100 || this->_YP > this->borneYMax+100 || this->_YP < this->borneYMin-100)
	{
		std::srand(std::time(nullptr));
		this->_XP = (rand() / ((RAND_MAX + 1u) / 780));
		this->_YP = (rand() / ((RAND_MAX + 1u) / 780));
	}*/
		

	this->projection.setPosition(Vector2f(this->_XP, this->_YP));
}

bool Boule::isColliding(Boule b)
{
	float distance = sqrt(pow((b._XP -this->_XP),2) + pow((b._YP -this->_YP),2));
	
	
	if (distance < (this->_radius)*2) {
	//	//std::cout << "salut" << endl;
		return true;
	}
	if (((this->_XP == b._XP || this->_XP == (b._XP + b._radius) || this->_XP == (b._XP - b._radius)) && (this->_YP == b._YP || this->_YP == (b._YP + b._radius) || this->_YP == (b._YP - b._radius)))) {
		return true;
	}
		
	return false;
}
