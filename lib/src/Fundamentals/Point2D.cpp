#include "Point2D.h"
#include <cmath>


Point2D::Point2D(double x, double y)
{
    double infinity = std::numeric_limits<double>::infinity();
    if (std::abs(x) == infinity || std::abs(y) == infinity)
        error("Coordinates must be finite");
    if (x == 0.0) x = 0.0;  // convert -0.0 to +0.0
    else          x = x;

    if (y == 0.0) y = 0.0;  // convert -0.0 to +0.0
    else          y = y;
}

double Point2D::x() const
{
    return m_x;
}

double Point2D::y() const
{
    return m_y;
}

double Point2D::r() const
{
    return std::sqrt(m_x*m_x + m_y*m_y);
}

double Point2D::theta() const
{
    return std::atan2(m_y, m_x);
}

double Point2D::angle_to(Point2D that) const
{
    double dx = that.x() - m_x;
    double dy = that.y() - m_y;
    return std::atan2(dy, dx);
}

int Point2D::ccw(Point2D a, Point2D b, Point2D c)
{
    double area2 = (b.x()-a.x())*(c.y()-a.y()) - (b.y()-a.y())*(c.x()-a.x());
    if      (area2 < 0) return -1;
    else if (area2 > 0) return +1;
    else                return  0;
}

double area2(Point2D a, Point2D b, Point2D c)
{
    return (b.x()-a.x())*(c.y()-a.y()) - (b.y()-a.y())*(c.x()-a.x());
}

double Point2D::distance_to(Point2D that) const
{
    double dx = m_x - that.x();
    double dy = m_y - that.y();
    return std::sqrt(dx*dx + dy*dy);
}

double Point2D::distance_squared_to(Point2D that) const
{
    double dx = m_x - that.x();
    double dy = m_y - that.y();
    return dx*dx + dy*dy;
}

// compare points according to their x-coordinate
bool Point2D::x_order(Point2D a, Point2D b)
{
    return a.x() < b.x();
}

// compare points according to their y-coordinate
bool Point2D::y_order(Point2D a, Point2D b)
{
    return a.y() < b.y();
}

// compare points according to their polar radius
bool Point2D::r_order(Point2D a, Point2D b)
{
    return (a.x()*a.x() + a.y()*a.y()) < (b.x()*b.x() + b.y()*b.y());
}


bool Point2D::polar_order(Point2D a, Point2D b) const
{
    double dx1 = a.x() - m_x;
    double dy1 = a.y() - m_y;
    double dx2 = b.x() - m_x;
    double dy2 = b.y() - m_y;

    if      (dy1 >= 0 && dy2 < 0) return -1;    // q1 above; q2 below
    else if (dy2 >= 0 && dy1 < 0) return +1;    // q1 below; q2 above
    else if (dy1 == 0 && dy2 == 0)              // 3-collinear and horizontal
    {            
        if      (dx1 >= 0 && dx2 < 0) return -1;
        else if (dx2 >= 0 && dx1 < 0) return +1;
        else                          return  0;
    }
    else return -ccw(*this, a, b);     // both above or below

    // Note: ccw() recomputes dx1, dy1, dx2, and dy2
}

bool Point2D::atan2_order(Point2D a, Point2D b) const
{
    double angle1 = angle_to(a);
    double angle2 = angle_to(b);

    return angle1 < angle2;
}

bool Point2D::distance_to_order(const Point2D a, const Point2D b) const
{
    double dist1 = distance_squared_to(a);
    double dist2 = distance_squared_to(b);
    
    return dist1 < dist2;
}

bool Point2D::operator==(Point2D& other) const
{
    if (&other == this) return false;
    return m_x == other.x() && m_y == other.y();
}

bool Point2D::operator!=(Point2D& other) const
{
    if (&other == this) return false;
    return m_y != other.y() || m_x != other.x();
}

bool Point2D::operator<(Point2D& other) const
{
    if (&other == this) return false;
    return m_y < other.y() && m_x < other.x();
}

bool Point2D::operator>(Point2D& other) const
{
    if (&other == this) return false;
    return m_y > other.y() && m_x > other.x();
}

bool Point2D::operator<=(Point2D& other) const
{
    if (&other == this) return false;
    return m_y <= other.y() && m_x <= other.x();
}

bool Point2D::operator>=(Point2D& other) const
{
    if (&other == this) return false;
    return m_y >= other.y() && m_x >= other.x();
}

std::string Point2D::to_string() const
{
    return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
}

std::ostream& operator<<(std::ostream& os, const Point2D& pt)
{
    os << pt.to_string();
    return os;
}

//TODO
size_t Point2D::hash_code()
{
    size_t hash_x = std::hash<double>{}(m_x);
    size_t hash_y = std::hash<double>{}(m_y);
    return 31*hash_x + hash_y;
}

/*void Point2D::draw()
{
    StdDraw.point(x, y);
}

void Point2D::drawTo(Point2D that)
{
    StdDraw.line(x, y, that.x, that.y);
}*/