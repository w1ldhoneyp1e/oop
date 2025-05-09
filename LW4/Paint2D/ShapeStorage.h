#pragma once
#include "Shape.h"
#include <vector>

class ShapeStorage
{
private:
	std::vector<Shape> m_shapes;
public:
	void AddShape(Shape shape);
	void Clear();
};

