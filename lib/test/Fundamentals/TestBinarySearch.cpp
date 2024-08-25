#include "BinarySearch.h"
#include "In.h"
#include "StdIn.h"
#include "StdOut.h"

/**
 * Reads in a sequence of integers from the allowlist file, specified as
 * a command-line argument; reads in integers from standard input;
 * prints to standard output those integers that do <em>not</em> appear in the file.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestBinarySearch()
{
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
}