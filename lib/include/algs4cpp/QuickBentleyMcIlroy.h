#ifndef QUICKBENTLEYMCILROY_H
#define QUICKBENTLEYMCILROY_H

#include "StdOut.h"

/******************************************************************************
 *  Compilation:  javac QuickBentleyMcIlroy.java
 *  Execution:    java QuickBentleyMcIlroy < input.txt
 *  Dependencies: StdOut.java StdIn.java
 *  Data files:   https://algs4.cs.princeton.edu/23quicksort/tiny.txt
 *                https://algs4.cs.princeton.edu/23quicksort/words3.txt
 *
 *  Uses the Bentley-McIlroy 3-way partitioning scheme,
 *  chooses the partitioning element using Tukey's ninther,
 *  and cuts off to insertion sort.
 *
 *  Reference: Engineering a Sort Function by Jon L. Bentley
 *  and M. Douglas McIlroy. Software-Practice and Experience,
 *  Vol. 23 (11), 1249-1265 (November 1993).
 *
 ******************************************************************************/

/**
 *  The {@code QuickBentleyMcIlroy} class provides static methods for sorting
 *  an array using an optimized version of quicksort (using Bentley-McIlroy
 *  3-way partitioning, Tukey's ninther, and cutoff to insertion sort).
 *  <p>
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/23quicksort">Section 2.3</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename T>
class QuickBentleyMcIlroy
{
public:
    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    static void sort(std::vector<T>& a)
    {
        sort(a, 0, a.size() - 1);
    }

    /***************************************************************************
    *  Check if array is sorted - useful for debugging.
    ***************************************************************************/
    static bool is_sorted(std::vector<T>& a)
    {
        for (int i = 1; i < a.size(); i++)
            if (less(a[i], a[i-1])) return false;
        return true;
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
    // cutoff to insertion sort, must be >= 1
    static const int INSERTION_SORT_CUTOFF = 8;

    // cutoff to median-of-3 partitioning
    static const int MEDIAN_OF_3_CUTOFF = 40;

    static void sort(std::vector<T>& a, int lo, int hi)
    {
        int n = hi - lo + 1;

        // cutoff to insertion sort
        if (n <= INSERTION_SORT_CUTOFF)
        {
            insertion_sort(a, lo, hi);
            return;
        }

        // use median-of-3 as partitioning element
        else if (n <= MEDIAN_OF_3_CUTOFF)
        {
            int m = median3(a, lo, lo + n/2, hi);
            exch(a, m, lo);
        }

        // use Tukey ninther as partitioning element
        else
        {
            int eps = n/8;
            int mid = lo + n/2;
            int m1 = median3(a, lo, lo + eps, lo + eps + eps);
            int m2 = median3(a, mid - eps, mid, mid + eps);
            int m3 = median3(a, hi - eps - eps, hi - eps, hi);
            int ninther = median3(a, m1, m2, m3);
            exch(a, ninther, lo);
        }

        // Bentley-McIlroy 3-way partitioning
        int i = lo, j = hi+1;
        int p = lo, q = hi+1;
        T v = a[lo];
        while (true)
        {
            while (less(a[++i], v))
                if (i == hi) break;
            while (less(v, a[--j]))
                if (j == lo) break;

            // pointers cross
            if (i == j && eq(a[i], v))
                exch(a, ++p, i);
            if (i >= j) break;

            exch(a, i, j);
            if (eq(a[i], v)) exch(a, ++p, i);
            if (eq(a[j], v)) exch(a, --q, j);
        }


        i = j + 1;
        for (int k = lo; k <= p; k++)
            exch(a, k, j--);
        for (int k = hi; k >= q; k--)
            exch(a, k, i++);

        sort(a, lo, j);
        sort(a, i, hi);
    }


    // sort from a[lo] to a[hi] using insertion sort
    static void insertion_sort(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && less(a[j], a[j-1]); j--)
                exch(a, j, j-1);
    }


    // return the index of the median element among a[i], a[j], and a[k]
    static int median3(std::vector<T>& a, int i, int j, int k)
    {
        return (less(a[i], a[j]) ?
               (less(a[j], a[k]) ? j : less(a[i], a[k]) ? k : i) :
               (less(a[k], a[j]) ? j : less(a[k], a[i]) ? k : i));
    }

   /***************************************************************************
    *  Helper sorting functions.
    ***************************************************************************/

    // is v < w ?
    static bool less(T v, T w)
    {
        if (v == w) return false;    // optimization when reference equal
        return v < w;
    }

    // does v == w ?
    static bool eq(T v, T w)
    {
        if (v == w) return true;    // optimization when reference equal
        return v == w;
    }

    // exchange a[i] and a[j]
    static void exch(std::vector<T>& a, int i, int j)
    {
        T swap = a[i];
        a[i] = a[j];
        a[j] = swap;
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