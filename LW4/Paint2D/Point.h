#pragma once
class Point
{
private:
	double x;
	double y;
public:
	Point(double x, double y);
	
	double GetX();
	double GetY();
	double DistanceTo(Point other);
};

