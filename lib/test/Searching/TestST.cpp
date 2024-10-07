#include "ST.h"
#include "In.h"
#include "StdOut.h"

/**
 * Unit tests the {@code ST} data type.
 *
 * @param args the command-line arguments
 */

int Searching_TestST(int argc, char** argv)
{
    ST<std::string, int> st = ST<std::string, int>();
    In tinyST_file("res/tinyST.cpp");
    std::vector<std::string> keys = tinyST_file.read_all_strings();

    for (int i = 0; i < keys.size(); i++)
    {
        st.put(keys[i], i);
    }
    for (std::string s : st.keys())
        StdOut::printf("%s %d", s.c_str(), st.get(s));

    return 0;
}