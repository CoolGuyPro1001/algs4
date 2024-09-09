#include "MergeBU.h"
#include "StdOut.h"
#include "In.h"

/**
 * Reads in a sequence of strings from standard input; bottom-up
 * mergesorts them; and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestMergeBU(int argc, char** argv)
{
    In tiny_file("res/tiny.txt");
    std::vector<std::string> tiny_data = tiny_file.read_all_strings();
    MergeBU<std::string>::sort(tiny_data);
    StdOut::println("Sorted Tiny Data");
    MergeBU<std::string>::show(tiny_data);
    StdOut::println();

    In words3_file("res/words3.txt");
    std::vector<std::string> words3_data = words3_file.read_all_strings();
    MergeBU<std::string>::sort(words3_data);
    StdOut::println("Sorted Words3 Data");
    MergeBU<std::string>::show(words3_data);

    return 0;
}