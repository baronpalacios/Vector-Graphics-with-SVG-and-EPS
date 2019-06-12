# Vector-Graphics-with-SVG-and-EPS
Vector Graphics with SVG and EPS


Two-dimensional (2D) vector graphics is an essential tool for many documenting and computer graphics applications. In this project, you will explore two portable vector graphics file formats EPS and SVG. You will write a C library that can generate vector graphics in EPS and SVG or convert between these two formats. Your library will handle only a subset of functionalities possible with EPS and SVG.
EPS: See https://www-cdf.fnal.gov/offline/PostScript/5002.PDF for a specification of EPS format.
SVG: See https://www.w3schools.com/graphics/svg_intro.asp for an introduction to SVG format.
Description: Your library would be able to draw vector graphics and export EPS or SVG formatted files including your graphics. Your library will have the following functions:
• Figure * start_figure(double width, double height):
Initializes your figure. A figure is initialized on a canvas of a given dimension (width × height). Anything that you draw on the canvas should be within this limit. Note that the coordinate system of your canvas starts from the bottom-left corner. x axis is towards left and y axis is perpendicular in the up direction. See the following figure for an illustration of the canvas geometry.

![Capture](https://user-images.githubusercontent.com/32982938/59383691-1ed70000-8d69-11e9-9eab-2c2188192832.PNG)





void set_thickness_resolution(Figure * fig, double thickness, double resolution):
Sets the thickness and resolution for the drawings to happen next. These will be used by some of the drawing functions below.
• void set_color(Figure * fig, Color c):
Set the color for the drawings to happen next.
• void draw_fx(Figure * fig, double f(double x), double start_x, double end_x):
Draws the given function in the figure initialized by “start_figure”. It will draw the function within the range defined by “start_x” and “end_x”. You should draw the function as a set of connected lines. Any such line should be no smaller in length than the resolution defined in “resolution”. The lines drawing the graph should have the thickness in the given same named argument.
Make sure that the figure fits in the intended position in the canvas. If the portion of the graph is outside the canvas, it should be removed properly. See the explanation for draw_resize_figure.


![Capturesdd](https://user-images.githubusercontent.com/32982938/59383692-1f6f9680-8d69-11e9-934b-cb2b892d80bc.PNG)



void draw_polyline(Point2D * poly_line, int n):
Draws a set of connected lines given in the array poly_line. Each point should be connected from the first point to the last in the given order.
• void draw_circle(Point2D * center, double r):
Draws a circle as a set of connected lines. See the explanation earlier for thickness and resolution.
• void draw_ellipse(…):
Draws an ellipse as a set of connected lines. Define the arguments for this function. See the explanation earlier for thickness and resolution.
• void draw_binary_tree(Tree * root):
Draws the given binary tree in the given canvas. Pick your choice of representation for trees for this function. Assume that the node has only integers between 0 and 999. Your tree should look like the following:

![Caadspture](https://user-images.githubusercontent.com/32982938/59383693-1f6f9680-8d69-11e9-9442-9fa0a0b64eda.PNG)


void scale_figure(double scale_x, double scale_y):
Scales your figure in both dimensions by scale_x and scale_y. You should make sure that the contents of the figure are properly scaled along both dimensions.
• void resize_figure(Point2D start_roi, Point2D end_roi):
Crops (may oversample) the given figure to be within a rectangle defined by start_roi indicating the bottom-left corner and end_roi indicating the top-right corner of the rectangle. Anything out of this range in the original figure should be erased. You should make sure that a line is split into two at the boundary and the piece within the boundary should not be deleted. See figure below for an example.


![Captuadfre](https://user-images.githubusercontent.com/32982938/59383690-1ed70000-8d69-11e9-8f2e-4b259446eb66.PNG)


Note that resizing can be also enlarging the image. For example, if start_roi has negative coordinates and end_roi has larger values than the width and height of the original figure, the new figure will be outside the boundary of the original figure.
• void append_figures(Figure * fig1, Figure * fig2):
Merges two figures and returns it in the first one. Assumes that the items in the second figure will be drawn on the first. The resulting canvas however should include both figures without any cropping.
• void export_eps(Figure * fig, char * file_name):
Exports the current figure to an EPS file.
• void export_svg(Figure * fig, char * file_name):
Exports the current figure to an SVG file.
• void import_svg(char * file_name, Figure * fig):
Imports the given vector graphics from SVG file. You can assume SVG file does not contain any entity not defined in this document.
Fractals: These series of functions will draw fractals as described in http://natureofcode.com/book/chapter-8-fractals/.
• void draw_koch_snowflake(Point2D * center, double thickness, int size, int num_iterations):
Draws the Koch Snowflake for the given parameters. The figure should be centered around center_x and center_y with the given size. Number of iterations indicate the level of iterations in generating the fractal.

![Captadfafdure](https://user-images.githubusercontent.com/32982938/59383689-1ed70000-8d69-11e9-8f2f-8dc122c03624.PNG)



void draw_fractal_tree(double center_x, double center_y, int size, int num_iterations):
Draws a symmetric fractal tree as shown below.

![Capaaadture](https://user-images.githubusercontent.com/32982938/59383686-1e3e6980-8d69-11e9-9c0b-617346e09446.PNG)




void draw_fractal_atree(double center_x, double center_y, int size, int num_iterations):
Draws an asymmetric fractal tree as shown below.

![Capadfature](https://user-images.githubusercontent.com/32982938/59383687-1e3e6980-8d69-11e9-8400-c381b6780283.PNG)

