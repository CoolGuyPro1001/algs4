#ifndef STOPWATCH_H
#define STOPWATCH_H

/******************************************************************************
 *  Compilation:  javac Stopwatch.java
 *  Execution:    java Stopwatch n
 *  Dependencies: none
 *
 *  A utility class to measure the running time (wall clock) of a program.
 *
 *  % java8 Stopwatch 100000000
 *  6.666667e+11  0.5820 seconds
 *  6.666667e+11  8.4530 seconds
 *
 ******************************************************************************/

/**
 *  The {@code Stopwatch} data type is for measuring
 *  the time that elapses between the start and end of a
 *  programming task (wall-clock time).
 *
 *  To measure the running time of a code fragment, construct a
 *  <code>Stopwatch</code> object, execute the code you want to time,
 *  and then call the <code>elapsedTime()</code> method to get the
 *  elapsed time in seconds.
 *  <pre>
 *
 *   Stopwatch stopwatch = new Stopwatch();
 *
 *   // do some computationally intensive calculation here
 *
 *   double time = stopwatch.elapsedTime();
 *  </pre>
 *  <p>
 *
 *  See {@link StopwatchCPU} for a version that measures CPU time.
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/14analysis">Section 1.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */


class Stopwatch 
{
public:
    /**
     * Initializes a new stopwatch.
     */
    Stopwatch();

    /**
     * Returns the elapsed CPU time (in seconds) since the stopwatch was created.
     *
     * @return elapsed CPU time (in seconds) since the stopwatch was created
     */
    double elapsed_time();

private:
    std::chrono::high_resolution_clock::time_point m_start;
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