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
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;

	uint32_t GetFillColor() override;

	Point GetVertex1();
	Point GetVertex2();
	Point GetVertex3();
};

