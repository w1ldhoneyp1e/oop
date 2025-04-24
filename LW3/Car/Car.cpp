#include <stdexcept>
#include "Car.h"

using SpeedRange = std::pair<Car::Speed, Car::Speed>; // vinesti v cpp
using GearLimits = std::map<Car::Gear, SpeedRange>;
const GearLimits gearLimits = {
    {Car::Gear::Reverse, {0, 20}},
    {Car::Gear::Neutral, {0, 150}},
    {Car::Gear::First, {0, 30}},
    {Car::Gear::Second, {20, 50}},
    {Car::Gear::Third, {30, 60}},
    {Car::Gear::Fourth, {40, 90}},
    {Car::Gear::Fifth, {50, 150}}
};

const signed char MIN_GEAR = -1;
const signed char MAX_GEAR = 5;

Car::Car()
{
    m_isEngineOn = false;
    m_speed = 0;
    m_gear = Gear::Neutral;
    m_direction = Direction::Stop;
}

void Car::TurnOnEngine()
{
    if (m_isEngineOn)
    {
        throw std::logic_error("Car is already started");
    }
    m_isEngineOn = true;
}

void Car::TurnOffEngine()
{
    if (!m_isEngineOn)
    {
        throw std::logic_error("Car is not started");
    }
    if (m_speed != 0)
    {
        throw std::logic_error("Car cannot be turned off while moving");
    }
    if (m_gear != Gear::Neutral)
    {
        throw std::logic_error("Car must be stopped and in neutral gear");
    }
    m_isEngineOn = false;
}

void Car::SetGear(int gear)
{
    if (gear < MIN_GEAR || gear > MAX_GEAR) // v const limits
    {
        throw std::logic_error("Invalid gear");
    }
    if (!m_isEngineOn)
    {
        throw std::logic_error("Cannot set gear while engine is off");
    }

    const Car::Gear gearTyped = static_cast<Gear>(gear);

    const auto speedLimit = gearLimits.find(gearTyped);
    if (speedLimit->second.first > m_speed || speedLimit->second.second < m_speed) // vinesti 
    {
        throw std::logic_error("Unsuitable current speed");
    }
    if (gearTyped == Gear::Reverse && m_speed != 0)
    {
        throw std::logic_error("Cannot reverse while moving");
    }
    m_gear = gearTyped;
}

void Car::SetSpeed(int speed)
{
    if (speed < 0)
    {
        throw std::logic_error("Speed cannot be negative");
    }
    if (!m_isEngineOn)
    {
        throw std::logic_error("Cannot set speed while engine is off");
    }
    if (m_gear == Gear::Neutral && (speed - m_speed) > 0)
    {
        throw std::logic_error("Cannot accelerate on neutral");
    }
    const auto speedLimit = gearLimits.find(m_gear);
    if (speedLimit->second.first > speed || speedLimit->second.second < speed) // pereisp find
    {
        throw std::logic_error("Speed is out of gear range");
    }
    if (speed == 0) // v func vinesti
    {
        m_direction = Direction::Stop;
    }
    else if (m_gear == Gear::Reverse)
    {
        m_direction = Direction::Backward;
    }
    else
    {
        m_direction = Direction::Forward;
    }
    m_speed = static_cast<Speed>(speed);
}

Car::Gear Car::GetGear() const
{
    return m_gear;
}

Car::Direction Car::GetDirection() const
{
    return m_direction;
}

bool Car::IsEngineOn() const
{
    return m_isEngineOn;
}

Car::Speed Car::GetSpeed() const
{
    return m_speed;
}