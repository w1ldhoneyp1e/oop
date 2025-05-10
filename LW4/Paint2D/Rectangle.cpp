#include "Rectangle.h"
#include <format>

Rectangle::Rectangle(double x, double y, double width, double height, uint32_t outlineColor, uint32_t fillColor)
    : SolidShape(outlineColor, fillColor)
    , m_leftTop(x, y)
    , m_rightBottom(x + width, y + height)
    , m_width(width)
    , m_height(height)
{
}

double Rectangle::GetArea()
{
    return m_width * m_height;
}

double Rectangle::GetPerimeter()
{
    return 2 * (m_width + m_height);
}

std::string Rectangle::ToString()
{
    return std::format(R"(
        Rectangle:
        Left Top: {}, {}
        Right Bottom: {}, {}
        Width: {}
        Height: {}
    )", m_leftTop.GetX(), m_leftTop.GetY(), 
    m_rightBottom.GetX(), m_rightBottom.GetY(), 
    m_width, m_height) 
    + SolidShape::ToString();
}

Point Rectangle::GetLeftTop()
{
    return m_leftTop;
}

Point Rectangle::GetRightBottom()
{
    return m_rightBottom;
}

double Rectangle::GetWidth()
{
    return m_width;
}

double Rectangle::GetHeight()
{
    return m_height;
}

void Rectangle::Draw(ICanvas& canvas) const
{
    canvas.DrawRectangle(m_leftTop, m_width, m_height, m_outlineColor);
    canvas.FillRectangle(m_leftTop, m_width, m_height, m_fillColor);
}
