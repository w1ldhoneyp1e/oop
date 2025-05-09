#pragma once
#include <string>
#include <map>
#include "Variable.h"

class Function 
{
public:
    Function() = default;
    Function(const std::string& name, const Variable* leftOperand);
    Function(const std::string& name, const Variable* leftOperand,
             const Variable* rightOperand, char operation);

    double Evaluate() const;

private:
    std::string m_name;
    const Variable* m_leftOperand;
    const Variable* m_rightOperand;
    char m_operation;
}; 