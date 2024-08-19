#include "Interval2D.h"
#include "Counter.h"
#include "StdOut.h"
#include "StdRandom.h"

Interval2D::Interval2D(Interval1D x, Interval1D y) : m_x(x), m_y(y)
{
}

bool Interval2D::intersects(Interval2D that) const
{
    if (!m_x.intersects(that.m_x)) return false;
    if (!m_y.intersects(that.m_y)) return false;
    return true;
}

bool Interval2D::contains(Point2D p) const
{
    return m_x.contains(p.x()) && m_y.contains(p.y());
}

double Interval2D::area() const
{
    return m_x.length() * m_y.length();
}

std::string Interval2D::to_string() const
{
    return m_x.to_string() + " x " + m_y.to_string();
}

std::ostream& operator<<(std::ostream& os, const Interval2D& i)
{
    os << i.m_x.to_string() << " x " << i.m_y.to_string();
    return os;
}

bool Interval2D::operator==(const Interval2D& other) const
{
    if (&other == this) return true;
    return m_x == other.m_x && m_y == other.m_y;
}

bool Interval2D::operator!=(const Interval2D& other) const
{
    if (&other == this) return false;
    return m_x != other.m_x || m_y != other.m_y;
}

size_t Interval2D::hash_code()
{
    size_t hash1 = m_x.hash_code();
    size_t hash2 = m_y.hash_code();
    return 31*hash1 + hash2;
}

/*void Interval2D::draw()
{
    double xc = (x.min() + x.max()) / 2.0;
    double yc = (y.min() + y.max()) / 2.0;
    StdDraw.rectangle(xc, yc, x.length() / 2.0, y.length() / 2.0);
}*/