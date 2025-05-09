#pragma once
#include "Shape.h"
#include "Canvas.h"
#include <vector>
#include <memory>

class ShapeProcessor
{
public:
	Shape* FindShapeWithBiggestArea(const std::vector<std::unique_ptr<Shape>>& shapes);
	Shape* FindShapeWithSmallestPerimeter(const std::vector<std::unique_ptr<Shape>>& shapes);

	void Draw(const std::vector<std::unique_ptr<Shape>>& shapes, Canvas& canvas);
};

