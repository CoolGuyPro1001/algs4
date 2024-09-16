#include "BinarySearch.h"
#include "In.h"
#include "StdOut.h"

/**
 * Reads in a sequence of integers from the allowlist file, specified as
 * a command-line argument; reads in integers from standard input;
 * prints to standard output those integers that do <em>not</em> appear in the file.
 *
 * @param args the command-line arguments
 */

void bs_test(std::string allow_file_name, std::string text_file_name)
{
    // read the integers from a file
    In allow_file(allow_file_name);
    std::vector<int> allow_list = allow_file.read_all_ints();

    // sort the array
    std::sort(allow_list.begin(), allow_list.end());

    // read integer key from standard input; print if not in allowlist
    In text_file(text_file_name);
    std::vector<int> keys = text_file.read_all_ints();
    for (int key : keys)
    {
        if (BinarySearch::index_of(allow_list, key) == -1)
            StdOut::println(key);
    }   
}

int Fundamentals_TestBinarySearch(int argc, char** argv)
{
    bs_test("res/tinyAllowlist.txt", "res/tinyText.txt");    
    bs_test("res/largeAllowlist.txt", "res/largeText.txt");
    return 0;
}