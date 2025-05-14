#include "SolidShape.h"
#include <format>
#include <stdexcept>

SolidShape::SolidShape(uint32_t outlineColor, uint32_t fillColor)
    : Shape(outlineColor)
    , m_fillColor(fillColor)
{
    if (!IsValidColor(fillColor)) {
        throw std::invalid_argument("Invalid fill color");
    }
}

uint32_t SolidShape::GetFillColor() const
{
    return m_fillColor;
}

std::string SolidShape::ToString()
{
    return Shape::ToString() + std::format(R"(
        Fill Color: {}
    )", m_fillColor);
}
