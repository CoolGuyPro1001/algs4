#include "ThreeSumFast.h"

/**
 * Reads in a sequence of distinct integers from a file, specified as a command-line argument;
 * counts the number of triples sum to exactly zero; prints out the time to perform
 * the computation.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestThreeSumFast(int argc, char** argv)
{
    In in = new In(args[0]);
    int[] a = in.readAllInts();
    int count = count(a);
    StdOut::println(count);

    return 0;
}