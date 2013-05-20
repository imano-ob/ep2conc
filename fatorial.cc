#include "fatorial.h"

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>

using namespace std;

mpf_class precalc[100];


mpf_class fatorial(int n){
  if (!cmp(precalc[n],0)){
    if (n==0)
     precalc[n] = 1;
    else{
      precalc[n] =  fatorial(n-1) * n;
    }
  }
  return precalc[n];
}
