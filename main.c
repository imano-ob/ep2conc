#include <stdio.h>
#include <omp.h>
#include <math.h>

#include "fatorial.h"

const double leftside = 426880 * sqrt(10005);

double iteration(k){
  const double upsummagicnumber = 43591409;
  const double upmultmagicnumber = 545140134;
  const double downmagicnumber = 640320;
  double up = fatorial( 6 * k ) * (upsummagicnumber + upmultmagicnumber * k);
  double down = fatorial(3*k) * (pow((double)fatorial(k),3))*(pow(downmagicnumber, 3.0*k));
  return up/down;
}


int main(int argc, char **argv){
  if (/*sequencial*/1)
    omp_set_num_threads(1);
  else
    omp_set_num_threads(omp_get_num_procs());
  fatinit(100);
  printf("%lf\n", iteration(1));
  return 0;
}

