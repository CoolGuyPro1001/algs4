#include "ResizingArrayBag.h"
#include "StdOut.h"

/**
 * Unit tests the {@code ResizingArrayBag} data type.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestResizingArrayBag(int argc, char** argv)
{
    ResizingArrayBag<std::string> bag = ResizingArrayBag<std::string>();
    bag.add("Hello");
    bag.add("World");
    bag.add("how");
    bag.add("are");
    bag.add("you");

    for (std::string s : bag)
        StdOut::println(s);

    return 0;
}