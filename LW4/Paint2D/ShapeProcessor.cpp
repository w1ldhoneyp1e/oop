#include "ShapeProcessor.h"
#include <memory>

std::unique_ptr<Shape> ShapeProcessor::FindShapeWithBiggestArea(std::vector<std::unique_ptr<Shape>>& shapes)
{
    return std::max_element(
        shapes.begin(), 
        shapes.end(), 
        [](const auto& a, const auto& b) { 
            return a->GetArea() < b->GetArea(); 
        }
    );
}

std::unique_ptr<Shape> ShapeProcessor::FindShapeWithSmallestPerimeter(std::vector<std::unique_ptr<Shape>>& shapes)
{
    return std::min_element(
        shapes.begin(), 
        shapes.end(), 
        [](const auto& a, const auto& b) { 
            return a->GetPerimeter() < b->GetPerimeter(); 
        }
    );
}

