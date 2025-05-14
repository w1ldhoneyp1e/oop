#include "CalculatorHandler.h" // Поменял название
#include <sstream>

CalculatorHandler::CalculatorHandler(Calculator& calculator)
    : m_calculator(calculator)
{
    m_commandHandlers = {
        { "var", [this](std::istringstream& iss, std::ostream&) { HandleVar(iss); } },
        { "let", [this](std::istringstream& iss, std::ostream&) { HandleLet(iss); } },
        { "fn", [this](std::istringstream& iss, std::ostream&) { HandleFn(iss); } },
        { "print", [this](std::istringstream& iss, std::ostream& output) { HandlePrint(iss, output); } },
        { "printvars", [this](std::istringstream&, std::ostream& output) { HandlePrintVars(output); } },
        { "printfns", [this](std::istringstream&, std::ostream& output) { HandlePrintFns(output); } }
    };
}

void CalculatorHandler::HandleCommand(const std::string& command, std::ostream& output)
{
    try
    {
        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        auto handlerIt = m_commandHandlers.find(cmd);
        if (handlerIt != m_commandHandlers.end()) 
        {
            handlerIt->second(iss, output);
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

void CalculatorHandler::HandleVar(std::istringstream& iss)
{
    std::string identifier;
    iss >> identifier;
    m_calculator.DeclareVariable(identifier);
}

void CalculatorHandler::HandleLet(std::istringstream& iss)
{
    std::string identifier;
    std::getline(iss, identifier, '=');
    identifier = m_calculator.RemoveSpaces(identifier);

    std::string value;
    iss >> value;
    m_calculator.AssignVariable(identifier, value);
}

void CalculatorHandler::HandleFn(std::istringstream& iss)
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

void CalculatorHandler::HandlePrint(std::istringstream& iss, std::ostream& output)
{
    std::string identifier;
    iss >> identifier;
    m_calculator.PrintIdentifier(identifier, output);
}

void CalculatorHandler::HandlePrintVars(std::ostream& output)
{
    m_calculator.PrintAllVariables(output);
}

void CalculatorHandler::HandlePrintFns(std::ostream& output)
{
    m_calculator.PrintAllFunctions(output);
}
