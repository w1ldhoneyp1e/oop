#include "Point.h"
#include <cmath>

Point::Point(double x, double y)
    : x(x)
    , y(y)
{
}

double Point::GetX()
{
    return x;
}

double Point::GetY()
{
    return y;
}

double Point::DistanceTo(Point other)
{
    return sqrt(
        (x - other.x) * (x - other.x) + 
        (y - other.y) * (y - other.y)
    );
}
