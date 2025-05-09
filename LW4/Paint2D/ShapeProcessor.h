#pragma once
#include <vector>
#include "Shape.h"
class ShapeProcessor
{
public:
	Shape* FindShapeWithBiggestArea(std::vector<Shape*> shapes);
	Shape* FindShapeWithSmallestPerimeter(std::vector<Shape*> shapes);
};

