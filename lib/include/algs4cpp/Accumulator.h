#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

/******************************************************************************
 *  Compilation:  javac Accumulator.java
 *  Execution:    java Accumulator < input.txt
 *  Dependencies: StdOut.java StdIn.java
 *
 *  Mutable data type that calculates the mean, sample standard
 *  deviation, and sample variance of a stream of real numbers
 *  use a stable, one-pass algorithm.
 *
 ******************************************************************************/

/**
 *  The {@code Accumulator} class is a data type for computing the running
 *  mean, sample standard deviation, and sample variance of a stream of real
 *  numbers. It provides an example of a mutable data type and a streaming
 *  algorithm.
 *  <p>
 *  This implementation uses a one-pass algorithm that is less susceptible
 *  to floating-point roundoff error than the more straightforward
 *  implementation based on saving the sum of the squares of the numbers.
 *  This technique is due to
 *  <a href = "https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance#Welford's_online_algorithm">B. P. Welford</a>.
 *  Each operation takes constant time in the worst case.
 *  The amount of memory is constant - the data values are not stored.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Accumulator
{
public:

    /**
     * Adds the specified data value to the accumulator.
     * @param  x the data value
     */
    void add_data_value(double x);

    /**
     * Returns the mean of the data values.
     * @return the mean of the data values
     */
    double mean() const;

    /**
     * Returns the sample variance of the data values.
     * @return the sample variance of the data values
     */
    double var() const;

    /**
     * Returns the sample standard deviation of the data values.
     * @return the sample standard deviation of the data values
     */
    double stddev() const;

    /**
     * Returns the number of data values.
     * @return the number of data values
     */
    int count() const;

    /**
     * Returns a string representation of this accumulator.
     * @return a string representation of this accumulator
     */
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Accumulator& acc);
    
private:
    int m_n = 0;          // number of data values
    double m_sum = 0.0;   // sample variance * (n-1)
    double m_mu = 0.0;    // sample mean
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