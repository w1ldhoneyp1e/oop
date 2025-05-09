#pragma once
#include "SolidShape.h"
#include "Point.h"

class Rectangle : public SolidShape
{
private:
	Point m_leftTop;
	Point m_rightBottom;
	double m_width;
	double m_height;
public:
	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	uint32_t GetOutlineColor() override;

	uint32_t GetFillColor() override;

	Point GetLeftTop();
	Point GetRightBottom();
	double GetWidth();
	double GetHeight();
};

