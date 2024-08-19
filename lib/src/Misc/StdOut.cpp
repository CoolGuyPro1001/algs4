#include "StdOut.h"

void StdOut::println()
{
    std::cout << "\n";
}

void StdOut::print()
{
    std::cout << std::flush;
}

void StdOut::printf(const char* format, ...)
{
    std::va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    fflush(stdin);
}