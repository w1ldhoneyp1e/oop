#include "RemoteControl.h"
#include "Car.h"
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <functional>

RemoteControl::RemoteControl(Car& car, std::istream& input, std::ostream& output)
    : car(car)
    , input(input)
    , output(output)
    , actionMap({
          { "Info", [this](std::istream&) { Info(); } },
          { "EngineOn", [this](std::istream&) { TurnOn(); } },
          { "EngineOff", [this](std::istream&) { TurnOff(); } },
          { "SetGear", std::bind(&RemoteControl::SetGear, this, std::placeholders::_1) },
          { "SetSpeed", std::bind(&RemoteControl::SetSpeed, this, std::placeholders::_1) }
      })
{
}

void RemoteControl::HandleCommand()
{
	std::string commandLine;
	getline(input, commandLine);
	std::istringstream strm(commandLine);

	std::string command;
	strm >> command;

	auto action = actionMap.find(command);
	if (action != actionMap.end())
	{
		return action->second(strm);
	}
}

void RemoteControl::Info()
{
	std::string engineInfo = (car.IsTurnedOn())
		? "������ ��������\n"
		: "������ ���������\n";

	std::string gearInfo = "��������: " + GetGearAsString() + "\n";
	std::string speedInfo = "��������: " + std::to_string(car.GetSpeed()) + "\n";
	std::string directionInfo = "�����������: " + GetDirectionAsString() + "\n";

	output << engineInfo << gearInfo << speedInfo << directionInfo;
}

void RemoteControl::TurnOn()
{
	car.TurnOn();
}

void RemoteControl::TurnOff()
{
	car.TurnOff();
}

void RemoteControl::SetGear(std::istream& args)
{
	int gear;
	args >> gear;
	car.SetGear(gear);
}

void RemoteControl::SetSpeed(std::istream& args)
{
	int speed;
	args >> speed;
	car.SetSpeed(speed);
}

std::string RemoteControl::GetDirectionAsString()
{
	switch (car.GetDirection())
	{
	case Car::Direction::Backward:
		return "�����";
	case Car::Direction::Forward:
		return "������";
	default:
		return "����� �� �����";
	}
}

std::string RemoteControl::GetGearAsString()
{
	switch (car.GetGear())
	{
	case Car::Gear::-1:
		return "������ ���";
	case Car::Gear::0:
		return "��������";
	case Car::Gear::1:
		return "������";
	case Car::Gear::2:
		return "������";
	case Car::Gear::3:
		return "������";
	case Car::Gear::4:
		return "���������";
	case Car::Gear::5:
		return "�����";
	}
}
