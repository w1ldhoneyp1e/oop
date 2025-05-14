#include "Triangle.h"
#include <format>

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3, uint32_t outlineColor, uint32_t fillColor)
    : SolidShape(outlineColor, fillColor)
    , m_vertex1(x1, y1)
    , m_vertex2(x2, y2)
    , m_vertex3(x3, y3)
{
}

double Triangle::GetArea()
{
    return 0.5 * abs(
        m_vertex1.GetX() * (m_vertex2.GetY() - m_vertex3.GetY()) + 
        m_vertex2.GetX() * (m_vertex3.GetY() - m_vertex1.GetY()) + 
        m_vertex3.GetX() * (m_vertex1.GetY() - m_vertex2.GetY())
    );
}


double Triangle::GetPerimeter()
{
    return m_vertex1.DistanceTo(m_vertex2) + m_vertex2.DistanceTo(m_vertex3) + m_vertex3.DistanceTo(m_vertex1);
}


std::string Triangle::ToString()
{
    return std::format(R"(
        Triangle:
        Vertex 1: {}, {}
        Vertex 2: {}, {}
        Vertex 3: {}, {}
    )", 
    m_vertex1.GetX(), m_vertex1.GetY(), 
    m_vertex2.GetX(), m_vertex2.GetY(), 
    m_vertex3.GetX(), m_vertex3.GetY()) 
    + SolidShape::ToString();
}

Point Triangle::GetVertex1()
{
    return m_vertex1;
}

Point Triangle::GetVertex2()
{
    return m_vertex2;
}

Point Triangle::GetVertex3()
{
    return m_vertex3;
}

void Triangle::Draw(ICanvas& canvas) const
{
    canvas.DrawTriangle(m_vertex1, m_vertex2, m_vertex3, GetOutlineColor());
    canvas.FillTriangle(m_vertex1, m_vertex2, m_vertex3, GetFillColor());
}
