#pragma once
#include <string>
#include <map>
#include "Variable.h"

class Function 
{
public:
    Function() = default;
    Function(const std::string& name, const std::string& leftOperand);
    Function(const std::string& name, const std::string& leftOperand, 
             const std::string& rightOperand, char operation);

    double Evaluate(const std::map<std::string, Variable>& variables) const;
    const std::string& GetName() const { return m_name; }

private:
    std::string m_name;
    std::string m_leftOperand;
    std::string m_rightOperand;
    char m_operation;
    bool m_isSingleOperand;
}; 