#pragma once
#include "Shape.h"
#include <vector>
#include <memory>

class ShapeStorage
{
private:
	std::vector<std::unique_ptr<Shape>> m_shapes;
public:
	void AddShape(std::unique_ptr<Shape> shape);
	std::vector<std::unique_ptr<Shape>>& GetShapes();
	void Clear();
};

