#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "ArraySum.h"
#include <string>
#include <vector>

TEST_CASE("for different types")
{
    SECTION("integers")
    {
        std::vector<int> integers = {1, 2, 3, 4, 5};
        REQUIRE(ArraySum(integers) == 15);
    }

    SECTION("doubles")
    {
        std::vector<double> doubles = {1.1, 2.2, 3.3};
        REQUIRE(ArraySum(doubles) == 6.6);
    }

    SECTION("strings")
    {
        std::vector<std::string> strings = {"a", "b", "c"};
        REQUIRE(ArraySum(strings) == "abc");
    }
}

TEST_CASE("handles edge cases")
{
    SECTION("empty vector of integers")
    {
        std::vector<int> emptyIntegers;
        REQUIRE(ArraySum(emptyIntegers) == 0);
    }

    SECTION("empty vector of strings")
    {
        std::vector<std::string> emptyStrings;
        REQUIRE(ArraySum(emptyStrings) == "");
    }

    SECTION("single-element vector")
    {
        std::vector<int> singleElement = {42};
        REQUIRE(ArraySum(singleElement) == 42);
    }

    SECTION("vector with negative numbers")
    {
        std::vector<int> negatives = {-1, -2, 3};
        REQUIRE(ArraySum(negatives) == 0);
    }
} 