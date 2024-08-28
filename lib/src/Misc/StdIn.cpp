#include "StdIn.h"
#include "StdOut.h"

bool StdIn::is_empty()
{
    return std::cin.eof();
}

bool StdIn::has_next_line()
{
    std::streampos current_pos = std::cin.tellg();
    while (has_next_char())
    {
        char c = std::cin.peek();
        if (c == '\n')
            return true;
        std::cin.seekg(1, std::ios_base::cur);
    }
    return !std::cin.eof();
}

bool StdIn::has_next_char()
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

std::vector<std::string> StdIn::read_all_lines()
{
    std::string line;
    std::vector<std::string> lines;

    while (std::getline(std::cin, line))
    {
       lines.push_back(line); 
    }

    return lines;
}

std::vector<std::string> StdIn::read_all_strings()
{
    std::vector<std::string> lines = read_all_lines();
    std::vector<std::string> tokens;
    std::vector<char> line = std::vector<char>(200); // Make vector for dynamic resizing

    for (auto it = lines.begin(); it != lines.end(); it++)
    {
        if (it->size() > line.size())
            line.resize(line.size() * 2);

        std::copy(it->begin(), it->end(), line.begin());
        char* token = strtok(&line[0], " \t");
        while (token != nullptr)
        {
            tokens.push_back(std::string(token));
            token = strtok(nullptr, " \t");
        }
    }

    return tokens;
}

bool StdIn::scanf(const char* format, ...)
{
    std::va_list args;
    va_start(args, format);

    char str[512];
    int test;
    fgets(str, 512, stdin);
    if (strncmp(str, "\n", 1) == 0)
         return false;
     
    int result = vsscanf(str, format, args);
    va_end(args);

    return result != 0 || result != EOF;
}