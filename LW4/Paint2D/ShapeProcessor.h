#pragma once
#include "Shape.h"
#include <vector>
#include <memory>

class ShapeProcessor
{
public:
	Shape* FindShapeWithBiggestArea(const std::vector<std::unique_ptr<Shape>>& shapes);
	Shape* FindShapeWithSmallestPerimeter(const std::vector<std::unique_ptr<Shape>>& shapes);
};

