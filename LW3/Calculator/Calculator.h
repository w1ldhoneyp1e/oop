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
    bool ValidateIdentifier(const std::string& identifier) const;
    bool IdentifierExists(const std::string& identifier) const;
    static std::string RemoveSpaces(const std::string& str);

    std::map<std::string, Variable> m_variables;
    std::map<std::string, Function> m_functions;
}; 