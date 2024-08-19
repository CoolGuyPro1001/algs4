#include "Interval2D.h"
#include "Counter.h"
#include "StdOut.h"
#include "StdRandom.h"

/**
 * Unit tests the {@code Interval2D} data type.
 *
 * @param args the command-line arguments
 */
int main(int argc, char** argv)
{
    if (argc < 6)
        return 0;

    double xmin = atof(argv[1]);
    double xmax = atof(argv[2]);
    double ymin = atof(argv[3]);
    double ymax = atof(argv[4]);
    int trials = atoi(argv[5]);

    Interval1D x_interval = Interval1D(xmin, xmax);
    Interval1D y_interval = Interval1D(ymin, ymax);
    Interval2D box = Interval2D(x_interval, y_interval);
    //box.draw();

    Counter counter = Counter("hits");
    for (int t = 0; t < trials; t++)
    {
        double x = StdRandom::uniform_double(0.0, 1.0);
        double y = StdRandom::uniform_double(0.0, 1.0);
        Point2D point = Point2D(x, y);

        if (box.contains(point)) counter.increment();
        //else                     //point.draw();
    }

    StdOut::println(counter);
    StdOut::printf("box area = %.2f\n", box.area());
}