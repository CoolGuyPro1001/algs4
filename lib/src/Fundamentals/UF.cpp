#include "UF.h"

UF::UF(int n)
{
    if (n < 0) error("illegal argument");
    m_count = n;
    m_parent = std::vector<int>(n);
    m_rank = std::vector<uint8_t>(n);
    for (int i = 0; i < n; i++)
    {
        m_parent[i] = i;
        m_rank[i] = 0;
    }
}

int UF::find(int p)
{
    validate(p);
    while (p != m_parent[p])
    {
        m_parent[p] = m_parent[m_parent[p]];    // path compression by halving
        p = m_parent[p];
    }
    return p;
}

int UF::count() const
{
    return m_count;
}

void UF::union_op(int p, int q)
{
    int root_p = find(p);
    int root_q = find(q);
    if (root_p == root_q) return;

    // make root of smaller m_rank point to root of larger m_rank
    if      (m_rank[root_p] < m_rank[root_q]) m_parent[root_p] = root_q;
    else if (m_rank[root_p] > m_rank[root_q]) m_parent[root_q] = root_p;
    else
    {
        m_parent[root_q] = root_p;
        m_rank[root_p]++;
    }
    m_count--;
}

void UF::validate(int p) const
{
    int n = m_parent.size();
    if (p < 0 || p >= n)
    {
        error("index {} is not between 0 and {}", p, (n-1));
    }
}