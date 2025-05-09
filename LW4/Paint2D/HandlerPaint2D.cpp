#include "HandlerPaint2D.h"
#include <string>
#include <sstream>
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "LineSegment.h"
#include "Point.h"
#include <memory>

void HandlerPaint2D::HandleCommand(std::istream& input, std::ostream& output)
{
    std::string command;
    while (std::getline(input, command))
    {
        std::istringstream iss(command);
        std::string cmd;
        while (iss >> cmd)
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
    }
    
}

void HandlerPaint2D::HandleAddCircle(std::istringstream& iss, std::ostream& output)
{
    double x, y, radius;
    uint32_t outlineColor, fillColor;
    iss >> x >> y >> radius >> outlineColor >> fillColor;
    m_storage.AddShape(std::make_unique<Circle>(x, y, radius, outlineColor, fillColor));
}

void HandlerPaint2D::HandleAddRectangle(std::istringstream& iss, std::ostream& output)
{
    double x, y, width, height;
    uint32_t outlineColor, fillColor;
    iss >> x >> y >> width >> height >> outlineColor >> fillColor;
    m_storage.AddShape(std::make_unique<Rectangle>(x, y, width, height, outlineColor, fillColor));
}

void HandlerPaint2D::HandleAddTriangle(std::istringstream& iss, std::ostream& output)
{
    double x1, y1, x2, y2, x3, y3;
    uint32_t outlineColor, fillColor;
    iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineColor >> fillColor;
    m_storage.AddShape(std::make_unique<Triangle>(x1, y1, x2, y2, x3, y3, outlineColor, fillColor));
}

void HandlerPaint2D::HandleAddLine(std::istringstream& iss, std::ostream& output)
{
    double x1, y1, x2, y2;
    uint32_t outlineColor;
    iss >> x1 >> y1 >> x2 >> y2 >> outlineColor;
    Point startPoint(x1, y1);
    Point endPoint(x2, y2);
    m_storage.AddShape(std::make_unique<LineSegment>(startPoint, endPoint, outlineColor));
}
