#ifndef POINT2D_H
#define POINT2D_H

/******************************************************************************
 *  Compilation:  javac Point2D.java
 *  Execution:    java Point2D x0 y0 n
 *  Dependencies: StdDraw.java StdRandom.java
 *
 *  Immutable point data type for points in the plane.
 *
 ******************************************************************************/
/**
 *  The {@code Point} class is an immutable data type to encapsulate a
 *  two-dimensional point with real-value coordinates.
 *  <p>
 *  Note: in order to deal with the difference behavior of double and
 *  Double with respect to -0.0 and +0.0, the Point2D constructor converts
 *  any coordinates that are -0.0 to +0.0.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

struct Point2D
{
    /**
     * Compares two points by x-coordinate.
     */
    static bool x_order(Point2D a, Point2D b);

    /**
     * Compares two points by y-coordinate.
     */
    static bool y_order(Point2D a, Point2D b);

    /**
     * Compares two points by polar radius.
     */
    static bool r_order(Point2D a, Point2D b);

    /**
     * Initializes a new point (x, y).
     * @param x the x-coordinate
     * @param y the y-coordinate
     * @throws IllegalArgumentException if either {@code x} or {@code y}
     *    is {@code Double.NaN}, {@code Double.POSITIVE_INFINITY} or
     *    {@code Double.NEGATIVE_INFINITY}
     */
    Point2D(double x, double y);

    /**
     * Returns the x-coordinate.
     * @return the x-coordinate
     */
    double x() const;

    /**
     * Returns the y-coordinate.
     * @return the y-coordinate
     */
    double y() const;

    /**
     * Returns the polar radius of this point.
     * @return the polar radius of this point in polar coordinates: sqrt(x*x + y*y)
     */
    double r() const;

    /**
     * Returns the angle of this point in polar coordinates.
     * @return the angle (in radians) of this point in polar coordinates (between –&pi; and &pi;)
     */
    double theta() const;

    /**
     * Returns true if a→b→c is a counterclockwise turn.
     * @param a first point
     * @param b second point
     * @param c third point
     * @return { -1, 0, +1 } if a→b→c is a { clockwise, collinear; counterclockwise } turn.
     */
    static int ccw(Point2D a, Point2D b, Point2D c);

    /**
     * Returns twice the signed area of the triangle a-b-c.
     * @param a first point
     * @param b second point
     * @param c third point
     * @return twice the signed area of the triangle a-b-c
     */
    static double area2(Point2D a, Point2D b, Point2D c);

    /**
     * Returns the Euclidean distance between this point and that point.
     * @param that the other point
     * @return the Euclidean distance between this point and that point
     */
    double distance_to(Point2D that) const;

    /**
     * Returns the square of the Euclidean distance between this point and that point.
     * @param that the other point
     * @return the square of the Euclidean distance between this point and that point
     */
    double distance_squared_to(Point2D that) const;

    /**
     * Compares two points by polar angle (between 0 and 2&pi;) with respect to this point.
     *
     * @return the comparator
     */
    bool polar_order(Point2D a, Point2D b) const;

    /**
     * Compares two points by atan2() angle (between –&pi; and &pi;) with respect to this point.
     *
     * @return the comparator
     */
    bool atan2_order(Point2D a, Point2D b) const;

    /**
     * Compares two points by distance to this point.
     *
     * @return the comparator
     */
    bool distance_to_order(Point2D a, Point2D b) const;

    /**
     * Compares this point to the specified point.
     *
     * @param  other the other point
     * @return {@code true} if this point equals {@code other};
     *         {@code false} otherwise
     */
    bool operator==(Point2D& other) const;
    bool operator!=(Point2D& other) const;
    bool operator<(Point2D& other) const;
    bool operator>(Point2D& other) const;
    bool operator<=(Point2D& other) const;
    bool operator>=(Point2D& other) const;

    /**
     * Return a string representation of this point.
     * @return a string representation of this point in the format (x, y)
     */
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Point2D& pt);

    /**
     * Returns an integer hash code for this point.
     * @return an integer hash code for this point
     */
    size_t hash_code();

    /**
     * Plot this point using standard draw.
     */
    //void draw();

    /**
     * Plot a line from this point to that point using standard draw.
     * @param that the other point
     */
    //void drawTo(Point2D that);

private:
    double m_x;    // x coordinate
    double m_y;    // y coordinate

     /**
     * Returns the angle between this point and that point.
     * @return the angle in radians (between –&pi; and &pi;) between this point and that point (0 if equal)
     */
    double angle_to(Point2D that) const;
};

/******************************************************************************
 *  Copyright 2002-2022, Robert Sedgewick and Kevin Wayne.
 *
 *  This file is part of algs4.jar, which accompanies the textbook
 *
 *      Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne,
 *      Addison-Wesley Professional, 2011, ISBN 0-321-57351-X.
 *      http://algs4.cs.princeton.edu
 *
 *
 *  algs4.jar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  algs4.jar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with algs4.jar.  If not, see http://www.gnu.org/licenses.
 ******************************************************************************/

#endif