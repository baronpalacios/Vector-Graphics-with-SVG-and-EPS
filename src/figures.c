//
// Created by wuday on 29/04/19.
//

#include "figures.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include "svg.h"
#include "eps.h"

#ifndef max
#define max(a, b) ( ((a) > (b)) ? (a) : (b) ) /// maximum of numerical values
#endif

// #define _USE_MATH_DEFINES

#define INSIDE 0u /// code for the clipping function
#define LEFT 1u /// code for the clipping function
#define RIGHT 2u /// code for the clipping function
#define BOTTOM 4u /// code for the clipping function
#define TOP 8u /// code for the clipping function
#define FALSE 0 /// the boolean constant false
#define TRUE !FALSE /// the boolean constant true
#define boolean int /// type boolean is int

/// start_figure creates an empty figure
/// \param width the width of the figure
/// \param height the height of the figure
/// \return the figure
Figure *start_figure(double width, double height) {
  Figure *f;
  f = (Figure *) malloc(sizeof(Figure));
  f->w = width;
  f->h = height;
  f->t = 1.00; // default value 1.00
  f->r = 0.05; // default value 0.05
  f->c = 0x000000; // default color black
  f->f = NONE;
  f->last = NULL;
  f->afc = NULL;
  return f;
}

/// set_thickness_resolution sets the actual thickness and resolution of the
/// figure. these values will be copied into an atomic figure at drawing,
/// allowing different atomic figures with different values
/// must be called before drawing to be effective
/// \param f the figure
/// \param t the thickness
/// \param r the resolution
void set_thickness_resolution(Figure *f, double t, double r) {
  f->t = t;
  f->r = r;
}

/// set_color change the color of the figure
/// must be called before drawing to be effective
/// \param f the figure
/// \param c the color
void set_color(Figure *f, Color c) {
  f->c = c;
}

/// set_fill sets the actual fill value of the figure. this valuee will be
/// copied into an atomic figure at drawing, allowing different atomic figures
/// with different fill parameters
/// \param f the figure
/// \param c the fill color
void set_fill(Figure *f, Color c) {
  f->f = c;
}

/// create_point2d_vector cteates a Point2D vector
/// \param length the length of the Point2D vector
/// \param ... the x and y coordinates of the vector
/// \return the figure
Point2D * create_point2d_vector (int length, ...) {
  va_list vl;
  int i;
  Point2D * points = (Point2D *) malloc(sizeof(Point2D)*length);
  Point2D * pptr = points;
  va_start(vl, length);
  for (i = 0; i < length; i++) {
    pptr->x = va_arg(vl, double);
    pptr->y = va_arg(vl, double);
    pptr++;
  }
  va_end(vl);
  return points;
}


/// create_polyline creates a polyline atomic picture
/// \param points The points of the polyline
/// \param length the length of the polyline
/// \param t the thickness of the polyline
/// \param r the resolution of the polyline
/// \param c the color of the polyline
/// \param f the fill color of the polylime
/// \return the polyline
Polyline *create_polyline(Point2D *points, int length, double t, double r,
                          Color c, Color f) {
  Polyline *p = (Polyline *) malloc(sizeof(Polyline));
  p->poly = points;
  p->len = length;
  p->t = t;
  p->r = r;
  p->c = c;
  p->f = f;
  return p;
}

/// create_polyline_af creates a polyline atomic figure
/// \param poly the polyline
/// \return the atomic figure
AtomicFigure *create_polyline_af(Polyline *poly) {
  union AtomicFigure *af = (AtomicFigure *) malloc(sizeof(union AtomicFigure));
  af->p = poly;
  return af;
}

/// create_empty_afc creates an empty atomic figure container
/// \return the container
AtomicFigureContainer *create_empty_afc() {
  AtomicFigureContainer *afc = (AtomicFigureContainer *) malloc(
    sizeof(struct AtomicFigureContainer));
  return afc;
}

/// create_polyline_afc creates an atomic figure container containing a
/// polyline
/// \param points The points of the polyline
/// \param length the length of the polyline
/// \param t the thickness of the polyline
/// \param r the resolution of the polyline
/// \param c the color of the polyline
/// \param f the fill color of the polylime
AtomicFigureContainer *create_polyline_afc(Point2D *points, int length,
                                           double t, double r, Color c,
                                           Color f) {
  Polyline *po = create_polyline(points, length, t, r, c, f);
  AtomicFigureContainer *afc = (AtomicFigureContainer *) malloc(
    sizeof(struct AtomicFigureContainer));
  afc->type = P;
  afc->af = create_polyline_af(po);
  afc->next = NULL;
  return afc;
}

/// create_text creates a text atomic figure
/// \param text the text
/// \param center the position of the text
/// \param f the color of the fonts
/// \return the atomic text
Text *create_text(char *text, Point2D *center, Color f) {
  Text *te = (Text *) malloc(sizeof(Text));
  char * t = malloc(sizeof(char) * (strlen(text)+1));
  strcpy(t, text);
  te->text = t;
  te->center = center;
  te->f = f;
  return te;
}

/// create_text_af creates a text atomic figure
/// \param text the text
/// \return the atomic figure
AtomicFigure *create_text_af(Text *text) {
  union AtomicFigure *af = (AtomicFigure *) malloc(sizeof(union AtomicFigure));
  af->t = text;
  return af;
}

/// create_Text_afc creates an atomic figure container containing a text
/// \param text the text
/// \param center the position of the text
/// \param f the color of the fonts
/// \return the container
AtomicFigureContainer *create_Text_afc(char *text, Point2D *center, Color f) {
  Text *te = create_text(text, center, f);
  AtomicFigureContainer *afc = (AtomicFigureContainer *) malloc(
    sizeof(struct AtomicFigureContainer));
  afc->type = T;
  afc->af = create_text_af(te);
  afc->next = NULL;
  return afc;
}

/// add_atomic_figure adds an atomic figure container to a figure
/// \param f the figure
/// \param afc the atomic figure container
void add_atomic_figure(Figure *f, AtomicFigureContainer *afc) {
  if (f->afc == NULL) {
    f->afc = afc;
    f->afc->next = NULL;
    f->last = afc;
  } else {
    f->last->next = afc;
    f->last = f->last->next;
    f->last->next = NULL;
  }
}

/// draw_fx draws the graph of the real valued function f(x) in the range
/// [start_x,end_x]
/// does not work for library function. to draw the library function sin(x)
/// we ned to define the function f(x) as
/// double f(double x) { return sin(x); }
/// function graphs are always clipped to the canevas size
/// draw f(x)
/// \param fig the figure
/// \param f the function
/// \param start_x of the range
/// \param end_x the end of the range
void draw_fx(Figure *fig, double f(double), double start_x, double end_x) {
  // create polyline
  int steps = 4 * (int) floor((end_x - start_x) / fig->r);
  Point2D *points = (Point2D *) malloc(sizeof(Point2D) * (steps + 1));
  Point2D *pptr = points;
  double x = start_x;
  double y;
  for (int i = 0; i < steps; i++) {
    y = f(x);
    pptr->x = x;
    pptr->y = y;
    x += fig->r / 4;
    pptr++;
  }
  pptr->x = end_x;
  pptr->y = f(end_x);
  AtomicFigureContainer *afc = create_polyline_afc(points, steps + 1, fig->t,
                                                   fig->r, fig->c, fig->f);
  add_atomic_figure(fig, afc);
  Point2D bl;
  Point2D tr;
  bl.x = -fig->w / 2;
  bl.y = -fig->h / 2;
  tr.x = fig->w / 2;
  tr.y = fig->h / 2;
  resize_figure(fig, bl, tr);
}

/// draw_polyline draws the polyline points of length n
/// \param fig the figure
/// \param points the points of the polyline
/// \param n the number of points of the polyline
void draw_polyline(Figure *fig, Point2D *points, int n) {
  AtomicFigureContainer *afc = create_polyline_afc(points, n, fig->t,
                                                   fig->r, fig->c, fig->f);
  add_atomic_figure(fig, afc);
}

/// draw_line daws the line segment [(ax,ay),(bx,by)]
/// the segment is implemented as a polyline of length 2
/// \param fig the figure
/// \param ax the x coordinate of the start point
/// \param ay the y coordinate of the start point
/// \param bx the y coordinate of the end point
/// \param by the y coordinate of the end point
void draw_line(Figure *fig, double ax, double ay, double bx, double by) {
  Point2D *points = (struct Point2D *) malloc(sizeof(Point2D) * 2);

  Point2D *pptr = points;
  pptr->x = ax;
  pptr->y = ay;
  pptr++;
  pptr->x = bx;
  pptr->y = by;
  draw_polyline(fig, points, 2);
}

/// draw_ellipse draw an ellipse
/// an ellipse centered at the origin (0,0) with semi-axes a and b satisfies
/// the equation x²/a² + y²/b² = 0. if a=b=r we get x²+y²=r², the equation of
/// a circle
/// \param fig the figure
/// \param center the center of the ellipse
/// \param a the first semi-axis
/// \param b the second semi-axis
void draw_ellipse(Figure *fig, Point2D *center, double a, double b) {
  // create an ellipse polyline
  double cx = center->x;
  double cy = center->y;
  int n = 2 * (int) floor(a / fig->r);
  Point2D *points = (Point2D *) malloc(sizeof(Point2D) * (2 * n + 1));
  Point2D *pptr = points;
  for (int i = 0; i < n; i++) {
    double x = -a + i * fig->r;
    pptr->x = cx + x;
    pptr->y = cy + (b / a) * sqrt(a * a - x * x);
    pptr++;
  }
  for (int i = 0; i < n; i++) {
    double x = a - i * fig->r;
    pptr->x = cx + x;
    pptr->y = cy - (b / a) * sqrt(a * a - x * x);
    pptr++;
  }
  pptr->x = cx - a;
  pptr->y = cy;
  AtomicFigureContainer *afc = create_polyline_afc(points, 2 * n + 1, fig->t,
                                                   fig->t, fig->c, fig->f);
  add_atomic_figure(fig, afc);
}

/// draw_circle draws a circle with center center and radius r
/// circle is considered as an ellipse with equal semi-axes
/// \param fig the figure
/// \param center the center of the circle
/// \param r the radius of the circle
void draw_circle(Figure *fig, Point2D *center, double r) {
  draw_ellipse(fig, center, r, r);
}

/// print_figure prints all figure informations on the screen
/// could be used as save format prototype for our figures
/// \param fig the figure
void print_figure(Figure *fig) {
  AtomicFigureContainer *atomicFigure = fig->afc;
  printf("  figure w %.2f h %.2f t %.2f r %.2f, c %d, f %d \n", fig->w, fig->h,
         fig->t, fig->r, fig->c, fig->f);
  while (atomicFigure != NULL) {
    if (atomicFigure->type == P) {
      Polyline *p = atomicFigure->af->p;
      printf("    polyline t %.2f r %.2f, c %d, f %d p ", p->t, p->r, p->c,
             p->f);
      for (int i = 0; i < p->len; i++) {
        printf("%.2f,%.2f ", p->poly[i].x, p->poly[i].y);
      }
      printf("\n");
    } else if (atomicFigure->type == T) {
      Text *te = atomicFigure->af->t;
      printf("    text f %d center %.2f,%.2f text %s\n", te->f,
             te->center->x, te->center->y, te->text);
    }
    atomicFigure = atomicFigure->next;
  }
}

/// draw_text the text text centered at center
/// this is a minimal implementation allowing to draw the node info of the
/// binary tree assignment
/// \param fig the figure
/// \param center the center of the text
/// \param text the text
void draw_text(Figure *fig, Point2D *center, char *text) {
  // create a text
  int f = fig->f;
  if (f == -1) {
    f = 0x000000; // color black
  }
  struct AtomicFigureContainer *afc = create_Text_afc(text, center, f);
  add_atomic_figure(fig, afc);
}

/// scale_figure scales a figure with a factor scale_x for the horizontal
/// direction and scale_y for the vertical direction
/// scaling of fonts of text elements is not implemented
/// \param fig the figure
/// \param scale_x the horizontal scaling factor
/// \param scale_y  the vertical scaling factor
void scale_figure(Figure *fig, double scale_x, double scale_y) {
  AtomicFigureContainer *atomicFigure = fig->afc;
  while (atomicFigure != NULL) {
    if (atomicFigure->type == P) {
      Polyline *p = atomicFigure->af->p;
      for (int i = 0; i < p->len; i++) {
        p->poly[i].x *= scale_x;
        p->poly[i].y *= scale_y;
      }
    } else if (atomicFigure->type == T) {
      Text *t = atomicFigure->af->t;
      t->center->x *= scale_x;
      t->center->y *= scale_y;
    }
    atomicFigure = atomicFigure->next;
  }
}

/// codeof computes the position of a point regarding the clipping rectangle
/// with bottom left corner bl, and top right corner tr
/// helper for the csl_line_clip function
/// \param p the point
/// \param bl the bottom left corner
/// \param tr top right corner
/// \return the code of the point
unsigned int codeof(Point2D *p, Point2D bl, Point2D tr) {
  unsigned int code = INSIDE;
  if (p->x < bl.x) {
    code |= LEFT;
  } else if (p->x > tr.x) {
    code |= RIGHT;
  } else if (p->y < bl.y) {
    code |= BOTTOM;
  } else if (p->y > tr.y) {
    code |= TOP;
  }
  return code;
}

/// csl_line_clip clips the segment [p0,p1] regarding to the clipping rectangle
/// with bottom left corner bl, and top right corner tr
/// the clipping algorithm used here is described in wikipedia
/// https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm
/// the wikipedia code has been adapted for our purpose
/// \param p0 the start point of the segment p0 can be replaced with  a clipped
/// point
/// \param p1 the end point of the segment p1 can be replaced with a clipped
/// point
/// \param bl the bottom left corner
/// \param tr tr top right corner
/// \return TRUE if the segment [p0,p1] is inside
boolean csl_line_clip(Point2D *p0, Point2D *p1, Point2D bl,
                      Point2D tr) {
  // compute outcodes for P0, P1, and whatever point lies outside the clip rectangle
  unsigned int code0 = codeof(p0, bl, tr);
  unsigned int code1 = codeof(p1, bl, tr);
  boolean accept = FALSE;
  while (TRUE) {
    if (!(code0 | code1)) {
      // bitwise OR is 0: both points inside window. accept and exit loop
      accept = TRUE;
      break;
    } else if (code0 & code1) {
      // bitwise AND is not 0: both points share an outside zone. reject
      // and exit loop
      break;
    } else {
      // clip segment
      double x = 0.00;
      double y = 0.00;
      // At least one endpoint is outside the clip rectangle; pick it.
      unsigned int codeOut = code0 ? code0 : code1;
      double slope = (p1->y - p0->y) / (p1->x - p0->x);
      if (codeOut & TOP) {           // point is above the clip window
        x = p0->x + (tr.y - p0->y) / slope;
        y = tr.y;
      } else if (codeOut & BOTTOM) { // point is below the clip window
        x = p0->x + (bl.y - p0->y) / slope;
        y = bl.y;
      } else if (codeOut & RIGHT) {  // point is to the right of clip window
        y = tr.x;
        x = p0->y + (tr.x - p0->x) * slope;
      } else if (codeOut & LEFT) {   // point is to the left of clip window
        y = bl.x;
        x = p0->y + (bl.x - p0->x) * slope;
      }
      // clip
      if (codeOut == code0) {
        p0->x = x;
        p0->y = y;
        code0 = codeof(p0, bl, tr);
      } else {
        p1->x = x;
        p1->y = y;
        code1 = codeof(p1, bl, tr);
      }
    }
  }
  return accept;
}

/// copy_point makes a copy of a point
/// \param p the point
/// \return the copy of the point
Point2D *copy_point(Point2D *p) {
  Point2D *r = (Point2D *) malloc(sizeof(Point2D));
  r->x = p->x;
  r->y = p->y;
  return r;
}

/// clip_afc clips the elements of the atomic figure containers
/// \param afc pointer to an afc
/// \param bl the bottom left point of the clipping rectangle
/// \param tr the top right point of the clipping rectangle
/// \param t the line thickness
/// \param r the resolution
/// \param c the color
/// \param f the fill color
/// \return the clipped afc's
AtomicFigureContainer *clip_afc(AtomicFigureContainer *afc,
                                Point2D bl, Point2D tr, double t,
                                double r, Color c, Color f) {
  AtomicFigureContainer *actual_afc = create_empty_afc();
  AtomicFigureContainer *result = actual_afc;
  Point2D *line = afc->af->p->poly;
  int line_pos = 0;
  int length = afc->af->p->len;
  Point2D *res = (Point2D *) malloc(sizeof(Point2D) * length);
  int res_pos = 0;
  boolean accept;
  Point2D *p0;
  Point2D *p1;
  Point2D *previous_point = NULL;
  // search for first inside segment
  while (line_pos < length - 1) {
    p0 = copy_point(&line[line_pos]);
    p1 = copy_point(&line[line_pos + 1]);
    accept = csl_line_clip(p0, p1, bl, tr);
    if (accept) {
      // add first segment
      res[res_pos].x = p0->x;
      res[res_pos].y = p0->y;
      res_pos++;
      res[res_pos].x = p1->x;
      res[res_pos].y = p1->y;
      res_pos++;
      previous_point = p1;
      break;
    }
    line_pos++;
  }
  // all points may be outside
  if (res_pos == 0) {
    return NULL;
  }
  while (line_pos < length - 1) {
    p0 = copy_point(&line[line_pos]);
    p1 = copy_point(&line[line_pos + 1]);
    accept = csl_line_clip(p0, p1, bl, tr);
    if (accept) {
      if (previous_point->x == p0->x &&
          previous_point->y == p0->y) { // no clip
        res[res_pos].x = p1->x;
        res[res_pos++].y = p1->y;
        previous_point = p1;
      } else { // clip
        // clean up garbage
        res = realloc(res,sizeof(Point2D) * res_pos);
        Polyline *p = create_polyline(res, res_pos, t, r, c, f);
        actual_afc->af = create_polyline_af(p);
        actual_afc->type = P;
        // atomic figure container
        actual_afc->next = create_empty_afc();
        actual_afc = actual_afc->next;
        // new result polyline
        res = (Point2D *) malloc(sizeof(Point2D) * length);
        res_pos = 0;
        res[res_pos].x = p0->x;
        res[res_pos++].y = p0->y;
        res[res_pos].x = p1->x;
        res[res_pos++].y = p1->y;
        previous_point = p1;
      }
    }
    line_pos++;
  }
  // clean up garbage
  res = realloc(res,sizeof(Point2D) * res_pos);
  Polyline *p = create_polyline(res, res_pos, t, r, c, f);
  actual_afc->af = create_polyline_af(p);
  actual_afc->type = P;
  actual_afc->next = NULL;
  return result;
}

/// resize_figure resizes the figure fig accordint to the clipping rectangle
/// with bottom left corner bl, and top right corner tr
/// \param fig the figure
/// \param bl the bottom left point of the clipping rectangle
/// \param tr the top right point of the clipping rectangle
void resize_figure(Figure *fig, Point2D bl, Point2D tr) {
  // change with and height of the figure (if necessary)
  if (bl.x < -fig->w / 2) {
    fig->w = 2 * bl.x;
  }
  if (tr.x > fig->w / 2) {
    fig->w = 2 * tr.x;
  }
  if (bl.y < fig->h / 2) {
    fig->h = -2 * bl.y;
  }
  if (tr.y > fig->w) {
    fig->h = 2 * tr.y;
  }
  AtomicFigureContainer *result = NULL; // result
  AtomicFigureContainer *rptr = NULL; // result ptr
  AtomicFigureContainer *lrptr = NULL; // last element of result list
  AtomicFigureContainer *afcptr = fig->afc; // ptr to figure afc list
  AtomicFigureContainer *fptr = NULL;
  fig->afc = NULL;
  // afc list
  while (afcptr != NULL) {
    boolean free_afc = FALSE;
    if (afcptr->type == P) {
      rptr = clip_afc(afcptr, bl, tr, afcptr->af->p->t,
                      afcptr->af->p->r, afcptr->af->p->c,
                      afcptr->af->p->f);
      // be careful, the result may be empty!
      if (rptr != NULL) {
        if (result == NULL) {
          result = rptr;
          lrptr = rptr;
        } else {
          lrptr->next = rptr;
        }
      }
      free_afc = TRUE;
    } else if (afcptr->type == T) {
      // a text element will be removed if its center is not inside the
      // clipping rectangle
      unsigned int in = codeof(afcptr->af->t->center, bl, tr);
      if (in == INSIDE) {
        rptr = afcptr;
        if (result == NULL) {
          result = rptr;
          lrptr = rptr;
        } else {
          lrptr->next = rptr;
        }
      } else {
        free_afc = TRUE;
      }
    }
    // move to the end of the result
    while (lrptr->next != 0) {
      lrptr = lrptr->next;
    }
    fptr = afcptr->next;
    // clean up possible garbage
    if (free_afc) {
      if (afcptr->type == P) {
          free(afcptr->af->p->poly);
          free(afcptr->af->p);
      } else if (afcptr->type == T) {
          free(afcptr->af->t->text);
          free(afcptr->af->t);
      }
      free(afcptr->af);
      free(afcptr);
    }
    afcptr = fptr;
  }
  // do not forget to update the figure last pointer
  fig->last = lrptr;
  fig->afc = result;
}

/// append_figures appends the figures fig1 and fig2 and writes the result
/// figure to fig2
/// \param fig1 the figure fig1
/// \param fig2 the figure fig2
void append_figures(Figure *fig1, Figure *fig2) {
  fig1->afc->next = fig2->afc;
  fig1->last = fig2->last;
  fig1->w = max(fig1->w, fig2->w);
  fig1->h = max(fig1->h, fig2->h);
}




