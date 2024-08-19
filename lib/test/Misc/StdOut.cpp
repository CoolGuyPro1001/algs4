#include "StdOut.h"

/**
 * Unit tests some methods in {@code StdOut}.
 *
 * @param args the command-line arguments
 */
int main()
{
    // write to stdout
    StdOut::println("Test");
    StdOut::println(17);
    StdOut::println(true);
    StdOut::printf("%.6f\n", 1.0/7.0);
}