#pragma once
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <compare>

enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

class CDate
{
private:
    uint64_t m_timestamp;

    static bool IsLeapYear(uint64_t year);
    static uint64_t LastDayOfMonth(uint16_t year, Month month);
    static bool IsValidDate(uint8_t day, Month month, uint16_t year);
    static uint64_t DaysFromCivil(uint8_t day, Month month, uint16_t year);
    static void CivilFromDays(uint64_t days, uint8_t& day, Month& month, uint16_t& year);

public:
    static const uint64_t MIN_TIMESTAMP = 0;
    static const uint64_t MAX_TIMESTAMP = 2932896;

    CDate(uint8_t day, Month month, uint16_t year);
    explicit CDate(uint64_t timestamp);
    CDate();

    uint8_t GetDay() const;
    Month GetMonth() const;
    uint16_t GetYear() const;
    WeekDay GetWeekDay() const;

    CDate& operator++();
    CDate operator++(int);
    CDate& operator--();
    CDate operator--(int);

    CDate operator+(int days) const;
    friend CDate operator+(int days, const CDate& date);
    CDate operator-(int days) const;
    int operator-(const CDate& other) const;

    CDate& operator+=(int days);
    CDate& operator-=(int days);

    std::strong_ordering operator<=>(const CDate& other) const = default;

    friend std::ostream& operator<<(std::ostream& os, const CDate& date);
    friend std::istream& operator>>(std::istream& is, CDate& date);
};