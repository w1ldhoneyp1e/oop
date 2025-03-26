#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "PrimeNumberSetGenerator.hpp"

TEST_CASE("GeneratePrimeNumbersSet handles invalid input", "[primes]")
{
    REQUIRE_THROWS_WITH(GeneratePrimeNumbersSet(0), ERR_OUT_OF_RANGE);
    REQUIRE_THROWS_WITH(GeneratePrimeNumbersSet(-1), ERR_OUT_OF_RANGE);
    REQUIRE_THROWS_WITH(GeneratePrimeNumbersSet(MAX_UPPER_BOUND + 1), ERR_OUT_OF_RANGE);
}

TEST_CASE("GeneratePrimeNumbersSet generates correct sets", "[primes]")
{
    SECTION("Small numbers")
    {
        auto primes = GeneratePrimeNumbersSet(10);
        std::set<int> expected = {2, 3, 5, 7};
        REQUIRE(primes == expected);
    }

    SECTION("Larger set")
    {
        auto primes = GeneratePrimeNumbersSet(20);
        std::set<int> expected = {2, 3, 5, 7, 11, 13, 17, 19};
        REQUIRE(primes == expected);
    }

    SECTION("Count of primes up to 100")
    {
        auto primes = GeneratePrimeNumbersSet(100);
        REQUIRE(primes.size() == 25);
    }

    SECTION("Count of primes up to 100000000")
    {
        auto primes = GeneratePrimeNumbersSet(100000000);
        REQUIRE(primes.size() == 5761455);
    }
}
