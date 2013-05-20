#include "fatorial.h"

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <gmpxx.h>

mpf_class precalc[100];

/*int fatinit(int n){
  int i;
  precalc = malloc(n*sizeof(*precalc));
  if (!precalc)
    return 0;
  for(i = 0; i < n; i++)
    precalc[i] = 0;
  return 1;
  }*/


mpf_class fatorial(int n){
  printf("int -> %d\n", n);
  if (!cmp(precalc[n],0)){
    if (n==1)
     precalc[n] = 1;
    else
      precalc[n] =  precalc[n-1] * n;
  }
  return precalc[n];
}
