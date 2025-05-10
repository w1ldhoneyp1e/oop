#pragma once
#include "SolidShape.h"
#include "Point.h"

class Triangle : public SolidShape
{
private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
public:
	Triangle(double x1, double y1, double x2, double y2, double x3, double y3, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	void Draw(ICanvas& canvas) const override;

	Point GetVertex1();
	Point GetVertex2();
	Point GetVertex3();
};

