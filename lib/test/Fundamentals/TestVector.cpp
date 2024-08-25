#include "Vector.h"
#include "StdOut.h"

/**
 * Unit tests the {@code Vector} data type.
 *
 * @param args the command-line arguments
 */
int Fundamentals_TestVector(int argc, char** argv)
{
    std::initializer_list<double> x_data = { 1.0, 2.0, 3.0, 4.0 };
    std::initializer_list<double> y_data = { 5.0, 2.0, 4.0, 1.0 };
    Vector x = Vector(x_data);
    Vector y = Vector(y_data);

    StdOut::printf("   x       = %s\n", x.to_string().c_str());
    StdOut::printf("   y       = %s\n", y.to_string().c_str());

    Vector z = x.plus(y);
    StdOut::printf("   z       = %s\n", z.to_string().c_str());

    z = z.scale(10.0);
    StdOut::printf(" 10z       = %s\n", z.to_string().c_str());

    StdOut::printf("  |x|      = %f\n", x.magnitude());
    StdOut::printf(" <x, y>    = %f\n", x.dot(y));
    StdOut::printf("dist(x, y) = %f\n", x.distance_to(y));
    StdOut::printf("dir(x)     = %s\n", x.direction().to_string().c_str());

    return 0;
}