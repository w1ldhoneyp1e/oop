#pragma once
#include <string>
#include <map>
#include <iostream>
#include <stdexcept>
#include "Variable.h"
#include "Function.h"

class Calculator
{
public:
    void DeclareVariable(const std::string& identifier);
    void AssignVariable(const std::string& identifier, const std::string& value);
    void DeclareFunction(const std::string& identifier, const std::string& expression);
    void PrintIdentifier(const std::string& identifier, std::ostream& output);
    void PrintAllVariables(std::ostream& output);
    void PrintAllFunctions(std::ostream& output);
    static std::string RemoveSpaces(const std::string& str);

private:
    void CheckIdentifierValidation(const std::string& identifier) const;
    void CheckIdentifierExistance(const std::string& identifier) const;
    Variable& GetOrCreateVariable(const std::string& identifier);
    std::map<std::string, Variable>::const_iterator TryFindVariable(const std::string& identifier) const;
    static void PrintValue(std::ostream& output, const std::string& name, double value);

    std::map<std::string, Variable> m_variables;
    std::map<std::string, Function> m_functions;
}; 