#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../FakeIt-master/single_header/catch/fakeit.hpp"
using namespace fakeit;
using Catch::Approx;

#include "ICanvas.h"
#include "ShapeStorage.h"
#include "ShapeProcessor.h"
#include "HandlerPaint2D.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Triangle.h"
#include "LineSegment.h"
#include <sstream>

TEST_CASE("Calculations of area and perimeter")
{
    SECTION("Circle area and perimeter")
    {
        Circle circle(0, 0, 10, 0, 0);
        REQUIRE(circle.GetArea() == Approx(314.1).epsilon(0.1));
        REQUIRE(circle.GetPerimeter() == Approx(62.8).epsilon(0.1));
    }

    SECTION("Rectangle area and perimeter")
    {
        Rectangle rect(0, 0, 10, 20, 0, 0);
        REQUIRE(rect.GetArea() == 200.0);
        REQUIRE(rect.GetPerimeter() == 60.0);
    }

    SECTION("Triangle area and perimeter")
    {
        Triangle triangle(0, 0, 3, 0, 0, 4, 0, 0);
        REQUIRE(triangle.GetArea() == 6.0);
        REQUIRE(triangle.GetPerimeter() == Approx(12.0).epsilon(0.001));
    }

    SECTION("Line segment area and perimeter")
    {
        LineSegment line(Point(0, 0), Point(3, 4), 0);
        REQUIRE(line.GetArea() == 0.0);
        REQUIRE(line.GetPerimeter() == 5.0);
    }
}

TEST_CASE("Shape storage operations")
{
    ShapeStorage storage;
    
    SECTION("Adding shapes")
    {
        storage.AddShape(std::make_unique<Circle>(0, 0, 10, 0, 0));
        REQUIRE(storage.GetShapes().size() == 1);
        
        storage.AddShape(std::make_unique<Rectangle>(0, 0, 10, 20, 0, 0));
        REQUIRE(storage.GetShapes().size() == 2);
    }
    
    SECTION("Clearing shapes")
    {
        storage.AddShape(std::make_unique<Circle>(0, 0, 10, 0, 0));
        storage.AddShape(std::make_unique<Rectangle>(0, 0, 10, 20, 0, 0));
        
        REQUIRE(storage.GetShapes().size() == 2);
        
        storage.Clear();
        REQUIRE(storage.GetShapes().empty());
    }
}

TEST_CASE("Command handling")
{
    ShapeStorage storage;
    ShapeProcessor processor;
    HandlerPaint2D handler(storage, processor);
    std::ostringstream output;

    SECTION("Adding circle with command")
    {
        std::string command = "circle 0 0 10 123456 654321";
        handler.HandleCommand(command, output);
        
        REQUIRE(storage.GetShapes().size() == 1);
        REQUIRE(storage.GetShapes()[0]->ToString().find("Circle") != std::string::npos);
    }

    SECTION("Adding rectangle with command")
    {
        std::string command = "rectangle 0 0 10 20 111111 222222";
        handler.HandleCommand(command, output);
        
        REQUIRE(storage.GetShapes().size() == 1);
        REQUIRE(storage.GetShapes()[0]->ToString().find("Rectangle") != std::string::npos);
    }
    
    SECTION("Finding shape with biggest area")
    {
        std::string cmd1 = "circle 0 0 10 1 2";
        handler.HandleCommand(cmd1, output);
        
        std::string cmd2 = "rectangle 0 0 5 5 3 4";
        handler.HandleCommand(cmd2, output);
        
        output.str("");
        output.clear();
        
        std::string findCmd = "find biggest area";
        handler.HandleCommand(findCmd, output);
        
        REQUIRE(output.str().find("Circle") != std::string::npos);
    }
    
    SECTION("Finding shape with smallest perimeter")
    {
        std::string cmd1 = "circle 0 0 10 1 2";
        handler.HandleCommand(cmd1, output);
        
        std::string cmd2 = "line 0 0 3 4 5";
        handler.HandleCommand(cmd2, output);
        
        output.str("");
        output.clear();
        
        std::string findCmd = "find smallest perimeter";
        handler.HandleCommand(findCmd, output);
        
        REQUIRE(output.str().find("Line") != std::string::npos);
    }
    
    SECTION("Clearing shapes with command")
    {
        std::string cmd1 = "circle 0 0 10 1 2";
        handler.HandleCommand(cmd1, output);
        
        std::string cmd2 = "rectangle 0 0 10 20 3 4";
        handler.HandleCommand(cmd2, output);
        
        REQUIRE(storage.GetShapes().size() == 2);
        
        std::string clearCmd = "clear";
        handler.HandleCommand(clearCmd, output);
        
        REQUIRE(storage.GetShapes().empty());
    }
}

TEST_CASE("Error handling")
{
    ShapeStorage storage;
    ShapeProcessor processor;
    HandlerPaint2D handler(storage, processor);
    std::ostringstream output;

    SECTION("Circle with negative radius")
    {
        std::string command = "circle 0 0 -5 123456 654321";
        handler.HandleCommand(command, output);
        
        REQUIRE(output.str().find("Radius must be positive") != std::string::npos);
        REQUIRE(storage.GetShapes().empty());
    }

    SECTION("Rectangle with zero dimensions")
    {
        std::string command = "rectangle 0 0 0 20 111111 222222";
        handler.HandleCommand(command, output);
        
        REQUIRE(output.str().find("Width and height must be positive") != std::string::npos);
        REQUIRE(storage.GetShapes().empty());
    }

    SECTION("Invalid command format")
    {
        std::string command = "circle 0 0 10";
        handler.HandleCommand(command, output);
        
        REQUIRE(output.str().find("Invalid parameters") != std::string::npos);
        REQUIRE(storage.GetShapes().empty());
    }
}

TEST_CASE("Shape drawing")
{
    SECTION("Circle drawing") 
    {
        Mock<ICanvas> mockCanvas;
        
        Fake(Method(mockCanvas, DrawCircle));
        Fake(Method(mockCanvas, FillCircle));
        
        Circle circle(100, 200, 50, 0xFF0000, 0x00FF00);
        circle.Draw(mockCanvas.get());
        
        Verify(Method(mockCanvas, DrawCircle).Matching([](Point p, double r, std::uint32_t c) {
            return p.GetX() == 100 && p.GetY() == 200 && r == 50 && c == 0xFF0000;
        })).Once();
        
        Verify(Method(mockCanvas, FillCircle).Matching([](Point p, double r, std::uint32_t c) {
            return p.GetX() == 100 && p.GetY() == 200 && r == 50 && c == 0x00FF00;
        })).Once();
    }
    
    SECTION("Rectangle drawing")
    {
        Mock<ICanvas> mockCanvas;
        Fake(Method(mockCanvas, DrawRectangle));
        Fake(Method(mockCanvas, FillRectangle));
        
        Rectangle rect(10, 20, 30, 40, 0x112233, 0x445566);
        rect.Draw(mockCanvas.get());
        
        Verify(Method(mockCanvas, DrawRectangle).Matching([](Point p, double w, double h, std::uint32_t c) {
            return p.GetX() == 10 && p.GetY() == 20 && w == 30 && h == 40 && c == 0x112233;
        })).Once();
        
        Verify(Method(mockCanvas, FillRectangle).Matching([](Point p, double w, double h, std::uint32_t c) {
            return p.GetX() == 10 && p.GetY() == 20 && w == 30 && h == 40 && c == 0x445566;
        })).Once();
    }
    
    SECTION("LineSegment drawing")
    {
        Mock<ICanvas> mockCanvas;
        Fake(Method(mockCanvas, DrawLine));
        
        LineSegment line(Point(10, 20), Point(30, 40), 0xABCDEF);
        line.Draw(mockCanvas.get());
        
        Verify(Method(mockCanvas, DrawLine).Matching([](Point from, Point to, std::uint32_t c) {
            return from.GetX() == 10 && from.GetY() == 20 && 
                   to.GetX() == 30 && to.GetY() == 40 && 
                   c == 0xABCDEF;
        })).Once();
    }
    
    SECTION("Triangle drawing")
    {
        Mock<ICanvas> mockCanvas;
        Fake(Method(mockCanvas, DrawTriangle));
        Fake(Method(mockCanvas, FillTriangle));
        
        Triangle triangle(10, 20, 30, 40, 50, 60, 0x111111, 0x222222);
        triangle.Draw(mockCanvas.get());
        
        Verify(Method(mockCanvas, DrawTriangle)).Once();
        Verify(Method(mockCanvas, FillTriangle)).Once();
    }
}
