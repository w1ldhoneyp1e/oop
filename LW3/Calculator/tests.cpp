#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "Calculator.h"
#include "HandleCalculator.h"
#include <sstream>

TEST_CASE("Variable declaration")
{
    Calculator calc;
    HandleCalculator handler(calc);
    std::stringstream output;

    SECTION("Can declare variable")
    {
        REQUIRE_NOTHROW(handler.HandleCommand("var x"));
    }

    SECTION("Cannot declare variable with invalid identifier")
    {
        handler.HandleCommand("var 1x", output);
        REQUIRE(output.str() == "Invalid usage\n");
    }

    SECTION("Cannot declare variable twice")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("var x", output);
        REQUIRE(output.str() == "Name already exists\n");
    }

    SECTION("Can initialize variable with number")
    {
        handler.HandleCommand("var x");
        REQUIRE_NOTHROW(handler.HandleCommand("let x = 42.5"));
    }

    SECTION("Can initialize variable with another variable")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("var y");
        REQUIRE_NOTHROW(handler.HandleCommand("let y = x"));
    }
}

TEST_CASE("Function declaration")
{
    Calculator calc;
    HandleCalculator handler(calc);
    std::stringstream output;

    SECTION("Can declare function with single variable")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("fn f = x");
        handler.HandleCommand("print f", output);
        REQUIRE(output.str() == "42.50\n");
    }

    SECTION("Can declare function with addition")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("var y");
        handler.HandleCommand("let y = 7.5");
        handler.HandleCommand("fn sum = x+y");
        handler.HandleCommand("print sum", output);
        REQUIRE(output.str() == "50.00\n");
    }

    SECTION("Can declare function with subtraction")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("var y");
        handler.HandleCommand("let y = 7.5");
        handler.HandleCommand("fn diff = x-y");
        handler.HandleCommand("print diff", output);
        REQUIRE(output.str() == "35.00\n");
    }

    SECTION("Can declare function with multiplication")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("var y");
        handler.HandleCommand("let y = 2");
        handler.HandleCommand("fn mult = x*y");
        handler.HandleCommand("print mult", output);
        REQUIRE(output.str() == "85.00\n");
    }

    SECTION("Can declare function with division")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("var y");
        handler.HandleCommand("let y = 2");
        handler.HandleCommand("fn div = x/y");
        handler.HandleCommand("print div", output);
        REQUIRE(output.str() == "21.25\n");
    }

    SECTION("Division by zero returns nan")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("var y");
        handler.HandleCommand("let y = 0");
        handler.HandleCommand("fn div = x/y");
        handler.HandleCommand("print div", output);
        REQUIRE(output.str() == "nan\n");
    }

    SECTION("Function with undefined variable returns nan")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("var y");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("fn sum = x+y");
        handler.HandleCommand("print sum", output);
        REQUIRE(output.str() == "nan\n");
    }

    SECTION("Cannot declare function with same name as variable")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("fn x = y", output);
        REQUIRE(output.str() == "Name already exists\n");
    }

    SECTION("Cannot declare function twice")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("fn f = x");
        handler.HandleCommand("fn f = x", output);
        REQUIRE(output.str() == "Name already exists\n");
    }

    SECTION("Function value updates when variables change")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("var y");
        handler.HandleCommand("let y = 7.5");
        handler.HandleCommand("fn sum = x+y");
        handler.HandleCommand("print sum", output);
        std::string firstResult = output.str();
        output.str("");

        handler.HandleCommand("let x = 10");
        handler.HandleCommand("print sum", output);
        REQUIRE(firstResult != output.str());
        REQUIRE(output.str() == "17.50\n");
    }
    SECTION("Handle invalid operator")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 10");
        handler.HandleCommand("var y");
        handler.HandleCommand("let y = 5");
        handler.HandleCommand("fn sum = x=y", output);
        REQUIRE(output.str() == "Invalid usage\n");
    }
}

TEST_CASE("Print commands")
{
    Calculator calc;
    HandleCalculator handler(calc);
    std::stringstream output;

    SECTION("Print undefined variable")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("print x", output);
        REQUIRE(output.str() == "nan\n");
    }

    SECTION("Print defined variable")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("print x", output);
        REQUIRE(output.str() == "42.50\n");
    }

    SECTION("Print function result")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("var y");
        handler.HandleCommand("let y = 7.5");
        handler.HandleCommand("fn sum = x + y");
        handler.HandleCommand("print sum", output);
        REQUIRE(output.str() == "50.00\n");
    }
}

TEST_CASE("Print all variables and functions")
{
    Calculator calc;
    HandleCalculator handler(calc);
    std::stringstream output;

    SECTION("Empty lists print nothing")
    {
        handler.HandleCommand("printvars", output);
        REQUIRE(output.str() == "");
        output.str("");
        handler.HandleCommand("printfns", output);
        REQUIRE(output.str() == "");
    }

    SECTION("Print all variables")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("var y");
        handler.HandleCommand("let y = 10.0");
        handler.HandleCommand("var z");
        handler.HandleCommand("printvars", output);
        REQUIRE(output.str() == "x:42.50\ny:10.00\nz:nan\n");
    }

    SECTION("Print all functions")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("var y");
        handler.HandleCommand("let y = 7.5");
        handler.HandleCommand("fn sum = x+y");
        handler.HandleCommand("fn mult = x*y");
        handler.HandleCommand("fn val = x");
        handler.HandleCommand("printfns", output);
        REQUIRE(output.str() == "mult:318.75\nsum:50.00\nval:42.50\n");
    }
}

TEST_CASE("Let command")
{
    Calculator calc;
    HandleCalculator handler(calc);
    std::stringstream output;

    SECTION("Can initialize variable with number")
    {
        handler.HandleCommand("var x");
        REQUIRE_NOTHROW(handler.HandleCommand("let x = 42.5"));
        handler.HandleCommand("print x", output);
        REQUIRE(output.str() == "42.50\n");
    }

    SECTION("Can initialize variable with another variable")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("var y");
        REQUIRE_NOTHROW(handler.HandleCommand("let y = x"));
        handler.HandleCommand("print y", output);
        REQUIRE(output.str() == "42.50\n");
    }

    SECTION("Can initialize undefined variable")
    {
        REQUIRE_NOTHROW(handler.HandleCommand("let x = 42.5"));
        handler.HandleCommand("print x", output);
        REQUIRE(output.str() == "42.50\n");
    }

    SECTION("Cannot initialize with undefined variable")
    {
        handler.HandleCommand("let x = y", output);
        REQUIRE(output.str() == "Name does not exist\n");
    }

    SECTION("Can handle spaces in expression")
    {
        handler.HandleCommand("var x");
        handler.HandleCommand("var y");
        handler.HandleCommand("let x = 42.5");
        handler.HandleCommand("let y=42.5");
        
        handler.HandleCommand("print x", output);
        std::string result1 = output.str();
        output.str("");
        output.clear();
        
        handler.HandleCommand("print y", output);
        REQUIRE(output.str() == result1);
    }
} 