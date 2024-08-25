#ifndef STDDRAW_H
#define STDDRAW_H

/******************************************************************************
 *  Compilation:  javac StdDraw.java
 *  Execution:    java StdDraw
 *  Dependencies: none
 *
 *  Standard drawing library. This class provides a basic capability for
 *  creating drawings with your programs. It uses a simple graphics model that
 *  allows you to create drawings consisting of geometric shapes (e.g.,
 *  points, lines, circles, rectangles) in a window on your computer
 *  and to save the drawings to a file.
 *
 *  Todo
 *  ----
 *    -  Don't show window until first unbuffered drawing command or call to show()
 *       (with setVisible not set to false).
 *    -  Add support for gradient fill, etc.
 *    -  Fix setCanvasSize() so that it can be called only once.
 *    -  On some systems, drawing a line (or other shape) that extends way
 *       beyond canvas (e.g., to infinity) dimensions does not get drawn.
 *
 *  Remarks
 *  -------
 *    -  don't use AffineTransform for rescaling since it inverts
 *       images and strings
 *
 ******************************************************************************/

/**
 *  The {@code StdDraw} class provides static methods for creating drawings
 *  with your programs. It uses a simple graphics model that
 *  allows you to create drawings consisting of points, lines, squares,
 *  circles, and other geometric shapes in a window on your computer and
 *  to save the drawings to a file. Standard drawing also includes
 *  facilities for text, color, pictures, and animation, along with
 *  user interaction via the keyboard and mouse.
 *  <p>
 *  <b>Getting started.</b>
 *  To use this class, you must have {@code StdDraw.class} in your
 *  Java classpath. If you used our autoinstaller, you should be all set.
 *  Otherwise, either download
 *  <a href = "https://introcs.cs.princeton.edu/java/code/stdlib.jar">stdlib.jar</a>
 *  and add to your Java classpath or download
 *  <a href = "https://introcs.cs.princeton.edu/java/stdlib/StdDraw.java">StdDraw.java</a>
 *  and put a copy in your working directory.
 *  <p>
 *  Now, cut-and-paste the following short program into your editor:
 *  <pre>
 *   public class TestStdDraw {
 *       public static void main(String[] args) {
 *           StdDraw.setPenRadius(0.05);
 *           StdDraw.setPenColor(StdDraw.BLUE);
 *           StdDraw.point(0.5, 0.5);
 *           StdDraw.setPenColor(StdDraw.MAGENTA);
 *           StdDraw.line(0.2, 0.2, 0.8, 0.2);
 *       }
 *   }
 *  </pre>
 *  If you compile and execute the program, you should see a window
 *  appear with a thick magenta line and a blue point.
 *  This program illustrates the two main types of methods in standard
 *  drawing—methods that draw geometric shapes and methods that
 *  control drawing parameters.
 *  The methods {@code StdDraw.line()} and {@code StdDraw.point()}
 *  draw lines and points; the methods {@code StdDraw.setPenRadius()}
 *  and {@code StdDraw.setPenColor()} control the line thickness and color.
 *  <p>
 *  <b>Points and lines.</b>
 *  You can draw points and line segments with the following methods:
 *  <ul>
 *  <li> {@link #point(double x, double y)}
 *  <li> {@link #line(double x1, double y1, double x2, double y2)}
 *  </ul>
 *  <p>
 *  The <em>x</em>- and <em>y</em>-coordinates must be in the drawing area
 *  (between 0 and 1 and by default) or the points and lines will not be visible.
 *  <p>
 *  <b>Squares, circles, rectangles, and ellipses.</b>
 *  You can draw squares, circles, rectangles, and ellipses using
 *  the following methods:
 *  <ul>
 *  <li> {@link #circle(double x, double y, double radius)}
 *  <li> {@link #ellipse(double x, double y, double semiMajorAxis, double semiMinorAxis)}
 *  <li> {@link #square(double x, double y, double halfLength)}
 *  <li> {@link #rectangle(double x, double y, double halfWidth, double halfHeight)}
 *  </ul>
 *  <p>
 *  All of these methods take as arguments the location and size of the shape.
 *  The location is always specified by the <em>x</em>- and <em>y</em>-coordinates
 *  of its <em>center</em>.
 *  The size of a circle is specified by its radius and the size of an ellipse is
 *  specified by the lengths of its semi-major and semi-minor axes.
 *  The size of a square or rectangle is specified by its half-width or half-height.
 *  The convention for drawing squares and rectangles is parallel to those for
 *  drawing circles and ellipses, but may be unexpected to the uninitiated.
 *  <p>
 *  The methods above trace outlines of the given shapes. The following methods
 *  draw filled versions:
 *  <ul>
 *  <li> {@link #filledCircle(double x, double y, double radius)}
 *  <li> {@link #filledEllipse(double x, double y, double semiMajorAxis, double semiMinorAxis)}
 *  <li> {@link #filledSquare(double x, double y, double radius)}
 *  <li> {@link #filledRectangle(double x, double y, double halfWidth, double halfHeight)}
 *  </ul>
 *  <p>
 *  <b>Circular arcs.</b>
 *  You can draw circular arcs with the following method:
 *  <ul>
 *  <li> {@link #arc(double x, double y, double radius, double angle1, double angle2)}
 *  </ul>
 *  <p>
 *  The arc is from the circle centered at (<em>x</em>, <em>y</em>) of the specified radius.
 *  The arc extends from angle1 to angle2. By convention, the angles are
 *  <em>polar</em> (counterclockwise angle from the <em>x</em>-axis)
 *  and represented in degrees. For example, {@code StdDraw.arc(0.0, 0.0, 1.0, 0, 90)}
 *  draws the arc of the unit circle from 3 o'clock (0 degrees) to 12 o'clock (90 degrees).
 *  <p>
 *  <b>Polygons.</b>
 *  You can draw polygons with the following methods:
 *  <ul>
 *  <li> {@link #polygon(double[] x, double[] y)}
 *  <li> {@link #filledPolygon(double[] x, double[] y)}
 *  </ul>
 *  <p>
 *  The points in the polygon are ({@code x[i]}, {@code y[i]}).
 *  For example, the following code fragment draws a filled diamond
 *  with vertices (0.1, 0.2), (0.2, 0.3), (0.3, 0.2), and (0.2, 0.1):
 *  <pre>
 *   double[] x = { 0.1, 0.2, 0.3, 0.2 };
 *   double[] y = { 0.2, 0.3, 0.2, 0.1 };
 *   StdDraw.filledPolygon(x, y);
 *  </pre>
 *  <p>
 *  <b>Pen size.</b>
 *  The pen is circular, so that when you set the pen radius to <em>r</em>
 *  and draw a point, you get a circle of radius <em>r</em>. Also, lines are
 *  of thickness 2<em>r</em> and have rounded ends. The default pen radius
 *  is 0.002 and is not affected by coordinate scaling. This default pen
 *  radius is about 1/500 the width of the default canvas, so that if
 *  you draw 200 points equally spaced along a horizontal or vertical line,
 *  you will be able to see individual circles, but if you draw 250 such
 *  points, the result will look like a line.
 *  <ul>
 *  <li> {@link #setPenRadius(double radius)}
 *  </ul>
 *  <p>
 *  For example, {@code StdDraw.setPenRadius(0.01)} makes
 *  the thickness of the lines and the size of the points to be five times
 *  the 0.002 default.
 *  To draw points with the minimum possible radius (one pixel on typical
 *  displays), set the pen radius to 0.0.
 *  <p>
 *  <b>Pen color.</b>
 *  All geometric shapes (such as points, lines, and circles) are drawn using
 *  the current pen color. By default, it is black.
 *  You can change the pen color with the following methods:
 *  <ul>
 *  <li> {@link #setPenColor(int red, int green, int blue)}
 *  <li> {@link #setPenColor(Color color)}
 *  </ul>
 *  <p>
 *  The first method allows you to specify colors using the RGB color system.
 *  This <a href = "http://johndyer.name/lab/colorpicker/">color picker</a>
 *  is a convenient way to find a desired color.
 *  <p>
 *  The second method allows you to specify colors using the
 *  {@link Color} data type, which is defined in Java's {@link java.awt} package.
 *  Standard drawing defines a number of predefined colors including
 *  {@link #BLACK}, {@link #WHITE}, {@link #RED}, {@link #GREEN},
 *  and {@link #BLUE}.
 *  For example, {@code StdDraw.setPenColor(StdDraw.RED)} sets the
 *  pen color to red.
 *  <p>
 *  <b>Window title.</b>
 *  By default, the standard drawing window title is "Standard Draw".
 *  You can change the title with the following method:
 *  <ul>
 *  <li> {@link #setTitle(String windowTitle)}
 *  </ul>
 *  <p>
 *  This sets the standard drawing window title to the specified string.
 *  <p>
 *  <b>Canvas size.</b>
 *  By default, all drawing takes places in a 512-by-512 canvas.
 *  The canvas does not include the window title or window border.
 *  You can change the size of the canvas with the following method:
 *  <ul>
 *  <li> {@link #setCanvasSize(int width, int height)}
 *  </ul>
 *  <p>
 *  This sets the canvas size to be <em>width</em>-by-<em>height</em> pixels.
 *  It also clears the current drawing using the default background color (white).
 *  Ordinarily, this method is called only once, at the very beginning of a program.
 *  For example, {@code StdDraw.setCanvasSize(800, 800)}
 *  sets the canvas size to be 800-by-800 pixels.
 *  <p>
 *  <b>Canvas scale and coordinate system.</b>
 *  By default, all drawing takes places in the unit square, with (0, 0) at
 *  lower left and (1, 1) at upper right. You can change the default
 *  coordinate system with the following methods:
 *  <ul>
 *  <li> {@link #setXscale(double xmin, double xmax)}
 *  <li> {@link #setYscale(double ymin, double ymax)}
 *  <li> {@link #setScale(double min, double max)}
 *  </ul>
 *  <p>
 *  The arguments are the coordinates of the minimum and maximum
 *  <em>x</em>- or <em>y</em>-coordinates that will appear in the canvas.
 *  For example, if you  wish to use the default coordinate system but
 *  leave a small margin, you can call {@code StdDraw.setScale(-.05, 1.05)}.
 *  <p>
 *  These methods change the coordinate system for subsequent drawing
 *  commands; they do not affect previous drawings.
 *  These methods do not change the canvas size; so, if the <em>x</em>-
 *  and <em>y</em>-scales are different, squares will become rectangles
 *  and circles will become ellipses.
 *  <p>
 *  <b>Text.</b>
 *  You can use the following methods to annotate your drawings with text:
 *  <ul>
 *  <li> {@link #text(double x, double y, String text)}
 *  <li> {@link #text(double x, double y, String text, double degrees)}
 *  <li> {@link #textLeft(double x, double y, String text)}
 *  <li> {@link #textRight(double x, double y, String text)}
 *  </ul>
 *  <p>
 *  The first two methods write the specified text in the current font,
 *  centered at (<em>x</em>, <em>y</em>).
 *  The second method allows you to rotate the text.
 *  The last two methods either left- or right-align the text at (<em>x</em>, <em>y</em>).
 *  <p>
 *  The default font is a Sans Serif font with point size 16.
 *  You can use the following method to change the font:
 *  <ul>
 *  <li> {@link #setFont(Font font)}
 *  </ul>
 *  <p>
 *  To specify the font, you use the {@link Font} data type,
 *  which is defined in Java's {@link java.awt} package.
 *  This allows you to
 *  choose the face, size, and style of the font. For example, the following
 *  code fragment sets the font to Arial Bold, 60 point.
 *  The <code>import</code> statement allows you to refer to <code>Font</code>
 *  directly, without needing the fully qualified name <code>java.awt.Font</code>.
 *  <pre>
 *   import java.awt.Font;
 *   ...
 *   Font font = new Font("Arial", Font.BOLD, 60);
 *   StdDraw.setFont(font);
 *   StdDraw.text(0.5, 0.5, "Hello, World");
 *  </pre>
 *  <p>
 *  <b>Images.</b>
 *  You can use the following methods to add images to your drawings:
 *  <ul>
 *  <li> {@link #picture(double x, double y, String filename)}
 *  <li> {@link #picture(double x, double y, String filename, double degrees)}
 *  <li> {@link #picture(double x, double y, String filename, double scaledWidth, double scaledHeight)}
 *  <li> {@link #picture(double x, double y, String filename, double scaledWidth, double scaledHeight, double degrees)}
 *  </ul>
 *  <p>
 *  These methods draw the specified image, centered at (<em>x</em>, <em>y</em>).
 *  The image must be in a supported file format (typically JPEG, PNG, GIF, TIFF, and BMP).
 *  The image will display at its native size, independent of the coordinate system.
 *  Optionally, you can rotate the image a specified number of degrees counterclockwise
 *  or rescale it to fit snugly inside a bounding box.
 *  <p>
 *  <b>Saving to a file.</b>
 *  You can save your image to a file using the <em>File → Save</em> menu option.
 *  You can also save a file programmatically using the following method:
 *  <ul>
 *  <li> {@link #save(String filename)}
 *  </ul>
 *  <p>
 *  You can save the drawing to a file in a supported file format
 *  (typically JPEG, PNG, GIF, TIFF, and BMP).
 *
 *  <p><b>File formats.</b>
 *  The {@code StdDraw} class supports reading and writing images to any of the
 *  file formats supported by {@link javax.imageio} (typically JPEG, PNG,
 *  GIF, TIFF, and BMP).
 *  The file extensions corresponding to JPEG, PNG, GIF, TIFF, and BMP,
 *  are {@code .jpg}, {@code .png}, {@code .gif}, {@code .tif},
 *  and {@code .bmp}, respectively.
 *  <p>
 *  We recommend using PNG for drawing that consist solely of geometric shapes
 *  and JPEG for drawings that contains pictures.
 *  The JPEG file format does not support transparent backgrounds.
 *
 *  <p>
 *  <b>Clearing the canvas.</b>
 *  To clear the entire drawing canvas, you can use the following methods:
 *  <ul>
 *  <li> {@link #clear()}
 *  <li> {@link #clear(Color color)}
 *  </ul>
 *  <p>
 *  The first method clears the canvas to the default background color (white);
 *  the second method allows you to specify the background color. For example,
 *  {@code StdDraw.clear(StdDraw.LIGHT_GRAY)} clears the canvas to a shade
 *  of gray. To make the background transparent,
 *  call {@code StdDraw.clear(StdDraw.TRANSPARENT)}.
 *
 *  <p>
 *  <b>Computer animations and double buffering.</b>
 *  Double buffering is one of the most powerful features of standard drawing,
 *  enabling computer animations.
 *  The following methods control the way in which objects are drawn:
 *  <ul>
 *  <li> {@link #enableDoubleBuffering()}
 *  <li> {@link #disableDoubleBuffering()}
 *  <li> {@link #show()}
 *  <li> {@link #pause(int t)}
 *  </ul>
 *  <p>
 *  By default, double buffering is disabled, which means that as soon as you
 *  call a drawing
 *  method—such as {@code point()} or {@code line()}—the
 *  results appear on the screen.
 *  <p>
 *  When double buffering is enabled by calling {@link #enableDoubleBuffering()},
 *  all drawing takes place on the <em>offscreen canvas</em>. The offscreen canvas
 *  is not displayed. Only when you call
 *  {@link #show()} does your drawing get copied from the offscreen canvas to
 *  the onscreen canvas, where it is displayed in the standard drawing window. You
 *  can think of double buffering as collecting all of the lines, points, shapes,
 *  and text that you tell it to draw, and then drawing them all
 *  <em>simultaneously</em>, upon request.
 *  <p>
 *  The most important use of double buffering is to produce computer
 *  animations, creating the illusion of motion by rapidly
 *  displaying static drawings. To produce an animation, repeat
 *  the following four steps:
 *  <ul>
 *  <li> Clear the offscreen canvas.
 *  <li> Draw objects on the offscreen canvas.
 *  <li> Copy the offscreen canvas to the onscreen canvas.
 *  <li> Wait for a short while.
 *  </ul>
 *  <p>
 *  The {@link #clear()}, {@link #show()}, and {@link #pause(int t)} methods
 *  support the first, third, and fourth of these steps, respectively.
 *  <p>
 *  For example, this code fragment animates two balls moving in a circle.
 *  <pre>
 *   StdDraw.setScale(-2.0, +2.0);
 *   StdDraw.enableDoubleBuffering();
 *
 *   for (double t = 0.0; true; t += 0.02) {
 *       double x = Math.sin(t);
 *       double y = Math.cos(t);
 *       StdDraw.clear();
 *       StdDraw.filledCircle(x, y, 0.1);
 *       StdDraw.filledCircle(-x, -y, 0.1);
 *       StdDraw.show();
 *       StdDraw.pause(20);
 *   }
 *  </pre>
 *  Without double buffering, the balls would flicker as they move.
 *  <p>
 *  <b>Keyboard and mouse inputs.</b>
 *  Standard drawing has very basic support for keyboard and mouse input.
 *  It is much less powerful than most user interface libraries provide, but also much simpler.
 *  You can use the following methods to intercept mouse events:
 *  <ul>
 *  <li> {@link #isMousePressed()}
 *  <li> {@link #mouseX()}
 *  <li> {@link #mouseY()}
 *  </ul>
 *  <p>
 *  The first method tells you whether a mouse button is currently being pressed.
 *  The last two methods tells you the <em>x</em>- and <em>y</em>-coordinates of the mouse's
 *  current position, using the same coordinate system as the canvas (the unit square, by default).
 *  You should use these methods in an animation loop that waits a short while before trying
 *  to poll the mouse for its current state.
 *  You can use the following methods to intercept keyboard events:
 *  <ul>
 *  <li> {@link #hasNextKeyTyped()}
 *  <li> {@link #nextKeyTyped()}
 *  <li> {@link #isKeyPressed(int keycode)}
 *  </ul>
 *  <p>
 *  If the user types lots of keys, they will be saved in a list until you process them.
 *  The first method tells you whether the user has typed a key (that your program has
 *  not yet processed).
 *  The second method returns the next key that the user typed (that your program has
 *  not yet processed) and removes it from the list of saved keystrokes.
 *  The third method tells you whether a key is currently being pressed.
 *  <p>
 *  <b>Accessing control parameters.</b>
 *  You can use the following methods to access the current pen color, pen radius,
 *  and font:
 *  <ul>
 *  <li> {@link #getPenColor()}
 *  <li> {@link #getBackgroundColor()}
 *  <li> {@link #getPenRadius()}
 *  <li> {@link #getFont()}
 *  </ul>
 *  <p>
 *  These methods are useful when you want to temporarily change a
 *  control parameter and, later, reset it back to its original value.
 *  <p>
 *  <b>Corner cases.</b>
 *  Here are some corner cases.
 *  <ul>
 *  <li> Drawing an object outside (or partly outside) the canvas is permitted.
 *       However, only the part of the object that appears inside the canvas
 *       will be visible.
 *  <li> Due to floating-point issues, an object drawn with an <em>x</em>- or
 *       <em>y</em>-coordinate that is way outside the canvas (such as the line segment
 *       from (0.5, –10^308) to (0.5, 10^308) may not be visible even in the
 *       part of the canvas where it should be.
 *  <li> Any method that is passed a {@code null} argument will throw an
 *       {@link IllegalArgumentException}.
 *  <li> Any method that is passed a {@link Double#NaN},
 *       {@link Double#POSITIVE_INFINITY}, or {@link Double#NEGATIVE_INFINITY}
 *       argument will throw an {@link IllegalArgumentException}.
 *  </ul>
 *  <p>
 *  <b>Performance tricks.</b>
 *  Standard drawing is capable of drawing large amounts of data.
 *  Here are a few tricks and tips:
 *  <ul>
 *  <li> Use <em>double buffering</em> for static drawing with a large
 *       number of objects.
 *       That is, call {@link #enableDoubleBuffering()} before
 *       the sequence of drawing commands and call {@link #show()} afterwards.
 *       Incrementally displaying a complex drawing while it is being
 *       created can be intolerably inefficient on many computer systems.
 *  <li> When drawing computer animations, call {@code show()}
 *       only once per frame, not after drawing each individual object.
 *  <li> If you call {@code picture()} multiple times with the same filename,
 *       Java will cache the image, so you do not incur the cost of reading
 *       from a file each time.
 *  </ul>
 *  <p>
 *  <b>Known bugs and issues.</b>
 *  <ul>
 *  <li> The {@code picture()} methods may not draw the portion of the image that is
 *       inside the canvas if the center point (<em>x</em>, <em>y</em>) is outside the
 *       canvas.
 *       This bug appears only on some systems.
 *  </ul>
 *  <p>
 *  <b>Reference.</b>
 *  For additional documentation,
 *  see <a href="https://introcs.cs.princeton.edu/15inout">Section 1.5</a> of
 *  <em>Computer Science: An Interdisciplinary Approach</em>
 *  by Robert Sedgewick and Kevin Wayne.
 *
 *  @author Robert Sedgewick
 *  @author Kevin Wayne
 */

class StdFrame : public wxFrame
{
public:
    StdFrame();
};

class StdApp : public wxApp
{
public:
    bool OnInit() override;
};

class StdDraw : public wxApp
{
public:
    /**
     *  The color aqua (0, 255, 255).
     */
    //static const wxColour* AQUA = new wxColour*(0, 255, 255);

    /**
     *  The color black (0, 0, 0).
     */
    //static const wxColour* BLACK = wxColour*.BLACK;

    /**
     *  The color blue (0, 0, 255).
     */
    //static const wxColour* BLUE = wxColour*.BLUE;

    /**
     *  The color cyan (0, 255, 255).
     */
    //static const wxColour* CYAN = wxColour*.CYAN;

    /**
     *  The color fuscia (255, 0, 255).
     */
    //static const wxColour* FUSCIA = new wxColour*(255, 0, 255);

    /**
     *  The color dark gray (64, 64, 64).
     */
    //static const wxColour* DARK_GRAY = wxColour*.DARK_GRAY;

    /**
     *  The color gray (128, 128, 128).
     */
    //static const wxColour* GRAY = wxColour*.GRAY;

    /**
     *  The color green (0, 128, 0).
     */
    //static const wxColour* GREEN = new wxColour*(0, 128, 0);

    /**
     *  The color light gray (192, 192, 192).
     */
    //static const wxColour* LIGHT_GRAY = wxColour*.LIGHT_GRAY;

    /**
     *  The color lime (0, 255, 0).
     */
    //static const wxColour* LIME = new wxColour*(0, 255, 0);

    /**
     *  The color magenta (255, 0, 255).
     */
    //static const wxColour* MAGENTA = wxColour*.MAGENTA;

    /**
     *  The color maroon (128, 0, 0).
     */
    //static const wxColour* MAROON = new wxColour*(128, 0, 0);

    /**
     *  The color navy (0, 0, 128).
     */
    //static const wxColour* NAVY = new wxColour*(0, 0, 128);

    /**
     *  The color olive (128, 128, 0).
     */
    //static const wxColour* OLIVE = new wxColour*(128, 128, 0);

    /**
     *  The color orange (255, 200, 0).
     */
    //static const wxColour* ORANGE = wxColour*.ORANGE;

    /**
     *  The color pink (255, 175, 175).
     */
    //static const wxColour* PINK = wxColour*.PINK;

    /**
     *  The color purple (128, 0, 128).
     */
    //static const wxColour* PURPLE = new wxColour*(128, 0, 128);

    /**
     *  The color red (255, 0, 0).
     */
    //static const wxColour* RED = wxColour*.RED;

    /**
     *  The color silver (192, 192, 192).
     */
    //static const wxColour* SILVER = new wxColour*(192, 192, 192);

    /**
     *  The color teal (0, 128, 128).
     */
    //static const wxColour* TEAL = new wxColour*(0, 128, 128);

    /**
     *  The color white (255, 255, 255).
     */
    //static const wxColour* WHITE = wxColour*.WHITE;

    /**
     *  The color yellow (255, 255, 0).
     */
    //static const wxColour* YELLOW = wxColour*.YELLOW;

    /**
     *  A 100% transparent color, for a transparent background.
     */
    //static const wxColour* TRANSPARENT = new wxColour*(0, 0, 0, 0);

    /**
     * The shade of blue used in <em>Introduction to Programming in Java</em>.
     * It is Pantone 300U. The RGB values are approximately (9, 90, 166).
     */
    //static const wxColour* BOOK_BLUE = new wxColour*(9, 90, 166);

    /**
     * The shade of light blue used in <em>Introduction to Programming in Java</em>.
     * The RGB values are approximately (103, 198, 243).
     */
    //static const wxColour* BOOK_LIGHT_BLUE = new wxColour*(103, 198, 243);

    /**
     * The shade of red used in <em>Algorithms, 4th edition</em>.
     * It is Pantone 1805U. The RGB values are approximately (150, 35, 31).
     */
    //static const wxColour* BOOK_RED = new wxColour*(150, 35, 31);

    /**
     * The shade of orange used in Princeton University's identity.
     * It is PMS 158. The RGB values are approximately (245, 128, 37).
     */
    //static const wxColour* PRINCETON_ORANGE = new wxColour*(245, 128, 37);

    /**
     * Initializes the wxWidgts library
     */
    StdDraw();
    ~StdDraw();
    static void run();
    /**
     * Makes the drawing window visible or invisible.
     *
     * @param  isVisible if {@code true}, makes the drawing window visible,
     *         otherwise hides the drawing window.
     */
    //static void setVisible(bool isVisible);

    /**
     * Sets the canvas (drawing area) to be 512-by-512 pixels.
     * This also clears the current drawing using the default background
     * color (white).
     * Ordinarily, this method is called once, at the very beginning
     * of a program.
     */
    //static void setCanvasSize();

    /**
     * Sets the canvas (drawing area) to be <em>width</em>-by-<em>height</em> pixels.
     * This also clears the current drawing using the default background
     * color (white).
     * Ordinarily, this method is called once, at the very beginning
     * of a program.
     *
     * @param  canvasWidth the width as a number of pixels
     * @param  canvasHeight the height as a number of pixels
     * @throws IllegalArgumentException unless both {@code canvasWidth} and
     *         {@code canvasHeight} are positive
     */
    //static void setCanvasSize(int canvasWidth, int canvasHeight);

    // initialize the drawing canvas
    //static void initCanvas();

    // initialize the GUI
    //static void initGUI();

    // create the menu bar
    //static JMenuBar createMenuBar();

    /**
     * Closes the standard drawing window.
     * This allows the client program to terminate instead of requiring
     * the user to close the standard drawing window manually.
     * Drawing after calling this method will restore the previous window state.
     */
    //static void close();

   /***************************************************************************
    *  Input validation helper methods.
    ***************************************************************************/

    // throw an IllegalArgumentException if x is NaN or infinite
    //static void validate(double x, String name);

    // throw an IllegalArgumentException if s is null
    //static void validateNonnegative(double x, String name);

    // throw an IllegalArgumentException if s is null
    //static void validateNotNull(Object x, String name);

   /***************************************************************************
    *  Set the title of standard drawing window.
    ***************************************************************************/

    /**
     * Sets the title of the standard drawing window to the specified string.
     *
     * @param  title the title
     * @throws IllegalArgumentException if {@code title} is {@code null}
     */
    //static void setTitle(String title);

   /***************************************************************************
    *  User and screen coordinate systems.
    ***************************************************************************/

    /**
     * Sets the <em>x</em>-scale to the default range (between 0.0 and 1.0).
     */
    //static void setXscale();

    /**
     * Sets the <em>y</em>-scale to the default range (between 0.0 and 1.0).
     */
    //static void setYscale();

    /**
     * Sets both the <em>x</em>-scale and <em>y</em>-scale to the default range
     * (between 0.0 and 1.0).
     */
    //static void setScale();

    /**
     * Sets the <em>x</em>-scale to the specified range.
     *
     * @param  min the minimum value of the <em>x</em>-scale
     * @param  max the maximum value of the <em>x</em>-scale
     * @throws IllegalArgumentException if {@code (max == min)}
     * @throws IllegalArgumentException if either {@code min} or {@code max} is either NaN or infinite
     */
    //static void setXscale(double min, double max);

    /**
     * Sets the <em>y</em>-scale to the specified range.
     *
     * @param  min the minimum value of the <em>y</em>-scale
     * @param  max the maximum value of the <em>y</em>-scale
     * @throws IllegalArgumentException if {@code (max == min)}
     * @throws IllegalArgumentException if either {@code min} or {@code max} is either NaN or infinite
     */
    //static void setYscale(double min, double max);

    /**
     * Sets both the <em>x</em>-scale and <em>y</em>-scale to the (same) specified range.
     *
     * @param  min the minimum value of the <em>x</em>- and <em>y</em>-scales
     * @param  max the maximum value of the <em>x</em>- and <em>y</em>-scales
     * @throws IllegalArgumentException if {@code (max == min)}
     * @throws IllegalArgumentException if either {@code min} or {@code max} is either NaN or infinite
     */
    //static void setScale(double min, double max);

    // helper functions that scale from user coordinates to screen coordinates and back
    //static double  scaleX(double x) { return width  * (x - xmin) / (xmax - xmin); }
    //static double  scaleY(double y) { return height * (ymax - y) / (ymax - ymin); }
    //static double factorX(double w) { return w * width  / Math.abs(xmax - xmin);  }
    //static double factorY(double h) { return h * height / Math.abs(ymax - ymin);  }
    //static double   userX(double x) { return xmin + x * (xmax - xmin) / width;    }
    //static double   userY(double y) { return ymax - y * (ymax - ymin) / height;   }
//

    /**
     * Clears the screen using the default background color (white).
     */
    //static void clear();

    /**
     * Clears the screen using the specified background color.
     * To make the background transparent, use {@code StdDraw.TRANSPARENT}.
     *
     * @param color the color to make the background
     * @throws IllegalArgumentException if {@code color} is {@code null}
     */
    //static void clear(wxColour color);

    /**
     * Returns the current pen radius.
     *
     * @return the current value of the pen radius
     */
    //static double getPenRadius();

    /**
     * Sets the pen size to the default size (0.002).
     * The pen is circular, so that lines have rounded ends, and when you set the
     * pen radius and draw a point, you get a circle of the specified radius.
     * The pen radius is not affected by coordinate scaling.
     */
    //static void setPenRadius();

    /**
     * Sets the radius of the pen to the specified size.
     * The pen is circular, so that lines have rounded ends, and when you set the
     * pen radius and draw a point, you get a circle of the specified radius.
     * The pen radius is not affected by coordinate scaling.
     *
     * @param  radius the radius of the pen
     * @throws IllegalArgumentException if {@code radius} is negative, NaN, or infinite
     */
    //static void setPenRadius(double radius);

    /**
     * Returns the current pen color.
     *
     * @return the current pen color
     */
    //static wxColour getPenColor();

    /**
     * Returns the current background color.
     *
     * @return the current background color
     */
    //static wxColour getBackgroundColor();

    /**
     * Sets the pen color to the default color (black).
     */
    //static void setPenColor();

    /**
     * Sets the pen color to the specified color.
     * <p>
     * There are a number predefined pen colors, such as
     * {@code StdDraw.BLACK}, {@code StdDraw.WHITE}, {@code StdDraw.RED},
     * {@code StdDraw.GREEN}, and {@code StdDraw.BLUE}.
     *
     * @param color the color to make the pen
     * @throws IllegalArgumentException if {@code color} is {@code null}
     */
    //static void setPenColor(wxColour color);

    /**
     * Sets the pen color to the specified RGB color.
     *
     * @param  red the amount of red (between 0 and 255)
     * @param  green the amount of green (between 0 and 255)
     * @param  blue the amount of blue (between 0 and 255)
     * @throws IllegalArgumentException if {@code red}, {@code green},
     *         or {@code blue} is outside its prescribed range
     */
    //static void setPenColor(int red, int green, int blue);

    /**
     * Returns the current font.
     *
     * @return the current font
     */
    //static Font getFont();

    /**
     * Sets the font to the default font (sans serif, 16 point).
     */
    //static void setFont();

    /**
     * Sets the font to the specified value.
     *
     * @param font the font
     * @throws IllegalArgumentException if {@code font} is {@code null}
     */
    //static void setFont(Font font);


   /***************************************************************************
    *  Drawing geometric shapes.
    ***************************************************************************/

    /**
     * Draws a line segment between (<em>x</em><sub>0</sub>, <em>y</em><sub>0</sub>) and
     * (<em>x</em><sub>1</sub>, <em>y</em><sub>1</sub>).
     *
     * @param  x0 the <em>x</em>-coordinate of one endpoint
     * @param  y0 the <em>y</em>-coordinate of one endpoint
     * @param  x1 the <em>x</em>-coordinate of the other endpoint
     * @param  y1 the <em>y</em>-coordinate of the other endpoint
     * @throws IllegalArgumentException if any coordinate is either NaN or infinite
     */
    //static void line(double x0, double y0, double x1, double y1);

    /**
     * Draws one pixel at (<em>x</em>, <em>y</em>).
     * This method is private because pixels depend on the display.
     * To achieve the same effect, set the pen radius to 0 and call {@code point()}.
     *
     * @param  x the <em>x</em>-coordinate of the pixel
     * @param  y the <em>y</em>-coordinate of the pixel
     * @throws IllegalArgumentException if {@code x} or {@code y} is either NaN or infinite
     */
    //static void pixel(double x, double y);

    /**
     * Draws a point centered at (<em>x</em>, <em>y</em>).
     * The point is a filled circle whose radius is equal to the pen radius.
     * To draw a single-pixel point, first set the pen radius to 0.
     *
     * @param x the <em>x</em>-coordinate of the point
     * @param y the <em>y</em>-coordinate of the point
     * @throws IllegalArgumentException if either {@code x} or {@code y} is either NaN or infinite
     */
    //static void point(double x, double y);

    /**
     * Draws a circle of the specified radius, centered at (<em>x</em>, <em>y</em>).
     *
     * @param  x the <em>x</em>-coordinate of the center of the circle
     * @param  y the <em>y</em>-coordinate of the center of the circle
     * @param  radius the radius of the circle
     * @throws IllegalArgumentException if {@code radius} is negative
     * @throws IllegalArgumentException if any argument is either NaN or infinite
     */
    //static void circle(double x, double y, double radius);

    /**
     * Draws a filled circle of the specified radius, centered at (<em>x</em>, <em>y</em>).
     *
     * @param  x the <em>x</em>-coordinate of the center of the circle
     * @param  y the <em>y</em>-coordinate of the center of the circle
     * @param  radius the radius of the circle
     * @throws IllegalArgumentException if {@code radius} is negative
     * @throws IllegalArgumentException if any argument is either NaN or infinite
     */
    //static void filledCircle(double x, double y, double radius)

    /**
     * Draws an ellipse with the specified semimajor and semiminor axes,
     * centered at (<em>x</em>, <em>y</em>).
     *
     * @param  x the <em>x</em>-coordinate of the center of the ellipse
     * @param  y the <em>y</em>-coordinate of the center of the ellipse
     * @param  semiMajorAxis is the semimajor axis of the ellipse
     * @param  semiMinorAxis is the semiminor axis of the ellipse
     * @throws IllegalArgumentException if either {@code semiMajorAxis}
     *         or {@code semiMinorAxis} is negative
     * @throws IllegalArgumentException if any argument is either NaN or infinite
     */
    //static void ellipse(double x, double y, double semiMajorAxis, double semiMinorAxis)

    /**
     * Draws a filled ellipse with the specified semimajor and semiminor axes,
     * centered at (<em>x</em>, <em>y</em>).
     *
     * @param  x the <em>x</em>-coordinate of the center of the ellipse
     * @param  y the <em>y</em>-coordinate of the center of the ellipse
     * @param  semiMajorAxis is the semimajor axis of the ellipse
     * @param  semiMinorAxis is the semiminor axis of the ellipse
     * @throws IllegalArgumentException if either {@code semiMajorAxis}
     *         or {@code semiMinorAxis} is negative
     * @throws IllegalArgumentException if any argument is either NaN or infinite
     */
    //static void filledEllipse(double x, double y, double semiMajorAxis, double semiMinorAxis)

    /**
     * Draws a circular arc of the specified radius,
     * centered at (<em>x</em>, <em>y</em>), from angle1 to angle2 (in degrees).
     *
     * @param  x the <em>x</em>-coordinate of the center of the circle
     * @param  y the <em>y</em>-coordinate of the center of the circle
     * @param  radius the radius of the circle
     * @param  angle1 the starting angle. 0 would mean an arc beginning at 3 o'clock.
     * @param  angle2 the angle at the end of the arc. For example, if
     *         you want a 90 degree arc, then angle2 should be angle1 + 90.
     * @throws IllegalArgumentException if {@code radius} is negative
     * @throws IllegalArgumentException if any argument is either NaN or infinite
     */
    //static void arc(double x, double y, double radius, double angle1, double angle2);

    /**
     * Draws a square of the specified size, centered at (<em>x</em>, <em>y</em>).
     *
     * @param  x the <em>x</em>-coordinate of the center of the square
     * @param  y the <em>y</em>-coordinate of the center of the square
     * @param  halfLength one half the length of any side of the square
     * @throws IllegalArgumentException if {@code halfLength} is negative
     * @throws IllegalArgumentException if any argument is either NaN or infinite
     */
    //static void square(double x, double y, double halfLength);

    /**
     * Draws a filled square of the specified size, centered at (<em>x</em>, <em>y</em>).
     *
     * @param  x the <em>x</em>-coordinate of the center of the square
     * @param  y the <em>y</em>-coordinate of the center of the square
     * @param  halfLength one half the length of any side of the square
     * @throws IllegalArgumentException if {@code halfLength} is negative
     * @throws IllegalArgumentException if any argument is either NaN or infinite
     */
    //static void filledSquare(double x, double y, double halfLength);


    /**
     * Draws a rectangle of the specified size, centered at (<em>x</em>, <em>y</em>).
     *
     * @param  x the <em>x</em>-coordinate of the center of the rectangle
     * @param  y the <em>y</em>-coordinate of the center of the rectangle
     * @param  halfWidth one half the width of the rectangle
     * @param  halfHeight one half the height of the rectangle
     * @throws IllegalArgumentException if either {@code halfWidth} or {@code halfHeight} is negative
     * @throws IllegalArgumentException if any argument is either NaN or infinite
     */
    //static void rectangle(double x, double y, double halfWidth, double halfHeight);

    /**
     * Draws a filled rectangle of the specified size, centered at (<em>x</em>, <em>y</em>).
     *
     * @param  x the <em>x</em>-coordinate of the center of the rectangle
     * @param  y the <em>y</em>-coordinate of the center of the rectangle
     * @param  halfWidth one half the width of the rectangle
     * @param  halfHeight one half the height of the rectangle
     * @throws IllegalArgumentException if either {@code halfWidth} or {@code halfHeight} is negative
     * @throws IllegalArgumentException if any argument is either NaN or infinite
     */
    //static void filledRectangle(double x, double y, double halfWidth, double halfHeight);

    /**
     * Draws a polygon with the vertices
     * (<em>x</em><sub>0</sub>, <em>y</em><sub>0</sub>),
     * (<em>x</em><sub>1</sub>, <em>y</em><sub>1</sub>), ...,
     * (<em>x</em><sub><em>n</em>–1</sub>, <em>y</em><sub><em>n</em>–1</sub>).
     *
     * @param  x an array of all the <em>x</em>-coordinates of the polygon
     * @param  y an array of all the <em>y</em>-coordinates of the polygon
     * @throws IllegalArgumentException unless {@code x[]} and {@code y[]}
     *         are of the same length
     * @throws IllegalArgumentException if any coordinate is either NaN or infinite
     * @throws IllegalArgumentException if either {@code x[]} or {@code y[]} is {@code null}
     */
    //static void polygon(double[] x, double[] y);

    /**
     * Draws a filled polygon with the vertices
     * (<em>x</em><sub>0</sub>, <em>y</em><sub>0</sub>),
     * (<em>x</em><sub>1</sub>, <em>y</em><sub>1</sub>), ...,
     * (<em>x</em><sub><em>n</em>–1</sub>, <em>y</em><sub><em>n</em>–1</sub>).
     *
     * @param  x an array of all the <em>x</em>-coordinates of the polygon
     * @param  y an array of all the <em>y</em>-coordinates of the polygon
     * @throws IllegalArgumentException unless {@code x[]} and {@code y[]}
     *         are of the same length
     * @throws IllegalArgumentException if any coordinate is either NaN or infinite
     * @throws IllegalArgumentException if either {@code x[]} or {@code y[]} is {@code null}
     */
    //static void filledPolygon(double[] x, double[] y);

   /***************************************************************************
    *  Drawing images.
    ***************************************************************************/
    // get an image from the given filename
    //static Image getImage(String filename)

    /**
     * Draws the specified image centered at (<em>x</em>, <em>y</em>).
     * The supported image formats are typically JPEG, PNG, GIF, TIFF, and BMP.
     * As an optimization, the picture is cached, so there is no performance
     * penalty for redrawing the same image multiple times (e.g., in an animation).
     * However, if you change the picture file after drawing it, subsequent
     * calls will draw the original picture.
     *
     * @param  x the center <em>x</em>-coordinate of the image
     * @param  y the center <em>y</em>-coordinate of the image
     * @param  filename the name of the image/picture, e.g., "ball.gif"
     * @throws IllegalArgumentException if the image filename is invalid
     * @throws IllegalArgumentException if either {@code x} or {@code y} is either NaN or infinite
     */
    //static void picture(double x, double y, String filename);

    /**
     * Draws the specified image centered at (<em>x</em>, <em>y</em>),
     * rotated given number of degrees.
     * The supported image formats are typically JPEG, PNG, GIF, TIFF, and BMP.
     *
     * @param  x the center <em>x</em>-coordinate of the image
     * @param  y the center <em>y</em>-coordinate of the image
     * @param  filename the name of the image/picture, e.g., "ball.gif"
     * @param  degrees is the number of degrees to rotate counterclockwise
     * @throws IllegalArgumentException if the image filename is invalid
     * @throws IllegalArgumentException if {@code x}, {@code y}, {@code degrees} is NaN or infinite
     * @throws IllegalArgumentException if {@code filename} is {@code null}
     */
    //static void picture(double x, double y, String filename, double degrees);

    /**
     * Draws the specified image centered at (<em>x</em>, <em>y</em>),
     * rescaled to the specified bounding box.
     * The supported image formats are typically JPEG, PNG, GIF, TIFF, and BMP.
     *
     * @param  x the center <em>x</em>-coordinate of the image
     * @param  y the center <em>y</em>-coordinate of the image
     * @param  filename the name of the image/picture, e.g., "ball.gif"
     * @param  scaledWidth the width of the scaled image (in screen coordinates)
     * @param  scaledHeight the height of the scaled image (in screen coordinates)
     * @throws IllegalArgumentException if either {@code scaledWidth}
     *         or {@code scaledHeight} is negative
     * @throws IllegalArgumentException if the image filename is invalid
     * @throws IllegalArgumentException if {@code x} or {@code y} is either NaN or infinite
     * @throws IllegalArgumentException if {@code filename} is {@code null}
     */
    //static void picture(double x, double y, String filename, double scaledWidth, double scaledHeight);

    /**
     * Draws the specified image centered at (<em>x</em>, <em>y</em>), rotated
     * given number of degrees, and rescaled to the specified bounding box.
     * The supported image formats are typically JPEG, PNG, GIF, TIFF, and BMP.
     *
     * @param  x the center <em>x</em>-coordinate of the image
     * @param  y the center <em>y</em>-coordinate of the image
     * @param  filename the name of the image/picture, e.g., "ball.gif"
     * @param  scaledWidth the width of the scaled image (in screen coordinates)
     * @param  scaledHeight the height of the scaled image (in screen coordinates)
     * @param  degrees is the number of degrees to rotate counterclockwise
     * @throws IllegalArgumentException if either {@code scaledWidth}
     *         or {@code scaledHeight} is negative
     * @throws IllegalArgumentException if the image filename is invalid
     */
    //static void picture(double x, double y, String filename, double scaledWidth, double scaledHeight, double degrees);

   /***************************************************************************
    *  Drawing text.
    ***************************************************************************/

    /**
     * Writes the given text string in the current font, centered at (<em>x</em>, <em>y</em>).
     *
     * @param  x the center <em>x</em>-coordinate of the text
     * @param  y the center <em>y</em>-coordinate of the text
     * @param  text the text to write
     * @throws IllegalArgumentException if {@code text} is {@code null}
     * @throws IllegalArgumentException if {@code x} or {@code y} is either NaN or infinite
     */
    //static void text(double x, double y, String text);

    /**
     * Writes the given text string in the current font, centered at (<em>x</em>, <em>y</em>) and
     * rotated by the specified number of degrees.
     * @param  x the center <em>x</em>-coordinate of the text
     * @param  y the center <em>y</em>-coordinate of the text
     * @param  text the text to write
     * @param  degrees is the number of degrees to rotate counterclockwise
     * @throws IllegalArgumentException if {@code text} is {@code null}
     * @throws IllegalArgumentException if {@code x}, {@code y}, or {@code degrees} is either NaN or infinite
     */
    //static void text(double x, double y, String text, double degrees);

    /**
     * Writes the given text string in the current font, left-aligned at (<em>x</em>, <em>y</em>).
     * @param  x the <em>x</em>-coordinate of the text
     * @param  y the <em>y</em>-coordinate of the text
     * @param  text the text
     * @throws IllegalArgumentException if {@code text} is {@code null}
     * @throws IllegalArgumentException if {@code x} or {@code y} is either NaN or infinite
     */
    //static void textLeft(double x, double y, String text);

    /**
     * Writes the given text string in the current font, right-aligned at (<em>x</em>, <em>y</em>).
     *
     * @param  x the <em>x</em>-coordinate of the text
     * @param  y the <em>y</em>-coordinate of the text
     * @param  text the text to write
     * @throws IllegalArgumentException if {@code text} is {@code null}
     * @throws IllegalArgumentException if {@code x} or {@code y} is either NaN or infinite
     */
    //static void textRight(double x, double y, String text);
    
    /**
     * Pauses for t milliseconds. This method is intended to support computer animations.
     * @param t number of milliseconds
     * @throws IllegalArgumentException if {@code t} is negative
     */
    //static void pause(int t);

    /**
     * Copies offscreen buffer to onscreen buffer. There is no reason to call
     * this method unless double buffering is enabled.
     */
    //static void show();

    // draw onscreen if defer is false
    //static void draw();

    /**
     * Enables double buffering. All subsequent calls to
     * drawing methods such as {@code line()}, {@code circle()},
     * and {@code square()} will be deferred until the next call
     * to show(). Useful for animations.
     */
    //static void enableDoubleBuffering();

    /**
     * Disables double buffering. All subsequent calls to
     * drawing methods such as {@code line()}, {@code circle()},
     * and {@code square()} will be displayed on screen when called.
     * This is the default.
     */
    //static void disableDoubleBuffering();


   /***************************************************************************
    *  Save drawing to a file.
    ***************************************************************************/

    /**
     * Saves the drawing to a file in a supported file format
     * (typically JPEG, PNG, GIF, TIFF, and BMP).
     * The filetype extension must be {@code .jpg}, {@code .png}, {@code .gif},
     * {@code .bmp}, or {@code .tif}.
     *
     * @param  filename the name of the file
     * @throws IllegalArgumentException if {@code filename} is {@code null}
     * @throws IllegalArgumentException if {@code filename} is the empty string
     * @throws IllegalArgumentException if {@code filename} has invalid filetype extension
     * @throws IllegalArgumentException if cannot write the file {@code filename}
     */
    //static void save(String filename);

    /**
     * This method cannot be called directly.
     */
    //void actionPerformed(ActionEvent event);


   /***************************************************************************
    *  Mouse interactions.
    ***************************************************************************/

    /**
     * Returns true if the mouse is being pressed.
     *
     * @return {@code true} if the mouse is being pressed; {@code false} otherwise
     */
    //static bool isMousePressed();

    /**
     * Returns the <em>x</em>-coordinate of the mouse.
     *
     * @return the <em>x</em>-coordinate of the mouse
     */
    //static double mouseX();

    /**
     * Returns the <em>y</em>-coordinate of the mouse.
     *
     * @return <em>y</em>-coordinate of the mouse
     */
    //static double mouseY();

    /**
     * This method cannot be called directly.
     */
    //void mouseClicked(MouseEvent event);

    /**
     * This method cannot be called directly.
     */
    //void mouseEntered(MouseEvent event);

    /**
     * This method cannot be called directly.
     */
    //void mouseExited(MouseEvent event);

    /**
     * This method cannot be called directly.
     */
    //void mousePressed(MouseEvent event);

    /**
     * This method cannot be called directly.
     */
    //void mouseReleased(MouseEvent event);

    /**
     * This method cannot be called directly.
     */
    //void mouseDragged(MouseEvent event);

    /**
     * This method cannot be called directly.
     */
    //void mouseMoved(MouseEvent event);


   /***************************************************************************
    *  Keyboard interactions.
    ***************************************************************************/

    /**
     * Returns true if the user has typed a key (that has not yet been processed).
     *
     * @return {@code true} if the user has typed a key (that has not yet been processed
     *         by {@link #nextKeyTyped()}; {@code false} otherwise
     */
    //static bool hasNextKeyTyped();

    /**
     * Returns the next key that was typed by the user (that your program has not already processed).
     * This method should be preceded by a call to {@link #hasNextKeyTyped()} to ensure
     * that there is a next key to process.
     * This method returns a Unicode character corresponding to the key
     * typed (such as {@code 'a'} or {@code 'A'}).
     * It cannot identify action keys (such as F1 and arrow keys)
     * or modifier keys (such as control).
     *
     * @return the next key typed by the user (that your program has not already processed).
     * @throws NoSuchElementException if there is no remaining key
     */
    //static char nextKeyTyped();

    /**
     * Returns true if the given key is being pressed.
     * <p>
     * This method takes the keycode (corresponding to a physical key)
    *  as an argument. It can handle action keys
     * (such as F1 and arrow keys) and modifier keys (such as shift and control).
     * See {@link KeyEvent} for a description of key codes.
     *
     * @param  keycode the key to check if it is being pressed
     * @return {@code true} if {@code keycode} is currently being pressed;
     *         {@code false} otherwise
     */
    //static bool isKeyPressed(int keycode);

    /**
     * This method cannot be called directly.
     */
    //void keyTyped(KeyEvent event);

    /**
     * This method cannot be called directly.
     */
    //void keyPressed(KeyEvent event);

    /**
     * This method cannot be called directly.
     */
    //void keyReleased(KeyEvent event);


   /***************************************************************************
    *  For improved resolution on Mac Retina displays.
    ***************************************************************************/

    /*private static class RetinaImageIcon extends ImageIcon {

        RetinaImageIcon(Image image) {
            super(image);
        }

        int getIconWidth() {
            return super.getIconWidth() / 2;
        }

        /**
         * Returns the height of the icon.
         *
         * @return the height in pixels of this icon
         */
      /*  int getIconHeight() {
            return super.getIconHeight() / 2;
        }

        synchronized void paintIcon(Component c, Graphics g, int x, int y) {
            Graphics2D g2 = (Graphics2D) g.create();
            g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION,RenderingHints.VALUE_INTERPOLATION_BICUBIC);
            g2.setRenderingHint(RenderingHints.KEY_RENDERING,RenderingHints.VALUE_RENDER_QUALITY);
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);
            g2.scale(0.5, 0.5);
            super.paintIcon(c, g2, x * 2, y * 2);
            g2.dispose();
        }
    }*/
private:
    std::thread m_gfx_thread;
};

/******************************************************************************
 *  Copyright 2002-2022, Robert Sedgewick and Kevin Wayne.
 *
 *  This file is part of algs4.jar, which accompanies the textbook
 *
 *      Algorithms, 4th edition by Robert Sedgewick and Kevin Wayne,
 *      Addison-Wesley Professional, 2011, ISBN 0-321-57351-X.
 *      http://algs4.cs.princeton.edu
 *
 *
 *  algs4.jar is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  algs4.jar is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with algs4.jar.  If not, see http://www.gnu.org/licenses.
 ******************************************************************************/

#endif