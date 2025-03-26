#include "PrimeNumberSetGenerator.hpp"
#include <vector>
#include <stdexcept>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
    if (upperBound <= 0 || upperBound > MAX_UPPER_BOUND)
    {
        throw std::out_of_range(ERR_OUT_OF_RANGE);
    }

    std::vector<bool> isPrime((upperBound - 1) / 2, true);
    std::set<int> primes;
    
    if (upperBound >= 2)
    {
        primes.insert(2);
    }

    for (int i = 3; i * i <= upperBound; i += 2)
    {
        if (isPrime[i/2 - 1])
        {
            for (int j = i * i; j <= upperBound; j += 2 * i)
            {
                isPrime[j/2 - 1] = false;
            }
        }
    }

    for (int i = 3; i <= upperBound; i += 2)
    {
        if (isPrime[i/2 - 1])
        {
            primes.insert(i);
        }
    }

    return primes;
}
