//
// Created by wuday on 07/05/19.
//

#ifndef FIGURES_FRACTALS_H
#define FIGURES_FRACTALS_H

#include "figures.h"

void draw_koch_snowflake(Figure *fig, Point2D *center, double thickness,
                         int size, int num_iterations);

void draw_koch_anti_snowflake(Figure *fig, Point2D *center, double thickness,
                         int size, int num_iterations);

void draw_fractal_tree(Figure *f, double center_x, double center_y, double size,
                       int n);

void draw_fractal_atree(Figure *f, double center_x, double center_y,
                        double size, int n);

#endif //FIGURES_FRACTALS_H
