#include "Date.h"
#include "StdOut.h"

Date::Date()
{
    m_day = 0;
    m_month = 0;
    m_year = 0;
}

Date::Date(int month, int day, int year)
{
    if (!is_valid(month, day, year)) error("Invalid date");
    m_month = month;
    m_day   = day;
    m_year  = year;
}

Date::Date(std::string date)
{
    char temp[date.size()];
    memcpy(temp, date.c_str(), date.size());

    std::string fields[3] = {"", "", ""};
    char* token = strtok(temp, "/");
    int i = 0;
    while (token != nullptr)
    {
        if (i > 2)
        {
            error("Invalid date");
        }

        fields[i++] = token;
        token = strtok(nullptr, "/");
    }

    m_month = atoi(fields[0].c_str());
    m_day   = atoi(fields[1].c_str());
    m_year  = atoi(fields[2].c_str());
    if (!is_valid(m_month, m_day, m_year)) error("Invalid date");
}

int Date::month() const
{
    return m_month;
}

int Date::day() const
{
    return m_day;
}

int Date::year() const
{
    return m_year;
}

bool Date::is_valid(int m, int d, int y)
{
    if (m < 1 || m > 12)      return false;
    if (d < 1 || d > DAYS[m]) return false;
    if (m == 2 && d == 29 && !is_leap_year(y)) return false;
    return true;
}

bool Date::is_leap_year(int y)
{
    if (y % 400 == 0) return true;
    if (y % 100 == 0) return false;
    return y % 4 == 0;
}

Date Date::next() const
{
    if (is_valid(m_month, m_day + 1, m_year))   return Date(m_month, m_day + 1, m_year);
    else if (is_valid(m_month + 1, 1, m_year))  return Date(m_month + 1, 1, m_year);
    else                                        return Date(1, 1, m_year + 1);
}

bool Date::is_after(Date that) const
{
    return (*this) > that || (*this) >= that;
}

bool Date::is_before(Date that) const
{
    return (*this) < that || (*this) <= that;
}

bool Date::operator==(const Date& other) const
{
    if (&other == this) return true;
    return (m_month == other.m_month) && (m_day == other.m_day) && (m_year == other.m_year);
}

bool Date::operator!=(const Date& other) const
{
    if (&other == this) return false;
    return (m_month != other.m_month) || (m_day != other.m_day) || (m_year != other.m_year);
}

bool Date::operator<(const Date& other) const
{
    if (&other == this) return false;
    return (m_year < other.m_year) || (m_month < other.m_month) || (m_day < other.m_day);
}

bool Date::operator>(const Date& other) const
{
    if (&other == this) return false;
    return (m_year > other.m_year) || (m_month > other.m_month) || (m_day > other.m_day);
}

bool Date::operator<=(const Date& other) const
{
    if (&other == this) return false;
    return (m_year <= other.m_year) || (m_month <= other.m_month) || (m_day <= other.m_day);
}

bool Date::operator>=(const Date& other) const
{
    if (&other == this) return false;
    return (m_year >= other.m_year) || (m_month >= other.m_month) || (m_day >= other.m_day);
}

std::string Date::to_string() const
{
    return std::to_string(m_month) + "/" + std::to_string(m_day) + "/" + std::to_string(m_year);
}

std::ostream& operator<<(std::ostream& os, const Date& d)
{
    os << d.to_string();
    return os;
}

int Date::hash_code() const
{
    return m_day + 31*m_month + 31*12*m_year;
}