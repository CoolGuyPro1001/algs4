#include "Quick.h"
#include "StdIn.h"
#include "StdRandom.h"

int Sorting_TestQuick(int argc, char** argv)
{
    std::vector<std::string> a = StdIn::read_all_strings();
    Quick<std::string>::sort(a);
    Quick<std::string>::show(a);
    assert(Quick<std::string>::is_sorted(a));

    // shuffle
    StdRandom::shuffle(a);

    // display results again using select
    StdOut::println();
    for (int i = 0; i < a.size(); i++)
    {
        std::string ith = Quick<std::string>::select(a, i);
        StdOut::println(ith);
    }

return 0;
}