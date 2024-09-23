#include "Queue.h"
#include "In.h"
#include "StdOut.h"

/**
 * Unit tests the {@code Queue} data type.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestQueue(int argc, char** argv)
{
    Queue<std::string> queue = Queue<std::string>();
    In tobe_file("res/tobe.txt");
    std::vector<std::string> items = tobe_file.read_all_strings();
    
    for (std::string item : items)
    {
        if (!(item == "-"))
            queue.enqueue(item);
        else if (!queue.is_empty())
            StdOut::printf("%s ", queue.dequeue().c_str());
    }
    StdOut::printf("(%d left on queue)\n", queue.size());
    return 0;
}