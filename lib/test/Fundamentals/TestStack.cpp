#include "Stack.h"
#include "In.h"
#include "StdOut.h"

/**
 * Unit tests the {@code Stack} data type.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestStack(int argc, char** argv)
{
    Stack<std::string> stack = Stack<std::string>();
    In tobe_file("res/tobe.txt");
    std::vector<std::string> items = tobe_file.read_all_strings();
    
    for (std::string item : items)
    {
        if (!(item == "-"))
            stack.push(item);
        else if (!stack.is_empty())
            StdOut::print(stack.pop() + " ");
    }
    StdOut::printf("(%d left on stack)\n", stack.size()); 

    return 0;
}