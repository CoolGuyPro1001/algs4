#include "QuickX.h"
#include "StdIn.h"

/**
 * Reads in a sequence of strings from standard input; quicksorts them
 * (using an optimized version of 2-way quicksort);
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestQuickX(int argc, char** argv)
{
    std::vector<std::string> a = StdIn::read_all_strings();
    QuickX<std::string>::sort(a);
    assert(QuickX<std::string>::is_sorted(a));
    QuickX<std::string>::show(a);

    return 0;
}