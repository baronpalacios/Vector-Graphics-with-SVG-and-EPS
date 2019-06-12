//
// Created by wuday on 03/05/19.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <libxml/parser.h>
#include "sxmlc.h"
#include "sxmlsearch.h"
#include "color.h"
#include "figures.h"
#include <ctype.h>

/// svg_header generates the root element of the SVG document
/// \param fptr fptr the file to be written to
/// \param width
/// \param heigth
void svg_header(FILE *fptr, double width, double heigth) {
  fprintf(fptr, "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
  fprintf(fptr,
          "<svg width=\"%.2f\" height=\"%.2f\" xmlns=\"http://www.w3.org/2000/svg\">\n",
          width, heigth);
}

/// export_svg writes the figure as a SVG file
/// \param figure the figure to be exported
/// \param file_name file_name the name of the export file
void export_svg(Figure *fig, char *file_name) {
  double t_x = fig->w / 2;
  double t_y = fig->h / 2;
  FILE *fptr;
  fptr = fopen(file_name, "w");
  // generate svg header
  svg_header(fptr, fig->w, fig->h);
  AtomicFigureContainer *d = fig->afc;
  while (d != NULL) {
    if (d->type == P) {
      Polyline *po = d->af->p;
      if (po->f == 0x1000000) {
        fprintf(fptr, "  <polyline stroke=\"#%06x\" stroke-width=\"%.2f\" "
                      "stroke-linecap=\"square\" "
                      "fill=\"none\" points=\"", po->c, po->t);
      } else {
        fprintf(fptr, "  <polyline stroke=\"#%06x\" stroke-width=\"%.2f\" "
                      "stroke-linecap=\"square\" "
                      "fill=\"#%06x\" points=\"", po->c, po->t,
                po->f);
      }
      Point2D *pptr = po->poly;
      fprintf(fptr, "%.2f,%.2f ", pptr[0].x + t_x, -pptr[0].y + t_y);
      for (int i = 1; i < po->len; i++) {
        fprintf(fptr, " %.2f,%.2f", pptr[i].x + t_x, -pptr[i].y + t_y);
      }
      fprintf(fptr, "\"/>\n");
    } else if (d->type == T) {
      // draw text
      Text *te = d->af->t;
      if (te->f == -1) {
        fprintf(fptr,
                "  <text x=\"%.2f\" y=\"%.2f\" fill=\"none\" "
                "text-anchor=\"middle\" font-size=\"10.00\">\n",
                te->center->x + t_x + 1.00, -te->center->y + 3.00 + t_y);
      } else {
        fprintf(fptr,
                "  <text x=\"%.2f\" y=\"%.2f\" fill=\"#%06x\" "
                "text-anchor=\"middle\" font-size=\"10.00\">\n",
                te->center->x + t_x + 1.00, -te->center->y + 3.00 + t_y, te->f);
      }
      fprintf(fptr, "    %s\n", te->text);
      fprintf(fptr, "  </text>\n");
    }
    d = d->next;
  }
  fprintf(fptr, "</svg>\n");
  fclose(fptr);
}

/// trim removes all leading and trailing whitespaces of the string str
/// \param  str the string to be trimmed
char *trim(char *s) {
  int l = strlen(s);
  while (isspace(s[l - 1])) --l;
  while (*s && isspace(*s)) ++s, --l;
  return strndup(s, l);
}

/// import_svg generates a figure from a SVG file
/// this function is using the DOM parser of the scmlc library
/// see https://github.com/matthieu-labas/sxmlc for more details
/// the function is able to import all SVG documents generated our
/// application only
/// \param filename the name of the SVG file
/// \returns fig the figure to be imported
Figure *import_svg(char *filename) {
  Figure *fig;
  XMLDoc doc;
  XMLSearch search;
  XMLNode *node;
  XMLDoc_init(&doc);
  char *edptr = NULL;
  XMLDoc_parse_file_DOM_text_as_nodes(C2SX(filename),
                                      &doc, 1);
  node = doc.nodes[doc.i_root];
  if (!
    strcmp(node
             ->tag, "svg")) {
    XMLNode *n = XMLNode_new(node->tag_type, "svg", "");
    XMLNode_copy(n, node,
                 0);
    int i = XMLNode_search_attribute(n, "width", 0);
    double width = strtod(n->attributes[i].value, &edptr);
    i = XMLNode_search_attribute(n, "height", 0);
    double height = strtod(n->attributes[i].value, &edptr);
    XMLNode_free(n);
    n = NULL;
    fig = start_figure(width, height);
  } else {
    printf("  invalid node\n");
    return NULL;
  }
  for (
    int i = 0;
    i < node->
      n_children;
    i++) {
    if (node->children[i]->tag_type == TAG_TEXT) {
    } else if (!
      strcmp(node
               ->children[i]->tag, "polyline")) {
      XMLNode *n = XMLNode_new(node->children[i]->tag_type, "polyline", "");
      XMLNode_copy(n, node
        ->children[i], 0);
      int j = XMLNode_search_attribute(n, "stroke", 0);
      int stroke;
      if (
        strcmp(n
                 ->attributes[j].value, "none")) {
        stroke = (int) strtol(strtok(n->attributes[j].value, "#"), NULL, 10);
      } else {
        stroke = NONE;
      }
      set_color(fig, stroke
      );
      j = XMLNode_search_attribute(n, "stroke-width", 0);
      double stroke_width = strtod(n->attributes[j].value, &edptr);
      set_thickness_resolution(fig, stroke_width,
                               0.05);
      j = XMLNode_search_attribute(n, "fill", 0);
      if (
        strcmp(n
                 ->attributes[j].value, "none")) {
        int fill = (int) strtol(strtok(n->attributes[j].value, "#"), NULL, 16);
        set_fill(fig, fill
        );
      } else {
        set_fill(fig,
                 0x1000000);
      }
      j = XMLNode_search_attribute(n, "points", 0);
// copy n->attributes[j].value
      int npts = 0;
      int l = strlen(n->attributes[j].value);
      char *copy = (char *) malloc(sizeof(char) * (l + 1));
      strcpy(copy, n
        ->attributes[j].value);
      char *cptr = copy;
      while (*cptr != '\0') {
        if (*cptr == ',') {
          *
            cptr = ' ';
          npts++;
        }
        cptr++;
      }
      Point2D *p = (struct Point2D *) malloc(sizeof(Point2D) * npts);
      Point2D *pptr = p;
      cptr = copy;
      char *token = strtok_r(cptr, " ", &cptr);
      for (
        int k = 0;
        k < npts;
        k++) {
        pptr->
          x = strtod(token, NULL) - fig->w / 2;
        token = strtok_r(cptr, " ", &cptr);
        pptr->
          y = strtod(token, NULL) - fig->h / 2;
        token = strtok_r(cptr, " ", &cptr);
        pptr++;
      }
      draw_polyline(fig, p, npts
      );
      free(copy);
      copy = NULL;
      XMLNode_free(n);
      n = NULL;
    } else if (!
      strcmp(node
               ->children[i]->tag, "text")) {
      if (node->children[i]->tag_type != TAG_TEXT) {
        XMLNode *n = XMLNode_new(node->children[i]->tag_type, "text", "");
        XMLNode_copy(n, node
          ->children[i], 0);
        int j = XMLNode_search_attribute(n, "x", 0);
        double x = strtod(n->attributes[j].value, &edptr);
        j = XMLNode_search_attribute(n, "y", 0);
        double y = strtod(n->attributes[j].value, &edptr);
        Point2D *ctr = (Point2D *) malloc(sizeof(Point2D));
        ctr->
          x = x - fig->w / 2 - 1;
        ctr->
          y = y - fig->h / 2 - 3;
        j = XMLNode_search_attribute(n, "fill", 0);
        if (
          strcmp(n
                   ->attributes[j].value, "none")) {
          int fill = (int) strtol(strtok(n->attributes[j].value, "#"), NULL,
                                  16);
          set_fill(fig, fill
          );
        } else {
          set_fill(fig,
                   0x1000000);
        }
        char *t = trim(node->children[i]->children[0]->text);
        draw_text(fig, ctr, t
        );
        XMLNode_free(n);
        n = NULL;
      }
    }
  }
  return fig;
}
