#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#define GNUPLOT "gnuplot -persist"

void plot_array(float *x, float *y, int n) {
  FILE *p = popen(GNUPLOT, "w");

  fprintf(p, "plot '-' with lines\n");

  for(int i = 0; i < n; i++)
    fprintf(p, "%f %f\n", x[i], y[i]);

  fprintf(p, "e\n");

  pclose(p);
}
