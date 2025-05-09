#pragma once
#include "SolidShape.h"
#include "Point.h"

class Circle : public SolidShape
{
private:
	Point m_center;
	double m_radius;
public:
	Circle(double x, double y, double radius, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;

	Point GetCenter();
	double GetRadius();
};

