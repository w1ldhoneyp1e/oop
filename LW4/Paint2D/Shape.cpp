#include "Shape.h"
#include <format>
#include <stdexcept>

Shape::Shape(uint32_t outlineColor)
    : m_outlineColor(outlineColor)
{
    if (!IsValidColor(outlineColor)) {
        throw std::invalid_argument("Invalid outline color");
    }
}

uint32_t Shape::GetOutlineColor() const
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

bool Shape::IsValidColor(uint32_t color)
{
    return color <= 0xFFFFFF;
}
