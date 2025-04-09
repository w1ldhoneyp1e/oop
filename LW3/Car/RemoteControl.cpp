#include "RemoteControl.h"
#include "Car.h"
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <functional>

RemoteControl::RemoteControl(Car& car, std::istream& input, std::ostream& output)
    : m_car(car)
    , m_input(input)
    , m_output(output)
    , m_actionMap({
          { Command::Info, std::bind(&RemoteControl::Info, this, std::placeholders::_1) },
          { Command::EngineOn, std::bind(&RemoteControl::TurnOn, this, std::placeholders::_1) },
          { Command::EngineOff, std::bind(&RemoteControl::TurnOff, this, std::placeholders::_1) },
          { Command::SetGear, std::bind(&RemoteControl::SetGear, this, std::placeholders::_1) },
          { Command::SetSpeed, std::bind(&RemoteControl::SetSpeed, this, std::placeholders::_1) }
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
		std::string commandAsString;
		strm >> commandAsString;
		Command command = StringToCommand(commandAsString);
		auto action = m_actionMap.find(command);

		switch (command)
		{
		case Command::Info:
		case Command::EngineOn:
		case Command::EngineOff:
		{
			std::string extraArg;
			if (strm >> extraArg)
			{
				throw std::invalid_argument("Invalid command argument\n");
			}
			action->second(0);
			return;
		}
		case Command::SetGear:
		case Command::SetSpeed:
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
			action->second(arg);
			return;
		}
		default:
			throw std::invalid_argument("Unknown command\n");
		}
	}
	catch (const std::exception& e)
	{
		m_output << e.what();
	}
}
	
void RemoteControl::Info(int)
{
	std::string engineInfo = (m_car.IsEngineOn())
		? "Engine is on\n"
		: "Engine is off\n";

	std::string gearInfo = "Gear: " + GetGearAsString() + "\n";
	std::string speedInfo = "Speed: " + std::to_string(m_car.GetSpeed()) + "\n";
	std::string directionInfo = "Direction: " + GetDirectionAsString() + "\n";

	m_output << engineInfo << gearInfo << speedInfo << directionInfo;
}

void RemoteControl::TurnOn(int)
{
	m_car.TurnOnEngine();
}

void RemoteControl::TurnOff(int)
{
	m_car.TurnOffEngine();
}

void RemoteControl::SetGear(int gear)
{
	m_car.SetGear(gear);
}

void RemoteControl::SetSpeed(int speed)
{
	m_car.SetSpeed(speed);
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

RemoteControl::Command RemoteControl::StringToCommand(std::string& command)
{
	if (command == "Info")
	{
		return Command::Info;
	}
	if (command == "EngineOn")
	{
		return Command::EngineOn;
	}
	if (command == "EngineOff")
	{
		return Command::EngineOff;
	}
	if (command == "SetGear")
	{
		return Command::SetGear;
	}
	if (command == "SetSpeed")
	{
		return Command::SetSpeed;
	}
	return Command::Unknown;
}
