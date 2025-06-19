#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "PrimeNumberSetGenerator.h"

TEST_CASE("GeneratePrimeNumbersSet handles invalid input", "[primes]")
{
    REQUIRE_THROWS_WITH(GeneratePrimeNumbersSet(0), ERR_OUT_OF_RANGE);
    REQUIRE_THROWS_WITH(GeneratePrimeNumbersSet(-1), ERR_OUT_OF_RANGE);
    REQUIRE_THROWS_WITH(GeneratePrimeNumbersSet(MAX_UPPER_BOUND + 1), ERR_OUT_OF_RANGE);
}

TEST_CASE("GeneratePrimeNumbersSet generates correct sets", "[primes]")
{
    SECTION("10")
    {
        auto primes = GeneratePrimeNumbersSet(10);
        std::set<int> expected = {2, 3, 5, 7};
        REQUIRE(primes == expected);
    }

    SECTION("100")
    {
        auto primes = GeneratePrimeNumbersSet(100);
        REQUIRE(primes.size() == 25);
    }

    SECTION("Boundary cases")
    {
        auto primes1 = GeneratePrimeNumbersSet(1);
        std::set<int> expected1 = {};
        REQUIRE(primes1 == expected1);

        auto primes2 = GeneratePrimeNumbersSet(2);
        std::set<int> expected2 = {2};
        REQUIRE(primes2 == expected2);

        auto primes3 = GeneratePrimeNumbersSet(3);
        std::set<int> expected3 = {2, 3};
        REQUIRE(primes3 == expected3);
    }

    SECTION("100000000")
    {
        auto primes = GeneratePrimeNumbersSet(100000000);
        REQUIRE(primes.size() == 5761455);
    }
}
