#include "Accumulator.h"
#include "StdIn.h"
#include "StdOut.h"

/**
 * Unit tests the {@code Accumulator} data type.
 * Reads in a stream of real number from standard input;
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
    while (!StdIn::is_empty())
    {
        double x = StdIn::read_double();
        stats.add_data_value(x);
    }

    StdOut::printf("n      = %d\n",   stats.count());
    StdOut::printf("mean   = %.5f\n", stats.mean());
    StdOut::printf("stddev = %.5f\n", stats.stddev());
    StdOut::printf("var    = %.5f\n", stats.var());
    StdOut::println(stats);

    return 0;
}