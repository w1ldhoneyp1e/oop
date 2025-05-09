#include "Shape.h"
#include <format>

Shape::Shape(uint32_t outlineColor)
    : m_outlineColor(outlineColor)
{
}

uint32_t Shape::GetOutlineColor()
{
    return m_outlineColor;
}

std::string Shape::ToString()
{
    return std::format(R"(
        Area: {}
        Perimeter: {}
        Outline Color: {}
    )", GetArea(), GetPerimeter(), m_outlineColor);
}
