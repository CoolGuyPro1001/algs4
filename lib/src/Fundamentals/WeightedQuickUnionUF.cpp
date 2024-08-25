#include "WeightedQuickUnionUF.h"

WeightedQuickUnionUF::WeightedQuickUnionUF(int n)
{
    m_count = n;
    m_parent = std::vector<int>(n);
    m_size = std::vector<int>(n);
    for (int i = 0; i < n; i++)
    {
        m_parent[i] = i;
        m_size[i] = 1;
    }
}

int WeightedQuickUnionUF::count()
{
    return m_count;
}

int WeightedQuickUnionUF::find(int p)
{
    validate(p);
    while (p != m_parent[p])
        p = m_parent[p];
    return p;
}

void WeightedQuickUnionUF::union_op(int p, int q)
{
    int root_p = find(p);
    int root_q = find(q);
    if (root_p == root_q) return;

    // make smaller root point to larger one
    if (m_size[root_p] < m_size[root_q])
    {
        m_parent[root_p] = root_q;
        m_size[root_q] += m_size[root_p];
    }
    else
    {
        m_parent[root_q] = root_p;
        m_size[root_p] += m_size[root_q];
    }
    m_count--;
}

// validate that p is a valid index
void WeightedQuickUnionUF::validate(int p)
{
    int n = m_parent.size();
    if (p < 0 || p >= n)
    {
        error(std::format("index {} is not between 0 and {}", p, (n-1)));
    }
}