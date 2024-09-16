#ifndef INVERSIONS_H
#define INVERSIONS_H

/******************************************************************************
 *  Compilation:  javac Inversions.java
 *  Execution:    java Inversions < input.txt
 *  Dependencies: StdIn.java StdOut.java
 *
 *  Read array of n integers and count number of inversions in n log n time.
 *
 ******************************************************************************/

/**
 *  The {@code Inversions} class provides static methods to count the
 *  number of <em>inversions</em> in either an array of integers or comparables.
 *  An inversion in an array {@code a[]} is a pair of indicies {@code i} and
 *  {@code j} such that {@code i < j} and {@code a[i] > a[j]}.
 *  <p>
 *  This implementation uses a generalization of mergesort. The <em>count</em>
 *  operation takes &Theta;(<em>n</em> log <em>n</em>) time to count the
 *  number of inversions in any array of length <em>n</em> (assuming
 *  comparisons take constant time).
 *  <p>
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/22mergesort">Section 2.2</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
namespace Inversions
{
    // is v < w ?
    template <typename Key>
    bool less(Key v, Key w)
    {
        return v < w;
    }

    // count number of inversions in a[lo..hi] via brute force (for debugging only)
    template <typename Key>
    long brute(std::vector<Key>& a, int lo, int hi)
    {
        long inversions = 0;
        for (int i = lo; i <= hi; i++)
            for (int j = i + 1; j <= hi; j++)
                if (less(a[j], a[i])) inversions++;
        return inversions;
    } 

    // merge and count (Comparable version)
    template <typename Key>
    long merge(std::vector<Key>& a, std::vector<Key>& aux, int lo, int mid, int hi)
    {
        long inversions = 0;

        // copy to aux[]
        std::copy(a.begin(), a.end(), aux.begin());

        // merge back to a[]
        int i = lo, j = mid+1;
        for (int k = lo; k <= hi; k++)
        {
            if      (i > mid)                a[k] = aux[j++];
            else if (j > hi)                 a[k] = aux[i++];
            else if (less(aux[j], aux[i])) { a[k] = aux[j++]; inversions += (mid - i + 1); }
            else                             a[k] = aux[i++];
        }
        return inversions;
    }

    // return the number of inversions in the subarray b[lo..hi]
    // side effect b[lo..hi] is rearranged in ascending order
    template <typename Key>
    long count(std::vector<Key>& a, std::vector<Key>& b, std::vector<Key>& aux, int lo, int hi)
    {
        long inversions = 0;
        if (hi <= lo) return 0;
        int mid = lo + (hi - lo) / 2;
        inversions += count(a, b, aux, lo, mid);
        inversions += count(a, b, aux, mid+1, hi);
        inversions += merge(b, aux, lo, mid, hi);
        assert(inversions == brute<Key>(a, lo, hi));
        return inversions;
    }

    /**
     * Returns the number of inversions in the comparable array.
     * The argument array is not modified.
     * @param  a the array
     * @param <Key> the inferred type of the elements in the array
     * @return the number of inversions in the array. An inversion is a pair of
     *         indicies {@code i} and {@code j} such that {@code i < j}
     *         and {@code a[i].compareTo(a[j]) > 0}.
     */
    template <typename Key>
    long count(std::vector<Key>& a)
    {
        std::vector<Key> b = std::vector<Key>(a.begin(), a.end());
        std::vector<Key> aux = std::vector<Key>(a.begin(), a.end());
        long inversions = count(a, b, aux, 0, a.size() - 1);
        return inversions;
    }
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