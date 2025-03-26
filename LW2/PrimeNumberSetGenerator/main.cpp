#include "PrimeNumberSetGenerator.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << ERR_INVALID_ARGS << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        int upperBound = std::stoi(argv[1]);
        auto primes = GeneratePrimeNumbersSet(upperBound);

        for (int prime : primes)
        {
            std::cout << prime << std::endl;
        }

        return EXIT_SUCCESS;
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}