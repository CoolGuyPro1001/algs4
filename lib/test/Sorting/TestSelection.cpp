#include "Selection.h"
#include "StdIn.h"

/**
 * Reads in a sequence of strings from standard input; selection sorts them;
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestSelection(int argc, char** argv)
{
    std::vector<std::string> a = StdIn::read_all_strings();
    Selection<std::string>::sort(a);
    Selection<std::string>::show(a);
    
    return 0;
}