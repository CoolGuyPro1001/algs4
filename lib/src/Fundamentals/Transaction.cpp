#include "Transaction.h"

Transaction::Transaction() :
    m_amount(0), m_when(Date()), m_who("John Doe")
{

}

Transaction::Transaction(std::string who, Date when, double amount)
{
    double infinity = std::numeric_limits<double>::infinity();
    double nan = std::numeric_limits<double>::signaling_NaN();

    if (amount == nan || amount == infinity)
        error("Amount cannot be NaN or infinite");
    m_who    = who;
    m_when   = when;
    m_amount = amount;
}

Transaction::Transaction(std::string transaction)
{
    char temp[transaction.size()];
    memcpy(temp, transaction.c_str(), transaction.size());

    std::string a[3] = {"", "", ""};
    char* token = strtok(temp, " ");
    int i = 0;
    while (token != nullptr)
    {
        if (i > 2)
        {
            error("Invalid Transaction");
        }
        
        a[i++] = token;
        token = strtok(nullptr, " ");
    }

    m_who    = a[0];
    m_when   = Date(a[1]);
    m_amount = atof(a[2].c_str());
    double infinity = std::numeric_limits<double>::infinity();
    double nan = std::numeric_limits<double>::signaling_NaN();
    if (m_amount == nan || m_amount == infinity)
        error("Amount cannot be NaN or infinite");
}

std::string Transaction::who() const
{
    return m_who;
}

Date Transaction::when() const
{
    return m_when;
}

double Transaction::amount() const
{
    return m_amount;
}

std::string Transaction::to_string() const
{
    char str[m_who.size() + 30];
    sprintf(str, "%-10s %10s %8.2f", m_who.c_str(), m_when.to_string().c_str(), m_amount);
    return std::string(str);
}

std::ostream& operator<<(std::ostream& os, const Transaction& t)
{
    os << t.to_string();
    return os;
}

bool Transaction::operator==(const Transaction& other) const
{
    if (&other == this) return true;
    return m_amount == other.m_amount && m_who == other.m_who && m_when == other.m_when;
}

bool Transaction::operator!=(const Transaction& other) const
{
    if (&other == this) return false;
    return m_amount != other.m_amount || m_who != other.m_who || m_when != other.m_when;
}

bool Transaction::operator>(const Transaction& other) const
{
    if (&other == this) return false;
    return m_amount > other.m_amount;
}

bool Transaction::operator<(const Transaction& other) const
{
    if (&other == this) return false;
    return m_amount < other.m_amount;
}

bool Transaction::operator>=(const Transaction& other) const
{
    if (&other == this) return false;
    return m_amount >= other.m_amount;
}

bool Transaction::operator<=(const Transaction& other) const
{
    if (&other == this) return false;
    return m_amount <= other.m_amount;
}

size_t Transaction::hash_code()
{
    size_t hash = 1;
    hash = 31*hash + std::hash<std::string>{}(m_who); 
    hash = 31*hash + m_when.hash_code();
    hash = 31*hash + std::hash<double>{}(m_amount);
    return hash;
}

bool Transaction::who_order(Transaction a, Transaction b)
{
    return a.m_who < b.m_who;
}

bool Transaction::when_order(Transaction a, Transaction b)
{
    return a.m_when < b.m_when;   
}

bool Transaction::how_much_order(Transaction a, Transaction b)
{
    return a.m_amount < b.m_amount;
}