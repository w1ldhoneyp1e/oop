#pragma once
#include <functional>
#include <map>
#include <string>
#include "Car.h"

class RemoteControl
{
public:
    RemoteControl(Car& car, std::istream& input, std::ostream& output);
    void HandleCommand();

private:
    Car& m_car;
    std::istream& m_input;
    std::ostream& m_output;

    using Handler = std::function<void(std::istream&)>;
    using ActionMap = std::map<std::string, Handler>;
    const ActionMap m_actionMap;

private:
    void Info(std::istream& strm);
    void TurnOn(std::istream& strm);
    void TurnOff(std::istream& strm);
    void SetGear(std::istream& strm);
    void SetSpeed(std::istream& strm);

    void ValidateWithoutArgs(std::istream& strm);
    int ValidateWithArgs(std::istream& strm);

    std::string GetDirectionAsString();
    std::string GetGearAsString();
};
