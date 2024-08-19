#include "Vector.h"

Vector::Vector(int d)
{
    m_d = d;
    m_data = std::vector<double>(d);
}

Vector::Vector(std::initializer_list<double> a)
{
    m_d = a.size();

    // defensive copy so that client can't alter our copy of data[]
    m_data = std::vector<double>(m_d);
    int i = 0;
    for (auto it = a.begin(); it != a.end(); it++)
    {
        m_data[i++] = *it;
    }
}

int Vector::dimension() const
{
    return m_d;
}

double Vector::dot(Vector that) const
{
    if (m_d != that.m_d) error("Dimensions don't agree");
    double sum = 0.0;
    for (int i = 0; i < m_d; i++)
        sum = sum + (m_data[i] * that.m_data[i]);
    return sum;
}

double Vector::magnitude() const
{
    return sqrt(dot(*this));
}

double Vector::distance_to(Vector that) const
{
    if (m_d != that.m_d) error("Dimensions don't agree");
    return minus(that).magnitude();
}

Vector Vector::plus(Vector that) const
{
    if (m_d != that.m_d) error("Dimensions don't agree");
    Vector c = Vector(m_d);
    for (int i = 0; i < m_d; i++)
        c.m_data[i] = m_data[i] + that.m_data[i];
    return c;
}

Vector Vector::minus(Vector that) const
{
    if (m_d != that.m_d) error("Dimensions don't agree");
    Vector c = Vector(m_d);
    for (int i = 0; i < m_d; i++)
        c.m_data[i] = m_data[i] - that.m_data[i];
    return c;
}

double Vector::cartesian(int i) const
{
    return m_data[i];
}

Vector Vector::scale(double alpha) const
{
    Vector c = Vector(m_d);
    for (int i = 0; i < m_d; i++)
        c.m_data[i] = alpha * m_data[i];
    return c;
}

Vector Vector::direction() const
{
    if (magnitude() == 0.0) error("Zero-vector has no direction");
    return scale(1.0 / magnitude());
}

std::string Vector::to_string() const
{
    std::string s = "";
    for (int i = 0; i < m_d; i++)
        s += std::to_string(m_data[i]) + std::string(" ");
    return s;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << v.to_string();
    return os;
}