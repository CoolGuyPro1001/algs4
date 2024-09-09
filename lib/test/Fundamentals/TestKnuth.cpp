#include "Knuth.h"
#include "StdOut.h"
#include "In.h"

/**
* Reads in a sequence of strings from standard input, shuffles
* them, and prints out the results.
*
* @param args the command-line arguments
*/

void knuth_test(std::string card_file_name)
{
    In card_file(card_file_name);

    // read in the data
    std::vector<std::string> a = card_file.read_all_strings(); 

    // shuffle the array
    Knuth::shuffle(a);

    // print results.
    for (int i = 0; i < a.size(); i++)
        StdOut::println(a[i]);
}

int Fundamentals_TestKnuth(int argc, char** argv)
{
    knuth_test("res/cards.txt");
    knuth_test("res/cardsUnicode.txt");
    return 0;
}