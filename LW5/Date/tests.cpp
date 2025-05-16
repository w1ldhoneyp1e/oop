#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "Date.h"
#include <sstream>

TEST_CASE("Constructors and validation")
{
    SECTION("Default constructor")
    {
        CDate date;
        REQUIRE(date.GetDay() == 1);
        REQUIRE(date.GetMonth() == Month::JANUARY);
        REQUIRE(date.GetYear() == 1970);
        REQUIRE(date.GetWeekDay() == WeekDay::THURSDAY);
    }

    SECTION("Constructor with valid parameters")
    {
        CDate date(15, Month::MARCH, 2023);
        REQUIRE(date.GetDay() == 15);
        REQUIRE(date.GetMonth() == Month::MARCH);
        REQUIRE(date.GetYear() == 2023);
    }

    SECTION("Constructor with invalid day")
    {
        REQUIRE_THROWS_AS(CDate(32, Month::JANUARY, 2023), std::invalid_argument);
    }

    SECTION("Constructor with invalid month")
    {
        REQUIRE_THROWS_AS(CDate(15, static_cast<Month>(13), 2023), std::invalid_argument);
    }

    SECTION("Constructor with invalid year (below minimum)")
    {
        REQUIRE_THROWS_AS(CDate(1, Month::JANUARY, 1969), std::invalid_argument);
    }

    SECTION("Constructor with invalid year (above maximum)")
    {
        REQUIRE_THROWS_AS(CDate(1, Month::JANUARY, 10000), std::invalid_argument);
    }

    SECTION("Constructor with timestamp")
    {
        CDate date1(0);
        REQUIRE(date1.GetDay() == 1);
        REQUIRE(date1.GetMonth() == Month::JANUARY);
        REQUIRE(date1.GetYear() == 1970);

        CDate date2(365);
        REQUIRE(date2.GetDay() == 1);
        REQUIRE(date2.GetMonth() == Month::JANUARY);
        REQUIRE(date2.GetYear() == 1971);
    }
    
    SECTION("Constructor with timestamp out of range")
    {
        REQUIRE_THROWS_AS(CDate(CDate::MAX_TIMESTAMP + 1), std::out_of_range);
    }
}

TEST_CASE("Leap year handling")
{
    SECTION("February 29 in leap year")
    {
        CDate date(29, Month::FEBRUARY, 2020);
    }

    SECTION("February 29 in non-leap year")
    {
        REQUIRE_THROWS_AS(CDate(29, Month::FEBRUARY, 2023), std::invalid_argument);
    }

    SECTION("Changing month in leap year")
    {
        CDate date(28, Month::FEBRUARY, 2020);
        ++date;
        REQUIRE(date.GetDay() == 29);
        REQUIRE(date.GetMonth() == Month::FEBRUARY);
        REQUIRE(date.GetYear() == 2020);
        
        ++date;
        REQUIRE(date.GetDay() == 1);
        REQUIRE(date.GetMonth() == Month::MARCH);
        REQUIRE(date.GetYear() == 2020);
    }

    SECTION("Changing month in non-leap year")
    {
        CDate date(28, Month::FEBRUARY, 2023);
        ++date;
        REQUIRE(date.GetDay() == 1);
        REQUIRE(date.GetMonth() == Month::MARCH);
        REQUIRE(date.GetYear() == 2023);
    }
}

TEST_CASE("Increment and decrement")
{
    SECTION("Prefix increment")
    {
        CDate date(31, Month::DECEMBER, 2020);
        CDate& ref = ++date;
        REQUIRE(std::addressof(ref) == std::addressof(date));
        REQUIRE(date.GetDay() == 1);
        REQUIRE(date.GetMonth() == Month::JANUARY);
        REQUIRE(date.GetYear() == 2021);
    }

    SECTION("Postfix increment")
    {
        CDate date(31, Month::DECEMBER, 2020);
        CDate prevDate = date++;
        REQUIRE(prevDate.GetDay() == 31);
        REQUIRE(prevDate.GetMonth() == Month::DECEMBER);
        REQUIRE(prevDate.GetYear() == 2020);
        
        REQUIRE(date.GetDay() == 1);
        REQUIRE(date.GetMonth() == Month::JANUARY);
        REQUIRE(date.GetYear() == 2021);
    }

    SECTION("Prefix decrement")
    {
        CDate date(1, Month::JANUARY, 2021);
        CDate& ref = --date;
        REQUIRE(std::addressof(ref) == std::addressof(date));
        REQUIRE(date.GetDay() == 31);
        REQUIRE(date.GetMonth() == Month::DECEMBER);
        REQUIRE(date.GetYear() == 2020);
    }

    SECTION("Postfix decrement")
    {
        CDate date(1, Month::JANUARY, 2021);
        CDate prevDate = date--;
        REQUIRE(prevDate.GetDay() == 1);
        REQUIRE(prevDate.GetMonth() == Month::JANUARY);
        REQUIRE(prevDate.GetYear() == 2021);
        
        REQUIRE(date.GetDay() == 31);
        REQUIRE(date.GetMonth() == Month::DECEMBER);
        REQUIRE(date.GetYear() == 2020);
    }

    SECTION("Decrement out of range")
    {
        CDate date(1, Month::JANUARY, 1970);
        REQUIRE_THROWS_AS(--date, std::out_of_range);
    }

    SECTION("Increment out of range")
    {
        CDate date(31, Month::DECEMBER, 9999);
        REQUIRE_THROWS_AS(++date, std::out_of_range);
    }
}

TEST_CASE("Addition and subtraction")
{
    SECTION("Add days")
    {
        CDate date(15, Month::MARCH, 2023);
        CDate result = date + 20;
        REQUIRE(result.GetDay() == 4);
        REQUIRE(result.GetMonth() == Month::APRIL);
        REQUIRE(result.GetYear() == 2023);
    }

    SECTION("Add days (days first)")
    {
        CDate date(15, Month::MARCH, 2023);
        CDate result = 20 + date;
        REQUIRE(result.GetDay() == 4);
        REQUIRE(result.GetMonth() == Month::APRIL);
        REQUIRE(result.GetYear() == 2023);
    }

    SECTION("Subtract days")
    {
        CDate date(15, Month::MARCH, 2023);
        CDate result = date - 20;
        REQUIRE(result.GetDay() == 23);
        REQUIRE(result.GetMonth() == Month::FEBRUARY);
        REQUIRE(result.GetYear() == 2023);
    }

    SECTION("Subtract dates")
    {
        CDate date1(15, Month::MARCH, 2023);
        CDate date2(23, Month::FEBRUARY, 2023);
        
        int diff1 = date1 - date2;
        REQUIRE(diff1 == 20);
        
        int diff2 = date2 - date1;
        REQUIRE(diff2 == -20);
    }

    SECTION("Add days out of range")
    {
        CDate date(31, Month::DECEMBER, 9999);
        REQUIRE_THROWS_AS(date + 1, std::out_of_range);
    }

    SECTION("Subtract days out of range")
    {
        CDate date(1, Month::JANUARY, 1970);
        REQUIRE_THROWS_AS(date - 1, std::out_of_range);
    }
}

TEST_CASE("+=")
{
    SECTION("Add")
    {
        CDate date(15, Month::MARCH, 2023);
        date += 20;
        REQUIRE(date.GetDay() == 4);
        REQUIRE(date.GetMonth() == Month::APRIL);
        REQUIRE(date.GetYear() == 2023);
    }

    SECTION("Subtract")
    {
        CDate date(15, Month::MARCH, 2023);
        date -= 20;
        REQUIRE(date.GetDay() == 23);
        REQUIRE(date.GetMonth() == Month::FEBRUARY);
        REQUIRE(date.GetYear() == 2023);
    }

    SECTION("Add out of range")
    {
        CDate date(31, Month::DECEMBER, 9999);
        REQUIRE_THROWS_AS(date += 1, std::out_of_range);
    }

    SECTION("Subtract out of range")
    {
        CDate date(1, Month::JANUARY, 1970);
        REQUIRE_THROWS_AS(date -= 1, std::out_of_range);
    }
}

TEST_CASE("Comparison")
{
    CDate date1(15, Month::MARCH, 2023);
    CDate date2(16, Month::MARCH, 2023);
    CDate date3(15, Month::MARCH, 2023);

    SECTION("Equality")
    {
        REQUIRE(date1 == date3);
        REQUIRE_FALSE(date1 == date2);
    }

    SECTION("Inequality")
    {
        REQUIRE(date1 != date2);
        REQUIRE_FALSE(date1 != date3);
    }

    SECTION("Less")
    {
        REQUIRE(date1 < date2);
        REQUIRE_FALSE(date2 < date1);
        REQUIRE_FALSE(date1 < date3);
    }

    SECTION("Greater")
    {
        REQUIRE(date2 > date1);
        REQUIRE_FALSE(date1 > date2);
        REQUIRE_FALSE(date1 > date3);
    }

    SECTION("Less or equal")
    {
        REQUIRE(date1 <= date2);
        REQUIRE(date1 <= date3);
        REQUIRE_FALSE(date2 <= date1);
    }

    SECTION("Greater or equal")
    {
        REQUIRE(date2 >= date1);
        REQUIRE(date1 >= date3);
        REQUIRE_FALSE(date1 >= date2);
    }
}

TEST_CASE("Input/Output")
{
    SECTION("Output valid date")
    {
        CDate date(15, Month::MARCH, 2023);
        std::ostringstream oss;
        oss << date;
        REQUIRE(oss.str() == "15.03.2023");
    }

    SECTION("Output invalid date")
    {
        REQUIRE_THROWS_AS(CDate(32, Month::JANUARY, 2023), std::invalid_argument);
    }

    SECTION("Input valid date")
    {
        std::istringstream iss("15.03.2023");
        CDate date;
        iss >> date;
        REQUIRE(date.GetDay() == 15);
        REQUIRE(date.GetMonth() == Month::MARCH);
        REQUIRE(date.GetYear() == 2023);
    }

    SECTION("Input invalid format")
    {
        std::istringstream iss("15-03-2023");
        CDate date;
        REQUIRE_THROWS(iss >> date);
    }
    
    SECTION("Input invalid date")
    {
        std::istringstream iss("31.02.2023");
        CDate date;
        REQUIRE_THROWS(iss >> date);
    }
}
