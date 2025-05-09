#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "HandlerPaint2D.h"
#include <sstream>

TEST_CASE("Adding shapes")
{
    HandlerPaint2D handler;
    std::stringstream input;
    std::stringstream output;

    SECTION("Adding circle")
    {
        input << "circle 0 0 10 123456 654321\n";
        handler.HandleCommand(input, output);
        auto& shapes = handler.GetStorage().GetShapes();
        REQUIRE(shapes.size() == 1);
        REQUIRE(shapes[0]->ToString().find("Circle") != std::string::npos);
    }

    SECTION("Adding rectangle")
    {
        input << "rectangle 0 0 10 20 111111 222222\n";
        handler.HandleCommand(input, output);
        auto& shapes = handler.GetStorage().GetShapes();
        REQUIRE(shapes.size() == 1);
        REQUIRE(shapes[0]->ToString().find("Rectangle") != std::string::npos);
    }

    SECTION("Adding triangle")
    {
        input << "triangle 0 0 1 0 0 1 333333 444444\n";
        handler.HandleCommand(input, output);
        auto& shapes = handler.GetStorage().GetShapes();
        REQUIRE(shapes.size() == 1);
        REQUIRE(shapes[0]->ToString().find("Triangle") != std::string::npos);
    }

    SECTION("Adding line segment")
    {
        input << "line 0 0 1 1 555555\n";
        handler.HandleCommand(input, output);
        auto& shapes = handler.GetStorage().GetShapes();
        REQUIRE(shapes.size() == 1);
        REQUIRE(shapes[0]->ToString().find("Line Segment") != std::string::npos);
    }
}

TEST_CASE("Finding shapes with maximum area and minimum perimeter")
{
    HandlerPaint2D handler;
    std::stringstream input;
    std::stringstream output;

    input << "circle 0 0 10 1 2\n";
    input << "rectangle 0 0 10 20 3 4\n";
    input << "triangle 0 0 1 0 0 1 5 6\n";
    input << "line 0 0 1 1 7\n";
    handler.HandleCommand(input, output);

    SECTION("find biggest area")
    {
        std::stringstream findInput("find biggest area\n");
        handler.HandleCommand(findInput, output);
        std::string result = output.str();
        REQUIRE(result.find("Circle") != std::string::npos);
    }

    SECTION("find smallest perimeter")
    {
        std::stringstream findInput("find smallest perimeter\n");
        handler.HandleCommand(findInput, output);
        std::string result = output.str();
        bool foundLine = result.find("Line Segment") != std::string::npos;
        bool foundTriangle = result.find("Triangle") != std::string::npos;
        if (!foundLine && !foundTriangle) {
            INFO("result: " << result);
            FAIL("Line Segment and Triangle not found");
        }
    }
}

TEST_CASE("Clearing shapes")
{
    HandlerPaint2D handler;
    std::stringstream input;
    std::stringstream output;

    input << "circle 0 0 10 1 2\n";
    input << "rectangle 0 0 10 20 3 4\n";
    handler.HandleCommand(input, output);

    REQUIRE(handler.GetStorage().GetShapes().size() == 2);

    std::stringstream clearInput("clear\n");
    handler.HandleCommand(clearInput, output);

    REQUIRE(handler.GetStorage().GetShapes().empty());
}

TEST_CASE("Negative cases for adding shapes")
{
    HandlerPaint2D handler;
    std::stringstream input;
    std::stringstream output;

    SECTION("Circle with negative radius")
    {
        input << "circle 0 0 -5 123456 654321\n";
        handler.HandleCommand(input, output);
        REQUIRE(output.str().find("Radius must be positive") != std::string::npos);
    }

    SECTION("Circle with missing parameters")
    {
        input << "circle 0 0 10 123456\n";
        handler.HandleCommand(input, output);
        REQUIRE(output.str().find("Invalid parameters for circle") != std::string::npos);
    }

    SECTION("Rectangle with zero width")
    {
        input << "rectangle 0 0 0 20 111111 222222\n";
        handler.HandleCommand(input, output);
        REQUIRE(output.str().find("Width and height must be positive") != std::string::npos);
    }

    SECTION("Rectangle with missing parameters")
    {
        input << "rectangle 0 0 10 20 111111\n";
        handler.HandleCommand(input, output);
        REQUIRE(output.str().find("Invalid parameters for rectangle") != std::string::npos);
    }

    SECTION("Triangle with missing parameters")
    {
        input << "triangle 0 0 1 0 0 1 333333\n";
        handler.HandleCommand(input, output);
        REQUIRE(output.str().find("Invalid parameters for triangle") != std::string::npos);
    }

    SECTION("Line with missing parameters")
    {
        input << "line 0 0 1 1\n";
        handler.HandleCommand(input, output);
        REQUIRE(output.str().find("Invalid parameters for line") != std::string::npos);
    }
}
