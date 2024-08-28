#include "Merge.h"
#include "StdIn.h"

/**
 * Reads in a sequence of strings from standard input; mergesorts them;
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestMerge(int argc, char** argv)
{
    std::vector<std::string> a = StdIn::read_all_strings();
    Merge<std::string>::sort(a);
    Merge<std::string>::show(a);

    return 0;
}