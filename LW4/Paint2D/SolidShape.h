#pragma once
#include "Shape.h"

class SolidShape : public Shape
{
private:
	uint32_t m_fillColor;
public:
	SolidShape(uint32_t outlineColor, uint32_t fillColor);

	std::string ToString() override;
	uint32_t GetFillColor() const;
};

