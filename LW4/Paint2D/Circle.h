#pragma once
#include "SolidShape.h"
#include "Point.h"
#include "ICanvas.h"

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
	void Draw(ICanvas& canvas) const override;

	Point GetCenter();
	double GetRadius();
};

