#include "MergeBU.h"
#include "StdIn.h"

/**
 * Reads in a sequence of strings from standard input; bottom-up
 * mergesorts them; and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestMergeBU(int argc, char** argv)
{
    std::vector<std::string> a = StdIn::read_all_strings();
    MergeBU<std::string>::sort(a);
    MergeBU<std::string>::show(a);

    return 0;
}