#include <catch2/catch_all.hpp>
#include "LW2.1_functions.h"
#include <iostream>
#include <sstream>

TEST_CASE("ProcessNumbers handles empty vector", "[ProcessNumbers]") 
{
    std::vector<double> numbers;
    ProcessNumbers(numbers);
    REQUIRE(numbers.empty());
}

TEST_CASE("ProcessNumbers correctly processes vector with positive numbers", "[ProcessNumbers]") 
{
    std::vector<double> numbers = {1.0, 2.0, 3.0};
    ProcessNumbers(numbers);
    
    REQUIRE(numbers[0] == Catch::Approx(3.0));
    REQUIRE(numbers[1] == Catch::Approx(4.0));
    REQUIRE(numbers[2] == Catch::Approx(5.0));
}

TEST_CASE("ProcessNumbers correctly handles negative numbers", "[ProcessNumbers]") 
{
    std::vector<double> numbers = {1.0, -2.0, 3.0};
    ProcessNumbers(numbers);
    
    REQUIRE(numbers[0] == Catch::Approx(3.0));
    REQUIRE(numbers[1] == Catch::Approx(0.0));
    REQUIRE(numbers[2] == Catch::Approx(5.0));
}

TEST_CASE("ProcessNumbers handles vector with single number", "[ProcessNumbers]") 
{
    std::vector<double> numbers = {5.0};
    ProcessNumbers(numbers);
    REQUIRE(numbers[0] == Catch::Approx(10.0));
}

TEST_CASE("ProcessNumbers handles all negative numbers", "[ProcessNumbers]") 
{
    std::vector<double> numbers = {-1.0, -2.0, -3.0};
    ProcessNumbers(numbers);

    REQUIRE(numbers[0] == Catch::Approx(-1.0));
    REQUIRE(numbers[1] == Catch::Approx(-2.0));
    REQUIRE(numbers[2] == Catch::Approx(-3.0));
}

TEST_CASE("ReadNumbers correctly reads input", "[ReadNumbers]") 
{
    std::vector<double> numbers;
    std::istringstream input("1.0 2.0\n3.0 4.0\n");
    auto oldCin = std::cin.rdbuf(input.rdbuf());
    
    ReadNumbers(numbers);
    std::cin.rdbuf(oldCin);

    REQUIRE(numbers.size() == 4);
    REQUIRE(numbers[0] == Catch::Approx(1.0));
    REQUIRE(numbers[1] == Catch::Approx(2.0));
    REQUIRE(numbers[2] == Catch::Approx(3.0));
    REQUIRE(numbers[3] == Catch::Approx(4.0));
}

TEST_CASE("ReadNumbers handles empty input", "[ReadNumbers]") 
{
    std::vector<double> numbers;
    std::istringstream input("");
    auto oldCin = std::cin.rdbuf(input.rdbuf());
    
    ReadNumbers(numbers);
    std::cin.rdbuf(oldCin);

    REQUIRE(numbers.empty());
}

TEST_CASE("ReadNumbers handles single number", "[ReadNumbers]") 
{
    std::vector<double> numbers;
    std::istringstream input("42.5");
    auto oldCin = std::cin.rdbuf(input.rdbuf());
    
    ReadNumbers(numbers);
    std::cin.rdbuf(oldCin);

    REQUIRE(numbers.size() == 1);
    REQUIRE(numbers[0] == Catch::Approx(42.5));
}

TEST_CASE("ReadNumbers throws on non-numeric input", "[ReadNumbers]") 
{
    std::vector<double> numbers;
    std::istringstream input("1.0 abc 2.0");
    auto oldCin = std::cin.rdbuf(input.rdbuf());
    
    REQUIRE_THROWS_AS(ReadNumbers(numbers), std::invalid_argument);
    std::cin.rdbuf(oldCin);
}

TEST_CASE("ReadNumbers throws on invalid number format", "[ReadNumbers]") 
{
    std::vector<double> numbers;
    std::istringstream input("1.0 2..0 3.0");
    auto oldCin = std::cin.rdbuf(input.rdbuf());
    
    REQUIRE_THROWS_AS(ReadNumbers(numbers), std::invalid_argument);
    std::cin.rdbuf(oldCin);
}

TEST_CASE("ReadNumbers handles multiple lines with spaces", "[ReadNumbers]") 
{
    std::vector<double> numbers;
    std::istringstream input("1.0  2.0\n  3.0\n4.0  \n");
    auto oldCin = std::cin.rdbuf(input.rdbuf());
    
    ReadNumbers(numbers);
    std::cin.rdbuf(oldCin);

    REQUIRE(numbers.size() == 4);
    REQUIRE(numbers[0] == Catch::Approx(1.0));
    REQUIRE(numbers[1] == Catch::Approx(2.0));
    REQUIRE(numbers[2] == Catch::Approx(3.0));
    REQUIRE(numbers[3] == Catch::Approx(4.0));
}

TEST_CASE("ReadNumbers throws on comma in number", "[ReadNumbers]") 
{
    std::vector<double> numbers;
    std::istringstream input("1.0 2,0 3.0");
    auto oldCin = std::cin.rdbuf(input.rdbuf());
    
    REQUIRE_THROWS_AS(ReadNumbers(numbers), std::invalid_argument);
    std::cin.rdbuf(oldCin);
}

TEST_CASE("ReadNumbers throws on comma and dot in number", "[ReadNumbers]") 
{
    std::vector<double> numbers;
    std::istringstream input("1.0 2.,0 3.0");
    auto oldCin = std::cin.rdbuf(input.rdbuf());
    
    REQUIRE_THROWS_AS(ReadNumbers(numbers), std::invalid_argument);
    std::cin.rdbuf(oldCin);
}