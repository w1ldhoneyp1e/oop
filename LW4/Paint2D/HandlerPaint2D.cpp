#include "HandlerPaint2D.h"
#include <string>
#include <sstream>
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "LineSegment.h"
#include "Point.h"
#include <memory>

ShapeStorage& HandlerPaint2D::GetStorage()
{
    return m_storage;
}

ShapeProcessor& HandlerPaint2D::GetProcessor()
{
    return m_processor;
}

void HandlerPaint2D::HandleCommand(std::istream& input, std::ostream& output)
{
    std::string command;
    while (std::getline(input, command))
    {
        std::istringstream iss(command);
        std::string cmd;
        while (iss >> cmd)
        {
            try
            {
                if (cmd == "circle")
                {
                    HandleAddCircle(iss, output);
                }
                else if (cmd == "rectangle")
                {
                    HandleAddRectangle(iss, output);
                }
                else if (cmd == "triangle")
                {
                    HandleAddTriangle(iss, output);
                }
                else if (cmd == "line")
                {
                    HandleAddLine(iss, output);
                }
                else if (command == "find biggest area")
                {
                    auto shape = m_processor.FindShapeWithBiggestArea(m_storage.GetShapes());
                    output << shape->ToString();
                }
                else if (command == "find smallest perimeter")
                {
                    auto shape = m_processor.FindShapeWithSmallestPerimeter(m_storage.GetShapes());
                    output << shape->ToString();
                }
                else if (command == "clear")
                {
                    m_storage.Clear();
                }
            }
            catch (const std::exception& ex)
            {
                output << "Error: " << ex.what() << std::endl;
            }
        }
    }
}

void HandlerPaint2D::HandleAddCircle(std::istringstream& iss, std::ostream& output)
{
    double x, y, radius;
    uint32_t outlineColor, fillColor;
    if (!(iss >> x >> y >> radius >> outlineColor >> fillColor)) {
        throw std::invalid_argument("Invalid parameters for circle");
    }
    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
    m_storage.AddShape(std::make_unique<Circle>(x, y, radius, outlineColor, fillColor));
}

void HandlerPaint2D::HandleAddRectangle(std::istringstream& iss, std::ostream& output)
{
    double x, y, width, height;
    uint32_t outlineColor, fillColor;
    if (!(iss >> x >> y >> width >> height >> outlineColor >> fillColor)) {
        throw std::invalid_argument("Invalid parameters for rectangle");
    }
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive");
    }
    m_storage.AddShape(std::make_unique<Rectangle>(x, y, width, height, outlineColor, fillColor));
}

void HandlerPaint2D::HandleAddTriangle(std::istringstream& iss, std::ostream& output)
{
    double x1, y1, x2, y2, x3, y3;
    uint32_t outlineColor, fillColor;
    if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineColor >> fillColor)) {
        throw std::invalid_argument("Invalid parameters for triangle");
    }
    m_storage.AddShape(std::make_unique<Triangle>(x1, y1, x2, y2, x3, y3, outlineColor, fillColor));
}

void HandlerPaint2D::HandleAddLine(std::istringstream& iss, std::ostream& output)
{
    double x1, y1, x2, y2;
    uint32_t outlineColor;
    if (!(iss >> x1 >> y1 >> x2 >> y2 >> outlineColor)) {
        throw std::invalid_argument("Invalid parameters for line");
    }
    m_storage.AddShape(std::make_unique<LineSegment>(Point(x1, y1), Point(x2, y2), outlineColor));
}
