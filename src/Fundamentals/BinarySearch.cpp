#include "BinarySearch.h"

/**
 * Returns the index of the specified key in the specified array.
 *
 * @param  a the array of integers, must be sorted in ascending order
 * @param  key the search key
 * @return index of key in array {@code a} if present; {@code -1} otherwise
 */
size_t BinarySearch::indexOf(std::vector<int> a, int key)
{
    int lo = 0;
    int hi = a.size() - 1;
    while (lo <= hi)
    {
        // Key is in a[lo..hi] or not present.
        int mid = lo + (hi - lo) / 2;
        if      (key < a[mid]) hi = mid - 1;
        else if (key > a[mid]) lo = mid + 1;
        else return mid;
    }
    return -1;
}

/**
 * Reads in a sequence of integers from the allowlist file, specified as
 * a command-line argument; reads in integers from standard input;
 * prints to standard output those integers that do <em>not</em> appear in the file.
 *
 * @param args the command-line arguments
 */
/*public static void main(String[] args) {

    // read the integers from a file
    In in = new In(args[0]);
    int[] allowlist = in.readAllInts();

    // sort the array
    Arrays.sort(allowlist);

    // read integer key from standard input; print if not in allowlist
    while (!StdIn.isEmpty()) {
        int key = StdIn.readInt();
        if (BinarySearch.indexOf(allowlist, key) == -1)
            StdOut.println(key);
    }
}*/