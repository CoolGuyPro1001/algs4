#include "Interval1D.h"
#include "StdOut.h"

bool Interval1D::min_endpoint_compare(Interval1D a, Interval1D b)
{
    if (a.min() < b.min())
        return true;
    else
        return false;

    if (a.max() < b.max())
        return true;
    else
        return false;
}

bool Interval1D::max_endpoint_compare(Interval1D a, Interval1D b)
{
    if (a.max() < b.max())
        return true;
    else
        return false;

    if (a.min() < b.min())
        return true;
    else
        return false;
}

bool Interval1D::length_compare(Interval1D a, Interval1D b)
{
    double alen = a.length();
    double blen = b.length();
    return alen < blen;
}

Interval1D::Interval1D(double min, double max)
{
    double infinity = std::numeric_limits<double>::infinity();
    double nan = std::numeric_limits<double>::signaling_NaN();

    if (min == infinity || max == infinity)
        error("Endpoints must be finite");
    if (min == nan || max == nan)
        error("Endpoints cannot be NaN");

    // convert -0.0 to +0.0
    if (min == 0.0) min = 0.0;
    if (max == 0.0) max = 0.0;

    if (min <= max) {
        m_min = min;
        m_max = max;
    }
    else error("Illegal interval");
}

double Interval1D::min() const
{
    return m_min;
}

double Interval1D::max() const
{
    return m_max;
}

bool Interval1D::intersects(Interval1D that) const
{
    if (m_max < that.m_min) return false;
    if (that.m_max < m_min) return false;
    return true;
}

bool Interval1D::contains(double x) const
{
    return (m_min <= x) && (x <= m_max);
}

double Interval1D::length() const
{
    return m_max - m_min;
}

std::string Interval1D::to_string() const
{
    return "[" + std::to_string(m_min) + ", " + std::to_string(m_max) + "]";
}

std::ostream& operator<<(std::ostream& os, const Interval1D& i)
{
    os << "[" << std::to_string(i.m_min) << ", " << std::to_string(i.m_max) << "]";
    return os;
}

bool Interval1D::operator==(const Interval1D& other) const
{
    if (&other == this) return true;
    return m_min == other.m_min && m_max == other.m_max;
}

bool Interval1D::operator!=(const Interval1D& other) const
{
    if (&other == this) return false;
    return m_min != other.m_min && m_max != other.m_max;
}

size_t Interval1D::hash_code()
{
    size_t hash1 = std::hash<double>{}(m_min);
    size_t hash2 = std::hash<double>{}(m_max);
    return 31*hash1 + hash2;
}