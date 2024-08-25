#include "ThreeSum.h"
#include "StdOut.h"

void ThreeSum::print_all(std::vector<int> a)
{
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (a[i] + a[j] + a[k] == 0)
                {
                    StdOut::printf("%d %d %d\n", a[i], a[j], a[k]);
                }
            }
        }
    }
}

int ThreeSum::count(std::vector<int> a)
{
    int n = a.size();
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                if (a[i] + a[j] + a[k] == 0)
                {
                    count++;
                }
            }
        }
    }
    return count;
}
