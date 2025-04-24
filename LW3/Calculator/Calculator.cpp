#include <iostream>
#include "Calculator.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

void Calculator::HandleCommand(const std::string& command, std::ostream& output)
{
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "var")
    {
        std::string identifier;
        iss >> identifier;
        
        if (!ValidateIdentifier(identifier))
        {
            throw std::invalid_argument("Invalid usage");
        }

        if (m_variables.find(identifier) != m_variables.end())
        {
            throw std::invalid_argument("Name already exists");
        }

        m_variables[identifier] = std::nan("");
    }
}

bool Calculator::ValidateIdentifier(const std::string& identifier) const
{
    if (identifier.empty() || std::isdigit(identifier[0]))
        return false;

    return std::all_of(identifier.begin(), identifier.end(), 
        [](char c) { return std::isalnum(c) || c == '_'; });
}
