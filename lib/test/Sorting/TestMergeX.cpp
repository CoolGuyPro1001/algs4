#include "MergeX.h"
#include "StdIn.h"

/**
 * Reads in a sequence of strings from standard input; mergesorts them
 * (using an optimized version of mergesort);
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestMergeX(int argc, char** argv)
{
    std::vector<std::string> a = StdIn::read_all_strings();
    MergeX<std::string>::sort(a);
    MergeX<std::string>::show(a);

    return 0;
}