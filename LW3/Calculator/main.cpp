#include <iostream>
#include "Calculator.h"

int main()
{
    Calculator calc;
    std::string command;
    while (std::getline(std::cin, command))
    {
        calc.HandleCommand(command, std::cout);
    }
    return 0;
}
