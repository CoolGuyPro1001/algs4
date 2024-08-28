#include "InsertionX.h"
#include "StdIn.h"

/**
 * Reads in a sequence of strings from standard input; insertion sorts them;
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestInsertionX(int argc, char** argv)
{
    std::vector<std::string> a = StdIn::read_all_strings();
    InsertionX<std::string>::sort(a);
    InsertionX<std::string>::show(a);

    return 0;
}