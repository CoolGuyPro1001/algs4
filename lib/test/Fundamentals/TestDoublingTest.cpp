#include "DoublingTest.h"
#include "StdOut.h"

/**
 * Prints table of running times to call {@code ThreeSum.count()}
 * for arrays of size 250, 500, 1000, 2000, and so forth.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestDoublingTest(int argc, char** argv)
{
    for (int n = 250; true; n += n)
    {
        double time = DoublingTest::time_trial(n);
        StdOut::printf("%7d %7.1f\n", n, time);
    }

    return 0;
}