//
// Created by wuday on 18/05/19.
//

#include <stdlib.h>
#include "free.h"

/// free_text frees a text atomic figure
/// \param t the text element
void free_text(Text *t) {
  if (t->text != NULL) free(t->text);
  t->text = NULL;
  if (t-> center != NULL)  free(t->center);
  t->center = NULL;
  free(t);
}

/// free_polyline frees an text atomic polyline
/// \param p the polyline element
void free_polyline(Polyline *p) {
  if (p->poly != NULL) free(p->poly);
  free(p);
}

/// free_afc frees an atomic figure container
/// \param afc the atomic figure container element
void free_afc(AtomicFigureContainer *afc) {
  AtomicFigure *af = afc->af;
  if (afc->type == T) {
    if (af->t != NULL) free_text(af->t);
    af->t = NULL;
  } else if (afc->type == P) {
    if (af->p != NULL) free_polyline(af->p);
    af->p = NULL;
  }
  free(afc->af);
}

/// free_afc_list frees a linked list of atomic figure containers
/// \param head the atomic figure container linked list
void free_afc_list(AtomicFigureContainer *head) {
  AtomicFigureContainer *tmp = NULL;
  while (head != NULL) {
    tmp = head;
    head = head->next;
    free_afc(tmp);
    tmp = NULL;
  }
}

/// free_figure frees a figure
/// \param f the figure
void free_figure(Figure *f) {
  if (f->afc != NULL) {
    free_afc_list(f->afc);
    f->afc = NULL;
  }
  // afc->last gets freed by free_afc_list(f->afc);
  free(f);
}

