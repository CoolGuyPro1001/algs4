#include "QuickUnionUF.h"

QuickUnionUF::QuickUnionUF(int n)
{
    m_parent = std::vector<int>(n);
    m_count = n;
    for (int i = 0; i < n; i++)
    {
        m_parent[i] = i;
    }
}

int QuickUnionUF::count() const
{
    return m_count;
}

int QuickUnionUF::find(int p) const
{
    validate(p);
    while (p != m_parent[p])
        p = m_parent[p];
    return p;
}

void QuickUnionUF::union_op(int p, int q)
{
    int root_p = find(p);
    int root_q = find(q);
    if (root_p == root_q) return;
    m_parent[root_p] = root_q;
    m_count--;
}

// validate that p is a valid index
void QuickUnionUF::validate(int p) const
{
    int n = m_parent.size();
    if (p < 0 || p >= n)
    {
        error("index {} is not between 0 and {}", p, (n-1));
    }
}