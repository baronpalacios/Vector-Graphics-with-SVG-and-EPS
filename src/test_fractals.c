//
// Created by wuday on 09/05/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "figures.h"
#include "fractals.h"
#include "eps.h"
#include "svg.h"

/// test_koch draws a koch snowflake curve and exports it to SVG and EPS
void test_koch_snowflake() {
  printf("> koch snowflake draw_koch_snowflake(f, ctr, 0.1, 30, 6)\n");
  Figure *f;
  f = start_figure(100, 100);
  set_thickness_resolution(f, 0.50, 1.0);
  set_color(f, 0x000000);
  Point2D *ctr = malloc(sizeof(Point2D));
  ctr->x = 0.00;
  ctr->y = 0.00;
  printf("  drawing koch snowflake\n");
  draw_koch_snowflake(f, ctr, 0.1, 30, 4);
  export_eps(f, "./figures/koch.eps");
  printf("  result exported to ./figures/koch.eps\n");
  export_svg(f, "./figures/koch.svg");
  printf("  result exported to ./figures/koch.svg\n");
  printf("  done\n");
  free_figure(f);
}

/// test_anti_koch draws a koch anti snowflake curve and exports it to SVG and
// EPS
void test_koch_anti_snowflake() {
  printf("> koch anti snowflake draw_koch_anti_snowflake(f, ctr, 0.1, 30, 6)\n");
  Figure *f;
  f = start_figure(100, 100);
  set_thickness_resolution(f, 0.50, 1.0);
  set_color(f, 0x000000);
  Point2D *ctr = malloc(sizeof(Point2D));
  ctr->x = 0.00;
  ctr->y = 0.00;
  printf("  drawing koch_anti_snowflake\n");
  draw_koch_anti_snowflake(f, ctr, 0.1, 30, 6);
  export_eps(f, "./figures/kocha.eps");
  printf("  result exported to ./figures/kocha.eps\n");
  export_svg(f, "./figures/kocha.svg");
  printf("  result exported to ./figures/kocha.svg\n");
  printf("  done\n");
  free_figure(f);
}

/// test_fractal_tree draws a fractal tree and exports it to SVG and EPS
void test_fractal_tree() {
  printf("> fractal tree draw_fractal_tree(f, 0.00, -40.00, 30.00, 10)\n");
  Figure *f;
  f = start_figure(100, 100);
  set_thickness_resolution(f, 0.1, 1.0);
  set_color(f, 0x000000);
  printf("  drawing fractal tree\n");
  draw_fractal_tree(f, 0.00, -40.00, 30.00, 10);
  export_eps(f, "./figures/ftree.eps");
  printf("  result exported to ./figures/ftree.eps\n");
  export_svg(f, "./figures/ftree.svg");
  printf("  result exported to ./figures/ftree.svg\n");
  printf("  done\n");
  free_figure(f);
}

/// test_fractal_atree draws an asymmetric fractal tree and exports it to SVG
/// and EPS
void test_fractal_atree() {
  printf("> asymmetric fractal tree draw_fractal_atree(f, 0.00, -40.00, 30.00, 8)\n");
  Figure *f;
  f = start_figure(100, 100);
  set_color(f, 0x000000);
  draw_fractal_atree(f, 0.00, -40.00, 30.00, 8);
  printf("  drawing asymmetric fractal tree\n");
  export_eps(f, "./figures/aftree.eps");
  printf("  result exported to ./figures/aftree.eps\n");
  export_svg(f, "./figures/aftree.svg");
  printf("  result exported to ./figures/aftree.svg\n");
  printf("  done\n");
  free_figure(f);
}

/// test_fractals executes all tests above
void test_fractals() {
  // koch snowflake
  test_koch_snowflake();
  // koch anto snowflake
  test_koch_anti_snowflake();
  // fractal tree
  test_fractal_tree();
  // asymmetric fractal tree
  test_fractal_atree();
}
