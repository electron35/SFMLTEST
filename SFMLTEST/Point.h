#pragma once
class Point
{
private:
	int _X;
	int _Y;
	int _id;
	int xBorne = 800;
	int yBorne = 800;

public:
	int X();
	void X(int X);
	int Y();
	void Y(int Y);

	int id();
	void id(int id);

	Point();
	Point(int id);
	Point(int X, int Y);
	Point(int id, int X, int Y);


	void move(int xMovement, int yMovement);
};



