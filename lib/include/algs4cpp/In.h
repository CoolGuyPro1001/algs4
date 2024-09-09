#ifndef IN_H
#define IN_H

/******************************************************************************
 *  Compilation:  javac In.java
 *  Execution:    java In   (basic test --- see source for required files)
 *  Dependencies: none
 *
 *  Reads in data of various types from standard input, files, and URLs.
 *
 ******************************************************************************/

/**
 *  The <code>In</code> data type provides methods for reading strings
 *  and numbers from standard input, file input, URLs, and sockets.
 *  <p>
 *  The Locale used is: language = English, country = US. This is consistent
 *  with the formatting conventions with Java floating-point literals,
 *  command-line arguments (via {@link Double#parseDouble(String)})
 *  and standard output.
 *  <p>
 *  For additional documentation, see
 *  <a href="https://introcs.cs.princeton.edu/31datatype">Section 3.1</a> of
 *  <i>Computer Science: An Interdisciplinary Approach</i>
 *  by Robert Sedgewick and Kevin Wayne.
 *  <p>
 *  Like {@link Scanner}, reading a token also consumes preceding Java
 *  whitespace, reading a full line consumes
 *  the following end-of-line delimiter, while reading a character consumes
 *  nothing extra.
 *  <p>
 *  Whitespace is defined in {@link Character#isWhitespace(char)}. Newlines
 *  consist of \n, \r, \r\n, and Unicode hex code points 0x2028, 0x2029, 0x0085;
 *  see <a href="http://www.docjar.com/html/api/java/util/Scanner.java.html">
 *  Scanner.java</a> (NB: Java 6u23 and earlier uses only \r, \r, \r\n).
 *
 *  @author David Pritchard
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */
class In
{
public:
   /**
     * Initializes an input stream from a socket.
     *
     * @param  socket the socket
     * @throws IllegalArgumentException if cannot open {@code socket}
     * @throws IllegalArgumentException if {@code socket} is {@code null}
     */
    //In(Socket socket);

   /**
     * Initializes an input stream from a URL.
     *
     * @param  url the URL
     * @throws IllegalArgumentException if cannot open {@code url}
     * @throws IllegalArgumentException if {@code url} is {@code null}
     */
    //In(URL url);

   /**
     * Initializes an input stream from a filename or web page name.
     *
     * @param  name the filename or web page name
     * @throws IllegalArgumentException if cannot open {@code name} as
     *         a file or URL
     * @throws IllegalArgumentException if {@code name} is {@code null}
     */
    In(std::string name);

    /**
     * Returns true if this input stream exists.
     *
     * @return {@code true} if this input stream exists; {@code false} otherwise
     */
    bool exists();

   /**
     * Returns true if input stream is empty (except possibly whitespace).
     * Use this to know whether the next call to {@link #readString()},
     * {@link #readDouble()}, etc. will succeed.
     *
     * @return {@code true} if this input stream is empty (except possibly whitespace);
     *         {@code false} otherwise
     */
    bool is_empty();

   /**
     * Reads and returns the next line in this input stream.
     *
     * @return the next line in this input stream; {@code null} if no such line
     */
    std::string read_line();

    /**
     * Reads and returns the next character in this input stream.
     *
     * @return the next {@code char} in this input stream
     * @throws NoSuchElementException if the input stream is empty
     */
    char read_char(); 

   /**
     * Reads and returns the remainder of this input stream, as a string.
     *
     * @return the remainder of this input stream, as a string
     */
    std::string read_all();

   /**
     * Reads the next token from this input stream and returns it as a {@code String}.
     *
     * @return the next {@code String} in this input stream
     * @throws NoSuchElementException if the input stream is empty
     */
    std::string read_string();

   /**
     * Reads the next token from this input stream, parses it as a {@code int},
     * and returns the {@code int}.
     *
     * @return the next {@code int} in this input stream
     * @throws NoSuchElementException if the input stream is empty
     * @throws InputMismatchException if the next token cannot be parsed as an {@code int}
     */
    int read_int();

   /**
     * Reads the next token from this input stream, parses it as a {@code double},
     * and returns the {@code double}.
     *
     * @return the next {@code double} in this input stream
     * @throws NoSuchElementException if the input stream is empty
     * @throws InputMismatchException if the next token cannot be parsed as a {@code double}
     */
    double read_double();

   /**
     * Reads the next token from this input stream, parses it as a {@code float},
     * and returns the {@code float}.
     *
     * @return the next {@code float} in this input stream
     * @throws NoSuchElementException if the input stream is empty
     * @throws InputMismatchException if the next token cannot be parsed as a {@code float}
     */
    float read_float();

   /**
     * Reads the next token from this input stream, parses it as a {@code long},
     * and returns the {@code long}.
     *
     * @return the next {@code long} in this input stream
     * @throws NoSuchElementException if the input stream is empty
     * @throws InputMismatchException if the next token cannot be parsed as a {@code long}
     */
    long read_long();

   /**
     * Reads the next token from this input stream, parses it as a {@code short},
     * and returns the {@code short}.
     *
     * @return the next {@code short} in this input stream
     * @throws NoSuchElementException if the input stream is empty
     * @throws InputMismatchException if the next token cannot be parsed as a {@code short}
     */
    short read_short();

   /**
     * Reads the next token from this input stream, parses it as a {@code byte},
     * and returns the {@code byte}.
     * <p>
     * To read binary data, use {@link BinaryIn}.
     *
     * @return the next {@code byte} in this input stream
     * @throws NoSuchElementException if the input stream is empty
     * @throws InputMismatchException if the next token cannot be parsed as a {@code byte}
     */
    uint8_t read_byte();

    /**
     * Reads the next token from this input stream, parses it as a {@code bool}
     * (interpreting either {@code "true"} or {@code "1"} as {@code true},
     * and either {@code "false"} or {@code "0"} as {@code false}).
     *
     * @return the next {@code bool} in this input stream
     * @throws NoSuchElementException if the input stream is empty
     * @throws InputMismatchException if the next token cannot be parsed as a {@code bool}
     */
    bool read_bool();

    /**
     * Reads all remaining tokens from this input stream and returns them as
     * an array of strings.
     *
     * @return all remaining tokens in this input stream, as an array of strings
     */
    std::vector<std::string> read_all_strings();

    /**
     * Reads all remaining lines from this input stream and returns them as
     * an array of strings.
     *
     * @return all remaining lines in this input stream, as an array of strings
     */
    std::vector<std::string> read_all_lines();

    /**
     * Reads all remaining tokens from this input stream, parses them as integers,
     * and returns them as an array of integers.
     *
     * @return all remaining lines in this input stream, as an array of integers
     */
    std::vector<int> read_all_ints();

    /**
     * Reads all remaining tokens from this input stream, parses them as longs,
     * and returns them as an array of longs.
     *
     * @return all remaining lines in this input stream, as an array of longs
     */
    std::vector<long> read_all_longs();

    /**
     * Reads all remaining tokens from this input stream, parses them as doubles,
     * and returns them as an array of doubles.
     *
     * @return all remaining lines in this input stream, as an array of doubles
     */
    std::vector<double> read_all_doubles();

   /**
     * Closes this input stream.
     */
    void close();
    
    /**
     * Reads from standard input as a format and stores the parameters in variables.
     * @param format - Parameter format. See std::format()
     * @param args - variables to pass data into
     * @return true if standard input was read succesfully
    */
    bool fscanf(const char* format, ...);

private:
    std::ifstream m_ifs;
};

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