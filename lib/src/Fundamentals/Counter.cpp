#include "Counter.h"
#include "StdRandom.h"
#include "StdOut.h"

Counter::Counter(std::string id)
{
    m_name = id;
}

void Counter::increment()
{
    m_count++;
}

int Counter::tally() const
{
    return m_count;
}

std::string Counter::to_string() const
{
    return std::to_string(m_count) + " " + m_name;
}

std::ostream& operator<<(std::ostream& os, const Counter& c)
{
    os << c.to_string();
    return os;
}

bool Counter::operator==(const Counter& other) const
{
    return m_count == other.m_count;
}

bool Counter::operator!=(const Counter& other) const
{
    return m_count != other.m_count;
}

bool Counter::operator<(const Counter& other) const
{
    return m_count < other.m_count;
}

bool Counter::operator>(const Counter& other) const
{
    return m_count > other.m_count;
}

bool Counter::operator<=(const Counter& other) const
{
    return m_count <= other.m_count;
}

bool Counter::operator>=(const Counter& other) const
{
    return m_count >= other.m_count;
}