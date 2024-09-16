#include "StaticSETofInts.h"

StaticSETofInts::StaticSETofInts(std::vector<int>& keys)
{
    // defensive copy
    m_a = std::vector<int>(keys.size());
    std::copy(keys.begin(), keys.end(), m_a.begin());

    // sort the integers
    std::sort(m_a.begin(), m_a.end());

    // erase any duplicates
    m_a.erase(std::unique(m_a.begin(), m_a.end()), m_a.end());
}

bool StaticSETofInts::contains(int key) const
{
    return rank(key) != -1;
}

int StaticSETofInts::rank(int key) const
{
    int lo = 0;
    int hi = m_a.size() - 1;
    while (lo <= hi)
    {
        // Key is in a[lo..hi] or not present.
        int mid = lo + (hi - lo) / 2;
        if      (key < m_a[mid]) hi = mid - 1;
        else if (key > m_a[mid]) lo = mid + 1;
        else return mid;
    }
    return -1;
}