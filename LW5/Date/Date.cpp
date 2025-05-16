#include "Date.h"
#include <sstream>
#include <iomanip>
#include <stdexcept>

bool CDate::IsLeapYear(uint64_t year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

uint64_t CDate::LastDayOfMonth(uint16_t year, Month month)
{
	static const uint64_t daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	uint64_t monthIdx = static_cast<uint64_t>(month);
	
	if (monthIdx < 1 || monthIdx > 12)
		return 0;
		
	if (monthIdx == 2 && IsLeapYear(year))
		return 29;
		
	return daysInMonth[monthIdx];
}

bool CDate::IsValidDate(uint8_t day, Month month, uint16_t year)
{
	uint8_t monthIdx = static_cast<uint8_t>(month);
	
	if (year < 1970 || year > 9999)
		return false;
		
	if (monthIdx < 1 || monthIdx > 12)
		return false;
		
	uint64_t lastDay = LastDayOfMonth(year, month);
	if (day < 1 || day > lastDay)
		return false;
		
	return true;
}

// Howard Hinnant
// https://howardhinnant.github.io/date_algorithms.html#days_from_civil
uint64_t CDate::DaysFromCivil(uint8_t day, Month month, uint16_t year)
{
	uint8_t m = static_cast<uint8_t>(month);
	int y = static_cast<int>(year);
	y -= (m <= 2);
	const int era = (y >= 0 ? y : y - 399) / 400;
	const uint64_t yoe = static_cast<uint64_t>(y - era * 400);
	const uint64_t doy = (153 * (m > 2 ? m - 3 : m + 9) + 2) / 5 + day - 1;
	const uint64_t doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
	return era * 146097 + doe - 719468;
}

void CDate::CivilFromDays(uint64_t days, uint8_t& day, Month& month, uint16_t& year)
{
	days += 719468;
	const int era = static_cast<int>(days / 146097);
	const uint64_t doe = static_cast<uint64_t>(days - era * 146097);
	const uint64_t yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
	const int y = static_cast<int>(yoe) + era * 400;
	const uint64_t doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
	const uint64_t mp = (5 * doy + 2) / 153;
	day = static_cast<uint8_t>(doy - (153 * mp + 2) / 5 + 1);
	month = static_cast<Month>((mp < 10 ? mp + 3 : mp - 9));
	year = static_cast<uint16_t>(y + (static_cast<uint64_t>(month) <= 2));
}

CDate::CDate(uint8_t day, Month month, uint16_t year)
{
	if (!IsValidDate(day, month, year))
	{
		throw std::invalid_argument("Invalid date");
	}
	
	m_timestamp = DaysFromCivil(day, month, year);
}

CDate::CDate(uint64_t timestamp) : m_timestamp(timestamp)
{
	if (timestamp > MAX_TIMESTAMP)
	{
		throw std::out_of_range("Invalid timestamp");
	}
}

CDate::CDate() : m_timestamp(0)
{
}

uint8_t CDate::GetDay() const
{
	uint8_t day;
	Month month;
	uint16_t year;
	CivilFromDays(m_timestamp, day, month, year);
	return day;
}

Month CDate::GetMonth() const
{
	uint8_t day;
	Month month;
	uint16_t year;
	CivilFromDays(m_timestamp, day, month, year);
	return month;
}

uint16_t CDate::GetYear() const
{
	uint8_t day;
	Month month;
	uint16_t year;
	CivilFromDays(m_timestamp, day, month, year);
	return year;
}

WeekDay CDate::GetWeekDay() const
{
	return static_cast<WeekDay>((m_timestamp + 4) % 7);
}

CDate& CDate::operator++()
{
	if (m_timestamp == MAX_TIMESTAMP)
	{
		throw std::out_of_range("Increment will cause an overflow");
	}
	
	++m_timestamp;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp = *this;
	++(*this);
	return temp;
}

CDate& CDate::operator--()
{
	if (m_timestamp == 0)
	{
		throw std::out_of_range("Decrement will cause an overflow");
	}
	
	--m_timestamp;
	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp = *this;
	--(*this);
	return temp;
}

CDate CDate::operator+(int days) const
{
	if (days >= 0 && static_cast<uint64_t>(days) > MAX_TIMESTAMP - m_timestamp)
	{
		throw std::out_of_range("Sum will cause an overflow");
	}
	
	if (days < 0 && static_cast<uint64_t>(-days) > m_timestamp)
	{
		throw std::out_of_range("Sum will cause an overflow");
	}
	
	return CDate(m_timestamp + days);
}

CDate operator+(int days, const CDate& date)
{
	return date + days;
}

CDate CDate::operator-(int days) const
{
	return (*this) + (-days);
}

int CDate::operator-(const CDate& other) const
{
	return static_cast<int>(m_timestamp) - static_cast<int>(other.m_timestamp);
}

CDate& CDate::operator+=(int days)
{
	if (days >= 0 && static_cast<uint64_t>(days) > MAX_TIMESTAMP - m_timestamp)
	{
		throw std::out_of_range("Sum will cause an overflow");
	}
	
	if (days < 0 && static_cast<uint64_t>(-days) > m_timestamp)
	{
		throw std::out_of_range("Sum will cause an overflow");
	}
	
	m_timestamp += days;
	return *this;
}

CDate& CDate::operator-=(int days)
{
	return (*this) += (-days);
}

std::ostream& operator<<(std::ostream& os, const CDate& date)
{
	os << std::setfill('0') 
	   << std::setw(2) << static_cast<unsigned>(date.GetDay()) << "."
	   << std::setw(2) << static_cast<unsigned>(date.GetMonth()) << "."
	   << std::setw(4) << date.GetYear();
	return os;
}

std::istream& operator>>(std::istream& is, CDate& date)
{
	uint64_t day, month, year;
	char dot1, dot2;
	
	if (!(is >> day >> dot1 >> month >> dot2 >> year) || dot1 != '.' || dot2 != '.')
	{
		is.setstate(std::ios::failbit);
		throw std::invalid_argument("Invalid date format");
	}
	
	try 
	{
		date = CDate(static_cast<uint8_t>(day), static_cast<Month>(month), static_cast<uint16_t>(year));
	} catch (const std::exception&) 
	{
		is.setstate(std::ios::failbit);
		throw;
	}
	
	return is;
}
