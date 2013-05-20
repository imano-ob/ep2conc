#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>

#include "fatorial.h"

mpf_class leftside = 426880 * sqrt(10005);
mpf_t tmp;

mpf_class upsummagicnumber = 13591409;
mpf_class upmultmagicnumber = 545140134;
mpf_class downmagicnumber = -640320;
mpf_class upfat;
mpf_class upresto;
mpf_class downfat;
mpf_class downfatexp;
mpf_class downresto; 
mpf_class up;
mpf_class down;
mpf_class returning;

  
using namespace std;

mpf_class iteration(int k){
  upfat = (fatorial( 6 * k ));
  upresto = upmultmagicnumber*k;
  upresto = upresto + upsummagicnumber;
  downfat = fatorial(3*k);
  mpf_pow_ui(tmp, fatorial(k).get_mpf_t(), 3);
  downfatexp = mpf_class(tmp);
  mpf_pow_ui(tmp, downmagicnumber.get_mpf_t(), 3*k);
  downresto = mpf_class(tmp); 
  up = upfat * upresto;
  down = (downfat * downfatexp);
  down = down* downresto;
  returning = up/down;
  return returning;
}


int main(int argc, char **argv){
  int i;
  mpf_class mynotpi= 0;
  mpf_init(tmp);
 
  mpf_set_default_prec(128);
  if (/*sequencial*/1)
    omp_set_num_threads(1);
  else
    omp_set_num_threads(omp_get_num_procs());
  //#pragma omp parallel private()
  for(i = 0; i < 15000; i++){
    mynotpi = mynotpi + iteration(i);
  }
  mynotpi =  leftside/mynotpi;
  //std::cout << mynotpi << "\n";
  mpf_out_str(stdout, 10, 0, mynotpi.get_mpf_t());
  return 0;
}

