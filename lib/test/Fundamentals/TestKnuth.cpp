#include "Knuth.h"
#include "StdOut.h"
#include "StdIn.h"

/**
* Reads in a sequence of strings from standard input, shuffles
* them, and prints out the results.
*
* @param args the command-line arguments
*/
int Fundamentals_TestKnuth(int argc, char** argv)
{
    // read in the data
    std::vector<std::string> a = std::vector<std::string>();
    a.reserve(1000);

    char* temp;
    while (StdIn::scanf("%s", temp))
    {
        a.push_back(std::string(temp));
    }

    // shuffle the array
    Knuth::shuffle(a);

    // print results.
    for (int i = 0; i < a.size(); i++)
        StdOut::println(a[i]);

    return 0;
}