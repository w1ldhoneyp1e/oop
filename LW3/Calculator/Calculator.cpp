#include <iostream>
#include "Calculator.h"
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cmath>

Variable& Calculator::GetOrCreateVariable(const std::string& identifier)
{
    if (m_variables.find(identifier) == m_variables.end())
    {
        m_variables.emplace(identifier, Variable(identifier));
    }
    return m_variables.at(identifier);
}

void Calculator::CheckIdentifierValidation(const std::string& identifier) const
{
    if (identifier.empty() || std::isdigit(identifier[0]))
    {
        throw std::invalid_argument("Invalid usage");
    }

    if (!std::all_of(identifier.begin(), identifier.end(), 
        [](char c) { 
            return std::isalpha(c) || 
                   std::isdigit(c) || 
                   c == '_'; 
        }))
    {
        throw std::invalid_argument("Invalid usage");
    }
}

void Calculator::CheckIdentifierExistance(const std::string& identifier) const
{
    if (m_variables.find(identifier) != m_variables.end() ||
        m_functions.find(identifier) != m_functions.end())
    {
        throw std::invalid_argument("Name already exists");
    }
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

std::map<std::string, Variable>::const_iterator Calculator::TryFindVariable(const std::string& identifier) const
{
    auto it = m_variables.find(identifier);
    if (it == m_variables.end())
    {
        throw std::invalid_argument("Name does not exist");
    }
    return it;
}

void Calculator::PrintValue(std::ostream& output, const std::string& name, double value)
{
    if (std::isnan(value))
    {
        output << "nan";
    }
    else
    {
        output << value;
    }
    output << "\n";
}

void Calculator::DeclareVariable(const std::string& identifier)
{
    CheckIdentifierValidation(identifier);
    CheckIdentifierExistance(identifier);
    m_variables.emplace(identifier, Variable(identifier));
}

void Calculator::AssignVariable(const std::string& identifier, const std::string& value)
{
    CheckIdentifierValidation(identifier);

    try
    {
        double numValue = std::stod(value);
        GetOrCreateVariable(identifier).SetValue(numValue);
    }
    catch (const std::invalid_argument&)
    {
        CheckIdentifierValidation(value);
        auto it = TryFindVariable(value);
        GetOrCreateVariable(identifier).SetValue(it->second.GetValue());
    }
}

void Calculator::DeclareFunction(const std::string& identifier, const std::string& expression)
{
    CheckIdentifierValidation(identifier);
    CheckIdentifierExistance(identifier);

    std::string cleanExpression = RemoveSpaces(expression);
    size_t operatorPos = cleanExpression.find_first_of("+-*/");

    if (operatorPos == std::string::npos)
    {
        CheckIdentifierValidation(cleanExpression);
        const auto variable = m_variables.find(cleanExpression);
        if (variable == m_variables.end())
        {
            throw std::invalid_argument("Name does not exist");
        }
        m_functions.emplace(identifier, Function(identifier, &variable->second));
    }
    else
    {
        std::string left = cleanExpression.substr(0, operatorPos);
        std::string right = cleanExpression.substr(operatorPos + 1);

        CheckIdentifierValidation(left);
        CheckIdentifierValidation(right);
        const auto leftOp = m_variables.find(left);
        const auto rightOp = m_variables.find(right);
        if (leftOp == m_variables.end() || rightOp == m_variables.end())
        {
            throw std::invalid_argument("Name does not exist");
        }

        m_functions.emplace(
            identifier,
            Function(identifier, &leftOp->second, &rightOp->second, cleanExpression[operatorPos])
        );
    }
}

void Calculator::PrintIdentifier(const std::string& identifier, std::ostream& output)
{
    output << std::fixed << std::setprecision(2);

    auto varIt = m_variables.find(identifier);
    if (varIt != m_variables.end())
    {
        PrintValue(output, identifier, varIt->second.GetValue());
        return;
    }

    auto funcIt = m_functions.find(identifier);
    if (funcIt != m_functions.end())
    {
        PrintValue(output, identifier, funcIt->second.Evaluate());
        return;
    }

    throw std::invalid_argument("Name does not exist");
}

void Calculator::PrintAllVariables(std::ostream& output)
{
    output << std::fixed << std::setprecision(2);
    for (const auto& [name, var] : m_variables)
    {
        output << name << ":";
        PrintValue(output, name, var.GetValue());
    }
}

void Calculator::PrintAllFunctions(std::ostream& output)
{
    output << std::fixed << std::setprecision(2);
    for (const auto& [name, func] : m_functions)
    {
        output << name << ":";
        PrintValue(output, name, func.Evaluate());
    }
}
