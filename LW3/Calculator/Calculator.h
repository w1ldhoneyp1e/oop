#pragma once
#include <string>
#include <map>
#include <iostream>
#include <stdexcept>

class Calculator
{
public:
    void HandleCommand(const std::string& command, std::ostream& output = std::cout);

private:
    void HandleVar(std::istringstream& iss);
    void HandleLet(std::istringstream& iss);
    void HandlePrint(std::istringstream& iss, std::ostream& output);
    bool ValidateIdentifier(const std::string& identifier) const;

    std::map<std::string, double> m_variables;
}; 