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
    void HandleCommand(const std::string& command, std::ostream& output = std::cout);

private:
    void HandleVar(std::istringstream& iss);
    void HandleLet(std::istringstream& iss);
    void HandleFn(std::istringstream& iss);
    void HandlePrint(std::istringstream& iss, std::ostream& output);
    void CheckIdentifierValidation(const std::string& identifier) const;
    void CheckIdentifierExistance(const std::string& identifier) const;
    static std::string RemoveSpaces(const std::string& str);
    Variable& GetOrCreateVariable(const std::string& identifier);
    void HandleFnAssignment(std::istringstream& iss, const std::string& expression, const std::string& identifier);
    void HandleFnEvaluation(const std::string& expression, const std::string& identifier, size_t operatorPos);
    std::map<std::string, Variable>::const_iterator TryFindVariable(const std::string& identifier) const;

    std::map<std::string, Variable> m_variables;
    std::map<std::string, Function> m_functions;
}; 