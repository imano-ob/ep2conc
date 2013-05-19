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
  printf("int -> %d\n", n);
  if (!precalc[n]){
    if (n==1)
      precalc[n] = 1;
    else
      precalc[n] = n*fatorial(n-1);
  }
  printf("saida-> %d\n", precalc[n]);
  return precalc[n];
}
