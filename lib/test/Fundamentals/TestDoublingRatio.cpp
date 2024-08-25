#include "DoublingRatio.h"
#include "StdOut.h"

/**
 * Prints table of running times to call {@code ThreeSum.count()}
 * for arrays of size 250, 500, 1000, 2000, and so forth, along
 * with ratios of running times between successive array sizes.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestDoublingRatio(int argc, char** argv)
{
    double prev = time_trial(125);
    for (int n = 250; true; n += n)
    {
        double time = time_trial(n);
        StdOut::printf("%7d %7.1f %5.1f\n", n, time, time/prev);
        prev = time;
    }

    return 0;
}