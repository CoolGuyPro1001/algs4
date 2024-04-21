#ifndef MERGE_H
#define MERGE_H

/******************************************************************************
 *  Compilation:  javac Merge.java
 *  Execution:    java Merge < input.txt
 *  Dependencies: StdOut.java StdIn.java
 *  Data files:   https://algs4.cs.princeton.edu/22mergesort/tiny.txt
 *                https://algs4.cs.princeton.edu/22mergesort/words3.txt
 *
 *  Sorts a sequence of strings from standard input using mergesort.
 *
 *  % more tiny.txt
 *  S O R T E X A M P L E
 *
 *  % java Merge < tiny.txt
 *  A E E L M O P R S T X                 [ one string per line ]
 *
 *  % more words3.txt
 *  bed bug dad yes zoo ... all bad yet
 *
 *  % java Merge < words3.txt
 *  all bad bed bug dad ... yes yet zoo    [ one string per line ]
 *
 ******************************************************************************/

/**
 *  The {@code Merge} class provides methods for sorting an
 *  array using a top-down, recursive version of <em>mergesort</em>.
 *  <p>
 *  This implementation takes &Theta;(<em>n</em> log <em>n</em>) time
 *  to sort any array of length <em>n</em> (assuming comparisons
 *  take constant time). It makes between
 *  ~ &frac12; <em>n</em> log<sub>2</sub> <em>n</em> and
 *  ~ 1 <em>n</em> log<sub>2</sub> <em>n</em> compares.
 *  <p>
 *  This sorting algorithm is stable.
 *  It uses &Theta;(<em>n</em>) extra memory (not including the input array).
 *  <p>
 *  For additional documentation, see
 *  <a href="https://algs4.cs.princeton.edu/22mergesort">Section 2.2</a> of
 *  <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *  For an optimized version, see {@link MergeX}.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class Merge
{
public:
    /**
     * Rearranges the array in ascending order, using the natural order.
     * @param a the array to be sorted
     */
    template <typename T>
    static void sort(std::vector<T>& a)
    {
        std::vector<T> aux = std::vector<T>(a.size());
        sort(a, aux, 0, a.size()-1);
        assert(isSorted(a));
    }

    /**
     * Returns a permutation that gives the elements in the array in ascending order.
     * @param a the array
     * @return a permutation {@code p[]} such that {@code a[p[0]]}, {@code a[p[1]]},
     *    ..., {@code a[p[n-1]]} are in ascending order
     */
    template <typename T>
    static std::vector<int> indexSort(std::vector<T>& a)
    {
        int n = a.size();
        std::vector<int> index = std::vector<int>(n);
        for (int i = 0; i < n; i++)
            index[i] = i;

        std::vector<int> aux = std::vector<int>(n);
        sort(a, index, aux, 0, n-1);
        return index;
    }

    //TODO
    // print array to standard output
    /*private void show(std::vector<T>& a) {
        for (int i = 0; i < a.size(); i++) {
            StdOut.println(a[i]);
        }
    }*/

private:
    // stably merge a[lo .. mid] with a[mid+1 ..hi] using aux[lo .. hi]
    template <typename T>
    static void merge(std::vector<T>& a, std::vector<T>& aux, int lo, int mid, int hi)
    {
        // precondition: a[lo .. mid] and a[mid+1 .. hi] are sorted subarrays
        assert(isSorted(a, lo, mid));
        assert(isSorted(a, mid+1, hi));

        // copy to aux[]
        for (int k = lo; k <= hi; k++)
        {
            aux[k] = a[k];
        }

        // merge back to a[]
        int i = lo, j = mid+1;
        for (int k = lo; k <= hi; k++)
        {
            if      (i > mid)              a[k] = aux[j++];
            else if (j > hi)               a[k] = aux[i++];
            else if (less(aux[j], aux[i])) a[k] = aux[j++];
            else                           a[k] = aux[i++];
        }

        // postcondition: a[lo .. hi] is sorted
        assert(isSorted(a, lo, hi));
    }

    // mergesort a[lo..hi] using auxiliary array aux[lo..hi]
    template <typename T>
    static void sort(std::vector<T>& a, std::vector<T>& aux, int lo, int hi)
    {
        if (hi <= lo) return;
        int mid = lo + (hi - lo) / 2;
        sort(a, aux, lo, mid);
        sort(a, aux, mid + 1, hi);
        merge(a, aux, lo, mid, hi);
    }


    /***************************************************************************
    *  Helper sorting function.
    ***************************************************************************/

    template <typename T>
    static bool less(T v, T w)
    {
        return v < w;
    }

    /***************************************************************************
    *  Check if array is sorted - useful for debugging.
    ***************************************************************************/

    template <typename T>
    static bool isSorted(std::vector<T>& a)
    {
        return isSorted(a, 0, a.size() - 1);
    }

    template <typename T>
    static bool isSorted(std::vector<T>& a, int lo, int hi)
    {
        for (int i = lo + 1; i <= hi; i++)
            if (less(a[i], a[i-1])) return false;
        return true;
    }


    /***************************************************************************
    *  Index mergesort.
    ***************************************************************************/
    template <typename T>
    static void merge(std::vector<T>& a, 
        std::vector<int>& index, std::vector<int>& aux, int lo, int mid, int hi)
    {

        // copy to aux[]
        for (int k = lo; k <= hi; k++)
        {
            aux[k] = index[k];
        }

        // merge back to a[]
        int i = lo, j = mid+1;
        for (int k = lo; k <= hi; k++)
        {
            if      (i > mid)                    index[k] = aux[j++];
            else if (j > hi)                     index[k] = aux[i++];
            else if (less(a[aux[j]], a[aux[i]])) index[k] = aux[j++];
            else                                 index[k] = aux[i++];
        }
    }

    template <typename T>
    static void sort(std::vector<T>& a, 
        std::vector<int>& index, std::vector<int>& aux, int lo, int hi)
    {
        if (hi <= lo) return;
        int mid = lo + (hi - lo) / 2;
        sort(a, index, aux, lo, mid);
        sort(a, index, aux, mid + 1, hi);
        merge(a, index, aux, lo, mid, hi);
    }

    /*template <typename T>
    void show(std::vector<T>& a)
    {
        for (int i = 0; i < a.size(); i++)
        {
            StdOut.println(a[i]);
        }
    }*/
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