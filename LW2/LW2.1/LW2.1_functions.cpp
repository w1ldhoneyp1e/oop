#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <sstream>
#include <functional>

void ReadNumbers(std::vector<double>& numbers)
{
    std::string line;

    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        std::string word;
        
        while (iss >> word)
        {
            bool hasDecimalPoint = false;
            for (size_t i = 0; i < word.length(); i++)
            {
                char c = word[i];
                if (c == '-' && i == 0) continue;
                if (c == '.' && !hasDecimalPoint)
                {
                    hasDecimalPoint = true;
                    continue;
                }
                if (!std::isdigit(c))
                {
                    throw std::invalid_argument("Non-numeric");
                }
            }

            try {
                numbers.push_back(std::stod(word));
            }
            catch (...) {
                throw std::invalid_argument("Non-numeric");
            }
        }
    }
}

double SumIfPositive(double acc, double val)
{
    return val > 0 ? acc + val : acc;
}

bool IsPositive(double val)
{
    return val > 0;
}

void ProcessNumbers(std::vector<double>& numbers)
{
    if (numbers.empty()) return;

    double sum = std::accumulate(numbers.begin(), numbers.end(), 0.0, SumIfPositive);

    int positive_count = std::count_if(numbers.begin(), numbers.end(), IsPositive);

    if (positive_count > 0)
    {
        double average = sum / positive_count;
        auto addAverageToNumber = [average](double val) {
            return val + average;
            };
        std::transform(numbers.begin(), numbers.end(), numbers.begin(), addAverageToNumber);
    }
}

void PrintSortedNumbers(const std::vector<double>& numbers)
{
    std::vector<double> sorted_numbers = numbers;
    std::sort(sorted_numbers.begin(), sorted_numbers.end());

    std::cout << std::fixed << std::setprecision(3);
    for (size_t i = 0; i < sorted_numbers.size(); ++i)
    {
        std::cout << sorted_numbers[i];
        if (i < sorted_numbers.size() - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}