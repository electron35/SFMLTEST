#pragma once
#include "Point.h"
#include <SFML/Graphics.hpp>
using namespace sf;
class Boule : public Point
{
public:
	int _radius;
	sf::CircleShape projection;
	int _XP;
	int _YP;
	sf::Color _color;
	float _Vx;
	float _Vy;
	float _Ax;
	float _Ay;


	int borneXMin = 0;
	int borneYMin = 0;
	int borneXMax = 800;
	int borneYMax = 800;


	Boule(int id, int x, int y, int radius, Color color, float Vx, float Vy, float Ax, float Ay);
	void move();
	bool isColliding(Boule b);
};

