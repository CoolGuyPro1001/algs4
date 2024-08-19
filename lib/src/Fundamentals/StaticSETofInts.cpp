#include "StaticSETofInts.h"

StaticSETofInts::StaticSETofInts(std::vector<int> keys)
{

    // defensive copy
    m_a = std::vector<int>(keys.size());
    for (int i = 0; i < keys.size(); i++)
        m_a[i] = keys[i];

    // sort the integers
    std::sort(keys.begin(), keys.end());

    // check for duplicates
    for (int i = 1; i < m_a.size(); i++)
    {
        if (m_a[i] == m_a[i-1])
            error("Argument arrays contains duplicate keys.");
    }
}

bool StaticSETofInts::contains(int key) const
{
    return rank(key) != -1;
}

int StaticSETofInts::rank(int key) const
{
    int lo = 0;
    int hi = m_a.size() - 1;
    while (lo <= hi) {
        // Key is in a[lo..hi] or not present.
        int mid = lo + (hi - lo) / 2;
        if      (key < m_a[mid]) hi = mid - 1;
        else if (key > m_a[mid]) lo = mid + 1;
        else return mid;
    }
    return -1;
}