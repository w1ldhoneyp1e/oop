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
        else if (cmd == "fn")
        {
            HandleFn(iss);
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

    if (IdentifierExists(identifier))
    {
        throw std::invalid_argument("Name already exists");
    }

    m_variables.emplace(identifier, Variable(identifier));
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
        if (m_variables.find(identifier) == m_variables.end())
        {
            m_variables.emplace(identifier, Variable(identifier));
        }
        m_variables.at(identifier).SetValue(numValue);
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

        if (m_variables.find(identifier) == m_variables.end())
        {
            m_variables.emplace(identifier, Variable(identifier));
        }
        m_variables.at(identifier).SetValue(it->second.GetValue());
    }
}

void Calculator::HandleFn(std::istringstream& iss)
{
    std::string identifier, equals;
    iss >> identifier;

    if (!ValidateIdentifier(identifier))
    {
        throw std::invalid_argument("Invalid usage");
    }

    if (IdentifierExists(identifier))
    {
        throw std::invalid_argument("Name already exists");
    }

    iss >> equals;
    if (equals != "=")
    {
        throw std::invalid_argument("Invalid usage");
    }

    std::string expression;
    std::getline(iss >> std::ws, expression);
    expression = RemoveSpaces(expression);

    size_t operatorPos = expression.find_first_of("+-*/");
    
    if (operatorPos == std::string::npos)
    {
        if (!ValidateIdentifier(expression))
        {
            throw std::invalid_argument("Invalid usage");
        }
        if (m_variables.find(expression) == m_variables.end())
        {
            throw std::invalid_argument("Name does not exist");
        }
        m_functions.emplace(identifier, Function(identifier, expression));
    }
    else
    {
        std::string left = expression.substr(0, operatorPos);
        std::string right = expression.substr(operatorPos + 1);
        
        if (!ValidateIdentifier(left) || !ValidateIdentifier(right))
        {
            throw std::invalid_argument("Invalid usage");
        }
        if (m_variables.find(left) == m_variables.end() || 
            m_variables.find(right) == m_variables.end())
        {
            throw std::invalid_argument("Name does not exist");
        }
        
        m_functions.emplace(identifier, 
            Function(identifier, left, right, expression[operatorPos]));
    }
}

void Calculator::HandlePrint(std::istringstream& iss, std::ostream& output)
{
    std::string identifier;
    iss >> identifier;

    output << std::fixed << std::setprecision(2);

    auto varIt = m_variables.find(identifier);
    if (varIt != m_variables.end())
    {
        double value = varIt->second.GetValue();
        if (std::isnan(value))
        {
            output << "nan\n";
        }
        else
        {
            output << value << "\n";
        }
        return;
    }

    auto funcIt = m_functions.find(identifier);
    if (funcIt != m_functions.end())
    {
        double result = funcIt->second.Evaluate(m_variables);
        if (std::isnan(result))
        {
            output << "nan\n";
        }
        else
        {
            output << result << "\n";
        }
        return;
    }

    throw std::invalid_argument("Name does not exist");
}

bool Calculator::ValidateIdentifier(const std::string& identifier) const
{
    if (identifier.empty() || std::isdigit(identifier[0]))
        return false;

    return std::all_of(identifier.begin(), identifier.end(), 
        [](char c) { return std::isalnum(c) || c == '_'; });
}

bool Calculator::IdentifierExists(const std::string& identifier) const
{
    return m_variables.find(identifier) != m_variables.end() ||
           m_functions.find(identifier) != m_functions.end();
}

std::string Calculator::RemoveSpaces(const std::string& str)
{
    std::string result;
    for (char c : str)
    {
        if (!std::isspace(c))
        {
            result += c;
        }
    }
    return result;
}
