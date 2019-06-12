//
// Created by wuday on 29/04/19.
//

#ifndef FIGURES_FIGURES_H
#define FIGURES_FIGURES_H

#include "color.h"

typedef struct Point2D {
    double x; // the x coosdinate of the point
    double y; // the x coosdinate of the point
} Point2D;

typedef struct Polyline {
    double t; // the actual thickness of the atomicFigure
    double r; // the actual resolution of the atomicFigure
    Color c; // the actual color of the atomicFigure
    Color f; // the actual fill color of the atomicFigure
    Point2D *poly; // a vector of Point2D
    int len; // the length of the vector
} Polyline;

typedef struct Text {
    Color f; // the actual fill color of the atomicFigure
    char *text; // the text
    Point2D *center; // the center of the text
} Text;

typedef union AtomicFigure {
    Polyline *p; // a polyline element
    Text *t; // a text element
} AtomicFigure;

typedef enum {
    P, T // P polyline, T text
} AtomicType;

typedef struct AtomicFigureContainer {
    AtomicType type; // P Polyline, T Text
    AtomicFigure *af; // the element
    struct AtomicFigureContainer *next; // the next atomicFigure of the figure
} AtomicFigureContainer;

typedef struct Figure {
    double w; // the width of the canvas
    double h; // the height of the canvas
    double t; // the actual thickness of the atomicFigure
    double r; // the actual resolution of the atomicFigure
    Color c; // the actual color of the atomicFigure
    Color f; // the actual fill color of the atomicFigure
    AtomicFigureContainer *last; // the last atomicFigure in the fiqure
    AtomicFigureContainer *afc; // the atomicFigures in the figure
} Figure;

Figure *start_figure(double width, double height);

void set_thickness_resolution(Figure *fig, double thickness, double resulution);

void set_color(Figure *fig, Color color);

void set_fill(Figure *fig, Color color);

void draw_fx(Figure *fig, double f(double x), double start_x, double end_x);

void draw_polyline(Figure *fig, Point2D *poly_line, int n);

void draw_line(Figure *fig, double ax, double ay, double bx, double by);

void draw_circle(Figure *fig, Point2D *center, double r);

void draw_ellipse(Figure *fig, Point2D *center, double a, double b);

void draw_text(Figure *fig, Point2D *center, char *text);

void scale_figure(Figure *fig, double scale_x, double scale_y);

void resize_figure(Figure *fig, Point2D start_roi, Point2D end_roi);

void append_figures(Figure *fig1, Figure *fig2);

void print_figure(Figure *fig);

void figures_test();

Point2D *create_point2d_vector(int length, ...);

#endif //FIGURES_FIGURES_H
