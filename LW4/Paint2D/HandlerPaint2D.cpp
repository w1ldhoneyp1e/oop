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
    m_commandHandlers = {
        { "circle", [this](std::istringstream& iss, std::ostream& output) { HandleAddCircle(iss, output); } },
        { "rectangle", [this](std::istringstream& iss, std::ostream& output) { HandleAddRectangle(iss, output); } },
        { "triangle", [this](std::istringstream& iss, std::ostream& output) { HandleAddTriangle(iss, output); } },
        { "line", [this](std::istringstream& iss, std::ostream& output) { HandleAddLine(iss, output); } },
        { "find biggest area", [this](std::istringstream& iss, std::ostream& output) { HandleBiggestArea(iss, output); } },
        { "find smallest perimeter", [this](std::istringstream& iss, std::ostream& output) { HandleSmallestPerimeter(iss, output); } },
        { "clear", [this](std::istringstream& iss, std::ostream& output) { HandleClear(iss, output); } }
    };
}

void HandlerPaint2D::HandleCommand(std::string& command, std::ostream& output)
{
    std::string cmd;
    std::istringstream iss(command);
    
    auto fullCommandIt = m_commandHandlers.find(command);
    if (fullCommandIt != m_commandHandlers.end()) {
        try {
            fullCommandIt->second(iss, output);
        }
        catch (const std::exception& ex) {
            output << "Error: " << ex.what() << std::endl;
        }
        return;
    }
    
    while (iss >> cmd)
    {
        try
        {
            auto handlerIt = m_commandHandlers.find(cmd);
            if (handlerIt != m_commandHandlers.end()) {
                handlerIt->second(iss, output);
            }
            else {
                output << "Error: Unknown command '" << cmd << "'" << std::endl;
            }
        }
        catch (const std::exception& ex)
        {
            output << "Error: " << ex.what() << std::endl;
        }
    }
}

void HandlerPaint2D::HandleBiggestArea(std::istringstream& iss, std::ostream& output)
{
    auto shape = m_processor.FindShapeWithBiggestArea(m_storage.GetShapes());
    if (shape) {
        output << shape->ToString();
    }
    else {
        output << "No shapes in storage" << std::endl;
    }
}

void HandlerPaint2D::HandleSmallestPerimeter(std::istringstream& iss, std::ostream& output)
{
    auto shape = m_processor.FindShapeWithSmallestPerimeter(m_storage.GetShapes());
    if (shape) {
        output << shape->ToString();
    }
    else {
        output << "No shapes in storage" << std::endl;
    }
}

void HandlerPaint2D::HandleClear(std::istringstream& iss, std::ostream& output)
{
    m_storage.Clear();
}

void HandlerPaint2D::HandleAddCircle(std::istringstream& iss, std::ostream& output)
{
    double x, y, radius;
    std::string outlineColorStr, fillColorStr;
    
    if (!(iss >> x >> y >> radius >> outlineColorStr >> fillColorStr)) {
        throw std::invalid_argument("Invalid parameters for circle");
    }
    
    uint32_t outlineColor = std::stoul(outlineColorStr, nullptr, 16);
    uint32_t fillColor = std::stoul(fillColorStr, nullptr, 16);
    
    try {
        m_storage.AddShape(std::make_unique<Circle>(x, y, radius, outlineColor, fillColor));
    }
    catch (const std::invalid_argument& e) {
        throw std::invalid_argument(e.what());
    }
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
    
    uint32_t outlineColor = std::stoul(outlineColorStr, nullptr, 16);
    uint32_t fillColor = std::stoul(fillColorStr, nullptr, 16);
    
    try {
        m_storage.AddShape(std::make_unique<Rectangle>(x, y, width, height, outlineColor, fillColor));
    }
    catch (const std::invalid_argument& e) {
        throw std::invalid_argument(e.what());
    }
}

void HandlerPaint2D::HandleAddTriangle(std::istringstream& iss, std::ostream& output)
{
    double x1, y1, x2, y2, x3, y3;
    std::string outlineColorStr, fillColorStr;
    if (!(iss >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> outlineColorStr >> fillColorStr)) {
        throw std::invalid_argument("Invalid parameters for triangle");
    }
    
    uint32_t outlineColor = std::stoul(outlineColorStr, nullptr, 16);
    uint32_t fillColor = std::stoul(fillColorStr, nullptr, 16);
    
    try {
        m_storage.AddShape(std::make_unique<Triangle>(x1, y1, x2, y2, x3, y3, outlineColor, fillColor));
    }
    catch (const std::invalid_argument& e) {
        throw std::invalid_argument(e.what());
    }
}

void HandlerPaint2D::HandleAddLine(std::istringstream& iss, std::ostream& output)
{
    double x1, y1, x2, y2;
    std::string outlineColorStr;
    if (!(iss >> x1 >> y1 >> x2 >> y2 >> outlineColorStr)) {
        throw std::invalid_argument("Invalid parameters for line");
    }
    
    uint32_t outlineColor = std::stoul(outlineColorStr, nullptr, 16);

    try {
        m_storage.AddShape(std::make_unique<LineSegment>(Point(x1, y1), Point(x2, y2), outlineColor));
    }
    catch (const std::invalid_argument& e) {
        throw std::invalid_argument(e.what());
    }
}
