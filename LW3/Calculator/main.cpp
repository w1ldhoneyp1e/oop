#include <iostream>
#include "Calculator.h"

int main()
{
    Calculator calc;
    std::string command;
    while (std::getline(std::cin, command))
    {
        try
        {
            calc.HandleCommand(command, std::cout);
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    return 0;
}
