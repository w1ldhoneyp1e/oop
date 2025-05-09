#include "SolidShape.h"
#include <format>

SolidShape::SolidShape(uint32_t outlineColor, uint32_t fillColor)
    : Shape(outlineColor)
    , m_fillColor(fillColor)
{
}

uint32_t SolidShape::GetFillColor()
{
    return m_fillColor;
}

std::string SolidShape::ToString()
{
    return Shape::ToString() + std::format(R"(
        Fill Color: {}
    )", m_fillColor);
}
