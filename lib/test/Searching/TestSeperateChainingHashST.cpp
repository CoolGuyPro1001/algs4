#include "SeperateChainingHashST.h"
#include "In.h"
#include "StdOut.h"

/**
 * Unit tests the {@code SeparateChainingHashST} data type.
 *
 * @param args the command-line arguments
 */
int Searching_TestSeperateChainingHashST(int argc, char** argv)
{
    SeparateChainingHashST<std::string, int> st = SeparateChainingHashST<std::string, int>();
    In tinyST_file("res/tinyST.txt");
    std::vector<std::string> keys = tinyST_file.read_all_strings();

    for (int i = 0; i < keys.size(); i++)
    {
        st.put(keys[i], i);
    }

    // print keys
    for (std::string s : st.keys())
        StdOut::printf("%s %d\n", s.c_str(), st.get(s));

    return 0;
}