#include "Heap.h"
#include "StdIn.h"

/**
 * Reads in a sequence of strings from standard input; heapsorts them;
 * and prints them to standard output in ascending order.
 *
 * @param args the command-line arguments
 */
int Sorting_TestHeap(int argc, char** argv)
{
    std::vector<std::string> a = StdIn::read_all_strings();
    Heap<std::string>::sort(a);
    Heap<std::string>::show(a);

    return 0;
}