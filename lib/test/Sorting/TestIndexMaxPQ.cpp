#include "IndexMaxPQ.h"
#include "In.h"
#include "StdOut.h"
#include "StdRandom.h"

/**
 * Unit tests the {@code IndexMaxPQ} data type.
 *
 * @param args the command-line arguments
 */
int Sorting_TestIndexMaxPQ(int argc, char** argv)
{
    // insert a bunch of strings
    std::vector<std::string> strings = { "it", "was", "the", "best", "of", "times", "it", "was", "the", "worst" };

    IndexMaxPQ<std::string> pq = IndexMaxPQ<std::string>(strings.size());
    for (int i = 0; i < strings.size(); i++)
    {
        pq.insert(i, strings[i]);
    }

    // print each key using the iterator
    for (int i : pq)
    {
        StdOut::printf("%d %s\n", i, strings[i].c_str());
    }

    StdOut::println();

    // increase or decrease the key
    for (int i = 0; i < strings.size(); i++)
    {
        if (StdRandom::bernoulli(0.5))
            pq.increase_key(i, strings[i] + strings[i]);
        else
            pq.decrease_key(i, strings[i].substr(0, 1));
    }

    // delete and print each key
    while (!pq.is_empty())
    {
        std::string key = pq.max_key();
        int i = pq.del_max();
        StdOut::printf("%d %s\n", i, key.c_str());
    }
    StdOut::println();

    // reinsert the same strings
    for (int i = 0; i < strings.size(); i++)
    {
        pq.insert(i, strings[i]);
    }

    // delete them in random order
    std::vector<int> perm = std::vector<int>(strings.size());
    for (int i = 0; i < strings.size(); i++)
        perm[i] = i;

    StdRandom::shuffle(perm);
    for (int i = 0; i < perm.size(); i++)
    {
        std::string key = pq.key_of(perm[i]);
        pq.delete_key(perm[i]);
        StdOut::printf(("%d %s\n"), perm[i], key.c_str());
    }

    return 0;
}