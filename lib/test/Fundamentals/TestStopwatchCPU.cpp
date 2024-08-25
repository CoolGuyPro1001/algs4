#include "StopwatchCPU.h"
#include "StdOut.h"

/**
 * Unit tests the {@code StopwatchCPU} data type.
 * Takes a command-line argument {@code n} and computes the
 * sum of the square roots of the first {@code n} positive integers,
 * first using {@code Math.sqrt()}, then using {@code Math.pow()}.
 * It prints to standard output the sum and the amount of time to
 * compute the sum. Note that the discrete sum can be approximated by
 * an integral - the sum should be approximately 2/3 * (n^(3/2) - 1).
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestStopwatchCPU(int argc, char** argv)
{
    if (argc != 2) return -1;
    int n = atoi(argv[1]);

    // sum of square roots of integers from 1 to n using Math.sqrt(x).
    StopwatchCPU timer1 = StopwatchCPU();
    double sum1 = 0.0;
    for (int i = 1; i <= n; i++)
    {
        sum1 += std::sqrt(i); 
    }
    double time1 = timer1.elapsed_time();
    StdOut::printf("%e (%.2f seconds)\n", sum1, time1);

    // sum of square roots of integers from 1 to n using Math.pow(x, 0.5).
    StopwatchCPU timer2 = StopwatchCPU();
    double sum2 = 0.0;
    for (int i = 1; i <= n; i++)
    {
        sum2 += std::pow(i, 0.5);
    }
    double time2 = timer2.elapsed_time();
    StdOut::printf("%e (%.2f seconds)\n", sum2, time2);

    return 0;
}