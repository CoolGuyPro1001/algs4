#ifndef RECTHV_H
#define RECTHV_H

/******************************************************************************
 *  Compilation:  javac RectHV.java
 *  Execution:    none
 *  Dependencies: Point2D.java
 *
 *  Immutable data type for 2D axis-aligned rectangle.
 *
 ******************************************************************************/

#include "Point2D.h"

/**
 *  The {@code RectHV} class is an immutable data type to encapsulate a
 *  two-dimensional axis-aligned rectagle with real-value coordinates.
 *  The rectangle is <em>closed</em>—it includes the points on the boundary.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

struct RectHV
{
public:
    /**
     * Initializes a new rectangle [<em>xmin</em>, <em>xmax</em>]
     * x [<em>ymin</em>, <em>ymax</em>].
     *
     * @param  xmin the <em>x</em>-coordinate of the lower-left endpoint
     * @param  ymin the <em>y</em>-coordinate of the lower-left endpoint
     * @param  xmax the <em>x</em>-coordinate of the upper-right endpoint
     * @param  ymax the <em>y</em>-coordinate of the upper-right endpoint
     * @throws IllegalArgumentException if any of {@code xmin},
     *         {@code ymin}, {@code xmax}, or {@code ymax}
     *         is {@code Double.NaN}.
     * @throws IllegalArgumentException if {@code xmax < xmin} or {@code ymax < ymin}.
     */
    RectHV(double xmin, double ymin, double xmax, double ymax);

    /**
     * Returns the minimum <em>x</em>-coordinate of any point in this rectangle.
     *
     * @return the minimum <em>x</em>-coordinate of any point in this rectangle
     */
    double xmin() const;

    /**
     * Returns the maximum <em>x</em>-coordinate of any point in this rectangle.
     *
     * @return the maximum <em>x</em>-coordinate of any point in this rectangle
     */
    double xmax() const;

    /**
     * Returns the minimum <em>y</em>-coordinate of any point in this rectangle.
     *
     * @return the minimum <em>y</em>-coordinate of any point in this rectangle
     */
    double ymin() const;

    /**
     * Returns the maximum <em>y</em>-coordinate of any point in this rectangle.
     *
     * @return the maximum <em>y</em>-coordinate of any point in this rectangle
     */
    double ymax() const;

    /**
     * Returns the width of this rectangle.
     *
     * @return the width of this rectangle {@code xmax - xmin}
     */
    double width() const;

    /**
     * Returns the height of this rectangle.
     *
     * @return the height of this rectangle {@code ymax - ymin}
     */
    double height() const;

    /**
     * Returns true if the two rectangles intersect, and false otherwise.
     * This includes <em>improper intersections</em> (at points on the
     * boundary of each rectangle) and <em>nested intersections</em>
     * (when one rectangle is contained inside the other).
     *
     * @param  that the other rectangle
     * @return {@code true} if this rectangle intersects the argument
               rectangle at one or more points; false otherwise
     */
    bool intersects(RectHV that) const;

    /**
     * Returns true if this rectangle contains the point, and false otherwise.
     * This includes point on the boundary of the rectangle.
     * @param  p the point
     * @return {@code true} if this rectangle contains the point {@code p},
               possibly at the boundary; {@code false} otherwise
     */
    bool contains(Point2D p) const;

    /**
     * Returns the Euclidean distance between this rectangle and the point {@code p}.
     *
     * @param  p the point
     * @return the Euclidean distance between the point {@code p} and the closest point
               on this rectangle; 0 if the point is contained in this rectangle
     */
    double distance_to(Point2D p) const;

    /**
     * Returns the square of the Euclidean distance between this rectangle and the point {@code p}.
     *
     * @param  p the point
     * @return the square of the Euclidean distance between the point {@code p} and
     *         the closest point on this rectangle; 0 if the point is contained
     *         in this rectangle
     */
    double distance_squared_to(Point2D p) const;

    /**
     * Compares this rectangle to the specified rectangle.
     *
     * @param  other the other rectangle
     * @return {@code true} if this rectangle equals {@code other};
     *         {@code false} otherwise
     */
    bool operator==(const RectHV& other) const;
    bool operator!=(const RectHV& other) const;

    /**
     * Returns an integer hash code for this rectangle.
     * @return an integer hash code for this rectangle
     */
    /*@Override
    int hash_code() {
        int hash1 = ((Double) xmin).hashCode();
        int hash2 = ((Double) ymin).hashCode();
        int hash3 = ((Double) xmax).hashCode();
        int hash4 = ((Double) ymax).hashCode();
        return 31*(31*(31*hash1 + hash2) + hash3) + hash4;
    }*/

    /**
     * Returns a string representation of this rectangle.
     *
     * @return a string representation of this rectangle, using the format
     *         {@code [xmin, xmax] x [ymin, ymax]}
     */
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const RectHV& r);

    /**
     * Draws this rectangle to standard draw.
     */
    void draw() const;

private:
    double m_xmin, m_ymin;   // minimum x- and y-coordinates
    double m_xmax, m_ymax;   // maximum x- and y-coordinates
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