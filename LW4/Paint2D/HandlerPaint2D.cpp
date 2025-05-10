#include "HandlerPaint2D.h"
#include <string>
#include <sstream>
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "LineSegment.h"
#include "Point.h"
#include <memory>

HandlerPaint2D::HandlerPaint2D(ShapeStorage& storage, ShapeProcessor& processor)
    : m_storage(storage), m_processor(processor)
{
}

void HandlerPaint2D::HandleCommand(std::string& command, std::ostream& output)
{
    std::string cmd;
    std::istringstream iss(command);
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

void HandlerPaint2D::HandleAddCircle(std::istringstream& iss, std::ostream& output)
{
    double x, y, radius;
    std::string outlineColorStr, fillColorStr;
    
    if (!(iss >> x >> y >> radius >> outlineColorStr >> fillColorStr)) {
        throw std::invalid_argument("Invalid parameters for circle");
    }
    
    if (radius <= 0) {
        throw std::invalid_argument("Radius must be positive");
    }
    
    if (!IsValidColor(outlineColorStr) || !IsValidColor(fillColorStr)) {
        throw std::invalid_argument("Invalid color format");
    }
    
    uint32_t outlineColor = std::stoul(outlineColorStr, nullptr, 16);
    uint32_t fillColor = std::stoul(fillColorStr, nullptr, 16);
    
    m_storage.AddShape(std::make_unique<Circle>(x, y, radius, outlineColor, fillColor));
}

void HandlerPaint2D::HandleAddRectangle(std::istringstream& iss, std::ostream& output)
{
    double x, y, width, height;
    std::string outlineColorStr, fillColorStr;
    
    if (!(iss >> x >> y >> width >> height >> outlineColorStr >> fillColorStr)) {
        throw std::invalid_argument("Invalid parameters for rectangle");
    }
    
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be positive");
    }
    
    if (!IsValidColor(outlineColorStr) || !IsValidColor(fillColorStr)) {
        throw std::invalid_argument("Invalid color format");
    }
    
    uint32_t outlineColor = std::stoul(outlineColorStr, nullptr, 16);
    uint32_t fillColor = std::stoul(fillColorStr, nullptr, 16);
    
    m_storage.AddShape(std::make_unique<Rectangle>(x, y, width, height, outlineColor, fillColor));
}

void HandlerPaint2D::HandleAddTriangle(std::istringstream& iss, std::ostream& output)
{
    double x1, y1, x2, y2, x3, y3;
    std::string outlineColorStr, fillColorStr;
    if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineColorStr >> fillColorStr)) {
        throw std::invalid_argument("Invalid parameters for triangle");
    }
    if (!IsValidColor(outlineColorStr) || !IsValidColor(fillColorStr)) {
        throw std::invalid_argument("Invalid color format");
    }
    uint32_t outlineColor = std::stoul(outlineColorStr, nullptr, 16);
    uint32_t fillColor = std::stoul(fillColorStr, nullptr, 16);
    m_storage.AddShape(std::make_unique<Triangle>(x1, y1, x2, y2, x3, y3, outlineColor, fillColor));
}

void HandlerPaint2D::HandleAddLine(std::istringstream& iss, std::ostream& output)
{
    double x1, y1, x2, y2;
    std::string outlineColorStr;
    if (!(iss >> x1 >> y1 >> x2 >> y2 >> outlineColorStr)) {
        throw std::invalid_argument("Invalid parameters for line");
    }
    if (!IsValidColor(outlineColorStr)) {
        throw std::invalid_argument("Invalid color format");
    }
    uint32_t outlineColor = std::stoul(outlineColorStr, nullptr, 16);
    m_storage.AddShape(std::make_unique<LineSegment>(Point(x1, y1), Point(x2, y2), outlineColor));
}

bool HandlerPaint2D::IsValidColor(const std::string& colorStr)
{
    try {
        for (char c : colorStr) {
            if (!isxdigit(c)) {
                return false;
            }
        }
        
        uint32_t color = std::stoul(colorStr, nullptr, 16);
        return color <= 0xFFFFFF;
    }
    catch (std::exception&) {
        return false;
    }
}
