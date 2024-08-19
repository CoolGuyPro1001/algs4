#include "ST.h"

/**
 * Unit tests the {@code ST} data type.
 *
 * @param args the command-line arguments
 
int main()
{
    ST<std::string, int> st = new ST<std::string, int>();
    for (int i = 0; !StdIn.isEmpty(); i++) {
        String key = StdIn.readString();
        st.put(key, i);
    }
    for (String s : st.keys())
        StdOut.println(s + " " + st.get(s));
}*/