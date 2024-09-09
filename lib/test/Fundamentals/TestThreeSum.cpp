#include "ThreeSum.h"
#include "In.h"
#include "StdOut.h"
#include "Stopwatch.h"

/**
 * Reads in a sequence of integers from a file, specified as a command-line argument;
 * counts the number of triples sum to exactly zero; prints out the time to perform
 * the computation.
 *
 * @param args the command-line arguments
 */
void ts_test(std::string file_name)
{
    In file(file_name); 
    std::vector<int> a = file.read_all_ints();

    Stopwatch timer = Stopwatch();
    int count = ThreeSum::count(a);
    StdOut::printf("elapsed time = %f\n", timer.elapsed_time());
    StdOut::println(count);
}

int Fundamentals_TestThreeSum(int argc, char** argv)
{
    ts_test("res/1Kints.txt");
    ts_test("res/2Kints.txt");
    ts_test("res/4Kints.txt");
    
    return 0;
}