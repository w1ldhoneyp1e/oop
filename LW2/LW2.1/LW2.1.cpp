#include "LW2.1_functions.h"
#include <iostream>

int main() 
{
    try 
    {
        std::vector<double> numbers;
        ReadNumbers(numbers);
        ProcessNumbers(numbers);
        PrintSortedNumbers(numbers);
    } 
    catch (const std::exception& e) 
    {
        std::cout << "ERROR" << std::endl;
    }

    return 0;
}