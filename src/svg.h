//
// Created by wuday on 03/05/19.
//

#ifndef FIGURES_SVG_H
#define FIGURES_SVG_H

#include "figures.h"

void export_svg(Figure *fig, char *file_name);

Figure *import_svg(char *filename);

#endif //FIGURES_SVG_H
