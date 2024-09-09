#include "Quick.h"
#include "StdOut.h"
#include "In.h"
#include "StdRandom.h"

int Sorting_TestQuick(int argc, char** argv)
{
    In tiny_file("res/tiny.txt");
    std::vector<std::string> tiny_data = tiny_file.read_all_strings();
    Quick<std::string>::sort(tiny_data);
    StdOut::println("Sorted Tiny Data");
    Quick<std::string>::show(tiny_data);
    if (!Quick<std::string>::is_sorted(tiny_data)) return 1;
    StdOut::println();

    // shuffle
    StdRandom::shuffle(tiny_data);

    // display results again using select
    StdOut::println();
    for (int i = 0; i < tiny_data.size(); i++)
    {
        std::string ith = Quick<std::string>::select(tiny_data, i);
        StdOut::println(ith);
    }

    In words3_file("res/words3.txt");
    std::vector<std::string> words3_data = words3_file.read_all_strings();
    Quick<std::string>::sort(words3_data);
    StdOut::println("Sorted Words3 Data");
    Quick<std::string>::show(words3_data);
    if (!Quick<std::string>::is_sorted(words3_data)) return 1;

    // shuffle
    StdRandom::shuffle(words3_data);

    // display results again using select
    StdOut::println();
    for (int i = 0; i < words3_data.size(); i++)
    {
        std::string ith = Quick<std::string>::select(words3_data, i);
        StdOut::println(ith);
    }

    return 0;
    

return 0;
}