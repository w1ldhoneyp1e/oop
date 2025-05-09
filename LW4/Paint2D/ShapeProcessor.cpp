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

void ShapeProcessor::Draw(const std::vector<std::unique_ptr<Shape>>& shapes, Canvas& canvas)
{
    for (const auto& shape : shapes)
    {
        if (auto circle = dynamic_cast<Circle*>(shape.get()))
        {
            canvas.DrawCircle(circle->GetCenter(), circle->GetRadius(), circle->GetOutlineColor());
            canvas.FillCircle(circle->GetCenter(), circle->GetRadius(), circle->GetFillColor());
        }
        else if (auto rect = dynamic_cast<Rectangle*>(shape.get()))
        {
            canvas.DrawRectangle(rect->GetLeftTop(), rect->GetWidth(), rect->GetHeight(), rect->GetOutlineColor());
            canvas.FillRectangle(rect->GetLeftTop(), rect->GetWidth(), rect->GetHeight(), rect->GetFillColor());
        }
        else if (auto triangle = dynamic_cast<Triangle*>(shape.get()))
        {
            canvas.DrawTriangle(triangle->GetVertex1(), triangle->GetVertex2(), triangle->GetVertex3(), triangle->GetOutlineColor());
            canvas.FillTriangle(triangle->GetVertex1(), triangle->GetVertex2(), triangle->GetVertex3(), triangle->GetFillColor());
        }
        else if (auto line = dynamic_cast<LineSegment*>(shape.get()))
        {
            canvas.DrawLine(line->GetStartPoint(), line->GetEndPoint(), line->GetOutlineColor());
        }
    }
}
