#pragma once
#include <string>
#include <cstdint>

class Shape
{
protected:
	uint32_t m_outlineColor;
public:
	explicit Shape(uint32_t outlineColor);

	virtual double GetArea() = 0;
	virtual double GetPerimeter() = 0;
	virtual std::string ToString();
	uint32_t GetOutlineColor();
};

