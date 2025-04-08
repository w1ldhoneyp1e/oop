#pragma once

#include <map>

class Car
{
public:
    Car();

    using Speed = unsigned char;

    enum Gear
    {
        Reverse = -1,
        Neutral = 0,
        First = 1,
        Second = 2,
        Third = 3,
        Fourth = 4,
        Fifth = 5
    };

    enum Direction
    {
        Backward = -1,
        Stop = 0,
        Forward = 1
    };

public:
    void TurnOnEngine();
    void TurnOffEngine();
    void SetGear(int gear);
    void SetSpeed(int speed);

    Gear GetGear() const;
    Direction GetDirection() const;
    bool IsEngineOn() const;
    Speed GetSpeed() const;

private:
	bool m_isEngineOn;
	Speed m_speed;

	Gear m_gear;
	Direction m_direction;

    using SpeedRange = std::pair<Speed, Speed>;
    using GearLimits = std::map<Gear, SpeedRange>;
    const GearLimits gearLimits = {
        {Gear::Reverse, {0, 20}},
        {Gear::Neutral, {0, 150}},
        {Gear::First, {0, 30}},
        {Gear::Second, {20, 50}},
        {Gear::Third, {30, 60}},
        {Gear::Fourth, {40, 90}},
        {Gear::Fifth, {50, 150}}
    };
};

