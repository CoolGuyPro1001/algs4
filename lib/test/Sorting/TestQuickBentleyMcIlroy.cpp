#include "QuickBentleyMcIlroy.h"
#include "StdOut.h"
#include "In.h"

/**
 * Reads in a sequence of strings from standard input; quicksorts them
 * (using an optimized version of quicksort);
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestQuickBentleyMcIlroy(int argc, char** argv)
{
    In tiny_file("res/tiny.txt");
    std::vector<std::string> tiny_data = tiny_file.read_all_strings();
    QuickBentleyMcIlroy<std::string>::sort(tiny_data);
    StdOut::println("Sorted Tiny Data");
    QuickBentleyMcIlroy<std::string>::show(tiny_data);
    if (!QuickBentleyMcIlroy<std::string>::is_sorted(tiny_data)) return 1;
    StdOut::println();

    In words3_file("res/words3.txt");
    std::vector<std::string> words3_data = words3_file.read_all_strings();
    QuickBentleyMcIlroy<std::string>::sort(words3_data);
    StdOut::println("Sorted Words3 Data");
    QuickBentleyMcIlroy<std::string>::show(words3_data);
    if (!QuickBentleyMcIlroy<std::string>::is_sorted(words3_data)) return 1;

    return 0;
}