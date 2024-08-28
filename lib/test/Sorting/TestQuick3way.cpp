#include "Quick3way.h"
#include "StdIn.h"

/**
 * Reads in a sequence of strings from standard input; 3-way
 * quicksorts them; and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestQuick3way(int argc, char** argv)
{
    std::vector<std::string> a = StdIn::read_all_strings();
    Quick3way<std::string>::sort(a);
    Quick3way<std::string>::show(a);

    return 0;
}