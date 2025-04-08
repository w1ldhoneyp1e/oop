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
		int arg;
		strm >> commandAsString;
		strm >> arg;
		Command command = StringToCommand(commandAsString);
		auto action = m_actionMap.find(command);
		switch (command)
		{
		case Command::Info:
		case Command::EngineOn:
		case Command::EngineOff:
		{
			if (strm.get() != EOF)
			{
				throw std::invalid_argument("Ошибка: команда не принимает аргумент\n");
			}
			action->second(0);
			return;
		}
		case Command::SetGear:
		case Command::SetSpeed:
		{
			std::string strEmpty;
			if ((strm >> strEmpty) || strm.get() != EOF)
			{
				throw std::invalid_argument("Ошибка: аргумент должен быть целым числом\n");
			}
			action->second(arg);
			return;
		}
		default:
			throw std::invalid_argument("Ошибка: неизвестная команда\n");
		}
	}
	catch (const std::exception& e)
	{
		m_output << e.what() << "\n";
	}
}
	
void RemoteControl::Info(int)
{
	std::string engineInfo = (m_car.IsEngineOn())
		? "Машина заведена\n"
		: "Машина заглушена\n";

	std::string gearInfo = "Передача: " + GetGearAsString() + "\n";
	std::string speedInfo = "Скорость: " + std::to_string(m_car.GetSpeed()) + "\n";
	std::string directionInfo = "Направление: " + GetDirectionAsString() + "\n";

	m_output << engineInfo << gearInfo << speedInfo << directionInfo;
}

void RemoteControl::TurnOn(int)
{
	m_car.TurnOnEngine();
	m_output << "Машина заведена\n";
}

void RemoteControl::TurnOff(int)
{
	m_car.TurnOffEngine();
	m_output << "Машина заглушена\n";
}

void RemoteControl::SetGear(int gear)
{
	m_car.SetGear(gear);
	m_output << "Передача установлена\n";
}

void RemoteControl::SetSpeed(int speed)
{
	m_car.SetSpeed(speed);
	m_output << "Скорость установлена\n";
}

std::string RemoteControl::GetDirectionAsString()
{
	switch (m_car.GetDirection())
	{
	case Car::Direction::Backward:
		return "Назад";
	case Car::Direction::Forward:
		return "Вперед";
	default:
		return "Стоит на месте";
	}
}

std::string RemoteControl::GetGearAsString()
{
	switch (m_car.GetGear())
	{
	case Car::Gear::Reverse:
		return "Задний ход";
	case Car::Gear::Neutral:
		return "Нейтраль";
	case Car::Gear::First:
		return "Первая";
	case Car::Gear::Second:
		return "Вторая";
	case Car::Gear::Third:
		return "Третья";
	case Car::Gear::Fourth:
		return "Четвертая";
	case Car::Gear::Fifth:
		return "Пятая";
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
