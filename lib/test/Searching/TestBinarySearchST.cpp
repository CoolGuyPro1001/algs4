#include "BinarySearchST.h"
#include "In.h"
#include "StdOut.h"

/**
 * Unit tests the {@code BinarySearchST} data type.
 *
 * @param args the command-line arguments
 */
int Searching_TestBinarySearchST(int argc, char** argv)
{
    BinarySearchST<std::string, int> st = BinarySearchST<std::string, int>();
    In tinyST_file("res/tinyST.txt");
    std::vector<std::string> keys = tinyST_file.read_all_strings();

    for (int i = 0; i < keys.size(); i++)
    {
        st.put(keys[i], i);
    }

    for (std::string s : st.keys())
        StdOut::printf("%s %d\n", s.c_str(), st.get(s));

    return 0;
}