#pragma once
#include <vector>
#include "Shape.h"
class ShapeProcessor
{
public:
	std::unique_ptr<Shape> FindShapeWithBiggestArea(std::vector<std::unique_ptr<Shape>>& shapes);
	std::unique_ptr<Shape> FindShapeWithSmallestPerimeter(std::vector<std::unique_ptr<Shape>>& shapes);
};

