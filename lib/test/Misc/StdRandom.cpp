#include "StdRandom.h"
#include "StdOut.h"

/**
 * Unit tests the methods in this class.
 *
 * @param args the command-line arguments
 */
int main(int argc, char** argv)
{
    if (argc != 3) return -1;

    int n = atoi(argv[1]);
    StdRandom::set_seed(atol(argv[2]));
    std::vector<double> probabilities = { 0.5, 0.3, 0.1, 0.1 };
    std::vector<int> frequencies = { 5, 3, 1, 1 };
    std::vector<std::string> a = {"A", "B", "C", "D", "E", "F", "G"};

    StdOut::printf("seed = %d\n", StdRandom::get_seed());
    for (int i = 0; i < n; i++)
    {
        StdOut::printf("%2d ",   StdRandom::uniform_int(100));
        StdOut::printf("%8.5f ", StdRandom::uniform_double(10.0, 99.0));
        StdOut::printf("%5d ",   (int) StdRandom::bernoulli(-1.5));
        StdOut::printf("%7.5f ", StdRandom::gaussian(9.0, 0.2));
        StdOut::printf("%1d ",   StdRandom::discrete(probabilities));
        StdOut::printf("%1d ",   StdRandom::discrete(frequencies));
        StdOut::printf("%11d ",  StdRandom::uniform_long(100000000000L));
        StdRandom::shuffle(a);
        for (auto it = a.begin(); it != a.end(); it++)
            StdOut::print(*it);
        StdOut::println();
    }
}