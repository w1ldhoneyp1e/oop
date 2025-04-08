#include <stdexcept>
#include "Car.h"

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
        throw std::logic_error("Машина уже заведена");
    }
    m_isEngineOn = true;
}

void Car::TurnOffEngine()
{
    if (!m_isEngineOn)
    {
        throw std::logic_error("Машина не заведена");
    }
    if (m_speed != 0)
    {
        throw std::logic_error("Машина не может быть заглушена, если она в движении");
    }
    if (m_gear != Gear::Neutral)
    {
        throw std::logic_error("Машина не может быть заглушена, если она не в нейтральной передаче");
    }
    m_isEngineOn = false;
}

void Car::SetGear(int gear)
{
    if (!m_isEngineOn)
    {
        throw std::logic_error("Машина не заведена, чтобы переключить передачу");
    }
    if (gear < -1 || gear > 5)
    {
        throw std::logic_error("Передача не существует");
    }

    const Car::Gear gearTyped = static_cast<Gear>(gear);

    if (gearLimits.find(gearTyped)->second.first > m_speed || gearLimits.find(gearTyped)->second.second < m_speed)
    {
        throw std::logic_error("Передача не соответствует скорости");
    }
    if (gearTyped == Gear::Reverse && m_speed != 0)
    {
        throw std::logic_error("Нельзя включить заднюю передачу, если машина в движении");
    }
    m_gear = gearTyped;
}

void Car::SetSpeed(int speed)
{
    if (!m_isEngineOn)
    {
        throw std::logic_error("Машина не заведена, чтобы изменить скорость");
    }
    if (m_gear == Gear::Neutral && speed > 0)
    {
        throw std::logic_error("Нельзя увеличить скорость, если машина в нейтральной передаче");
    }
    if (gearLimits.find(m_gear)->second.first > speed || gearLimits.find(m_gear)->second.second < speed)
    {
        throw std::logic_error("Скорость не соответствует передаче");
    }
    if (speed == 0)
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
    speed = static_cast<Speed>(speed);
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