#include "QuickX.h"
#include "StdOut.h"
#include "In.h"

/**
 * Reads in a sequence of strings from standard input; quicksorts them
 * (using an optimized version of 2-way quicksort);
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestQuickX(int argc, char** argv)
{
    In tiny_file("res/tiny.txt");
    std::vector<std::string> tiny_data = tiny_file.read_all_strings();
    QuickX<std::string>::sort(tiny_data);
    StdOut::println("Sorted Tiny Data");
    QuickX<std::string>::show(tiny_data);
    if (!QuickX<std::string>::is_sorted(tiny_data)) return 1;
    StdOut::println();

    In words3_file("res/words3.txt");
    std::vector<std::string> words3_data = words3_file.read_all_strings();
    QuickX<std::string>::sort(words3_data);
    StdOut::println("Sorted Words3 Data");
    QuickX<std::string>::show(words3_data);
    if (!QuickX<std::string>::is_sorted(words3_data)) return 1;

    return 0;
}