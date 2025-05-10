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
	Rectangle(double x, double y, double width, double height, uint32_t outlineColor, uint32_t fillColor);

	double GetArea() override;
	double GetPerimeter() override;
	std::string ToString() override;
	void Draw(ICanvas& canvas) const override;

	Point GetLeftTop();
	Point GetRightBottom();
	double GetWidth();
	double GetHeight();
};

