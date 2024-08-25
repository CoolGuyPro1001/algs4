#include "StdDraw.h"

/*static wxColour* DEFAULT_PEN_COLOR = wxBLACK;
static wxColour* DEFAULT_BACKGROUND_COLOR = wxWHITE;

static wxColour* penColor = DEFAULT_PEN_COLOR;

static wxColour* backgroundColor = DEFAULT_BACKGROUND_COLOR;

static const std::string DEFAULT_WINDOW_TITLE = "Standard Draw";

static std::string windowTitle = DEFAULT_WINDOW_TITLE;

static const int DEFAULT_SIZE = 512;
static int width  = DEFAULT_SIZE;
static int height = DEFAULT_SIZE;

static const double DEFAULT_PEN_RADIUS = 0.002;

static double penRadius = DEFAULT_PEN_RADIUS;

static bool defer = false;

static const double BORDER = 0.00;
static const double DEFAULT_XMIN = 0.0;
static const double DEFAULT_XMAX = 1.0;
static const double DEFAULT_YMIN = 0.0;
static const double DEFAULT_YMAX = 1.0;

static double xmin = DEFAULT_XMIN;
static double xmax = DEFAULT_XMAX;
static double ymin = DEFAULT_YMIN;
static double ymax = DEFAULT_YMAX;*/

//static const Object MOUSE_LOCK = new Object();
//static const Object KEY_LOCK = new Object();

//static const Font DEFAULT_FONT = new Font("SansSerif", Font.PLAIN, 16);
//
//static Font font = DEFAULT_FONT;
//
//static BufferedImage offscreenImage, onscreenImage;
//static Graphics2D offscreen, onscreen;
//
//static StdDraw std = new StdDraw();
//
//static JFrame frame;
//
//static bool isJFrameVisible = true;
//
//static bool isMousePressed = false;
//static double mouseX = 0;
//static double mouseY = 0;
//
//static LinkedList<Character> keysTyped = new LinkedList<Character>();
//
//
//static TreeSet<Integer> keysDown = new TreeSet<Integer>();

StdFrame::StdFrame() : wxFrame(nullptr, wxID_ANY, "Hello World")
{

}

void StdDraw::run()
{
    StdApp* app = new StdApp();
    wxApp::SetInstance(app);
    int argc = 0;
    char* argv[0];
    wxEntryStart(argc, argv);
    app->CallOnInit();
    app->OnRun();
    app->OnExit();
    wxEntryCleanup();
}

StdDraw::StdDraw()
{
    run();
    //m_gfx_thread = std::thread(&StdDraw::run);
}

StdDraw::~StdDraw()
{
    //m_gfx_thread.join();
}

bool StdApp::OnInit()
{
    StdFrame* frame = new StdFrame(); 
    frame->Show();
    return true;
}

/*
void setVisible(bool is_visible)
{
    isJFrameVisible = is_visible;
    frame.setVisible(is_visible);
}

public static void setCanvasSize() {
    setCanvasSize(DEFAULT_SIZE, DEFAULT_SIZE);
}

public static void setCanvasSize(int canvasWidth, int canvasHeight) {
    if (canvasWidth <= 0) throw new IllegalArgumentException("width must be positive");
    if (canvasHeight <= 0) throw new IllegalArgumentException("height must be positive");
    width = canvasWidth;
    height = canvasHeight;
    initCanvas();
    initGUI();
}

private static void initCanvas() {

    // BufferedImage stuff
    offscreenImage = new BufferedImage(2*width, 2*height, BufferedImage.TYPE_INT_ARGB);
    onscreenImage  = new BufferedImage(2*width, 2*height, BufferedImage.TYPE_INT_ARGB);
    offscreen = offscreenImage.createGraphics();
    onscreen  = onscreenImage.createGraphics();
    offscreen.scale(2.0, 2.0);  // since we made it 2x as big

    // initialize drawing window
    offscreen.setBackground(DEFAULT_BACKGROUND_COLOR);
    offscreen.clearRect(0, 0, width, height);
    onscreen.setBackground(DEFAULT_BACKGROUND_COLOR);
    onscreen.clearRect(0, 0, 2*width, 2*height);

    // set the pen color
    offscreen.setColor(DEFAULT_PEN_COLOR);

    // add antialiasing
    RenderingHints hints = new RenderingHints(null);
    hints.put(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
    hints.put(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY);
    offscreen.addRenderingHints(hints);
}

private static void initGUI() {

    // create the JFrame (if necessary)
    if (frame == null) {
        frame = new JFrame();
        frame.addKeyListener(std);    // JLabel cannot get keyboard focus
        frame.setFocusTraversalKeysEnabled(false);  // allow VK_TAB with isKeyPressed()
        frame.setResizable(false);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);            // closes all windows
        // frame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);      // closes only current window
        frame.setTitle(windowTitle);
        frame.setJMenuBar(createMenuBar());
    }

    // create the ImageIcon
    RetinaImageIcon icon = new RetinaImageIcon(onscreenImage);
    JLabel draw = new JLabel(icon);
    draw.addMouseListener(std);
    draw.addMouseMotionListener(std);

    // finsh up the JFrame
    frame.setContentPane(draw);
    frame.pack();
    frame.requestFocusInWindow();
    frame.setVisible(false);
}

private static JMenuBar createMenuBar() {
    JMenuBar menuBar = new JMenuBar();
    JMenu menu = new JMenu("File");
    menuBar.add(menu);
    JMenuItem menuItem1 = new JMenuItem(" Save...   ");
    menuItem1.addActionListener(std);
    // Java 11: use getMenuShortcutKeyMaskEx()
    // Java 8:  use getMenuShortcutKeyMask()
    menuItem1.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S,
                            Toolkit.getDefaultToolkit().getMenuShortcutKeyMaskEx()));
    menu.add(menuItem1);
    return menuBar;
}

public static void close() {
    frame.dispose();
}

/***************************************************************************
*  Input validation helper methods.
***************************************************************************/

/*private static void validate(double x, std::string name) {
    if (Double.isNaN(x)) throw new IllegalArgumentException(name + " is NaN");
    if (Double.isInfinite(x)) throw new IllegalArgumentException(name + " is infinite");
}

private static void validateNonnegative(double x, std::string name) {
    if (x < 0) throw new IllegalArgumentException(name + " negative");
}

private static void validateNotNull(Object x, std::string name) {
    if (x == null) throw new IllegalArgumentException(name + " is null");
}


/***************************************************************************
*  Set the title of standard drawing window.
***************************************************************************/

/*public static void setTitle(std::string title) {
    validateNotNull(title, "title");
    frame.setTitle(title);
    windowTitle = title;
}

/***************************************************************************
*  User and screen coordinate systems.
***************************************************************************/

/*public static void setXscale() {
    setXscale(DEFAULT_XMIN, DEFAULT_XMAX);
}

public static void setYscale() {
    setYscale(DEFAULT_YMIN, DEFAULT_YMAX);
}

public static void setScale() {
    setXscale();
    setYscale();
}

public static void setXscale(double min, double max) {
    validate(min, "min");
    validate(max, "max");
    double size = max - min;
    if (size == 0.0) throw new IllegalArgumentException("the min and max are the same");
    synchronized (MOUSE_LOCK) {
        xmin = min - BORDER * size;
        xmax = max + BORDER * size;
    }
}

public static void setYscale(double min, double max) {
    validate(min, "min");
    validate(max, "max");
    double size = max - min;
    if (size == 0.0) throw new IllegalArgumentException("the min and max are the same");
    synchronized (MOUSE_LOCK) {
        ymin = min - BORDER * size;
        ymax = max + BORDER * size;
    }
}

public static void setScale(double min, double max) {
    validate(min, "min");
    validate(max, "max");
    double size = max - min;
    if (size == 0.0) throw new IllegalArgumentException("the min and max are the same");
    synchronized (MOUSE_LOCK) {
        xmin = min - BORDER * size;
        xmax = max + BORDER * size;
        ymin = min - BORDER * size;
        ymax = max + BORDER * size;
    }
}

private static double  scaleX(double x) { return width  * (x - xmin) / (xmax - xmin); }
private static double  scaleY(double y) { return height * (ymax - y) / (ymax - ymin); }
private static double factorX(double w) { return w * width  / Math.abs(xmax - xmin);  }
private static double factorY(double h) { return h * height / Math.abs(ymax - ymin);  }
private static double   userX(double x) { return xmin + x * (xmax - xmin) / width;    }
private static double   userY(double y) { return ymax - y * (ymax - ymin) / height;   }

public static void clear() {
    clear(DEFAULT_BACKGROUND_COLOR);
}

public static void clear(wxColour color) {
    validateNotNull(color, "color");

    backgroundColor = color;

    offscreen.setBackground(backgroundColor);
    offscreen.clearRect(0, 0, width, height);

    draw();
}

public static double getPenRadius() {
    return penRadius;
}

public static void setPenRadius() {
    setPenRadius(DEFAULT_PEN_RADIUS);
}

public static void setPenRadius(double radius) {
    validate(radius, "pen radius");
    validateNonnegative(radius, "pen radius");

    penRadius = radius;
    float scaledPenRadius = (float) (radius * DEFAULT_SIZE);
    BasicStroke stroke = new BasicStroke(scaledPenRadius, BasicStroke.CAP_ROUND, BasicStroke.JOIN_ROUND);
    // BasicStroke stroke = new BasicStroke(scaledPenRadius);
    offscreen.setStroke(stroke);
}

public static wxColour getPenColor() {
    return penColor;
}

public static wxColour getBackgroundColor() {
    return backgroundColor;
}

public static void setPenColor() {
    setPenColor(DEFAULT_PEN_COLOR);
}

public static void setPenColor(wxColour color) {
    validateNotNull(color, "color");
    penColor = color;
    offscreen.setColor(penColor);
}

public static void setPenColor(int red, int green, int blue) {
    if (red   < 0 || red   >= 256) throw new IllegalArgumentException("red must be between 0 and 255");
    if (green < 0 || green >= 256) throw new IllegalArgumentException("green must be between 0 and 255");
    if (blue  < 0 || blue  >= 256) throw new IllegalArgumentException("blue must be between 0 and 255");
    setPenColor(new Color(red, green, blue));
}

public static Font getFont() {
    return font;
}

public static void setFont() {
    setFont(DEFAULT_FONT);
}

public static void setFont(Font font) {
    validateNotNull(font, "font");
    StdDraw.font = font;
}


/***************************************************************************
*  Drawing geometric shapes.
***************************************************************************/

/*public static void line(double x0, double y0, double x1, double y1) {
    validate(x0, "x0");
    validate(y0, "y0");
    validate(x1, "x1");
    validate(y1, "y1");
    offscreen.draw(new Line2D.Double(scaleX(x0), scaleY(y0), scaleX(x1), scaleY(y1)));
    draw();
}

private static void pixel(double x, double y) {
    validate(x, "x");
    validate(y, "y");
    offscreen.fillRect((int) Math.round(scaleX(x)), (int) Math.round(scaleY(y)), 1, 1);
}

public static void point(double x, double y) {
    validate(x, "x");
    validate(y, "y");

    double xs = scaleX(x);
    double ys = scaleY(y);
    double r = penRadius;
    float scaledPenRadius = (float) (r * DEFAULT_SIZE);

    // double ws = factorX(2*r);
    // double hs = factorY(2*r);
    // if (ws <= 1 && hs <= 1) pixel(x, y);
    if (scaledPenRadius <= 1) pixel(x, y);
    else offscreen.fill(new Ellipse2D.Double(xs - scaledPenRadius/2, ys - scaledPenRadius/2,
                                                scaledPenRadius, scaledPenRadius));
    draw();
}

public static void circle(double x, double y, double radius) {
    validate(x, "x");
    validate(y, "y");
    validate(radius, "radius");
    validateNonnegative(radius, "radius");

    double xs = scaleX(x);
    double ys = scaleY(y);
    double ws = factorX(2*radius);
    double hs = factorY(2*radius);
    if (ws <= 1 && hs <= 1) pixel(x, y);
    else offscreen.draw(new Ellipse2D.Double(xs - ws/2, ys - hs/2, ws, hs));
    draw();
}

public static void filledCircle(double x, double y, double radius) {
    validate(x, "x");
    validate(y, "y");
    validate(radius, "radius");
    validateNonnegative(radius, "radius");

    double xs = scaleX(x);
    double ys = scaleY(y);
    double ws = factorX(2*radius);
    double hs = factorY(2*radius);
    if (ws <= 1 && hs <= 1) pixel(x, y);
    else offscreen.fill(new Ellipse2D.Double(xs - ws/2, ys - hs/2, ws, hs));
    draw();
}

public static void ellipse(double x, double y, double semiMajorAxis, double semiMinorAxis) {
    validate(x, "x");
    validate(y, "y");
    validate(semiMajorAxis, "semimajor axis");
    validate(semiMinorAxis, "semiminor axis");
    validateNonnegative(semiMajorAxis, "semimajor axis");
    validateNonnegative(semiMinorAxis, "semiminor axis");

    double xs = scaleX(x);
    double ys = scaleY(y);
    double ws = factorX(2*semiMajorAxis);
    double hs = factorY(2*semiMinorAxis);
    if (ws <= 1 && hs <= 1) pixel(x, y);
    else offscreen.draw(new Ellipse2D.Double(xs - ws/2, ys - hs/2, ws, hs));
    draw();
}

public static void filledEllipse(double x, double y, double semiMajorAxis, double semiMinorAxis) {
    validate(x, "x");
    validate(y, "y");
    validate(semiMajorAxis, "semimajor axis");
    validate(semiMinorAxis, "semiminor axis");
    validateNonnegative(semiMajorAxis, "semimajor axis");
    validateNonnegative(semiMinorAxis, "semiminor axis");

    double xs = scaleX(x);
    double ys = scaleY(y);
    double ws = factorX(2*semiMajorAxis);
    double hs = factorY(2*semiMinorAxis);
    if (ws <= 1 && hs <= 1) pixel(x, y);
    else offscreen.fill(new Ellipse2D.Double(xs - ws/2, ys - hs/2, ws, hs));
    draw();
}

public static void arc(double x, double y, double radius, double angle1, double angle2) {
    validate(x, "x");
    validate(y, "y");
    validate(radius, "arc radius");
    validate(angle1, "angle1");
    validate(angle2, "angle2");
    validateNonnegative(radius, "arc radius");

    while (angle2 < angle1) angle2 += 360;
    double xs = scaleX(x);
    double ys = scaleY(y);
    double ws = factorX(2*radius);
    double hs = factorY(2*radius);
    if (ws <= 1 && hs <= 1) pixel(x, y);
    else offscreen.draw(new Arc2D.Double(xs - ws/2, ys - hs/2, ws, hs, angle1, angle2 - angle1, Arc2D.OPEN));
    draw();
}

public static void square(double x, double y, double halfLength) {
    validate(x, "x");
    validate(y, "y");
    validate(halfLength, "halfLength");
    validateNonnegative(halfLength, "half length");

    double xs = scaleX(x);
    double ys = scaleY(y);
    double ws = factorX(2*halfLength);
    double hs = factorY(2*halfLength);
    if (ws <= 1 && hs <= 1) pixel(x, y);
    else offscreen.draw(new Rectangle2D.Double(xs - ws/2, ys - hs/2, ws, hs));
    draw();
}

public static void filledSquare(double x, double y, double halfLength) {
    validate(x, "x");
    validate(y, "y");
    validate(halfLength, "halfLength");
    validateNonnegative(halfLength, "half length");

    double xs = scaleX(x);
    double ys = scaleY(y);
    double ws = factorX(2*halfLength);
    double hs = factorY(2*halfLength);
    if (ws <= 1 && hs <= 1) pixel(x, y);
    else offscreen.fill(new Rectangle2D.Double(xs - ws/2, ys - hs/2, ws, hs));
    draw();
}

public static void rectangle(double x, double y, double halfWidth, double halfHeight) {
    validate(x, "x");
    validate(y, "y");
    validate(halfWidth, "halfWidth");
    validate(halfHeight, "halfHeight");
    validateNonnegative(halfWidth, "half width");
    validateNonnegative(halfHeight, "half height");

    double xs = scaleX(x);
    double ys = scaleY(y);
    double ws = factorX(2*halfWidth);
    double hs = factorY(2*halfHeight);
    if (ws <= 1 && hs <= 1) pixel(x, y);
    else offscreen.draw(new Rectangle2D.Double(xs - ws/2, ys - hs/2, ws, hs));
    draw();
}

public static void filledRectangle(double x, double y, double halfWidth, double halfHeight) {
    validate(x, "x");
    validate(y, "y");
    validate(halfWidth, "halfWidth");
    validate(halfHeight, "halfHeight");
    validateNonnegative(halfWidth, "half width");
    validateNonnegative(halfHeight, "half height");

    double xs = scaleX(x);
    double ys = scaleY(y);
    double ws = factorX(2*halfWidth);
    double hs = factorY(2*halfHeight);
    if (ws <= 1 && hs <= 1) pixel(x, y);
    else offscreen.fill(new Rectangle2D.Double(xs - ws/2, ys - hs/2, ws, hs));
    draw();
}


public static void polygon(double[] x, double[] y) {
    validateNotNull(x, "x-coordinate array");
    validateNotNull(y, "y-coordinate array");
    for (int i = 0; i < x.length; i++) validate(x[i], "x[" + i + "]");
    for (int i = 0; i < y.length; i++) validate(y[i], "y[" + i + "]");

    int n1 = x.length;
    int n2 = y.length;
    if (n1 != n2) throw new IllegalArgumentException("arrays must be of the same length");
    int n = n1;
    if (n == 0) return;

    GeneralPath path = new GeneralPath();
    path.moveTo((float) scaleX(x[0]), (float) scaleY(y[0]));
    for (int i = 0; i < n; i++)
        path.lineTo((float) scaleX(x[i]), (float) scaleY(y[i]));
    path.closePath();
    offscreen.draw(path);
    draw();
}

public static void filledPolygon(double[] x, double[] y) {
    validateNotNull(x, "x-coordinate array");
    validateNotNull(y, "y-coordinate array");
    for (int i = 0; i < x.length; i++) validate(x[i], "x[" + i + "]");
    for (int i = 0; i < y.length; i++) validate(y[i], "y[" + i + "]");

    int n1 = x.length;
    int n2 = y.length;
    if (n1 != n2) throw new IllegalArgumentException("arrays must be of the same length");
    int n = n1;
    if (n == 0) return;

    GeneralPath path = new GeneralPath();
    path.moveTo((float) scaleX(x[0]), (float) scaleY(y[0]));
    for (int i = 0; i < n; i++)
        path.lineTo((float) scaleX(x[i]), (float) scaleY(y[i]));
    path.closePath();
    offscreen.fill(path);
    draw();
}


/***************************************************************************
*  Drawing images.
***************************************************************************/

/*private static Image getImage(std::string filename) {
    if (filename == null) throw new IllegalArgumentException();

    // to read from file
    ImageIcon icon = new ImageIcon(filename);

    // try to read from URL
    if (icon.getImageLoadStatus() != MediaTracker.COMPLETE) {
        try {
            URI uri = new URI(filename);
            if (uri.isAbsolute()) {
                URL url = uri.toURL();
                icon = new ImageIcon(url);
            }
        }
        catch (MalformedURLException | URISyntaxException e) {
            /* not a url */
    //    }
    //}

    /*// in case file is inside a .jar (classpath relative to StdDraw)
    if (icon.getImageLoadStatus() != MediaTracker.COMPLETE) {
        URL url = StdDraw.class.getResource(filename);
        if (url != null)
            icon = new ImageIcon(url);
    }

    // in case file is inside a .jar (classpath relative to root of jar)
    if (icon.getImageLoadStatus() != MediaTracker.COMPLETE) {
        URL url = StdDraw.class.getResource("/" + filename);
        if (url == null) throw new IllegalArgumentException("could not read image: '" + filename + "'");
        icon = new ImageIcon(url);
    }

    return icon.getImage();
}

public static void picture(double x, double y, std::string filename) {
    validate(x, "x");
    validate(y, "y");
    validateNotNull(filename, "filename");

    // BufferedImage image = getImage(filename);
    Image image = getImage(filename);
    double xs = scaleX(x);
    double ys = scaleY(y);
    // int ws = image.getWidth();    // can call only if image is a BufferedImage
    // int hs = image.getHeight();
    int ws = image.getWidth(null);
    int hs = image.getHeight(null);
    if (ws < 0 || hs < 0) throw new IllegalArgumentException("image " + filename + " is corrupt");

    offscreen.drawImage(image, (int) Math.round(xs - ws/2.0), (int) Math.round(ys - hs/2.0), null);
    draw();
}

public static void picture(double x, double y, std::string filename, double degrees) {
    validate(x, "x");
    validate(y, "y");
    validate(degrees, "degrees");
    validateNotNull(filename, "filename");

    // BufferedImage image = getImage(filename);
    Image image = getImage(filename);
    double xs = scaleX(x);
    double ys = scaleY(y);
    // int ws = image.getWidth();    // can call only if image is a BufferedImage
    // int hs = image.getHeight();
    int ws = image.getWidth(null);
    int hs = image.getHeight(null);
    if (ws < 0 || hs < 0) throw new IllegalArgumentException("image " + filename + " is corrupt");

    offscreen.rotate(Math.toRadians(-degrees), xs, ys);
    offscreen.drawImage(image, (int) Math.round(xs - ws/2.0), (int) Math.round(ys - hs/2.0), null);
    offscreen.rotate(Math.toRadians(+degrees), xs, ys);

    draw();
}

public static void picture(double x, double y, std::string filename, double scaledWidth, double scaledHeight) {
    validate(x, "x");
    validate(y, "y");
    validate(scaledWidth, "scaled width");
    validate(scaledHeight, "scaled height");
    validateNotNull(filename, "filename");
    validateNonnegative(scaledWidth, "scaled width");
    validateNonnegative(scaledHeight, "scaled height");

    Image image = getImage(filename);
    double xs = scaleX(x);
    double ys = scaleY(y);
    double ws = factorX(scaledWidth);
    double hs = factorY(scaledHeight);
    if (ws < 0 || hs < 0) throw new IllegalArgumentException("image " + filename + " is corrupt");
    if (ws <= 1 && hs <= 1) pixel(x, y);
    else {
        offscreen.drawImage(image, (int) Math.round(xs - ws/2.0),
                                    (int) Math.round(ys - hs/2.0),
                                    (int) Math.round(ws),
                                    (int) Math.round(hs), null);
    }
    draw();
}


public static void picture(double x, double y, std::string filename, double scaledWidth, double scaledHeight, double degrees) {
    validate(x, "x");
    validate(y, "y");
    validate(scaledWidth, "scaled width");
    validate(scaledHeight, "scaled height");
    validate(degrees, "degrees");
    validateNotNull(filename, "filename");
    validateNonnegative(scaledWidth, "scaled width");
    validateNonnegative(scaledHeight, "scaled height");

    Image image = getImage(filename);
    double xs = scaleX(x);
    double ys = scaleY(y);
    double ws = factorX(scaledWidth);
    double hs = factorY(scaledHeight);
    if (ws < 0 || hs < 0) throw new IllegalArgumentException("image " + filename + " is corrupt");
    if (ws <= 1 && hs <= 1) pixel(x, y);

    offscreen.rotate(Math.toRadians(-degrees), xs, ys);
    offscreen.drawImage(image, (int) Math.round(xs - ws/2.0),
                                (int) Math.round(ys - hs/2.0),
                                (int) Math.round(ws),
                                (int) Math.round(hs), null);
    offscreen.rotate(Math.toRadians(+degrees), xs, ys);

    draw();
}

/***************************************************************************
*  Drawing text.
***************************************************************************/

/*public static void text(double x, double y, std::string text) {
    validate(x, "x");
    validate(y, "y");
    validateNotNull(text, "text");

    offscreen.setFont(font);
    FontMetrics metrics = offscreen.getFontMetrics();
    double xs = scaleX(x);
    double ys = scaleY(y);
    int ws = metrics.stringWidth(text);
    int hs = metrics.getDescent();
    offscreen.drawstd::string(text, (float) (xs - ws/2.0), (float) (ys + hs));
    draw();
}

public static void text(double x, double y, std::string text, double degrees) {
    validate(x, "x");
    validate(y, "y");
    validate(degrees, "degrees");
    validateNotNull(text, "text");

    double xs = scaleX(x);
    double ys = scaleY(y);
    offscreen.rotate(Math.toRadians(-degrees), xs, ys);
    text(x, y, text);
    offscreen.rotate(Math.toRadians(+degrees), xs, ys);
}


public static void textLeft(double x, double y, std::string text) {
    validate(x, "x");
    validate(y, "y");
    validateNotNull(text, "text");

    offscreen.setFont(font);
    FontMetrics metrics = offscreen.getFontMetrics();
    double xs = scaleX(x);
    double ys = scaleY(y);
    int hs = metrics.getDescent();
    offscreen.drawstd::string(text, (float) xs, (float) (ys + hs));
    draw();
}

public static void textRight(double x, double y, std::string text) {
    validate(x, "x");
    validate(y, "y");
    validateNotNull(text, "text");

    offscreen.setFont(font);
    FontMetrics metrics = offscreen.getFontMetrics();
    double xs = scaleX(x);
    double ys = scaleY(y);
    int ws = metrics.stringWidth(text);
    int hs = metrics.getDescent();
    offscreen.drawString(text, (float) (xs - ws), (float) (ys + hs));
    draw();
}

public static void pause(int t) {
    validateNonnegative(t, "t");
    try {
        Thread.sleep(t);
    }
    catch (InterruptedException e) {
        System.out.println("Error sleeping");
    }
}

public static void show() {
    onscreen.setBackground(backgroundColor);
    onscreen.clearRect(0, 0, 2*width, 2*height);
    onscreen.drawImage(offscreenImage, 0, 0, null);

    // make frame visible upon first call to show()
    if (frame.isVisible() != isJFrameVisible) {
        frame.setVisible(isJFrameVisible);
    }

    frame.repaint();
}

private static void draw() {
    if (!defer) show();
}

public static void enableDoubleBuffering() {
    defer = true;
}

public static void disableDoubleBuffering() {
    defer = false;
}


/***************************************************************************
*  Save drawing to a file.
***************************************************************************/

/*public static void save(std::string filename) {
    validateNotNull(filename, "filename");
    if (filename.length() == 0) {
        throw new IllegalArgumentException("argument to save() is the empty string");
    }

    File file = new File(filename);
}

@Override
public void mouseReleased(MouseEvent event) {
    synchronized (MOUSE_LOCK) {
        isMousePressed = false;
    }
}

@Override
public void mouseDragged(MouseEvent event)  {
    synchronized (MOUSE_LOCK) {
        mouseX = StdDraw.userX(event.getX());
        mouseY = StdDraw.userY(event.getY());
    }
}

@Override
public void mouseMoved(MouseEvent event) {
    synchronized (MOUSE_LOCK) {
        mouseX = StdDraw.userX(event.getX());
        mouseY = StdDraw.userY(event.getY());
    }
}


/***************************************************************************
*  Keyboard interactions.
***************************************************************************/

/*public static bool hasNextKeyTyped() {
    synchronized (KEY_LOCK) {
        return !keysTyped.isEmpty();
    }
}

public static char nextKeyTyped() {
    synchronized (KEY_LOCK) {
        if (keysTyped.isEmpty()) {
            throw new NoSuchElementException("your program has already processed all keystrokes");
        }
        return keysTyped.remove(keysTyped.size() - 1);
        // return keysTyped.removeLast();
    }
}

public static bool isKeyPressed(int keycode) {
    synchronized (KEY_LOCK) {
        return keysDown.contains(keycode);
    }
}


@Override
public void keyTyped(KeyEvent event) {
    synchronized (KEY_LOCK) {
        keysTyped.addFirst(event.getKeyChar());
    }
}

@Override
public void keyPressed(KeyEvent event) {
    synchronized (KEY_LOCK) {
        keysDown.add(event.getKeyCode());
    }
}

@Override
public void keyReleased(KeyEvent event) {
    synchronized (KEY_LOCK) {
        keysDown.remove(event.getKeyCode());
    }
}


/***************************************************************************
*  For improved resolution on Mac Retina displays.
***************************************************************************/

/*private static class RetinaImageIcon extends ImageIcon {

    public RetinaImageIcon(Image image) {
        super(image);
    }

    public int getIconWidth() {
        return super.getIconWidth() / 2;
    }

    public int getIconHeight() {
        return super.getIconHeight() / 2;
    }

    public synchronized void paintIcon(Component c, Graphics g, int x, int y) {
        Graphics2D g2 = (Graphics2D) g.create();
        g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION,RenderingHints.VALUE_INTERPOLATION_BICUBIC);
        g2.setRenderingHint(RenderingHints.KEY_RENDERING,RenderingHints.VALUE_RENDER_QUALITY);
        g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON);
        g2.scale(0.5, 0.5);
        super.paintIcon(c, g2, x * 2, y * 2);
        g2.dispose();
    }
}*/