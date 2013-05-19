#include "fatorial.h"

#include <stdlib.h>
#include <stdio.h>

int *precalc;

int fatinit(int n){
  precalc = malloc(n*sizeof(*precalc));
  if (!precalc)
    return 0;
  return 1;
}


int fatorial(int n){
  if (!precalc[n])
    precalc[n] = n*fatorial(n-1);
  printf("%lf\n", precalc[n]);
  return precalc[n];
}
