#pragma once
#include <string>
#include <cstdint>

class Shape
{
public:
	virtual double GetArea();
	virtual double GetPerimeter();
	virtual std::string ToString();
	virtual uint32_t GetOutlineColor();
};

