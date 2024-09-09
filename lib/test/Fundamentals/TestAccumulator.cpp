#include "Accumulator.h"
#include "In.h"
#include "StdOut.h"

/**
 * Unit tests the {@code Accumulator} data type.
 * Reads in a stream of real number from stats.txt;
 * adds them to the accumulator; and prints the mean,
 * sample standard deviation, and sample variance to standard
 * output.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestAccumulator(int argc, char** argv)
{
    std::cin.clear();
    Accumulator stats = Accumulator();
    In in("res/stats.txt");
    std::vector<double> all_data = in.read_all_doubles();

    for (auto it = all_data.begin(); it != all_data.end(); it++)
    {
        stats.add_data_value(*it);
    }

    /**
     * It's very difficult to have two doubles be exactly the same.
     * Have the accuracy be within 0.001. 
    */

    StdOut::printf("n      = %d\n",   stats.count());
    if (stats.count() != 100) return -1;

    StdOut::printf("mean   = %.5f\n", stats.mean());
    if (std::abs(stats.mean() - (-4.337)) > 0.001) return 1;

    StdOut::printf("stddev = %.5f\n", stats.stddev());
    if (std::abs(stats.stddev() - 57.958) > 0.001) return 1;

    StdOut::printf("var    = %.5f\n", stats.var());
    if (std::abs(stats.var() - 3359.207) > 0.001) return 1;

    StdOut::println(stats);
    return 0;
}