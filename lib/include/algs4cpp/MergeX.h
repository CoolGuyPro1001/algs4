#ifndef MERGEX_H
#define MERGEX_H

#include "StdOut.h"

/******************************************************************************
 *  Compilation:  javac MergeX.java
 *  Execution:    java MergeX < input.txt
 *  Dependencies: StdOut.java StdIn.java
 *  Data files:   https://algs4.cs.princeton.edu/22mergesort/tiny.txt
 *                https://algs4.cs.princeton.edu/22mergesort/words3.txt
 *
 *  Sorts a sequence of strings from standard input using an
 *  optimized version of mergesort.
 *
 *  % more tiny.txt
 *  S O R T E X A M P L E
 *
 *  % java MergeX < tiny.txt
 *  A E E L M O P R S T X                 [ one string per line ]
 *
 *  % more words3.txt
 *  bed bug dad yes zoo ... all bad yet
 *
 *  % java MergeX < words3.txt
 *  all bad bed bug dad ... yes yet zoo    [ one string per line ]
 *
 ******************************************************************************/

/**
 *  The {@code MergeX} class provides static methods for sorting an
 *  array using an optimized version of mergesort.
 *  <p>
 *  In the worst case, this implementation takes
 *  &Theta;(<em>n</em> log <em>n</em>) time to sort an array of
 *  length <em>n</em> (assuming comparisons take constant time).
 *  <p>
 *  This sorting algorithm is stable.
 *  It uses &Theta;(<em>n</em>) extra memory (not including the input array).
 *  <p>
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/22mergesort">Section 2.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename T>
class MergeX
{
public: 
    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    static void sort(std::vector<T>& a)
    {
        std::vector<T> aux = std::vector<T>(a.begin(), a.end());
        sort(aux, a, 0, a.size()-1);
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
    static const int CUTOFF = 7;  // cutoff to insertion sort

    static void merge(std::vector<T>& src, std::vector<T>& dst, int lo, int mid, int hi) {

        // precondition: src[lo .. mid] and src[mid+1 .. hi] are sorted subarrays
        assert(is_sorted(src, lo, mid));
        assert(is_sorted(src, mid+1, hi));

        int i = lo, j = mid+1;
        for (int k = lo; k <= hi; k++)
        {
            if      (i > mid)              dst[k] = src[j++];
            else if (j > hi)               dst[k] = src[i++];
            else if (less(src[j], src[i])) dst[k] = src[j++];   // to ensure stability
            else                           dst[k] = src[i++];
        }

        // postcondition: dst[lo .. hi] is sorted subarray
        assert(is_sorted(dst, lo, hi));
    }

    static void sort(std::vector<T>& src, std::vector<T>& dst, int lo, int hi)
    {
        // if (hi <= lo) return;
        if (hi <= lo + CUTOFF)
        {
            insertion_sort(dst, lo, hi);
            return;
        }
        int mid = lo + (hi - lo) / 2;
        sort(dst, src, lo, mid);
        sort(dst, src, mid+1, hi);

        if (!less(src[mid+1], src[mid]))
        {
            std::copy(src.begin() + lo, src.begin() + hi + 1, dst.begin() + lo);
            return;
        }

        merge(src, dst, lo, mid, hi);
    }

    /*******************************************************************
     *  Version that takes Comparator as argument.
     *******************************************************************/

    /**
     * Rearranges the array in ascending order, using the provided order.
     *
     * @param a the array to be sorted
     * @param comparator the comparator that defines the total order
     */
    static void sort(std::vector<T>& a, cmp_func)
    {
        std::vector<T> aux = a.clone();
        sort(aux, a, 0, a.size()-1, cmp);
        assert(is_sorted(a, cmp));
    }

private:
    // sort from a[lo] to a[hi] using insertion sort
    static void insertion_sort(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && less(a[j], a[j-1]); j--)
                exch(a, j, j-1);
    }


    /*******************************************************************
     *  Utility methods.
     *******************************************************************/

    // exchange a[i] and a[j]
    static void exch(std::vector<T>& a, int i, int j)
    {
        T swap = a[i];
        a[i] = a[j];
        a[j] = swap;
    }

    // is a[i] < a[j]?
    static bool less(T a, T b)
    {
        return a < b;
    }

    // is a[i] < a[j]?
    static bool less(T a, T b, cmp_func)
    {
        return (*cmp)(a, b);
    }


    /*******************************************************************
     *  Version that takes Comparator as argument.
     *******************************************************************/

    static void merge(std::vector<T>& src, std::vector<T>& dst, int lo, int mid, int hi, cmp_func)
    {

        // precondition: src[lo .. mid] and src[mid+1 .. hi] are sorted subarrays
        assert(is_sorted(src, lo, mid, cmp));
        assert(is_sorted(src, mid+1, hi, cmp));

        int i = lo, j = mid+1;
        for (int k = lo; k <= hi; k++)
        {
            if      (i > mid)                          dst[k] = src[j++];
            else if (j > hi)                           dst[k] = src[i++];
            else if (less(src[j], src[i], cmp)) dst[k] = src[j++];
            else                                       dst[k] = src[i++];
        }

        // postcondition: dst[lo .. hi] is sorted subarray
        assert(is_sorted(dst, lo, hi, cmp));
    }

    static void sort(std::vector<T>& src, std::vector<T>& dst, int lo, int hi, cmp_func)
    {
        if (hi <= lo + CUTOFF)
        {
            insertion_sort(dst, lo, hi, cmp);
            return;
        }
        int mid = lo + (hi - lo) / 2;
        sort(dst, src, lo, mid, cmp);
        sort(dst, src, mid+1, hi, cmp);

        // using System.arraycopy() is a bit faster than the above loop
        if (!less(src[mid+1], src[mid], cmp))
        {
            std::copy(src.begin() + lo, src.begin() + hi + 1, dst.begin() + lo);            return;
        }

        merge(src, dst, lo, mid, hi, cmp);
    }

    // sort from a[lo] to a[hi] using insertion sort
    static void insertion_sort(std::vector<T>& a, int lo, int hi, cmp_func)
    {
        for (int i = lo; i <= hi; i++)
            for (int j = i; j > lo && less(a[j], a[j-1], cmp); j--)
                exch(a, j, j-1);
    }


   /***************************************************************************
    *  Check if array is sorted - useful for debugging.
    ***************************************************************************/
    static bool is_sorted(std::vector<T>& a)
    {
        return is_sorted(a, 0, a.size() - 1);
    }

    static bool is_sorted(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo + 1; i <= hi; i++)
            if (less(a[i], a[i-1])) return false;
        return true;
    }

    static bool is_sorted(std::vector<T>& a, cmp_func)
    {
        return is_sorted(a, 0, a.size() - 1, cmp);
    }

    static bool is_sorted(std::vector<T>& a, int lo, int hi, cmp_func)
    {
        for (int i = lo + 1; i <= hi; i++)
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