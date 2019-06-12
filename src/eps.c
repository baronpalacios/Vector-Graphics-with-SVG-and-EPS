//
// Created by wuday on 05/05/19.
//

#include "eps.h"
#include "color.h"
#include <stdio.h>
#include <time.h>


/// eps_header generates the eps header. this includes the a clip path such
/// that the height and width correspond to the value of the input parameters 
///
/// \param fptr the file to be written to
/// \param width the width of the figure
/// \param height of the figure
void eps_header(FILE *fptr, double width, double heigth) {
  fprintf(fptr, "%%!PS-Adobe-3.0 EPSF-3.0\n");
  fprintf(fptr, "%%%%Creator: Wuday Colley ");
  time_t current_time = time(NULL);
  char *c_time_string = ctime(&current_time);
  fprintf(fptr, "%%%%CreationDate: %s", c_time_string);
  fprintf(fptr, "%%%%Pages: 1\n");
  fprintf(fptr, "%%%%DocumentData: Clean7Bit\n");
  fprintf(fptr, "%%%%LanguageLevel: 2\n");
  fprintf(fptr, "%%%%BoundingBox: 0 0 %.2f %.2f\n", width, heigth);
  fprintf(fptr, "%%%%EndComments\n");
  fprintf(fptr, "%%%%BeginProlog\n");
  fprintf(fptr, "8 dict begin\n");
  fprintf(fptr, "/m { moveto } bind def\n");
  fprintf(fptr, "/l { lineto } bind def\n");
  fprintf(fptr, "/a { arc } bind def\n");
  fprintf(fptr, "/h { closepath } bind def\n");
  fprintf(fptr, "/n { newpath } bind def\n");
  fprintf(fptr, "/t { translate } bind def\n");
  fprintf(fptr, "/s { scale } bind def\n");
  fprintf(fptr, "/c { rectclip } bind def\n");
  fprintf(fptr, "%%%%EndProlog\n");
  fprintf(fptr, "0 0 %.2f %.2f c\n", width, heigth);
}

/// eps_footer generates the eps footer.
///
/// \param fptr the file to be written to
void eps_footer(FILE *fptr) {
  fprintf(fptr, "showpage\n");
  fprintf(fptr, "%%%%Trailer\n");
  fprintf(fptr, "end\n");
  fprintf(fptr, "%%%%EOF\n");
}

/// R computes the RGB red color part of the color
///
/// \param c the color
/// \returns the RGB red value
double R(Color c) {
  return (c >> 16) / 255.0;
}

/// G computes the RGB green color part of the color
///
/// \param c the color
/// \returns the RGB green value
double G(Color c) {
  return (c >> 8) % 256/ 255.0;
}

/// B computes the RGB blue color part of the color
///
/// \param c the color
/// \returns the RGB blue value
double B(Color c) {
  return c % 256 / 255.0;
}

/// eps_polyline draws a polyline
///
/// \param fptr the file to be written to
/// \param polyline the polyline
/// \param t the line thickness
/// \param c the color of the line
/// \param f the fill color of the line
/// \param tx The x translation of the points
/// \param ty The y translation of the points
void eps_polyline(FILE *fptr, Polyline *polyline, double t,
                  Color c, Color f, double tx, double ty) {
  fprintf(fptr, "n\n");
  Point2D *pptr = polyline->poly;
  fprintf(fptr, "%.2f %.2f m\n", pptr[0].x + tx, pptr[0].y + ty);
  for (
    int i = 1; i < polyline->len; i++) {
    fprintf(fptr, "%.2f %.2f l\n", pptr[i].x + tx, pptr[i].y + ty);
  }
  if (f != NONE) {
    fprintf(fptr, "h\n");
    fprintf(fptr, "gsave\n");
    fprintf(fptr, "%.2f %.2f %.2f setrgbcolor\n", R(f), G(f), B(f));
    fprintf(fptr, "fill\n");
    fprintf(fptr, "grestore\n");
  }
  fprintf(fptr, "%.2f setlinewidth\n", t);
  fprintf(fptr, "%.2f %.2f %.2f setrgbcolor\n", R(c), G(c), B(c));
  fprintf(fptr, "stroke\n");
}

/// eps_polyline draws a text
///
/// \param fptr the file to be written to
/// \param text the text to draw
/// \param tx The x translation of the points
/// \param ty The y translation of the points
/// \param c the color of the text
void eps_text(FILE *fptr, Text *text, double tx, double ty, Color color) {
  Point2D *center = text->center;
  fprintf(fptr, "%.2f %.2f m\n", center->x + tx, center->y + tx);
  fprintf(fptr, "/Times-Roman 12 selectfont\n");
  fprintf(fptr, "/ctext {(%s)} bind def\n", text->text);
  fprintf(fptr, "ctext stringwidth pop 2 div neg -5 rmoveto\n");
  fprintf(fptr, "%.2f %.2f %.2f setrgbcolor\n", R(color), G(color), B(color));
  fprintf(fptr, "ctext show\n");
}

/// export_eps writes the figure to as an eps file
///
/// \param file_name the name of the export file
void export_eps(Figure *fig, char *file_name) {
  FILE *fptr;
  double tx = fig->w / 2;
  double ty = fig->h / 2;
  fptr = fopen(file_name, "w");
  // generate svg header
  eps_header(fptr, fig->w, fig->h);
  AtomicFigureContainer *d = fig->afc;
  while (d != NULL) {
    if (d->type == P) {
      Polyline *polyline = d->af->p;
      eps_polyline(fptr, polyline, polyline->t, polyline->c,
                   polyline->f, tx, ty);
      // polyline
    } else if (d->type == T) {
      Text *text = d->af->t;
      eps_text(fptr, text, tx, ty, text->f);
    }
    d = d->next;
  }
  eps_footer(fptr);
  fclose(fptr);
}
