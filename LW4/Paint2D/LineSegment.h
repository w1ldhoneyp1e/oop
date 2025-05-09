#pragma once
#include "Shape.h"
#include "Point.h"

class LineSegment : public Shape
{
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;

	CPoint GetStartPoint();
	CPoint GetEndPoint();
};

