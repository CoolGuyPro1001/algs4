#include "ThreeSumFast.h"
#include "StdOut.h"

/***************************************************************************
* Private Function 
***************************************************************************/

// returns true if the sorted array a[] contains any duplicated integers
bool contains_duplicates(std::vector<int>& a)
{
    for (int i = 1; i < a.size(); i++)
        if (a[i] == a[i-1]) return true;
    return false;
}

/***************************************************************************
* Public Functions
***************************************************************************/

void ThreeSumFast::print_all(std::vector<int>& a)
{
    int n = a.size();
    std::sort(a.begin(), a.end());
    if (contains_duplicates(a)) error("array contains duplicate integers");
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            int k = std::binary_search(a.begin(), a.end(), -(a[i] + a[j]));
            if (k > j) StdOut::printf("%d %d %d\n", a[i], a[j], a[k]);
        }
    }
}

int ThreeSumFast::count(std::vector<int>& a)
{
    int count = 0;
    int n = a.size();
    std::sort(a.begin(), a.end());
    if (contains_duplicates(a)) error("array contains duplicate integers");
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (std::binary_search(a.begin() + j + 1, a.end(), -(a[i] + a[j])))
                count++;
        }
    }
    return count;
}