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
    void Info();
    void TurnOn();
    void TurnOff();
    void SetGear(std::istream& args);
    void SetSpeed(std::istream& args);

    std::string GetDirectionAsString();
    std::string GetGearAsString();

private:
    Car& car;
    std::istream& input;
    std::ostream& output;

    using Handler = std::function<void(std::istream& args)>;
    using ActionMap = std::map<std::string, Handler>;
    const ActionMap actionMap;
};

