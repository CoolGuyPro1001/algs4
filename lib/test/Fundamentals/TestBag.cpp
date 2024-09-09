#include "Bag.h"
#include "StdOut.h"
#include "In.h"

/**
 * Unit tests the {@code Bag} data type.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestBag(int argc, char** argv)
{
    Bag<std::string> bag = Bag<std::string>();
    In tobe_file("res/tobe.txt");
    std::vector<std::string> items = tobe_file.read_all_strings();
    
    for (auto item = items.begin(); item != items.end(); item++)
    {
        bag.add(*item);
    }

    StdOut::printf("size of bag = %d\n", bag.size());
    // for (String s : bag) {
    //     StdOut::println(s);
    // }

    return 0;
}