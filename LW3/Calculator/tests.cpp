#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "Calculator.h"
#include <sstream>

TEST_CASE("Variable declaration and initialization")
{
    Calculator calc;
    std::stringstream output;

    SECTION("Can declare variable")
    {
        REQUIRE_NOTHROW(calc.HandleCommand("var x"));
    }

    SECTION("Cannot declare variable with invalid identifier")
    {
        calc.HandleCommand("var 1x", output);
        REQUIRE(output.str() == "Invalid usage\n");
    }

    SECTION("Cannot declare variable twice")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("var x", output);
        REQUIRE(output.str() == "Name already exists\n");
    }

    SECTION("Can initialize variable with number")
    {
        calc.HandleCommand("var x");
        REQUIRE_NOTHROW(calc.HandleCommand("let x = 42.5"));
    }

    SECTION("Can initialize variable with another variable")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("var y");
        REQUIRE_NOTHROW(calc.HandleCommand("let y = x"));
    }
}

TEST_CASE("Function declaration and evaluation")
{
    Calculator calc;
    std::stringstream output;

    SECTION("Can declare function with single variable")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("fn f = x");
        calc.HandleCommand("print f", output);
        REQUIRE(output.str() == "42.50\n");
    }

    SECTION("Can declare function with addition")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("var y");
        calc.HandleCommand("let y = 7.5");
        calc.HandleCommand("fn sum = x+y");
        calc.HandleCommand("print sum", output);
        REQUIRE(output.str() == "50.00\n");
    }

    SECTION("Can declare function with subtraction")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("var y");
        calc.HandleCommand("let y = 7.5");
        calc.HandleCommand("fn diff = x-y");
        calc.HandleCommand("print diff", output);
        REQUIRE(output.str() == "35.00\n");
    }

    SECTION("Can declare function with multiplication")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("var y");
        calc.HandleCommand("let y = 2");
        calc.HandleCommand("fn mult = x*y");
        calc.HandleCommand("print mult", output);
        REQUIRE(output.str() == "85.00\n");
    }

    SECTION("Can declare function with division")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("var y");
        calc.HandleCommand("let y = 2");
        calc.HandleCommand("fn div = x/y");
        calc.HandleCommand("print div", output);
        REQUIRE(output.str() == "21.25\n");
    }

    SECTION("Division by zero returns nan")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("var y");
        calc.HandleCommand("let y = 0");
        calc.HandleCommand("fn div = x/y");
        calc.HandleCommand("print div", output);
        REQUIRE(output.str() == "nan\n");
    }

    SECTION("Function with undefined variable returns nan")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("var y");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("fn sum = x+y");
        calc.HandleCommand("print sum", output);
        REQUIRE(output.str() == "nan\n");
    }

    SECTION("Cannot declare function with same name as variable")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("fn x = y", output);
        REQUIRE(output.str() == "Name already exists\n");
    }

    SECTION("Cannot declare function twice")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("fn f = x");
        calc.HandleCommand("fn f = x", output);
        REQUIRE(output.str() == "Name already exists\n");
    }

    SECTION("Function value updates when variables change")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("var y");
        calc.HandleCommand("let y = 7.5");
        calc.HandleCommand("fn sum = x+y");
        calc.HandleCommand("print sum", output);
        std::string firstResult = output.str();
        output.str("");

        calc.HandleCommand("let x = 10");
        calc.HandleCommand("print sum", output);
        REQUIRE(firstResult != output.str());
        REQUIRE(output.str() == "17.50\n");
    }
}

TEST_CASE("Print commands")
{
    Calculator calc;
    std::stringstream output;

    SECTION("Print undefined variable")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("print x", output);
        REQUIRE(output.str() == "nan\n");
    }

    SECTION("Print defined variable")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("print x", output);
        REQUIRE(output.str() == "42.50\n");
    }

    SECTION("Print function result")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("var y");
        calc.HandleCommand("let y = 7.5");
        calc.HandleCommand("fn sum = x + y");
        calc.HandleCommand("print sum", output);
        REQUIRE(output.str() == "50.00\n");
    }
}

TEST_CASE("Print all variables and functions")
{
    Calculator calc;
    std::stringstream output;

    SECTION("Print empty lists")
    {
        calc.HandleCommand("printvars", output);
        REQUIRE(output.str() == "");
        output.str("");
        calc.HandleCommand("printfns", output);
        REQUIRE(output.str() == "");
    }

    SECTION("Print variables")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("var y");
        calc.HandleCommand("printvars", output);
        REQUIRE(output.str() == "x:42.50\ny:nan\n");
    }

    SECTION("Print functions")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("var y");
        calc.HandleCommand("let y = 7.5");
        calc.HandleCommand("fn sum = x + y");
        calc.HandleCommand("fn diff = x - y");
        calc.HandleCommand("printfns", output);
        REQUIRE(output.str() == "diff:35.00\nsum:50.00\n");
    }
}

TEST_CASE("Let command")
{
    Calculator calc;
    std::stringstream output;

    SECTION("Can initialize variable with number")
    {
        calc.HandleCommand("var x");
        REQUIRE_NOTHROW(calc.HandleCommand("let x = 42.5"));
        calc.HandleCommand("print x", output);
        REQUIRE(output.str() == "42.50\n");
    }

    SECTION("Can initialize variable with another variable")
    {
        calc.HandleCommand("var x");
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("var y");
        REQUIRE_NOTHROW(calc.HandleCommand("let y = x"));
        calc.HandleCommand("print y", output);
        REQUIRE(output.str() == "42.50\n");
    }

    SECTION("Can initialize undefined variable")
    {
        REQUIRE_NOTHROW(calc.HandleCommand("let x = 42.5"));
        calc.HandleCommand("print x", output);
        REQUIRE(output.str() == "42.50\n");
    }

    SECTION("Cannot initialize with undefined variable")
    {
        calc.HandleCommand("let x = y", output);
        REQUIRE(output.str() == "Name does not exist\n");
    }

    SECTION("Can handle spaces in expression")
    {
        calc.HandleCommand("let x = 42.5");
        calc.HandleCommand("let y=42.5");
        calc.HandleCommand("print x", output);
        std::string result1 = output.str();
        output.str("");
        calc.HandleCommand("print y", output);
        REQUIRE(result1 == output.str());
    }
} 