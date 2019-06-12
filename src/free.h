//
// Created by wuday on 18/05/19.
//

#ifndef FIGURES_FREE_H
#define FIGURES_FREE_H

#include "figures.h"

void free_figure(Figure * f);

void free_afc_list(AtomicFigureContainer * afcl);

void free_afc(AtomicFigureContainer * afc);

void free_polyline(Polyline * p);

void free_text(Text * t);

void free_afc_list(AtomicFigureContainer * afcl);

#endif //FIGURES_FREE_H
