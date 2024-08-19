/******************************************************************************
 *  Compilation:  javac RandomSeq.java
 *  Execution:    java RandomSeq n lo hi
 *  Dependencies: StdOut.java
 *
 *  Prints N numbers between lo and hi.
 *
 *  % java RandomSeq 5 100.0 200.0
 *  123.43
 *  153.13
 *  144.38
 *  155.18
 *  104.02
 *
 ******************************************************************************/

#include "StdOut.h"
#include "StdRandom.h"

/**
    * Reads in two command-line arguments lo and hi and prints n uniformly
    * random real numbers in [lo, hi) to standard output.
    *
    * @param args the command-line arguments
    */
int main(int argc, char** argv)
{
    // command-line arguments
    int n = std::atoi(argv[1]); 

    // for backward compatibility with Intro to Programming in Java version of RandomSeq
    if (argc == 2)
    {
        // generate and print n numbers between 0.0 and 1.0
        for (int i = 0; i < n; i++)
        {
            double x = StdRandom::uniform_double(0.0, 1.0);
            StdOut::println(x);
        }
    }
    else if (argc == 4)
    {
        double lo = atof(argv[2]);
        double hi = atof(argv[3]);

        // generate and print n numbers between lo and hi
        for (int i = 0; i < n; i++)
        {
            double x = StdRandom::uniform_double(lo, hi);
            StdOut::printf("%.2f\n", x);
        }
    }
    else 
    {
        StdOut::printf("Invalid number of arguments");
    }
}

/******************************************************************************
 *  Copyright 2002-2022, Robert Sedgewick and Kevin Wayne.
 *
 *  This file is part of algs4.jar, which accompanies the textbook
 *
 *      Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne,
 *      Addison-Wesley Professional, 2011, ISBN 0-321-57351-X.
 *      http://algs4.cs.princeton.edu
 *
 *
 *  algs4.jar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  algs4.jar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with algs4.jar.  If not, see http://www.gnu.org/licenses.
 ******************************************************************************/