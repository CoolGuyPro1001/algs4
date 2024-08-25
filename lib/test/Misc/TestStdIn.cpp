#include "StdIn.h"
#include "StdOut.h"

int Misc_TestStdIn(int argc, char** argv)
{
    StdOut::print("Type a string: ");
    std::string s = StdIn::read_string();
    StdOut::println("Your string was: " + s);
    StdOut::println();

    StdOut::print("Type an int: ");
    int a = StdIn::read_int();
    StdOut::println("Your int was: " + std::to_string(a));
    StdOut::println();

    StdOut::print("Type a boolean: ");
    bool b = StdIn::read_boolean();
    StdOut::println("Your boolean was: " + std::to_string(b));
    StdOut::println();

    StdOut::print("Type a double: ");
    double c = StdIn::read_double();
    StdOut::println("Your double was: " + std::to_string(c));
    StdOut::println();

    return 0;
}