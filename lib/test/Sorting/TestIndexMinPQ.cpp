#include "IndexMinPQ.h"
#include "In.h"
#include "StdOut.h"

/**
 * Unit tests the {@code IndexMaxPQ} data type.
 *
 * @param args the command-line arguments
 */
int Sorting_TestIndexMinPQ(int argc, char** argv)
{
    // insert a bunch of strings
    std::vector<std::string> strings = { "it", "was", "the", "best", "of", "times", "it", "was", "the", "worst" };

    IndexMinPQ<std::string> pq = IndexMinPQ<std::string>(strings.size());
    for (int i = 0; i < strings.size(); i++)
    {
        pq.insert(i, strings[i]);
    }

    // delete and print each key
    while (!pq.is_empty())
    {
        int i = pq.del_min();
        StdOut::printf("%d %s\n", i, strings[i].c_str());
    }
    StdOut::println();

    // reinsert the same strings
    for (int i = 0; i < strings.size(); i++)
    {
        pq.insert(i, strings[i]);
    }

    // print each key using the iterator
    for (int i : pq)
    {
        StdOut::printf("%d %s\n", i, strings[i].c_str());
    }
    while (!pq.is_empty())
    {
        pq.del_min();
    }

    return 0;
}