#include "Point2D.h"
#include <cmath>


Point2D::Point2D(double x, double y)
{
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

double Point2D::r()
{
    return std::sqrt(m_x*m_x + m_y*m_y);
}

double Point2D::theta()
{
    return std::atan2(m_y, m_x);
}

double Point2D::angleTo(Point2D that)
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

double Point2D::distanceTo(Point2D that)
{
    double dx = m_x - that.x();
    double dy = m_y - that.y();
    return std::sqrt(dx*dx + dy*dy);
}

double Point2D::distanceSquaredTo(Point2D that)
{
    double dx = m_x - that.x();
    double dy = m_y - that.y();
    return dx*dx + dy*dy;
}

int Point2D::compareTo(Point2D that)
{
    if (m_y < that.y()) return -1;
    if (m_y > that.y()) return +1;
    if (m_x < that.x()) return -1;
    if (m_x > that.x()) return +1;
    return 0;
}

// compare points according to their x-coordinate
bool Point2D::xOrder(Point2D a, Point2D b)
{
    return a.x() < b.x();
}

// compare points according to their y-coordinate
bool Point2D::yOrder(Point2D a, Point2D b)
{
    return a.y() < b.y();
}

// compare points according to their polar radius
bool Point2D::rOrder(Point2D a, Point2D b)
{
    return (a.x()*a.x() + a.y()*a.y()) < (b.x()*b.x() + b.y()*b.y());
}


bool Point2D::polarOrder(Point2D a, Point2D b)
{
    double dx1 = a.x() - x();
    double dy1 = a.y() - y();
    double dx2 = b.x() - x();
    double dy2 = b.y() - y();

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

bool Point2D::atan2Order(Point2D a, Point2D b)
{
    double angle1 = angleTo(a);
    double angle2 = angleTo(b);

    return angle1 < angle2;
}

/**
 * Compares two points by distance to this point.
 *
 * @return the comparator
 */
bool Point2D::distanceToOrder(const Point2D a, const Point2D b)
{
    double dist1 = distanceSquaredTo(a);
    double dist2 = distanceSquaredTo(b);
    
    return dist1 < dist2;
}

bool Point2D::operator==(Point2D other)
{
    if (&other == this) return true;
    if (&other == nullptr) return false;

    return m_x == other.x() && m_y == other.y();
}

std::ostream& operator<<(std::ostream &os, const Point2D &pt)
{
    os << "(" << pt.x() << ", " << pt.y() << ")";
    return os;
}

//TODO
/*int Point2D::hashCode()
{
    int hashX = ((Double) x).hashCode();
    int hashY = ((Double) y).hashCode();
    return 31*hashX + hashY;
}*/

/*void Point2D::draw()
{
    StdDraw.point(x, y);
}

void Point2D::drawTo(Point2D that)
{
    StdDraw.line(x, y, that.x, that.y);
}


/**
 * Unit tests the point data type.
 *
 * @param args the command-line arguments
 
int main(int argc, char** argv) 
{
    int x0 = atoi(argv[0]);
    int y0 = atoi(argv[1]);
    int n = atoi(argv[2]);

    StdDraw.setCanvasSize(800, 800);
    StdDraw.setXscale(0, 100);
    StdDraw.setYscale(0, 100);
    StdDraw.setPenRadius(0.005);
    StdDraw.enableDoubleBuffering();

    Point2D[] points = new Point2D[n];
    for (int i = 0; i < n; i++) {
        int x = StdRandom.uniformInt(100);
        int y = StdRandom.uniformInt(100);
        points[i] = new Point2D(x, y);
        points[i].draw();
    }

    // draw p = (x0, x1) in red
    Point2D p = new Point2D(x0, y0);
    StdDraw.setPenColor(StdDraw.RED);
    StdDraw.setPenRadius(0.02);
    p.draw();


    // draw line segments from p to each point, one at a time, in polar order
    StdDraw.setPenRadius();
    StdDraw.setPenColor(StdDraw.BLUE);
    Arrays.sort(points, p.polarOrder());
    for (int i = 0; i < n; i++) {
        p.drawTo(points[i]);
        StdDraw.show();
        StdDraw.pause(100);
    }
}*/