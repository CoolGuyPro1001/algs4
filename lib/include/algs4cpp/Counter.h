#ifndef COUNTER_H
#define COUNTER_H

/******************************************************************************
 *  Compilation:  javac Counter.java
 *  Execution:    java Counter n trials
 *  Dependencies: StdRandom.java StdOut.java
 *
 *  A mutable data type for an integer counter.
 *
 *  The test clients create n counters and performs trials increment
 *  operations on random counters.
 *
 * java Counter 6 600000
 *  100140 counter0
 *  100273 counter1
 *  99848 counter2
 *  100129 counter3
 *  99973 counter4
 *  99637 counter5
 *
 ******************************************************************************/

/**
 *  The {@code Counter} class is a mutable data type to encapsulate a counter.
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/12oop">Section 1.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Counter
{
public:
    /**
     * Initializes a new counter starting at 0, with the given id.
     *
     * @param id the name of the counter
     */
    Counter(std::string id);

    /**
     * Increments the counter by 1.
     */
    void increment();

    /**
     * Returns the current value of this counter.
     *
     * @return the current value of this counter
     */
    int tally() const;

    /**
     * Returns a string representation of this counter.
     *
     * @return a string representation of this counter
     */
    std::string to_string() const;
    friend std::ostream& operator<<(std::ostream& os, const Counter& c);

    /**
     * Compares this counter to the specified counter.
     *
     * @param  that the other counter
     * @return {@code 0} if the value of this counter equals
     *         the value of that counter; a negative integer if
     *         the value of this counter is less than the value of
     *         that counter; and a positive integer if the value
     *         of this counter is greater than the value of that
     *         counter
     */
    bool operator==(const Counter& other) const;
    bool operator!=(const Counter& other) const;
    bool operator<(const Counter& other) const;
    bool operator>(const Counter& other) const;
    bool operator<=(const Counter& other) const;
    bool operator>=(const Counter& other) const;

private:
    std::string m_name;     // counter name
    int m_count = 0;         // current value
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