#include "Accumulator.h"
#include "StdIn.h"
#include "StdOut.h"

void Accumulator::add_data_value(double x)
{
    m_n++;
    double delta = x - m_mu;
    m_mu  += delta / m_n;
    m_sum += (double) (m_n - 1) / m_n * delta * delta;
}

double Accumulator::mean() const
{
    return m_mu;
}

double Accumulator::var() const
{
    double nan = std::numeric_limits<double>::signaling_NaN();
    if (m_n <= 1) return nan;
    return m_sum / (m_n - 1);
}

double Accumulator::stddev() const
{
    return sqrt(var());
}

int Accumulator::count() const
{
    return m_n;
}

std::string Accumulator::to_string() const
{
    return "n = " + std::to_string(m_n) + ", mean = " + std::to_string(mean()) + ", stddev = " + std::to_string(stddev());
}

std::ostream& operator<<(std::ostream& os, const Accumulator& acc)
{
    os << acc.to_string();
    return os;
}