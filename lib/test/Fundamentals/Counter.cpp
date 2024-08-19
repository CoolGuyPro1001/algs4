#include "Counter.h"
#include "StdRandom.h"
#include "StdOut.h"

/**
    * Reads two command-line integers n and trials; creates n counters;
    * increments trials counters at random; and prints results.
    *
    * @param args the command-line arguments
*/
int main(int argc, char** argv)
{
    if (argc < 3)
        return 0;

    int n = atoi(argv[1]);
    int trials = atoi(argv[2]);

    // create n counters
    std::vector<Counter> hits = std::vector<Counter>();
    hits.reserve(n * 2);
    for (int i = 0; i < n; i++) 
    {
        hits.push_back(Counter("counter " + std::to_string(i)));
    }

    // increment trials counters at random
    for (int t = 0; t < trials; t++)
    {
        hits[StdRandom::uniform_int(n)].increment();
    }

    // print results
    for (int i = 0; i < n; i++)
    {
        StdOut::println(hits[i]);
    }
}