//
// Created by wuday on 07/05/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "figures.h"
#include "svg.h"

#define pow2(n) (1 << (n))
#define PI 3.14159265358979323846

/// generate_koch_spike generates a spike in a koch curve line
/// \param a the start point of the line
/// \param b the end point of the line
/// \param c the point at (a+b) /3
/// \param d the point outside the line
/// \param e the point at 2*(a+b)/
void generate_koch_spike(Point2D *a, Point2D *b, Point2D *c, Point2D *d,
                         Point2D *e) {
  double ax = a->x;
  double ay = a->y;
  double bx = b->x;
  double by = b->y;
  c->x = ax + (bx - ax) / 3;
  c->y = ay + (by - ay) / 3;
  d->x = (bx + ax) / 2 + sqrt(3) / 6 * (by - ay);
  d->y = (by + ay) / 2 - sqrt(3) / 6 * (bx - ax);
  e->x = ax + 2 * (bx - ax) / 3;
  e->y = ay + 2 * (by - ay) / 3;
}

/// draw_koch_line draws a koch curve line
/// see https://en.wikipedia.org/wiki/Koch_snowflake
/// \param fig the figure
/// \param a the start point of the curve
/// \param b the end point of the curve
/// \param n the number of iterations
void draw_koch_line(Figure *fig, Point2D *a, Point2D *b, int n) {
  if (n > 0) {
    Point2D *c = malloc(sizeof(Point2D));
    Point2D *d = malloc(sizeof(Point2D));
    Point2D *e = malloc(sizeof(Point2D));
    generate_koch_spike(a, b, c, d, e);
    draw_koch_line(fig, a, c, n - 1);
    draw_koch_line(fig, c, d, n - 1);
    draw_koch_line(fig, d, e, n - 1);
    draw_koch_line(fig, e, b, n - 1);
  } else {
    draw_line(fig, a->x, a->y, b->x, b->y);
  }
}

/// draw_koch_snowflake draws the koch snowflake
/// see https://en.wikipedia.org/wiki/Koch_snowflake
/// \param fig fig the figure
/// \param center the center of the koch snowflake
/// \param thickness the line thickness
/// \param r the circle containing the equilateral base triangle
/// \param n the number of iterations
void draw_koch_snowflake(Figure *fig, Point2D *center, double thickness,
                         int r, int n) {
  fig->t = thickness;
  Point2D *a = malloc(sizeof(Point2D));
  a->x = center->x - (double) r / 2;
  a->y = center->y + sqrt(3) * r / 2;
  Point2D *b = malloc(sizeof(Point2D));
  b->x = center->x + r;
  b->y = center->y;
  Point2D *c = malloc(sizeof(Point2D));
  c->x = center->x - (double) r / 2;
  c->y = center->y - sqrt(3) * r / 2;
  draw_koch_line(fig, a, c, n);
  draw_koch_line(fig, c, b, n);
  draw_koch_line(fig, b, a, n);
}

/// draw_koch_anti_snowflake draws the koch snowflake
/// here, the spikes are inside the triangle
/// see https://en.wikipedia.org/wiki/Koch_snowflake
/// \param fig fig the figure
/// \param center the center of the koch snowflake
/// \param thickness the line thickness
/// \param r the circle containing the equilateral base triangle
/// \param n the number of iterations
void draw_koch_anti_snowflake(Figure *fig, Point2D *center, double thickness,
                         int r, int n) {
  fig->t = thickness;
  double cx = center->x;
  Point2D *a = malloc(sizeof(Point2D));
  a->x = center->x - (double) r / 2;
  a->y = center->y + sqrt(3) * r / 2;
  Point2D *b = malloc(sizeof(Point2D));
  b->x = center->x + r;
  b->y = center->y;
  Point2D *c = malloc(sizeof(Point2D));
  c->x = center->x - (double) r / 2;
  c->y = center->y - sqrt(3) * r / 2;
  draw_koch_line(fig, a, b, n);
  draw_koch_line(fig, b, c, n);
  draw_koch_line(fig, c, a, n);
}

/// fractal_tree implementation of the algorithm
/// \param f the figure
/// \param x the x coordinate of the starting point
/// \param y the y coordinate of the starting point
/// \param dir the direction of the trunk (angle)
/// \param angle the angle of the branches
/// \param size the thickness of the trunk
/// \param n the number of iterations
void fractal_tree(Figure *f, double x, double y, double dir, double angle,
                  double size, int n) {
  set_thickness_resolution(f, size * 0.1, 1);
  draw_line(f, x, y, x + size * cos(dir), y + size * sin(dir));
  if (n == 0) {
    return;
  } else {
    fractal_tree(f, x + size * cos(dir), y + size * sin(dir), dir - angle,
                 angle,
                 size / 1.5, n - 1);
    fractal_tree(f, x + size * cos(dir), y + size * sin(dir), dir + angle,
                 angle,
                 size / 1.5, n - 1);
  }
}

/// draw_f fractal_tree draws a fractal tree
/// algorithm from https://rosettacode.org/wiki/Fractal_tree
/// \param f the figure
/// \param center_x the x coordinate of the starting point
/// \param center_y the y coordinate of the starting point
/// \param size the thickness of the trunk
/// \param n the number of iterations
void draw_fractal_tree(Figure *f, double center_x, double center_y, double size,
                       int n) {
  fractal_tree(f, center_x, center_y, PI / 2, PI / 8, size, n);
}

/// asymmetric_fractal_tree implementation of the algorithm
/// similar to fractal trees, here the angles and the lengths of the branches
/// can vary independently
/// \param f the figure
/// \param x the x coordinate of the starting point
/// \param y the y coordinate of the starting point
/// \param dir the direction of the trunk (angle)
/// \param angle the angle of the branches
/// \param size the thickness of the trunk
/// \param n the number of iterations
void asymmetric_fractal_tree(Figure *f, double x, double y, double dir,
                             double angle1, double angle2, double size,
                             int n) {
  set_thickness_resolution(f, size * 0.1, 1);
  draw_line(f, x, y, x + size * cos(dir), y + size * sin(dir));
  if (n == 0) {
    return;
  } else {
    asymmetric_fractal_tree(f, x + size * cos(dir), y + size * sin(dir),
                            dir - angle1, angle1, angle2,
                            size * 0.40, n - 1);
    asymmetric_fractal_tree(f, x + size * cos(dir), y + size * sin(dir),
                            dir + angle2, angle1, angle2,
                            size * 0.60, n - 1);
  }
}

/// draw_f fractal_atree draws an asymmetric fractal tree
/// algorithm from https://rosettacode.org/wiki/Fractal_tree
/// \param f the figure
/// \param center_x the x coordinate of the starting point
/// \param center_y the y coordinate of the starting point
/// \param size the thickness of the trunk
/// \param n the number of iterations
void draw_fractal_atree(Figure *f, double center_x, double center_y,
                        double size, int n) {
  asymmetric_fractal_tree(f, center_x, center_y, PI / 2, PI / 8, PI / 4, size,
    n);
}


