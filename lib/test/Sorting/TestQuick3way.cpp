#include "Quick3way.h"
#include "StdOut.h"
#include "In.h"

/**
 * Reads in a sequence of strings from standard input; 3-way
 * quicksorts them; and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestQuick3way(int argc, char** argv)
{
    In tiny_file("res/tiny.txt");
    std::vector<std::string> tiny_data = tiny_file.read_all_strings();
    Quick3way<std::string>::sort(tiny_data);
    StdOut::println("Sorted Tiny Data");
    Quick3way<std::string>::show(tiny_data);
    if (!Quick3way<std::string>::is_sorted(tiny_data)) return 1;
    StdOut::println();

    In words3_file("res/words3.txt");
    std::vector<std::string> words3_data = words3_file.read_all_strings();
    Quick3way<std::string>::sort(words3_data);
    StdOut::println("Sorted Words3 Data");
    Quick3way<std::string>::show(words3_data);
    if (!Quick3way<std::string>::is_sorted(words3_data)) return 1;

    return 0;
}