#include "MaxPQ.h"
#include "In.h"
#include "StdOut.h"


/**
 * Unit tests the {@code MaxPQ} data type.
 *
 * @param args the command-line arguments
 */
int Sorting_TestMaxPQ(int argc, char** argv)
{
    In pq_file("res/tinyPQ.txt");
    MaxPQ<std::string> pq = MaxPQ<std::string>();
    std::vector<std::string> items = pq_file.read_all_strings(); 

    for (std::string item : items)
    {
        if (!(item == "-")) pq.insert(item);
        else if (!pq.is_empty()) StdOut::printf("%s ", pq.del_max().c_str()); 
    }
    StdOut::printf("(%d left on pq)\n",pq.size()); 

    return 0;
}