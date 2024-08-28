#include "Bag.h"
#include "StdOut.h"
#include "StdIn.h"

/**
 * Unit tests the {@code Bag} data type.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestBag(int argc, char** argv)
{
    Bag<std::string> bag = Bag<std::string>();
    char item[64];
    while (StdIn::scanf("%s", &item))
    {
        bag.add(std::string(item));
    }

    StdOut::printf("size of bag = %d\n", bag.size());
    // for (String s : bag) {
    //     StdOut::println(s);
    // }

    return 0;
}