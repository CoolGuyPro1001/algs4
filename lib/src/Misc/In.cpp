#include "In.h"

In::In(std::string name)
{
    if (name.length() == 0) error("The file needs a name bro.");

    // first try to read file from local file system
    m_ifs.open(name);
    if (m_ifs.fail()) error("istream has failed");
    if (!m_ifs.is_open()) error("file not open");
    return;

    // resource relative to .class file
    /*URL url = getClass().getResource(name);

    // resource relative to classloader root
    if (url == null) {
        url = getClass().getClassLoader().getResource(name);
    }

    // or URL from web
    if (url == null) {
        URI uri = new URI(name);
        if (uri.isAbsolute()) url = uri.toURL();
        else throw new IllegalArgumentException("could not read: '" + name + "'");
        url = new URL(name);
    }

    URLConnection site = url.openConnection();

    // in order to set User-Agent, replace above line with these two
    // HttpURLConnection site = (HttpURLConnection) url.openConnection();
    // site.addRequestProperty("User-Agent", "Mozilla/4.76");

    InputStream is     = site.getInputStream();
    scanner            = new Scanner(new BufferedInputStream(is), CHARSET_NAME);
    scanner.useLocale(LOCALE);
    }*/
}

bool In::exists()
{
    return m_ifs.is_open();
}

bool In::is_empty()
{
    return m_ifs.eof();
}

std::string In::read_line()
{
    std::string line;
    std::getline(m_ifs, line);
    if (m_ifs.fail() && !m_ifs.eof()) error("Error reading line from file");
    return line;
}

char In::read_char()
{
    char c = m_ifs.get();
    if (m_ifs.fail() && !m_ifs.eof()) error("Error reading char from file");
    return c;
}

std::string In::read_all()
{
    std::string contents;
    while (m_ifs.good())
    {
        contents += read_line();
    }    
    return contents;
}

std::string In::read_string()
{
    std::string str;
    m_ifs >> str;
    if (m_ifs.fail() && !m_ifs.eof()) error("Error reading string from file. " \
        "This error also occurs when reading bool");
    return str;
}

int In::read_int()
{
    int i;
    m_ifs >> i;
    if (m_ifs.fail() && !m_ifs.eof()) error("Error reading int from file");
    return i;
}

double In::read_double()
{
    double d;
    m_ifs >> d;
    if (m_ifs.fail() && !m_ifs.eof()) error("Error reading double from file");
    return d;
}

float In::read_float()
{
    float f;
    m_ifs >> f;
    if (m_ifs.fail() && !m_ifs.eof()) error("Error reading float from file");
    return f;
}

long In::read_long()
{
    long l;
    m_ifs >> l;
    if (m_ifs.fail() && !m_ifs.eof()) error("Error reading long from file");
    return l;
}

short In::read_short()
{
    long s;
    m_ifs >> s;
    if (m_ifs.fail() && !m_ifs.eof()) error("Error reading short from file");
    return s;
}

uint8_t In::read_byte()
{
    uint8_t b;
    m_ifs >> b;
    if (m_ifs.fail() && !m_ifs.eof()) error ("Error reading byte from file");
    return b;
}

bool In::read_bool()
{
    std::string token = read_string();
    std::transform(token.begin(), token.end(), token.begin(), 
        [](unsigned char c) {return std::tolower(c);}
    );
    
    if ("true" == token) return true;
    if ("false" ==token) return false;
    if ("1" == token) return true;
    if ("0" == token) return false;

    error("Error string read from file is not bool (true, false, 1, 0)");
    return false;
}

std::vector<std::string> In::read_all_strings()
{
    std::vector<std::string> tokens;
    tokens.reserve(100);

    while (m_ifs.good())
    {
        std::string str = read_string();
        if (str == "") continue;
        tokens.push_back(str);
    }
    return tokens;
}

std::vector<std::string> In::read_all_lines()
{
    std::vector<std::string> lines; 
    lines.reserve(100);

    while (m_ifs.good())
    {
        lines.push_back(read_line());
    }
    return lines;
}

std::vector<int> In::read_all_ints()
{
    std::vector<int> values;
    values.reserve(100);

    int value;
    for(;;)
    {
        value = read_int();
        if (m_ifs.fail()) break;
        values.push_back(value);
    }
    return values;
}

std::vector<long> In::read_all_longs()
{
    std::vector<long> values;
    values.reserve(100);

    long value;
    for(;;)
    {
        value = read_long();
        if (m_ifs.fail()) break;
        values.push_back(value);
    }
    return values;

}

std::vector<double> In::read_all_doubles()
{
    std::vector<double> values;
    values.reserve(100);

    double value;
    for(;;)
    {
        value = read_double();
        if (m_ifs.fail()) break;
        values.push_back(value);
    }
    return values;

}

bool In::fscanf(const char* format, ...)
{
    std::va_list args;
    va_start(args, format);

    std::string line = read_line();
     
    int result = vsscanf(line.c_str(), format, args);
    va_end(args);

    return result != EOF;
}

void In::close()
{
    m_ifs.close();
}