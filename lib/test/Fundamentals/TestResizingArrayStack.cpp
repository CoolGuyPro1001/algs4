#include "ResizingArrayStack.h"
#include "StdIn.h"
#include "StdOut.h"

/**
 * Unit tests the {@code Stack} data type.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestResizingArrayStack()
{
    ResizingArrayStack<std::string> stack = ResizingArrayStack<std::string>();
    while (!StdIn::is_empty())
    {
        std::string item = StdIn::read_string();
        if (!(item == "-")) stack.push(item);
        else if (!stack.is_empty()) StdOut::printf("%d ", stack.pop()); 
    }
    StdOut::printf("(%d left on stack)", stack.size()); 
}