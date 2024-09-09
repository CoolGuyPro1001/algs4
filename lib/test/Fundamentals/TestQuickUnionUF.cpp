#include "QuickUnionUF.h"
#include "StdOut.h"
#include "In.h"

/**
 * Reads an integer {@code n} and a sequence of pairs of integers
 * (between {@code 0} and {@code n-1}) from standard input, where each integer
 * in the pair represents some element;
 * if the elements are in different sets, merge the two sets
 * and print the pair to standard output.
 *
 * @param args the command-line arguments
 */
void qu_test(std::string uf_file_name)
{
    In uf_file(uf_file_name);
    int n = uf_file.read_int();
    QuickUnionUF uf = QuickUnionUF(n);
    uf_file.read_line(); // Skip newline after first number
    int p, q;
    while (uf_file.fscanf("%d %d\n", &p, &q))
    {
        if (uf.find(p) == uf.find(q)) continue;
        uf.union_op(p, q);
        StdOut::printf("%d %d\n", p, q);
    }
    StdOut::printf("%d components\n", uf.count());
}

int Fundamentals_TestQuickUnionUF(int argc, char** argv)
{
    qu_test("res/tinyUF.txt");
    qu_test("res/mediumUF.txt");
    qu_test("res/largeUF.txt");
    return 0;
}