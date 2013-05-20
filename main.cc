#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <semaphore.h>

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

mpf_class pi_parcial;
mpf_class parciais[100];

sem_t *arrive;

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
  int i, it, tid, num_rodadas, other, num_threads, rodada_calc = 0, rodada_barreira = 0;
  mpf_class f, soma, soma_old, diff;
  soma = 0;
  f = argv[1];
  if (argc > 2 && !strcmp("SEQUENCIAL", argv[2]))
    num_threads = 1;
  else
    num_threads = omp_get_num_procs();
  omp_set_num_threads(num_threads);
  arrive = (sem_t *)malloc(num_threads * sizeof *arrive);
  for (i = 0; i < num_threads; i++)
    sem_init(&arrive[i], 0, 0);
#pragma omp parallel private(upfat, upresto, downfat, downfatexp, downresto, up, down, returning, tid, it, rodada_calc, rodada_barreira, other, tmp)
  {
    mpf_init(tmp);
    tid = omp_get_thread_num();
    num_rodadas = ilogb(num_threads);
    if (num_threads > 1 && ilogb(num_threads - 1) == num_rodadas)
      num_rodadas++;
    do{
      it = rodada_calc * num_threads + tid;
      other = (int)(exp2(rodada_barreira) + tid) % num_threads;
      rodada_barreira = (rodada_barreira + 1) % num_rodadas;
      parciais[it] = iteration(it);
      sem_post(&arrive[tid]);
      sem_wait(&arrive[other]);
      rodada_calc++;
#pragma omp critical
      {
	soma_old = soma;
	soma = soma + parciais[it];
	diff = leftside / parciais[it];
      }
      
    }while(cmp(diff, f) > 1);
  }
  //mpf_out_str(stdout, 10, 0, mynotpi.get_mpf_t());
  return 0;
}

