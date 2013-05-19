#include <stdio.h>
#include <omp.h>
#include <math.h>

#include "fatorial.h"

const double leftside = 426880 * sqrt(10005);

long double iteration(k){
  const long double upsummagicnumber = 43591409;
  const long double upmultmagicnumber = 545140134;
  const long double downmagicnumber = 640320;
  long double up = fatorial( 6 * k ) * (upsummagicnumber + upmultmagicnumber * k);
  printf("%llf\n", up);
  long double down = fatorial(3*k) * (powl((double)fatorial(k),3))*(powl(downmagicnumber, 3.0*k));
  printf("%llf\n", down);
  return up/down;
}


int main(int argc, char **argv){
  if (/*sequencial*/1)
    omp_set_num_threads(1);
  else
    omp_set_num_threads(omp_get_num_procs());
  fatinit(100);
  printf("%llf\n", iteration(1));
  return 0;
}

