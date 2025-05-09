#include "Function.h"
#include <cmath>

Function::Function(const std::string& name, const Variable* leftOperand)
    : m_name(name)
    , m_leftOperand(leftOperand)
    , m_rightOperand(nullptr)
    , m_operation('\0')
{
}

Function::Function(const std::string& name, const Variable* leftOperand,
                  const Variable* rightOperand, char operation)
    : m_name(name)
    , m_leftOperand(leftOperand)
    , m_rightOperand(rightOperand)
    , m_operation(operation)
{
}

double Function::Evaluate() const // Хранить вместо названий ссылки на left и right. Поправить схему после изменений DONE
{
    if (m_rightOperand == nullptr)
    {
        return m_leftOperand->GetValue();
    }

    double left = m_leftOperand->GetValue();
    double right = m_rightOperand->GetValue();

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