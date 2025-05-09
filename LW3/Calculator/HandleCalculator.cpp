#include "HandleCalculator.h"
#include <sstream>

HandleCalculator::HandleCalculator(Calculator& calculator)
    : m_calculator(calculator)
{
}

void HandleCalculator::HandleCommand(const std::string& command, std::ostream& output)
{
    try
    {
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "var")
        {
            HandleVar(iss);
        }
        else if (cmd == "let")
        {
            HandleLet(iss);
        }
        else if (cmd == "fn")
        {
            HandleFn(iss);
        }
        else if (cmd == "print")
        {
            HandlePrint(iss, output);
        }
        else if (cmd == "printvars")
        {
            HandlePrintVars(output);
        }
        else if (cmd == "printfns")
        {
            HandlePrintFns(output);
        }
        else
        {
            throw std::invalid_argument("Unknown command");
        }
    }
    catch (const std::invalid_argument& e)
    {
        output << e.what() << "\n";
    }
}

void HandleCalculator::HandleVar(std::istringstream& iss)
{
    std::string identifier;
    iss >> identifier;
    m_calculator.DeclareVariable(identifier);
}

void HandleCalculator::HandleLet(std::istringstream& iss)
{
    std::string identifier;
    std::getline(iss, identifier, '=');
    identifier = m_calculator.RemoveSpaces(identifier);

    std::string value;
    iss >> value;
    m_calculator.AssignVariable(identifier, value);
}

void HandleCalculator::HandleFn(std::istringstream& iss)
{
    std::string identifier, equals;
    iss >> identifier;

    iss >> equals;
    if (equals != "=")
    {
        throw std::invalid_argument("Invalid usage");
    }

    std::string expression;
    std::getline(iss >> std::ws, expression);
    m_calculator.DeclareFunction(identifier, expression);
}

void HandleCalculator::HandlePrint(std::istringstream& iss, std::ostream& output)
{
    std::string identifier;
    iss >> identifier;
    m_calculator.PrintIdentifier(identifier, output);
}

void HandleCalculator::HandlePrintVars(std::ostream& output)
{
    m_calculator.PrintAllVariables(output);
}

void HandleCalculator::HandlePrintFns(std::ostream& output)
{
    m_calculator.PrintAllFunctions(output);
}
