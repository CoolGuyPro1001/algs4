#include "DoublingRatio.h"
#include "StdRandom.h"
#include "ThreeSum.h"
#include "Stopwatch.h"

static const int MAXIMUM_INTEGER = 1000000;

double DoublingRatio::time_trial(int n)
{
    std::vector<int> a = std::vector<int>(n);
    for (int i = 0; i < n; i++)
    {
        a[i] = StdRandom::uniform_int(-MAXIMUM_INTEGER, MAXIMUM_INTEGER);
    }
    Stopwatch timer = Stopwatch();
    int ignore = ThreeSum::count(a);
    return timer.elapsed_time();
}
