#include "Inversions.h"
#include "StdOut.h"
#include "StdIn.h"

/**
 * Reads a sequence of integers from standard input and
 * prints the number of inversions to standard output.
 *
 * @param args the command-line arguments
 */
int Sorting_TestInversions(int argc, char** argv)
{
    std::vector<int> a; 
    while (!StdIn::is_empty())
    {
        a.push_back(StdIn::read_int());
    }
    StdOut::println(Inversions::count(a));

    return 0;
}