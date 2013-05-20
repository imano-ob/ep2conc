#include <stdio.h>
#include <omp.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>

#include "fatorial.h"

mpf_class leftside = 426880 * sqrt(10005);

using namespace std;

mpf_class iteration(int k){
  mpf_t tmp;
  mpf_init(tmp);
  mpf_class upsummagicnumber = 13591409;
  mpf_class upmultmagicnumber = 545140134;
  mpf_class downmagicnumber = -640320;
  cout << upsummagicnumber << "\n";
  cout << upmultmagicnumber << "\n";
  cout << downmagicnumber << "\n";
  mpf_class upfat = (fatorial( 6 * k ));
  cout << upfat << " upfat\n";
  cout << "iprest\n";
  mpf_class upresto = upmultmagicnumber*k;
  cout << upresto << "\n";
  upresto = upresto + upsummagicnumber;
  cout << "pizza\n";
  cout << upresto << " uprestod=fin\n";
  mpf_class downfat = fatorial(3*k);
  cout << downfat << " downdat\n";
  mpf_pow_ui(tmp, fatorial(k).get_mpf_t(), 3);
  mpf_class downfatexp = mpf_class(tmp);
  cout << "a\n";
  mpf_pow_ui(tmp, downmagicnumber.get_mpf_t(), 3*k);
  mpf_class downresto = mpf_class(tmp); 
  cout << downresto << " ihnis\n";
  mpf_class up = upfat * upresto;
  mpf_class down = (downfat * downfatexp);
  down = down* downresto;
  cout << up << "\n";
  cout << down << "\n";
  cout << "moo\n";
  mpf_class returning = up/down;
  cout << "cow\n";
  return returning;
}


int main(int argc, char **argv){
  int i;
  mpf_class mynotpi= 0;
  if (/*sequencial*/1)
    omp_set_num_threads(1);
  else
    omp_set_num_threads(omp_get_num_procs());
  //  fatinit(100);
  //#pragma omp parallel private()
  for(i = 0; i < 1; i++){
    cout << "pi\n";
    mynotpi = mynotpi + iteration(i);
  }
  mynotpi =  leftside/mynotpi;
  std::cout << mynotpi << "\n";
  return 0;
}

