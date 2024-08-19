#include "Interval1D.h"
#include "StdOut.h"

/**
 * Unit tests the {@code Interval1D} data type.
 *
 * @param args the command-line arguments
 */
int main()
{
    std::vector<Interval1D> intervals = std::vector<Interval1D>();
    intervals.reserve(10);

    intervals.push_back(Interval1D(15.0, 33.0));
    intervals.push_back(Interval1D(45.0, 60.0));
    intervals.push_back(Interval1D(20.0, 70.0));
    intervals.push_back(Interval1D(46.0, 55.0));

    StdOut::println("Unsorted");
    for (int i = 0; i < intervals.size(); i++)
        StdOut::println(intervals[i]);
    StdOut::println();

    StdOut::println("Sort by min endpoint");
    std::sort(intervals.begin(), intervals.end(), Interval1D::min_endpoint_compare);
    for (int i = 0; i < intervals.size(); i++)
        StdOut::println(intervals[i]);
    StdOut::println();

    StdOut::println("Sort by max endpoint");
    std::sort(intervals.begin(), intervals.end(), Interval1D::max_endpoint_compare);
    for (int i = 0; i < intervals.size(); i++)
        StdOut::println(intervals[i]);
    StdOut::println();

    StdOut::println("Sort by length");
    std::sort(intervals.begin(), intervals.end(), Interval1D::length_compare);
    for (int i = 0; i < intervals.size(); i++)
        StdOut::println(intervals[i]);
    StdOut::println();
}