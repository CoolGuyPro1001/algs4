#include "MergeX.h"
#include "StdOut.h"
#include "In.h"

/**
 * Reads in a sequence of strings from standard input; mergesorts them
 * (using an optimized version of mergesort);
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestMergeX(int argc, char** argv)
{
    In tiny_file("res/tiny.txt");
    std::vector<std::string> tiny_data = tiny_file.read_all_strings();
    MergeX<std::string>::sort(tiny_data);
    StdOut::println("Sorted Tiny Data");
    MergeX<std::string>::show(tiny_data);
    StdOut::println();

    In words3_file("res/words3.txt");
    std::vector<std::string> words3_data = words3_file.read_all_strings();
    MergeX<std::string>::sort(words3_data);
    StdOut::println("Sorted Words3 Data");
    MergeX<std::string>::show(words3_data);

    return 0;
}