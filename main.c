#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <gmp.h>

#include "fatorial.h"

mpf_t leftside;
mpf_t upsummagicnumber = 13591409;
mpf_t upmultmagicnumber = 545140134;
mpf_t downmagicnumber = -640320;
mpf_t upfat = fatorial( 6 * k );
mpf_t upresto = (upsummagicnumber + upmultmagicnumber * k);
mpf_t downfat = fatorial(3*k);
mpf_t downfatexp =  (powl((long double)fatorial(k),3.0));
mpf_t downresto = (powl(downmagicnumber, 3.0*k));
mpf_t up = upfat * upresto;
mpf_t down = downfat * downfatexp * downresto;


long double iteration(int k){
  return up/down;
}


int main(int argc, char **argv){
  int i;
  long double mynotpi = 0.;
  if (/*sequencial*/1)
    omp_set_num_threads(1);
  else
    omp_set_num_threads(omp_get_num_procs());
  fatinit(100);
  for(i = 0; i < 10; i++)
    mynotpi += iteration(i);
  printf("%.15Lf\n", leftside/mynotpi);
  return 0;
}

