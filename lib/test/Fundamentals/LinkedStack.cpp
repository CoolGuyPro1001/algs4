#include "LinkedStack.h"
#include "StdIn.h"
#include "StdOut.h"

/**
 * Unit tests the {@code LinkedStack} data type.
 *
 * @param args the command-line arguments
 */
int main()
{
    LinkedStack<std::string> stack = LinkedStack<std::string>();
    while (!StdIn::is_empty())
    {
        std::string item = StdIn::read_string();
        if (!(item == "-"))
            stack.push(item);
        else if (!stack.is_empty())
            StdOut::print(stack.pop() + " ");
    }
    StdOut::printf("(%d left on stack)\n",stack.size()); 
}