#pragma once
#include "Car.h"
#include <functional>
#include <map>
#include <string>

class RemoteControl
{
public:
    RemoteControl(Car& car, std::istream& input, std::ostream& output);
    void HandleCommand();

private:
    Car& m_car;
    std::istream& m_input;
    std::ostream& m_output;

    using Handler = std::function<void(int arg)>;
    enum class Command
    {
        Info,
        EngineOn,
        EngineOff,
        SetGear,
        SetSpeed,
        Unknown
    };
    using ActionMap = std::map<Command, Handler>;
    const ActionMap m_actionMap;

private:
    void Info(int);
    void TurnOn(int);
    void TurnOff(int);
    void SetGear(int gear);
    void SetSpeed(int speed);

    std::string GetDirectionAsString();
    std::string GetGearAsString();
    Command StringToCommand(std::string& command);
};
