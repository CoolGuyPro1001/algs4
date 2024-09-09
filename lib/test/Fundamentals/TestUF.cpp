#include "UF.h"
#include "In.h"
#include "StdOut.h"

/**
 * Reads an integer {@code n} and a sequence of pairs of integers
 * (between {@code 0} and {@code n-1}) from standard input, where each integer
 * in the pair represents some element;
 * if the elements are in different sets, merge the two sets
 * and print the pair to standard output.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestUF(int argc, char** argv)
{
    In tinyUF_file("res/tinyUF.txt");
    UF uf = UF(tinyUF_file.read_int());
    tinyUF_file.read_line(); // Skip the newline after the first number
    int p, q;
    while (tinyUF_file.fscanf("%d %d\n", &p, &q))
    {
        if (uf.find(p) == uf.find(q)) continue;
        uf.union_op(p, q);
        StdOut::printf("%d %d\n", p, q); 
    }
    StdOut::printf("%d components\n",uf.count());

    return 0;
}