#ifndef INTERVAL1D_H
#define INTERVAL1D_H

/******************************************************************************
 *  Compilation:  javac Interval1D.java
 *  Execution:    java Interval1D
 *  Dependencies: StdOut.java
 *
 *  1-dimensional interval data type.
 *
 ******************************************************************************/

/**
 *  The {@code Interval1D} class represents a one-dimensional interval.
 *  The interval is <em>closed</em>—it contains both endpoints.
 *  Intervals are immutable: their values cannot be changed after they are created.
 *  The class {@code Interval1D} includes methods for checking whether
 *  an interval contains a point and determining whether two intervals intersect.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
struct Interval1D
{
public:
    /**
     * Compares two intervals by min endpoint.
     */
    static bool min_endpoint_compare(Interval1D a, Interval1D b);

    /**
     * Compares two intervals by max endpoint.
     */
    static bool max_endpoint_compare(Interval1D a, Interval1D b);

    /**
     * Compares two intervals by length.
     */
    static bool length_compare(Interval1D a, Interval1D b);

    /**
     * Initializes a closed interval [min, max].
     *
     * @param  min the smaller endpoint
     * @param  max the larger endpoint
     * @throws IllegalArgumentException if the min endpoint is greater than the max endpoint
     * @throws IllegalArgumentException if either {@code min} or {@code max}
     *         is {@code Double.NaN}, {@code Double.POSITIVE_INFINITY} or
     *         {@code Double.NEGATIVE_INFINITY}

     */
    Interval1D(double min, double max);

    /**
     * Returns the min endpoint of this interval.
     *
     * @return the min endpoint of this interval
     */
    double min() const;

    /**
     * Returns the max endpoint of this interval.
     *
     * @return the max endpoint of this interval
     */
    double max() const;

    /**
     * Returns true if this interval intersects the specified interval.
     *
     * @param  that the other interval
     * @return {@code true} if this interval intersects the argument interval;
     *         {@code false} otherwise
     */
    bool intersects(Interval1D that) const;

    /**
     * Returns true if this interval contains the specified value.
     *
     * @param x the value
     * @return {@code true} if this interval contains the value {@code x};
     *         {@code false} otherwise
     */
    bool contains(double x) const;

    /**
     * Returns the length of this interval.
     *
     * @return the length of this interval (max - min)
     */
    double length() const;

    /**
     * Returns a string representation of this interval.
     *
     * @return a string representation of this interval in the form [min, max]
     */
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Interval1D& i);

    /**
     * Compares this transaction to the specified object.
     *
     * @param  other the other interval
     * @return {@code true} if this interval equals the other interval;
     *         {@code false} otherwise
     */
    bool operator==(const Interval1D& other) const;
    bool operator!=(const Interval1D& other) const;

    /**
     * Returns an integer hash code for this interval.
     *
     * @return an integer hash code for this interval
     */
    size_t hash_code();

private:
    double m_min;
    double m_max;
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