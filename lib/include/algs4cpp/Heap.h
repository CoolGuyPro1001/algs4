#ifndef HEAP_H
#define HEAP_H

#include "Heap.h"
#include "StdOut.h"

/******************************************************************************
 *  Compilation:  javac Heap.java
 *  Execution:    java Heap < input.txt
 *  Dependencies: StdOut.java StdIn.java
 *  Data files:   https://algs4.cs.princeton.edu/24pq/tiny.txt
 *                https://algs4.cs.princeton.edu/24pq/words3.txt
 *
 *  Sorts a sequence of strings from standard input using heapsort.
 *
 *  % more tiny.txt
 *  S O R T E X A M P L E
 *
 *  % java Heap < tiny.txt
 *  A E E L M O P R S T X                 [ one string per line ]
 *
 *  % more words3.txt
 *  bed bug dad yes zoo ... all bad yet
 *
 *  % java Heap < words3.txt
 *  all bad bed bug dad ... yes yet zoo   [ one string per line ]
 *
 ******************************************************************************/

/**
 *  The {@code Heap} class provides a static method to sort an array
 *  using <em>heapsort</em>.
 *  <p>
 *  This implementation takes &Theta;(<em>n</em> log <em>n</em>) time
 *  to sort any array of length <em>n</em> (assuming comparisons
 *  take constant time). It makes at most
 *  2 <em>n</em> log<sub>2</sub> <em>n</em> compares.
 *  <p>
 *  This sorting algorithm is not stable.
 *  It uses &Theta;(1) extra memory (not including the input array).
 *  <p>
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/24pq">Section 2.4</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename T>
class Heap
{
public:
    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param pq the array to be sorted
     */
    static void sort(std::vector<T>& pq)
    {
        int n = pq.size();

        // heapify phase
        for (int k = n/2; k >= 1; k--)
            sink(pq, k, n);

        // sortdown phase
        int k = n;
        while (k > 1)
        {
            exch(pq, 1, k--);
            sink(pq, 1, k);
        }
    }

    // print array to standard output
    static void show(std::vector<T>& a)
    {
        for (int i = 0; i < a.size(); i++)
        {
            StdOut::println(a[i]);
        }
    }

private:
   /***************************************************************************
    * Helper functions to restore the heap invariant.
    ***************************************************************************/

    static void sink(std::vector<T>& pq, int k, int n)
    {
        while (2 * k <= n)
        {
            int j = 2 * k;
            if (j < n && less(pq, j, j+1)) j++;
            if (!less(pq, k, j)) break;
            exch(pq, k, j);
            k = j;
        }
    }

   /***************************************************************************
    * Helper functions for comparisons and swaps.
    * Indices are "off-by-one" to support 1-based indexing.
    ***************************************************************************/
    static bool less(std::vector<T>& pq, int i, int j)
    {
        return pq[i-1] < pq[j-1];
    }

    static void exch(std::vector<T>& pq, int i, int j)
    {
        T swap = pq[i-1];
        pq[i-1] = pq[j-1];
        pq[j-1] = swap;
    }
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