#include "ShapeStorage.h"

void ShapeStorage::AddShape(std::unique_ptr<Shape> shape)
{
    m_shapes.push_back(std::move(shape));
}

std::vector<std::unique_ptr<Shape>>& ShapeStorage::GetShapes()
{
    return m_shapes;
}

void ShapeStorage::Clear()
{
    m_shapes.clear();
}