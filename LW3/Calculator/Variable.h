#pragma once
#include <string>
#include <cmath>

class Variable 
{
public:
    explicit Variable(const std::string& name)
        : m_name(name)
        , m_value(std::nan(""))
    {}

    void SetValue(double value) { m_value = value; }
    double GetValue() const { return m_value; }
    const std::string& GetName() const { return m_name; }

private:
    std::string m_name;
    double m_value;
}; 