#include "fatorial.h"

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

mpf_t *precalc;

int fatinit(int n){
  int i;
  precalc = malloc(n*sizeof(*precalc));
  if (!precalc)
    return 0;
  for(i = 0; i < n; i++)
    mpf_init(precalc[i]);
  return 1;
}


mpf_t fatorial(int n){
  printf("int -> %d\n", n);
  if (!mpf_cmp_ui(precalc[n], 0)){
    if (n==1)
      mpf_set_ui(precalc[n], 1);
    else
      mpf_mul_ui(precalc[n], precalc[n-1], (unsigned long int)n);
  }
  return precalc[n];
}
