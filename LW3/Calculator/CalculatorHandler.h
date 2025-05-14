#pragma once
#include <string>
#include <sstream>
#include <map>
#include <functional>
#include "Calculator.h"

class CalculatorHandler
{
public:
    explicit CalculatorHandler(Calculator& calculator);
    void HandleCommand(const std::string& command, std::ostream& output = std::cout);

private:
    void HandleVar(std::istringstream& iss);
    void HandleLet(std::istringstream& iss);
    void HandleFn(std::istringstream& iss);
    void HandlePrint(std::istringstream& iss, std::ostream& output);
    void HandlePrintVars(std::ostream& output);
    void HandlePrintFns(std::ostream& output);

    Calculator& m_calculator;
    
    using CommandHandler = std::function<void(std::istringstream&, std::ostream&)>;
    std::map<std::string, CommandHandler> m_commandHandlers;
};

