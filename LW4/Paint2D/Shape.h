#pragma once
#include <string>
#include <cstdint>
#include "CanvasDrawable.h"

class Shape : public CanvasDrawable
{
protected:
	uint32_t m_outlineColor;
public:
	explicit Shape(uint32_t outlineColor);
	virtual ~Shape() = default;

	virtual double GetArea() = 0;
	virtual double GetPerimeter() = 0;
	virtual std::string ToString();
	uint32_t GetOutlineColor() const;
	
	static bool IsValidColor(uint32_t color);
};

