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


mpf_class pi_parcial;
mpf_class parciais[100];

sem_t **arrive;

using namespace std;

mpf_class iteration(int k){

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
  mpf_class tmpfat;
  mpf_t tmp;

  mpf_init(tmp);
 
  upfat = (fatorial( 6 * k ));
  upresto = upmultmagicnumber*k;
  upresto = upresto + upsummagicnumber;
  downfat = fatorial(3*k);
  tmpfat = fatorial(k);
  mpf_pow_ui(tmp, tmpfat.get_mpf_t(), 3);
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
  int i, j, it, tid, num_rodadas, other, num_threads, rodada_calc = 0, rodada_barreira = 0, p = 0, tmpexp, *rodada;
  mpf_class f, soma, mypi, mypiold, diff;
  bool dummy = false, done = false;
  fatseminit();
  soma = 0;
  mypi = 0;
  f = argv[1];
  if (argc > 2 && !strcmp("SEQUENCIAL", argv[2]))
    num_threads = 1;
  else{
    num_threads = omp_get_num_procs();
    if (num_threads % 2){
      dummy = true;
      num_threads++;
    }
  }
  num_rodadas = ilogb(num_threads);
  if(num_rodadas == 0) num_rodadas = 1;
  if (num_threads > 1 && ilogb(num_threads - 1) == num_rodadas){
    num_rodadas++;
  }
  
  rodada = (int *)malloc(num_threads * sizeof *rodada);
  omp_set_num_threads(num_threads);
  arrive = (sem_t **)malloc(num_threads * sizeof *arrive);
  for (i=0; i<num_threads; i++){
    arrive[i] = (sem_t *)malloc(num_rodadas * sizeof *arrive[i]);
    for(j=0; j < num_rodadas; j++)
      sem_init(&arrive[i][j], 0, 0);
  }
#pragma omp parallel private(diff, tid, it, rodada_calc, rodada_barreira, other, tmpexp,  i, j), shared(soma, mypi, mypiold, p, num_threads, num_rodadas, rodada, parciais)
  {
    i = 0;
    rodada_calc = 0;
#pragma omp atomic capture
    {tid = p; p++;}
    rodada[tid] = 0;
    rodada_barreira = 0;
    do{
      it = rodada_calc * num_threads + tid;
      tmpexp = (int)(exp2(rodada_barreira));
      other = ((tid & tmpexp) != 0 ? (tid - tmpexp): (tid + tmpexp))  % num_threads;
      rodada_barreira = (rodada_barreira + 1) % num_rodadas;
      if (dummy == false || tid != 0){
	parciais[it] = iteration(it);
#pragma omp critical
	{ 
	  soma = soma + parciais[it];
	  mypiold = mypi;
	  mypi = leftside / soma;
	  diff = mypi - mypiold;
	}
#pragma omp critical	
	if(cmp(diff, f) <=0 ){
	    done = true;
	}
      }
      sem_post(&arrive[tid][rodada[tid]]);
      sem_wait(&arrive[other][rodada[tid]]);
      
      rodada_calc++;
      rodada[tid] += 1;
      i++;
    }while(!(done));
    for(j = 0; j < num_rodadas; j++)
      sem_post(&arrive[tid][j]);
  }
  mpf_out_str(stdout, 10, 0, mypi.get_mpf_t());
  cout << "\n";
  return 0;
}

