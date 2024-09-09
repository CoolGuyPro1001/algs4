#include "Stack.h"
#include "StdIn.h"
#include "StdOut.h"

/**
 * Unit tests the {@code Stack} data type.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestStack()
{
    Stack<std::string> stack = Stack<std::string>();
    std::string item;
    while (StdIn::scanf("{}\n", item))
    {
        if (!item == "-")
            stack.push(item);
        else if (!stack.is_empty())
            StdOut::print(stack.pop() + " ");
    }
    StdOut::println("(" + stack.size() + " left on stack)");
}