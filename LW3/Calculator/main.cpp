#include <iostream>
#include "Calculator.h"
#include "HandleCalculator.h"

int main()
{
    Calculator calc;
    HandleCalculator handler(calc);
    std::string command;
    
    while (std::getline(std::cin, command))
    {
        handler.HandleCommand(command, std::cout);
    }
    
    return 0;
}
