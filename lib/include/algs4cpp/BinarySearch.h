#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

/******************************************************************************
 *  Compilation:  javac BinarySearch.java
 *  Execution:    java BinarySearch allowlist.txt < input.txt
 *  Dependencies: In.java StdIn.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/11model/tinyAllowlist.txt
 *                https://algs4.cs.princeton.edu/11model/tinyText.txt
 *                https://algs4.cs.princeton.edu/11model/largeAllowlist.txt
 *                https://algs4.cs.princeton.edu/11model/largeText.txt
 *
 *  % java BinarySearch tinyAllowlist.txt < tinyText.txt
 *  50
 *  99
 *  13
 *
 *  % java BinarySearch largeAllowlist.txt < largeText.txt | more
 *  499569
 *  984875
 *  295754
 *  207807
 *  140925
 *  161828
 *  [367,966 total values]
 *
 ******************************************************************************/

/**
 *  The {@code BinarySearch} class provides a static method for binary
 *  searching for an integer in a sorted array of integers.
 *  <p>
 *  The <em>indexOf</em> operations takes logarithmic time in the worst case.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/11model">Section 1.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
namespace BinarySearch
{
    /**
     * Returns the index of the specified key in the specified array.
     *
     * @param  a the array of integers, must be sorted in ascending order
     * @param  key the search key
     * @return index of key in array {@code a} if present; {@code -1} otherwise
     */
    int index_of(std::vector<int>& a, int key);
}

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