#include "Shell.h"
#include "StdIn.h"

/**
 * Reads in a sequence of strings from standard input; Shellsorts them;
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestShell(int argc, char** argv)
{
    std::vector<std::string> a = StdIn::read_all_strings();
    Shell<std::string>::sort(a);
    Shell<std::string>::show(a);

    return 0;
}