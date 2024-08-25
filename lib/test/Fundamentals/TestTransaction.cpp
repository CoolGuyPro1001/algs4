#include "Transaction.h"
#include "StdOut.h"

/**
    * Unit tests the {@code Transaction} data type.
    *
    * @param args the command-line arguments
*/
int Fundamentals_TestTransaction(int argc, char** argv)
{
    std::vector<Transaction> a = std::vector<Transaction>();
    a.emplace_back(Transaction("Turing   6/17/1990  644.08"));
    a.emplace_back(Transaction("Tarjan   3/26/2002 4121.85"));
    a.emplace_back(Transaction("Knuth    6/14/1999  288.34"));
    a.emplace_back(Transaction("Dijkstra 8/22/2007 2678.40"));

    StdOut::println("Unsorted");
    for (int i = 0; i < a.size(); i++)
        StdOut::println(a[i]);
    StdOut::println();

    StdOut::println("Sort by date");
    std::sort(a.begin(), a.end(), Transaction::when_order);
    for (int i = 0; i < a.size(); i++)
        StdOut::println(a[i]);
    StdOut::println();

    StdOut::println("Sort by customer");
    std::sort(a.begin(), a.end(), Transaction::who_order);
    for (int i = 0; i < a.size(); i++)
        StdOut::println(a[i]);
    StdOut::println();

    StdOut::println("Sort by amount");
    std::sort(a.begin(), a.end(), Transaction::how_much_order);
    for (int i = 0; i < a.size(); i++)
        StdOut::println(a[i]);
    StdOut::println();

    return 0;
}