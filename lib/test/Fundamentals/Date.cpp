#include "Date.h"
#include "StdOut.h"

/**
 * Unit tests the {@code Date} data type.
 *
 * @param args the command-line arguments
 */
int main()
{
    Date today = Date(2, 25, 2004);
    StdOut::println(today);
    for (int i = 0; i < 10; i++) {
        today = today.next();
        StdOut::println(today);
    }

    StdOut::println(today.is_after(today.next()));
    StdOut::println(today.is_after(today));
    StdOut::println(today.next().is_after(today));


    Date birthday = Date(10, 16, 1971);
    StdOut::println(birthday);
    for (int i = 0; i < 10; i++) {
        birthday = birthday.next();
        StdOut::println(birthday);
    }
}