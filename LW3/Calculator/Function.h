#pragma once
#include <string>
#include <map>
#include "Variable.h"
#include <optional>

class Function // Заменил указатели на ссылки
{
public:
    Function() = default;
    Function(const std::string& name, const Variable& leftOperand);
    Function(const std::string& name, const Variable& leftOperand,
             const Variable& rightOperand, char operation);

    double Evaluate() const;

private:
    std::string m_name;
    const Variable& m_leftOperand;
    const std::optional<std::reference_wrapper<const Variable>> m_rightOperand;
    char m_operation;
}; 