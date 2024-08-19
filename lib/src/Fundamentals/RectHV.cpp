#include "RectHV.h"

RectHV::RectHV(double xmin, double ymin, double xmax, double ymax)
{
    m_xmin = xmin;
    m_ymin = ymin;
    m_xmax = xmax;
    m_ymax = ymax;

    double nan = std::numeric_limits<double>::signaling_NaN();

    if (m_xmin == nan || m_xmax == nan)
    {
        error("x-coordinate is NaN: " + to_string());
    }
    if (m_ymin == nan || m_ymax == nan)
    {
        error("y-coordinate is NaN: " + to_string());
    }
    if (m_xmax < m_xmin)
    {
        error("xmax < xmin: " + to_string());
    }
    if (m_ymax < m_ymin)
    {
        error("ymax < ymin: " + to_string());
    }
}

double RectHV::xmin() const
{
    return m_xmin;
}

double RectHV::xmax() const
{
    return m_xmax;
}

double RectHV::ymin() const
{
    return m_ymin;
}

double RectHV::ymax() const
{
    return m_ymax;
}

double RectHV::width() const
{
    return m_xmax - m_xmin;
}

double RectHV::height() const
{
    return m_ymax - m_ymin;
}

bool RectHV::intersects(RectHV that) const
{
    return m_xmax >= that.m_xmin && m_ymax >= that.m_ymin
        && that.m_xmax >= m_xmin && that.m_ymax >= m_ymin;
}

bool RectHV::contains(Point2D p) const
{
    return (p.x() >= m_xmin) && (p.x() <= m_xmax)
        && (p.y() >= m_ymin) && (p.y() <= m_ymax);
}

double RectHV::distance_to(Point2D p) const
{
    return sqrt(distance_squared_to(p));
}

double RectHV::distance_squared_to(Point2D p) const
{
    double dx = 0.0, dy = 0.0;
    if      (p.x() < m_xmin) dx = p.x() - m_xmin;
    else if (p.x() > m_xmax) dx = p.x() - m_xmax;
    if      (p.y() < m_ymin) dy = p.y() - m_ymin;
    else if (p.y() > m_ymax) dy = p.y() - m_ymax;
    return dx*dx + dy*dy;
}

bool RectHV::operator==(const RectHV& other) const
{
    if (&other == this) return true;
    return m_xmin == other.m_xmin && m_ymin == other.m_ymin &&
        m_xmax == other.m_xmax && m_ymax == other.m_ymax;
}

bool RectHV::operator!=(const RectHV& other) const
{
    if (&other == this) return false;
    return m_xmin != other.m_xmin || m_ymin != other.m_ymin ||
        m_xmax != other.m_xmax || m_ymax != other.m_ymax;
}

std::string RectHV::to_string() const
{
    return "[" + std::to_string(m_xmin) + ", " + std::to_string(m_xmax) + "] x [" + std::to_string(m_ymin) + ", " + std::to_string(m_ymax) + "]";
}

std::ostream& operator<<(std::ostream& os, const RectHV& r)
{
    os << "[" << std::to_string(r.m_xmin) << ", " << std::to_string(r.m_xmax) << "] x [" << std::to_string(r.m_ymin) << ", " << std::to_string(r.m_ymax) << "]";
    return os;
}

void RectHV::draw() const
{
    /*StdDraw.line(m_xmin, m_ymin, m_xmax, m_ymin);
    StdDraw.line(m_xmax, m_ymin, m_xmax, m_ymax);
    StdDraw.line(m_xmax, m_ymax, m_xmin, m_ymax);
    StdDraw.line(m_xmin, m_ymax, m_xmin, m_ymin);*/
}