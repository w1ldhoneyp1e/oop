#pragma once
#include <string>
#include <map>
#include <memory>
#include <iostream>

class Calculator
{
public:
    void HandleCommand(const std::string& command, std::ostream& output = std::cout);

private:
    std::map<std::string, double> m_variables;
    struct Function
    {
        std::string leftOperand;
        std::string rightOperand;
        char operation;
    };
    std::map<std::string, Function> m_functions;

    bool ValidateIdentifier(const std::string& identifier) const;
}; 