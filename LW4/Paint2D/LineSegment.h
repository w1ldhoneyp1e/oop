#pragma once
#include "Shape.h"
#include "Point.h"

class LineSegment : public Shape
{
private:
	Point m_startPoint;
	Point m_endPoint;
public:
	LineSegment(Point startPoint, Point endPoint, uint32_t outlineColor);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;

	Point GetStartPoint();
	Point GetEndPoint();
};

