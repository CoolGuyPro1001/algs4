#include "BinaryInsertion.h"
#include "StdOut.h"
#include "In.h"

/**
 * Reads in a sequence of strings from standard input; insertion sorts them;
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */

int Sorting_TestBinaryInsertion(int argc, char** argv)
{
    In tiny_file("res/tiny.txt");
    std::vector<std::string> tiny_data = tiny_file.read_all_strings();
    BinaryInsertion<std::string>::sort(tiny_data);
    StdOut::println("Sorted Tiny Data");
    BinaryInsertion<std::string>::show(tiny_data);
    StdOut::println();

    In words3_file("res/words3.txt");
    std::vector<std::string> words3_data = words3_file.read_all_strings();
    BinaryInsertion<std::string>::sort(words3_data);
    StdOut::println("Sorted Words3 Data");
    BinaryInsertion<std::string>::show(words3_data);

    return 0;
}