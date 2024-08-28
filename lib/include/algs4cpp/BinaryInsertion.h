#ifndef BINARYINSERTION_H
#define BINARYINSERTION_H

#include "StdOut.h"

/******************************************************************************
 *  Compilation:  javac BinaryInsertion.java
 *  Execution:    java BinaryInsertion < input.txt
 *  Dependencies: StdOut.java StdIn.java
 *  Data files:   https://algs4.cs.princeton.edu/21elementary/tiny.txt
 *                https://algs4.cs.princeton.edu/21elementary/words3.txt
 *
 *  Sorts a sequence of strings from standard input using
 *  binary insertion sort with half exchanges.
 *
 *  % more tiny.txt
 *  S O R T E X A M P L E
 *
 *  % java BinaryInsertion < tiny.txt
 *  A E E L M O P R S T X                 [ one string per line ]
 *
 *  % more words3.txt
 *  bed bug dad yes zoo ... all bad yet
 *
 *  % java BinaryInsertion < words3.txt
 *  all bad bed bug dad ... yes yet zoo   [ one string per line ]
 *
 ******************************************************************************/

/**
 *  The {@code BinaryInsertion} class provides a static method for sorting an
 *  array using an optimized binary insertion sort with half exchanges.
 *  <p>
 *  In the worst case, this implementation makes
 *  ~ <em>n</em> log<sub>2</sub><em>n</em> compares to sort an array of length
 *  <em>n</em>. However, in the worst case, the running time is
 *  &Theta;(<em>n</em><sup>2</sup>) because the number of array accesses
 *  can be quadratic.
 *  As such, it is not suitable for sorting large arrays
 *  (unless the number of inversions is small).
 *  <p>
 *  This sorting algorithm is stable.
 *  It uses &Theta;(1) extra memory (not including the input array).
 *  <p>
 *  For additional documentation,
 *  see <a href="https://algs4.cs.princeton.edu/21elementary">Section 2.1</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Ivan Pesin
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename T>
class BinaryInsertion
{
public:
    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    static void sort(std::vector<T>& a)
    {
        int n = a.size();
        for (int i = 1; i < n; i++)
        {
            // binary search to determine index j at which to insert a[i]
            T v = a[i];
            int lo = 0, hi = i;
            while (lo < hi)
            {
                int mid = lo + (hi - lo) / 2;
                if (less(v, a[mid])) hi = mid;
                else                 lo = mid + 1;
            }

            // insertion sort with "half exchanges"
            // (insert a[i] at index j and shift a[j], ..., a[i-1] to right)
            for (int j = i; j > lo; --j)
                a[j] = a[j-1];
            a[lo] = v;
        }
        assert(is_sorted(a));
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
    *  Helper sorting function.
    ***************************************************************************/

    // is v < w ?
    static bool less(T v, T w)
    {
        return v < w; 
    }

   /***************************************************************************
    *  Check if array is sorted - useful for debugging.
    ***************************************************************************/
    static bool is_sorted(std::vector<T>& a)
    {
        return is_sorted(a, 0, a.size() - 1);
    }

    // is the array sorted from a[lo] to a[hi]
    static bool is_sorted(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo + 1; i <= hi; i++)
            if (less(a[i], a[i-1])) return false;
        return true;
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