#include "ThreeSum.h"

/**
 * Reads in a sequence of integers from a file, specified as a command-line argument;
 * counts the number of triples sum to exactly zero; prints out the time to perform
 * the computation.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestThreeSum(int argc, char** argv)
{
    In in = new In(args[0]);
    int[] a = in.readAllInts();

    Stopwatch timer = new Stopwatch();
    int count = count(a);
    StdOut::println("elapsed time = " + timer.elapsedTime());
    StdOut::println(count);

    return 0;
}