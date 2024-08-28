#ifndef INSERTION_H
#define INSERTION_H

#include "StdOut.h"

/******************************************************************************
 *  Compilation:  javac Insertion.java
 *  Execution:    java Insertion < input.txt
 *  Dependencies: StdOut.java StdIn.java
 *  Data files:   https://algs4.cs.princeton.edu/21elementary/tiny.txt
 *                https://algs4.cs.princeton.edu/21elementary/words3.txt
 *
 *  Sorts a sequence of strings from standard input using insertion sort.
 *
 *  % more tiny.txt
 *  S O R T E X A M P L E
 *
 *  % java Insertion < tiny.txt
 *  A E E L M O P R S T X                 [ one string per line ]
 *
 *  % more words3.txt
 *  bed bug dad yes zoo ... all bad yet
 *
 *  % java Insertion < words3.txt
 *  all bad bed bug dad ... yes yet zoo   [ one string per line ]
 *
 ******************************************************************************/
/**
 *  The {@code Insertion} class provides static methods for sorting an
 *  array using insertion sort.
 *  <p>
 *  In the worst case, this implementation makes ~ &frac12; <em>n</em><sup>2</sup>
 *  compares and ~ &frac12; <em>n</em><sup>2</sup> exchanges to sort an array
 *  of length <em>n</em>. So, it is not suitable for sorting large arbitrary
 *  arrays. More precisely, the number of exchanges is exactly equal to the
 *  number of inversions. So, for example, it sorts a partially-sorted array
 *  in linear time.
 *  <p>
 *  This sorting algorithm is stable.
 *  It uses &Theta;(1) extra memory (not including the input array).
 *  <p>
 *  See <a href="https://algs4.cs.princeton.edu/21elementary/InsertionPedantic.java.html">InsertionPedantic.java</a>
 *  for a version that eliminates the compiler warning.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/21elementary">Section 2.1</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

template <typename T>
class Insertion
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
            for (int j = i; j > 0 && less(a[j], a[j-1]); j--)
            {
                exch(a, j, j-1);
            }
            assert(is_sorted(a, 0, i));
        }
        assert(is_sorted(a));
    }

    /**
     * Rearranges the subarray a[lo..hi) in ascending order, using the natural order.
     * @param a the array to be sorted
     * @param lo left endpoint (inclusive)
     * @param hi right endpoint (exclusive)
     */
    static void sort(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo + 1; i < hi; i++)
        {
            for (int j = i; j > lo && less(a[j], a[j-1]); j--)
            {
                exch(a, j, j-1);
            }
        }
        assert(is_sorted(a, lo, hi));
    }

    /**
     * Rearranges the array in ascending order, using a comparator.
     * @param a the array
     * @param comparator the comparator specifying the order
     */
    static void sort(std::vector<T>& a, cmp_func)
    {
        int n = a.size();
        for (int i = 1; i < n; i++)
        {
            for (int j = i; j > 0 && less(a[j], a[j-1], cmp); j--)
            {
                exch(a, j, j-1);
            }
            assert(is_sorted(a, 0, i, cmp));
        }
        assert(is_sorted(a, cmp));
    }

    /**
     * Rearranges the subarray a[lo..hi) in ascending order, using a comparator.
     * @param a the array
     * @param lo left endpoint (inclusive)
     * @param hi right endpoint (exclusive)
     * @param comparator the comparator specifying the order
     */
    static void sort(std::vector<T>& a, int lo, int hi, cmp_func)
    {
        for (int i = lo + 1; i < hi; i++)
        {
            for (int j = i; j > lo && less(a[j], a[j-1], cmp); j--)
            {
                exch(a, j, j-1);
            }
        }
        assert(is_sorted(a, lo, hi, cmp));
    }

    // return a permutation that gives the elements in a[] in ascending order
    // do not change the original array a[]
    /**
     * Returns a permutation that gives the elements in the array in ascending order.
     * @param a the array
     * @return a permutation {@code p[]} such that {@code a[p[0]]}, {@code a[p[1]]},
     *    ..., {@code a[p[n-1]]} are in ascending order
     */
    static std::vector<int> index_sort(std::vector<T> a)
    {
        int n = a.size();
        std::vector<int> index = std::vector<int>(n);
        for (int i = 0; i < n; i++)
            index[i] = i;

        for (int i = 1; i < n; i++)
            for (int j = i; j > 0 && less(a[index[j]], a[index[j-1]]); j--)
                exch(index, j, j-1);

        return index;
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
    *  Helper sorting functions.
    ***************************************************************************/

    // is v < w ?
    static bool less(T v, T w)
    {
        return v < w;
    }

    // is v < w ?
    static bool less(T v, T w, cmp_func)
    {
        return (*cmp)(v, w);
    }

    // exchange a[i] and a[j]
    static void exch(std::vector<T>& a, int i, int j)
    {
        T swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

    /***************************************************************************
    *  Check if array is sorted - useful for debugging.
    ***************************************************************************/

    static bool is_sorted(std::vector<T>& a)
    {
        return is_sorted(a, 0, a.size());
    }

    // is the array a[lo..hi) sorted
    static bool is_sorted(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo + 1; i < hi; i++)
            if (less(a[i], a[i-1])) return false;
        return true;
    }

    static bool is_sorted(std::vector<T>& a, cmp_func)
    {
        return is_sorted(a, 0, a.size(), cmp);
    }
    
    // is the array a[lo..hi) sorted
    static bool is_sorted(std::vector<T>& a, int lo, int hi, cmp_func)
    {
        for (int i = lo + 1; i < hi; i++)
            if (less(a[i], a[i-1], cmp)) return false;
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