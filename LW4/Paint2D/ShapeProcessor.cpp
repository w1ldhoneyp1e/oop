#include "ShapeProcessor.h"
#include <algorithm>
#include <memory>
#include "LineSegment.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "Circle.h"

Shape* ShapeProcessor::FindShapeWithBiggestArea(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    if (shapes.empty()) return nullptr;
    auto it = std::max_element(
        shapes.begin(),
        shapes.end(),
        [](const auto& a, const auto& b) {
            return a->GetArea() < b->GetArea();
        }
    );
    return it->get();
}

Shape* ShapeProcessor::FindShapeWithSmallestPerimeter(const std::vector<std::unique_ptr<Shape>>& shapes)
{
    if (shapes.empty()) return nullptr;
    auto it = std::min_element(
        shapes.begin(),
        shapes.end(),
        [](const auto& a, const auto& b) {
            return a->GetPerimeter() < b->GetPerimeter();
        }
    );
    return it->get();
}
