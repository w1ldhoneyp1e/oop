#pragma once
#include <vector>
#include "Shape.h"
#include <memory>

class ShapeProcessor
{
public:
	Shape* FindShapeWithBiggestArea(const std::vector<std::unique_ptr<Shape>>& shapes);
	Shape* FindShapeWithSmallestPerimeter(const std::vector<std::unique_ptr<Shape>>& shapes);
};

