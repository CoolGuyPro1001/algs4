#include "ThreeSumFast.h"
#include "In.h"
#include "StdOut.h"
#include "Stopwatch.h"

/**
 * Reads in a sequence of distinct integers from a file, specified as a command-line argument;
 * counts the number of triples sum to exactly zero; prints out the time to perform
 * the computation.
 *
 * @param args the command-line arguments
 */
void tsf_test(std::string file_name)
{
    In file(file_name);
    std::vector<int> a = file.read_all_ints();
    int count = ThreeSumFast::count(a);
    StdOut::println(count);
}

int Fundamentals_TestThreeSumFast(int argc, char** argv)
{
    tsf_test("res/1Kints.txt");
    tsf_test("res/2Kints.txt");
    tsf_test("res/4Kints.txt");
    tsf_test("res/8Kints.txt");
    tsf_test("res/16Kints.txt");
    tsf_test("res/32Kints.txt");
    
    return 0;
}