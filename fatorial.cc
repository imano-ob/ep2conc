#include "fatorial.h"

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>

#define SIZE 1000

using namespace std;

mpf_class precalc[SIZE];
int cur_n[SIZE];


mpf_class fatorial(int n){
  if (n == 0){
    precalc[n] = 1;
    cur_n[n] = n;
  }
  else if (cur_n[n%SIZE] != n){
    precalc[n%SIZE] =  fatorial(n-1) * n;
    cur_n[n%SIZE] = n;
  }
  return precalc[n%SIZE];
}
