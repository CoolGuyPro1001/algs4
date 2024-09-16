#ifndef STOPWATCHCPU_H
#define STOPWATCHCPU_H

/******************************************************************************
 *  Compilation:  javac StopwatchCPU.java
 *  Execution:    java StopwatchCPU n
 *  Dependencies: none
 *
 *  A version of Stopwatch.java that measures CPU time on a single
 *  core or processor (instead of wall clock time).
 *
 *  % java8 StopwatchCPU 100000000
 *  6.666667e+11 (1.05 seconds)
 *  6.666667e+11 (7.50 seconds)
 *
 ******************************************************************************/

/**
 *  The {@code StopwatchCPU} data type is for measuring
 *  the CPU time used during a programming task.
 *
 *  See {@link Stopwatch} for a version that measures wall-clock time
 *  (the real time that elapses).
 *
 *  @author Josh Hug
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

class StopwatchCPU
{
public:
    /**
     * Initializes a new stopwatch.
     */
    StopwatchCPU(); 

    /**
     * Returns the elapsed CPU time (in seconds) since the stopwatch was created.
     *
     * @return elapsed CPU time (in seconds) since the stopwatch was created
     */
    double elapsed_time() const; 
 
private: 
    std::clock_t m_start;
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