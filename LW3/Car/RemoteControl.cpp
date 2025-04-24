#include "RemoteControl.h"
#include "Car.h"
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <functional>

using Handler = std::function<void(std::istream&)>;

RemoteControl::RemoteControl(Car& car, std::istream& input, std::ostream& output)
    : m_car(car)
    , m_input(input)
    , m_output(output)
    , m_actionMap({
		  { "Info", std::bind(&RemoteControl::Info, this, std::placeholders::_1) },
		  { "EngineOn", std::bind(&RemoteControl::TurnOn, this, std::placeholders::_1) },
		  { "EngineOff", std::bind(&RemoteControl::TurnOff, this, std::placeholders::_1) },
		  { "SetGear", std::bind(&RemoteControl::SetGear, this, std::placeholders::_1) },
          { "SetSpeed", std::bind(&RemoteControl::SetSpeed, this, std::placeholders::_1)}
      })
{
}

void RemoteControl::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);

	try
	{
		std::string command;
		strm >> command;
		auto action = m_actionMap.find(command); // delete Command, obrabotku vinesti v method
		if (action == m_actionMap.end())
		{
			throw std::invalid_argument("Unknown command\n");
		}
		action->second(strm);
	}
	catch (const std::exception& e)
	{
		m_output << e.what();
	}
}
	
void RemoteControl::Info(std::istream& strm)
{
	ValidateWithoutArgs(strm);

	std::string engineInfo = (m_car.IsEngineOn())
		? "Engine is on\n"
		: "Engine is off\n";

	std::string gearInfo = "Gear: " + GetGearAsString() + "\n";
	std::string speedInfo = "Speed: " + std::to_string(m_car.GetSpeed()) + "\n";
	std::string directionInfo = "Direction: " + GetDirectionAsString() + "\n";

	m_output << engineInfo << gearInfo << speedInfo << directionInfo;
}

void RemoteControl::TurnOn(std::istream& strm)
{
	ValidateWithoutArgs(strm);
	m_car.TurnOnEngine();
}

void RemoteControl::TurnOff(std::istream& strm)
{
	ValidateWithoutArgs(strm);
	m_car.TurnOffEngine();
}

void RemoteControl::SetGear(std::istream& strm)
{
	int arg = ValidateWithArgs(strm);
	m_car.SetGear(arg);
}

void RemoteControl::SetSpeed(std::istream& strm)
{
	int arg = ValidateWithArgs(strm);
	m_car.SetSpeed(arg);
}

std::string RemoteControl::GetDirectionAsString()
{
	switch (m_car.GetDirection())
	{
	case Car::Direction::Backward:
		return "Backward";
	case Car::Direction::Forward:
		return "Forward";
	default:
		return "Stopped";
	}
}

std::string RemoteControl::GetGearAsString()
{
	switch (m_car.GetGear())
	{
	case Car::Gear::Reverse:
		return "Reverse";
	case Car::Gear::Neutral:
		return "Neutral";
	case Car::Gear::First:
		return "First";
	case Car::Gear::Second:
		return "Second";
	case Car::Gear::Third:
		return "Third";
	case Car::Gear::Fourth:
		return "Fourth";
	case Car::Gear::Fifth:
		return "Fifth";
	}
}

void RemoteControl::ValidateWithoutArgs(std::istream& strm)
{
	std::string extraArg;
	if (strm >> extraArg)
	{
		throw std::invalid_argument("Invalid command argument\n");
	}
}

int RemoteControl::ValidateWithArgs(std::istream& strm)
{
	int arg;
	if (!(strm >> arg))
	{
		throw std::invalid_argument("Invalid command argument\n");
	}
	std::string extraArg;
	if (strm >> extraArg)
	{
		throw std::invalid_argument("Invalid command argument\n");
	}

	return arg;
}