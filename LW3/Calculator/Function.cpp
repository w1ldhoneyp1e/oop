#include "Function.h"
#include <cmath>

Function::Function(const std::string& name, const std::string& leftOperand)
    : m_name(name)
    , m_leftOperand(leftOperand)
    , m_isSingleOperand(true)
{
}

Function::Function(const std::string& name, const std::string& leftOperand, 
                  const std::string& rightOperand, char operation)
    : m_name(name)
    , m_leftOperand(leftOperand)
    , m_rightOperand(rightOperand)
    , m_operation(operation)
    , m_isSingleOperand(false)
{
}

double Function::Evaluate(const std::map<std::string, Variable>& variables) const 
{
    if (m_isSingleOperand) 
    {
        return variables.at(m_leftOperand).GetValue();
    }

    double left = variables.at(m_leftOperand).GetValue();
    double right = variables.at(m_rightOperand).GetValue();

    if (std::isnan(left) || std::isnan(right)) 
    {
        return std::nan("");
    }

    switch (m_operation) 
    {
    case '+':
        return left + right;
    case '-':
        return left - right;
    case '*':
        return left * right;
    case '/':
        if (right == 0) 
        {
            return std::nan("");
        }
        return left / right;
    default:
        return std::nan("");
    }
} 