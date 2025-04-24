#include <iostream>
#include "Calculator.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

void Calculator::HandleCommand(const std::string& command, std::ostream& output)
{
    try
    {
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "var")
        {
            HandleVar(iss);
        }
        else if (cmd == "let")
        {
            HandleLet(iss);
        }
        else if (cmd == "print")
        {
            HandlePrint(iss, output);
        }
        else
        {
            throw std::invalid_argument("Unknown command");
        }
    }
    catch (const std::invalid_argument& e)
    {
        output << e.what() << "\n";
    }
}

void Calculator::HandleVar(std::istringstream& iss)
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

void Calculator::HandleLet(std::istringstream& iss)
{
    std::string identifier, equals;
    iss >> identifier;

    if (!ValidateIdentifier(identifier))
    {
        throw std::invalid_argument("Invalid usage");
    }

    iss >> equals;
    if (equals != "=")
    {
        throw std::invalid_argument("Invalid usage");
    }

    std::string value;
    iss >> value;

    try
    {
        double numValue = std::stod(value);
        m_variables[identifier] = numValue;
    }
    catch (const std::invalid_argument&)
    {
        if (!ValidateIdentifier(value))
        {
            throw std::invalid_argument("Invalid usage");
        }

        auto it = m_variables.find(value);
        if (it == m_variables.end())
        {
            throw std::invalid_argument("Name does not exist");
        }

        m_variables[identifier] = it->second;
    }
}

void Calculator::HandlePrint(std::istringstream& iss, std::ostream& output)
{
    std::string identifier;
    iss >> identifier;

    auto it = m_variables.find(identifier);
    if (it == m_variables.end())
    {
        throw std::invalid_argument("Name does not exist");
    }

    output << std::fixed << std::setprecision(2);
    if (std::isnan(it->second))
    {
        output << "nan\n";
    }
    else
    {
        output << it->second << "\n";
    }
}

bool Calculator::ValidateIdentifier(const std::string& identifier) const
{
    if (identifier.empty() || std::isdigit(identifier[0]))
        return false;

    return std::all_of(identifier.begin(), identifier.end(), 
        [](char c) { return std::isalnum(c) || c == '_'; });
}
