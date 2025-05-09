#pragma once
#include "SolidShape.h"
#include "Point.h"

class Circle : public SolidShape
{
private:
	Point m_center;
	double m_radius;
public:
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;

	uint32_t GetFillColor() override;

	Point GetCenter();
	double GetRadius();
};

