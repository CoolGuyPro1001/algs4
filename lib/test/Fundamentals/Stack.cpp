#include "Stack.h"
#include "StdIn.h"
#include "StdOut.h"

/**
 * Unit tests the {@code Stack} data type.
 *
 * @param args the command-line arguments
 */
int main()
{
    Stack<std::string> stack = Stack<std::string>();
    while (!StdIn::is_empty()) {
        String item = StdIn.readString();
        if (!item == "-")
            stack.push(item);
        else if (!stack.is_empty())
            StdOut::print(stack.pop() + " ");
    }
    StdOut::println("(" + stack.size() + " left on stack)");
}