#include "QuickBentleyMcIlroy.h"
#include "StdIn.h"

/**
 * Reads in a sequence of strings from standard input; quicksorts them
 * (using an optimized version of quicksort);
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestQuickBentleyMcIlroy(int argc, char** argv)
{
    std::vector<std::string> a = StdIn::read_all_strings();
    QuickBentleyMcIlroy<std::string>::sort(a);
    assert(QuickBentleyMcIlroy<std::string>::is_sorted(a));
    QuickBentleyMcIlroy<std::string>::show(a);

    return 0;
}