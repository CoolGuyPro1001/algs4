#include "MinPQ.h"
#include "In.h"
#include "StdOut.h"

/**
 * Unit tests the {@code MinPQ} data type.
 *
 * @param args the command-line arguments
 */
int Sorting_TestMinPQ(int argc, char** argv)
{
    In pq_file("res/tinyPQ.txt");
    MinPQ<std::string> pq = MinPQ<std::string>();
    std::vector<std::string> items = pq_file.read_all_strings(); 

    for (std::string item : items)
    {
        if (!(item == "-")) pq.insert(item);
        else if (!pq.is_empty()) StdOut::printf("%s ", pq.del_min().c_str()); 
    }
    StdOut::printf("(%d left on pq)\n",pq.size()); 

    return 0;
}