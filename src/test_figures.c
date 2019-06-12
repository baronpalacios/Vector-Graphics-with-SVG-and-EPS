//
// Created by wuday on 09/05/19.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "test_figures.h"
#include "figures.h"
#include "free.h"
#include "eps.h"
#include "svg.h"

/// figure_test
void figure_test() {
  printf("> figure initialisation start_figure(100, 100)\n");
  Figure *f = start_figure(100, 100);
  set_thickness_resolution(f, 1, 1);
  set_color(f, 0xFF0000);
  print_figure(f);
  free_figure(f);
  printf("  done\n");
}

/// empty_test
void empty_test() {
  printf("> empty figure start_figure(100, 100)\n");
  Figure *f = start_figure(100, 100);
  print_figure(f);
  export_svg(f, "./figures/empty.svg");
  printf("  result exported to empty.svg\n");
  export_eps(f, "./figures/empty.eps");
  printf("  result exported to empty.eps\n");
  free_figure(f);
  printf("  done\n");
}

/// circle_test
void circle_test() {
  printf("> circle draw_circle(c, ctr, 10.0)\n");
  Figure *c = start_figure(100, 100);
  set_thickness_resolution(c, 1, 0.05);
  Point2D *ctr = (Point2D *) malloc(sizeof(Point2D));
  ctr->x = 0.0;
  ctr->y = 0.0;
  draw_circle(c, ctr, 10.0);
  print_figure(c);
  export_svg(c, "./figures/circle.svg");
  printf("  result exported to ./figures/circle.svg\n");
  export_eps(c, "./figures/circle.eps");
  printf("  result exported to ./figures/circle\n");
  free(ctr);
  free_figure(c);
  printf("  done\n");
}

double mf(double x) {
  return x * x * x - 5 * x * x + 5 * x - 1;
}

double si(double x) {
  return sin(x);
}

/// function_test
void function_test() {
  printf("> function draw_fx(f, mf, -20, 20.0) draw_fx(f, si, -20, 20.0)\n");
  Figure *f = start_figure(100, 100);
  //Point2D bl;
  //Point2D tr;
  //bl.x = -f->w / 2;
  //bl.y = -f->h / 2;
  //tr.x = f->w / 2;
  //tr.y = f->h / 2;
  set_thickness_resolution(f, 0.5, 0.5);
  draw_fx(f, mf, -20, 20.0);
  draw_fx(f, si, -20, 20.0);
  Point2D *ctr = (Point2D *) malloc(sizeof(Point2D));
  ctr->x = 60.0;
  ctr->y = 60.0;
  set_fill(f, 0xFF0000);
  draw_text(f, ctr, "text");
  print_figure(f);
  export_eps(f, "./figures/mf.eps");
  printf("  result exported to ./figures/mf.eps\n");
  export_svg(f, "./figures/mf.svg");
  printf("  result exported to ./figures/mf.svg\n");
  //free(ctr);
  free_figure(f);
  printf("  done\n");
}

/// text_test
void text_test() {
  printf("> text draw_text(f, ctr, \"text\")\n");
  Figure *f = start_figure(100, 100);
  Point2D *ctr = (Point2D *) malloc(sizeof(Point2D));
  ctr->x = 0.0;
  ctr->y = 0.0;
  set_thickness_resolution(f, 0.5, 0.5);
  set_fill(f, 0x00FF00);
  draw_text(f, ctr, "text");
  print_figure(f);
  export_svg(f, "./figures/text.svg");
  printf("  result exported to ./figures/text.svg\n");
  export_eps(f, "./figures/text.eps");
  printf("  result exported to ./figures/text.eps\n");
  //free(ctr);
  free_figure(f);
  printf("  done\n");
}

/// ellipse_test
void ellipse_test() {
  printf("> ellipse draw_ellipse(e, ctr, 20.0, 10.0)\n");
  Figure *e = start_figure(100, 100);
  Point2D *ctr = (Point2D *) malloc(sizeof(Point2D));
  ctr->x = 0.0;
  ctr->y = 0.0;
  draw_ellipse(e, ctr, 20.0, 10.0);
  print_figure(e);
  export_svg(e, "./figures/ellipse.svg");
  printf("  result exported to ./figures/ellipse.svg\n");
  export_eps(e, "./figures/ellipse.eps");
  printf("  result exported to ./figures/ellipse.eps\n");
  free(ctr);
  free_figure(e);
  printf("  done\n");
}

/// polyline_test
void polyline_test() {
  printf("> polyline draw_polyline(f, pts, 5)\n");
  Figure *f = start_figure(100, 100);
  Point2D *pts = create_point2d_vector(5, -40.0, 0.0, 0.0, 40.0, 40.0, 0.0,
                                       0.0, -40.0, -40.0, 0.0);
  draw_polyline(f, pts, 5);
  print_figure(f);
  export_eps(f, "./figures/point2DVector.eps");
  printf("  result exported to ./figures/point2DVector.eps\n");
  export_svg(f, "./figures/point2DVector.svg");
  printf("  result exported to ./figures/point2DVector.svg\n");
  // free(pts);
  free_figure(f);
  printf("  done\n");
}

/// color_test
void color_test() {
  printf("> circle draw_circle(c, ctr, 10.0\n");
  Figure *c = start_figure(100, 100);
  set_thickness_resolution(c, 1, 0.05);
  set_color(c, 0xFF0000);
  Point2D *ctr = (Point2D *) malloc(sizeof(Point2D));
  ctr->x = 0.0;
  ctr->y = 0.0;
  draw_circle(c, ctr, 10.0);
  print_figure(c);
  export_svg(c, "./figures/red_circle.svg");
  printf("  result exported to ./figures/red_circle.svg\n");
  export_eps(c, "./figures/red_circle.eps");
  printf("  result exported to ./figures/red_circle.eps\n");
  free_figure(c);
  free(ctr);
  printf("  done\n");
}

/// scaling_test
void scaling_test() {
  printf("> scaling scale_figure(c, 1, 0.5)\n");
  Figure *c = start_figure(100, 100);
  Point2D *ctr = (Point2D *) malloc(sizeof(Point2D));
  ctr->x = 0.0;
  ctr->y = 0.0;
  draw_circle(c, ctr, 10.0);
  print_figure(c);
  export_eps(c, "./figures/unscaled_circle.eps");
  printf("  result exported ./figures/unscaled_circle.eps\n");
  export_svg(c, "./figures/unscaled_circle.svg");
  printf("  result exported ./figures/unscaled_circle.svg\n");
  scale_figure(c, 1, 0.5);
  print_figure(c);
  export_eps(c, "./figures/scaled_circle.eps");
  printf("  result exported to ./figures/scaled_circle.eps\n");
  export_svg(c, "./figures/scaled_circle.svg");
  printf("  result exported to ./figures/scaled_circle.svg\n");
  free(ctr);
  free_figure(c);
  printf("  done\n");

}

/// resize_test
void resizet_test() {
  printf("> resize resize_figure(f, bl, tr) [texp]\n");
  Figure *f = start_figure(100, 100);
  Point2D *pts = create_point2d_vector(5, -40.0, -40.0, -40.0, 40.0, 40.0,
                                       40.0, 40.0, -40.0, -40.0, -40.0);
  draw_polyline(f, pts, 5);
  Point2D *ctr1 = (Point2D *) malloc(sizeof(Point2D));
  ctr1->x = 0.0;
  ctr1->y = 45.0;
  set_fill(f, 0xFF0000);
  draw_text(f, ctr1, "out");
  Point2D *ctr2 = (Point2D *) malloc(sizeof(Point2D));
  ctr2->x = 0.0;
  ctr2->y = 0.0;
  set_fill(f, 0xFF0000);
  draw_text(f, ctr2, "in");
  Point2D bl;
  Point2D tr;
  bl.x = -50.00;
  bl.y = -40.00;
  tr.x = 50.00;
  tr.y = 40.00;
  printf("  original figure\n");
  print_figure(f);
  export_svg(f, "./figures/utext.svg");
  printf("  result exported to ./figures/utext.svg\n");
  export_eps(f, "./figures/utext.eps");
  printf("  result exported to ./figures/utext.eps\n");
  resize_figure(f, bl, tr);
  printf("  resized figure\n");
  print_figure(f);
  export_svg(f, "./figures/rtext.svg");
  printf("  result exported to ./figures/rtext.svg\n");
  export_eps(f, "./figures/rtext.eps");
  printf("  result exported to ./figures/rtext.eps\n");
  free_figure(f);
  printf("  done\n");
}

/// resize_test
void resizep_test() {
  printf("> resize resize_figure(f, bl, tr) [polyline]\n");
  Figure *f = start_figure(100, 100);
  Point2D *pts = create_point2d_vector(5, -40.0, 0.0, 0.0, 40.0, 40.0, 0.0,
                                       0.0, -40.0, -40.0, 0.0);

  draw_polyline(f, pts, 5);
  printf("  original figure\n");
  print_figure(f);
  export_svg(f, "./figures/upoly.svg");
  printf("  result exported to ./figures/upoly.svg\n");
  export_eps(f, "./figures/upoly.eps");
  printf("  result exported to ./figures/upoly.eps\n");
  Point2D bl;
  Point2D tr;
  bl.x = -50.00;
  bl.y = -10.00;
  tr.x = 50.00;
  tr.y = 10.00;
  resize_figure(f, bl, tr);
  printf("  resized figure\n");
  print_figure(f);
  export_svg(f, "./figures/rpoly.svg");
  printf("  result exported to ./figures/rpoly.svg\n");
  export_eps(f, "./figures/rpoly.eps");
  printf("  result exported to ./figures/rpoly.eps\n");
  free_figure(f);
  printf("  done\n");
}

/// append test
void append_test() {
  printf("> append append_figures(fig1, fig2)\n");
  Figure *fig1 = start_figure(100, 100);
  Point2D *ctr1 = (Point2D *) malloc(sizeof(Point2D));
  ctr1->x = 0.0;
  ctr1->y = 0.0;
  draw_ellipse(fig1, ctr1, 20.0, 10.0);
  export_eps(fig1, "./figures/fig1.eps");
  printf("  fig1 exported to ./figures/fig1.eps\n");
  export_svg(fig1, "./figures/fig1.svg");
  printf("  fig1 exported to ./figures/fig1.svg\n");
  
  Figure *fig2 = start_figure(100, 200);
  Point2D *ctr2 = (Point2D *) malloc(sizeof(Point2D));
  ctr2->x = 10.0;
  ctr2->y = 10.0;
  draw_ellipse(fig2, ctr2, 10.0, 20.0);
  export_eps(fig2, "./figures/fig2.eps");
  printf("  fig2 exported to ./figures/fig2.eps\n");
  export_svg(fig2, "./figures/fig2.svg");
  printf("  fig2 exported to ./figures/fig2.svg\n");
  append_figures(fig1, fig2);
  export_eps(fig1, "./figures/fig1_append_fig2.eps");
  printf("  result exported to ./figures/fig1_append_fig2.eps\n");
  export_svg(fig1, "./figures/fig1_append_fig2.svg");
  printf("  result exported to ./figures/fig1_append_fig2.svg\n");
  free_figure(fig1);
  // afc and last have already been freed by free_figure(fig1);
  fig2->afc = NULL;
  fig2->last = NULL;
  free_figure(fig2);
  printf("  done\n");
}

/// import_test
void import_test() {
  printf("> import import_svg(r, \"./figures/import.svg\")\n");
  Figure *f = start_figure(100, 100);
  Point2D *pts = create_point2d_vector(5, -40.0, 0.0, 0.0, 40.0, 40.0, 0.0,
                                       0.0, -40.0, -40.0, 0.0);

  draw_polyline(f, pts, 5);
  Point2D *ctr = (Point2D *) malloc(sizeof(Point2D));
  ctr->x = 0.00;
  ctr->y = 0.00;
  set_color(f, 0x000000);
  set_fill(f, 0x00FF00);
  set_thickness_resolution(f, 1.0, 0.05);
  draw_text(f, ctr, "text");
  print_figure(f);
  export_svg(f, "./figures/import.svg");
  free_figure(f);
  printf("  importing ./figures/import.svg\n");
  f =import_svg("./figures/import.svg");
  print_figure(f);
  export_svg(f, "./figures/imported.svg");
  printf("  result exported to ./figures/imported.eps\n");
  free_figure(f);
  printf("  done\n");
}

/// figures_test tests all figure tests
void figures_test() {
  // figures
  figure_test();
  // empty figure
  empty_test();
  // circle
  circle_test();
  // ellipse
  ellipse_test();
  // function
  function_test();
  // text
  text_test();
  // polyline
  polyline_test();
  // circle
  color_test();
  // scaling
  scaling_test();
  // resize
  resizep_test();
  // append
  resizet_test();
  // append
  append_test();
  // import
  import_test();
}
