#include "StdIn.h"
#include "StdOut.h"

bool StdIn::is_empty()
{
    return std::cin.eof();
}

std::string StdIn::read_line()
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}

char StdIn::read_char()
{
    char c;
    std::cin >> c;
    return c;
}

std::string StdIn::read_all()
{
    std::string str;
    std::string line;
    while(std::getline(std::cin, line))
    {
        if (line.empty())
        {
            break;
        }

        str += line;
    }

    return str;
}

std::string StdIn::read_string()
{
    std::string str;
    std::cin >> str;
    return str;
}

int StdIn::read_int()
{
    int num;
    std::cin >> num;
    return num;
}

double StdIn::read_double()
{
    double num;
    std::cin >> num;
    return num;
}

float StdIn::read_float()
{
    float num;
    std::cin >> num;
    return num;
}

long StdIn::read_long()
{
    long num;
    std::cin >> num;
    return num;
}

short StdIn::read_short()
{
    short num;
    std::cin >> num;
    return num;
}

uint8_t StdIn::read_byte()
{
    uint8_t num;
    std::cin >> num;
    return num;
}

bool StdIn::read_bool()
{
    bool b;
    std::cin >> b;
    return b;
}


bool StdIn::scanf(const char* format, ...)
{
    std::va_list args;
    va_start(args, format);

    std::string line;
    std::getline(std::cin, line);
     
    int result = vsscanf(line.c_str(), format, args);
    va_end(args);

    return result != EOF;
}