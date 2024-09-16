#include "QuickFindUF.h"


QuickFindUF::QuickFindUF(int n)
{
    m_count = n;
    m_id = std::vector<int>(n);
    for (int i = 0; i < n; i++)
        m_id[i] = i;
}

int QuickFindUF::count() const
{
    return m_count;
}

int QuickFindUF::find(int p) const
{
    validate(p);
    return m_id[p];
}

void QuickFindUF::union_op(int p, int q)
{
    validate(p);
    validate(q);
    int pid = m_id[p];   // needed for correctness
    int qid = m_id[q];   // to reduce the number of array accesses

    // p and q are already in the same component
    if (pid == qid) return;

    for (int i = 0; i < m_id.size(); i++)
        if (m_id[i] == pid) m_id[i] = qid;
    m_count--;
}

void QuickFindUF::validate(int p) const
{
    int n = m_id.size();
    if (p < 0 || p >= n)
    {
        error("index {} is not between 0 and {}", p, (n-1));
    }
}