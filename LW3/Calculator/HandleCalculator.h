#pragma once
#include <string>
#include <sstream>
#include "Calculator.h"

class HandleCalculator
{
public:
    explicit HandleCalculator(Calculator& calculator);
    void HandleCommand(const std::string& command, std::ostream& output = std::cout);

private:
    void HandleVar(std::istringstream& iss);
    void HandleLet(std::istringstream& iss);
    void HandleFn(std::istringstream& iss);
    void HandlePrint(std::istringstream& iss, std::ostream& output);
    void HandlePrintVars(std::ostream& output);
    void HandlePrintFns(std::ostream& output);

    Calculator& m_calculator;
};

