#include "RedBlackBST.h"
#include "In.h"
#include "StdOut.h"

/**
 * Unit tests the {@code RedBlackBST} data type.
 *
 * @param args the command-line arguments
 */
int Searching_TestRedBlackBST(int argc, char** argv)
{
    RedBlackBST<std::string, int> st = RedBlackBST<std::string, int>();
    In tinyST_file("res/tinyST.txt");
    std::vector<std::string> keys = tinyST_file.read_all_strings();

    for (int i = 0; i < keys.size(); i++)
    {
        st.put(keys[i], i);
    }
    StdOut::println();
    for (std::string s : st.keys())
        StdOut::printf("%s %d", s.c_str(), st.get(s));
    StdOut::println();

    return 0;
}