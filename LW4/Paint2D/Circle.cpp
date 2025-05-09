#include "Circle.h"
#include <format>
#include <numbers>

Circle::Circle(double x, double y, double radius, uint32_t outlineColor, uint32_t fillColor)
    : SolidShape(outlineColor, fillColor)
    , m_center(x, y)
    , m_radius(radius)
{
}

double Circle::GetArea()
{
    return std::numbers::pi * m_radius * m_radius;
}


double Circle::GetPerimeter()
{
    return 2 * std::numbers::pi * m_radius;
}

std::string Circle::ToString()
{
    return std::format(R"(
        Circle:
        Center: {}, {}
        Radius: {}
    )", m_center.GetX(), m_center.GetY(), m_radius) + SolidShape::ToString();
}

Point Circle::GetCenter()
{
    return m_center;
}

double Circle::GetRadius()
{
    return m_radius;
}
