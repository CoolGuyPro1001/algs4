#include "Point1D.h"
#include "StdDraw.h"
#include "StdRandom.h"

/**
 * Unit tests the point data type.
 *
 * @param args the command-line arguments
*/ 
int Fundamentals_TestPoint2D(int argc, char** argv) 
{
    if (argc != 3) return -1;
    
    int x0 = atoi(argv[0]);
    int y0 = atoi(argv[1]);
    int n = atoi(argv[2]);

    StdDraw.setCanvasSize(800, 800);
    StdDraw.setXscale(0, 100);
    StdDraw.setYscale(0, 100);
    StdDraw.setPenRadius(0.005);
    StdDraw.enableDoubleBuffering();

    Point2D[] points = new Point2D[n];
    for (int i = 0; i < n; i++) {
        int x = StdRandom.uniformInt(100);
        int y = StdRandom.uniformInt(100);
        points[i] = new Point2D(x, y);
        points[i].draw();
    }

    // draw p = (x0, x1) in red
    Point2D p = new Point2D(x0, y0);
    StdDraw.setPenColor(StdDraw.RED);
    StdDraw.setPenRadius(0.02);
    p.draw();


    // draw line segments from p to each point, one at a time, in polar order
    StdDraw.setPenRadius();
    StdDraw.setPenColor(StdDraw.BLUE);
    Arrays.sort(points, p.polarOrder());
    for (int i = 0; i < n; i++) {
        p.drawTo(points[i]);
        StdDraw.show();
        StdDraw.pause(100);
    }
}