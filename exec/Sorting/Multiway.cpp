#ifndef MULTIWAY_H
#define MULTIWAY_H

#include "In.h"
#include "StdOut.h"
#include "IndexMinPQ.h"

/******************************************************************************
 *  Compilation:  javac Multiway.java
 *  Execution:    java Multiway input1.txt input2.txt input3.txt ...
 *  Dependencies: IndexMinPQ.java In.java StdOut.java
 *  Data files:   https://algs4.cs.princeton.edu/24pq/m1.txt
 *                https://algs4.cs.princeton.edu/24pq/m2.txt
 *                https://algs4.cs.princeton.edu/24pq/m3.txt
 *
 *  Merges together the sorted input stream given as command-line arguments
 *  into a single sorted output stream on standard output.
 *
 *  % more m1.txt
 *  A B C F G I I Z
 *
 *  % more m2.txt
 *  B D H P Q Q
 *
 *  % more m3.txt
 *  A B E F J N
 *
 *  % java Multiway m1.txt m2.txt m3.txt
 *  A A B B B C D E F F G H I I J N P Q Q Z
 *
 ******************************************************************************/

/**
 *  The {@code Multiway} class provides a client for reading in several
 *  sorted text files and merging them together into a single sorted
 *  text stream.
 *  This implementation uses a {@link IndexMinPQ} to perform the multiway
 *  merge.
 *  <p>
 *  For additional documentation, see <a href="https://algs4.cs.princeton.edu/24pq">Section 2.4</a>
 *  of <i>Algorithms, 4th Edition</i> by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

// merge together the sorted input streams and write the sorted result to standard output
void merge(std::vector<In>& streams)
{
    int n = streams.size();
    IndexMinPQ<std::string> pq = IndexMinPQ<std::string>(n);
    for (int i = 0; i < n; i++)
        if (!streams[i].is_empty())
            pq.insert(i, streams[i].read_string());

    // Extract and print min and read next from its stream.
    while (!pq.is_empty())
    {
        StdOut::printf("%s ", pq.min_key().c_str()); 
        int i = pq.del_min();
        if (!streams[i].is_empty())
        {
            std::string str = streams[i].read_string();
            if (str == "") continue;
            pq.insert(i, str); 
        }
    }
    StdOut::println();
}


/**
 *  Reads sorted text files specified as command-line arguments;
 *  merges them together into a sorted output; and writes
 *  the results to standard output.
 *  Note: this client does not check that the input files are sorted.
 *
 * @param args the command-line arguments
 */
int main(int argc, char** argv)
{
    int n = argc - 1; 
    std::vector<In> streams = std::vector<In>();
    streams.emplace_back("res/m1.txt");
    streams.emplace_back("res/m2.txt");
    streams.emplace_back("res/m3.txt");
    //for (int i = 0; i < n; i++)
    //    streams.emplace_back(argv[i + 1]);
    merge(streams);
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

#endif