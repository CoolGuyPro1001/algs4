#ifndef SELECTION_H
#define SELECTION_H

#include "StdOut.h"

/******************************************************************************
 *  Compilation:  javac Selection.java
 *  Execution:    java  Selection < input.txt
 *  Dependencies: StdOut.java StdIn.java
 *  Data files:   https://algs4.cs.princeton.edu/21elementary/tiny.txt
 *                https://algs4.cs.princeton.edu/21elementary/words3.txt
 *
 *  Sorts a sequence of strings from standard input using selection sort.
 *
 *  % more tiny.txt
 *  S O R T E X A M P L E
 *
 *  % java Selection < tiny.txt
 *  A E E L M O P R S T X                 [ one string per line ]
 *
 *  % more words3.txt
 *  bed bug dad yes zoo ... all bad yet
 *
 *  % java Selection < words3.txt
 *  all bad bed bug dad ... yes yet zoo    [ one string per line ]
 *
 ******************************************************************************/

/**
 *  The {@code Selection} class provides static methods for sorting an
 *  array using <em>selection sort</em>.
 *  This implementation makes ~ &frac12; <em>n</em><sup>2</sup> compares to sort
 *  any array of length <em>n</em>, so it is not suitable for sorting large arrays.
 *  It performs exactly <em>n</em> exchanges.
 *  <p>
 *  This sorting algorithm is not stable. It uses &Theta;(1) extra memory
 *  (not including the input array).
 *  <p>
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/21elementary">Section 2.1</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
template <typename T>
class Selection
{
public:
    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    static void sort(std::vector<T>& a)
    {
        int n = a.size();
        for (int i = 0; i < n; i++)
        {
            int min = i;
            for (int j = i+1; j < n; j++)
            {
                if (less(a[j], a[min])) min = j;
            }
            exch(a, i, min);
            assert(is_sorted(a, 0, i));
        }
        assert(is_sorted(a));
    }

    /**
     * Rearranges the array in ascending order, using a comparator.
     * @param a the array
     * @param comparator the comparator specifying the order
     */
    static void sort(std::vector<T>& a, cmp_func)
    {
        int n = a.size();
        for (int i = 0; i < n; i++)
        {
            int min = i;
            for (int j = i+1; j < n; j++)
            {
                if (less(cmp, a[j], a[min])) min = j;
            }
            exch(a, i, min);
            assert(is_sorted(a, cmp, 0, i));
        }
        assert(is_sorted(a, cmp));
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
    static bool less(cmp_func, T v, T w)
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

    // is the array a[] sorted?
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

    // is the array a[] sorted?
    static bool is_sorted(std::vector<T>& a, cmp_func)
    {
        return is_sorted(a, cmp, 0, a.size() - 1);
    }

    // is the array sorted from a[lo] to a[hi]
    static bool is_sorted(std::vector<T>& a, cmp_func, int lo, int hi)
    {
        for (int i = lo + 1; i <= hi; i++)
            if (less(cmp, a[i], a[i-1])) return false;
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