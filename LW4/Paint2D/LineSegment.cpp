#include "LineSegment.h"
#include <format>

LineSegment::LineSegment(Point startPoint, Point endPoint, uint32_t outlineColor)
    : Shape(outlineColor)
    , m_startPoint(startPoint)
    , m_endPoint(endPoint)
{
}

double LineSegment::GetArea()
{
    return 0;
}

double LineSegment::GetPerimeter()
{
    return m_startPoint.DistanceTo(m_endPoint);
}

std::string LineSegment::ToString()
{
    return Shape::ToString() + std::format(R"(
        Line Segment:
        Start Point: {}, {}
        End Point: {}, {}
    )", m_startPoint.GetX(), m_startPoint.GetY(), m_endPoint.GetX(), m_endPoint.GetY());
}

Point LineSegment::GetStartPoint()
{
    return m_startPoint;
}

Point LineSegment::GetEndPoint()
{
    return m_endPoint;
}
