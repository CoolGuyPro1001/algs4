#include "QuickUnionUF.h"
#include "StdOut.h"
#include "StdIn.h"

/**
 * Reads an integer {@code n} and a sequence of pairs of integers
 * (between {@code 0} and {@code n-1}) from standard input, where each integer
 * in the pair represents some element;
 * if the elements are in different sets, merge the two sets
 * and print the pair to standard output.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestQuickUnionUF(int argc, char** argv)
{
    int n = StdIn::read_int();
    QuickUnionUF uf = QuickUnionUF(n);
    while (!StdIn::is_empty())
    {
        int p = StdIn::read_int();
        int q = StdIn::read_int();
        if (uf.find(p) == uf.find(q)) continue;
        uf.union_op(p, q);
        StdOut::printf("%d %d\n", p, q);
    }
    StdOut::printf("%d components\n", uf.count());

    return 0;
}