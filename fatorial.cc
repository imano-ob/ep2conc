#include "fatorial.h"

#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>
#include <gmpxx.h>
#include <iostream>
#include <semaphore.h>

#define SIZE 1000

using namespace std;

mpf_class precalc[SIZE];
int cur_n[SIZE];
sem_t lock[SIZE];

void fatseminit(){
  int i;
  for(i = 0; i < SIZE; i++)
    sem_init(&lock[i], 0, 1);
}

mpf_class fatorial(int n){
  cout << "oi\n";
  sem_wait(&lock[n%SIZE]);
  if (n == 0){
    precalc[n] = 1;
    cur_n[n] = n;
  }
  else if (cur_n[n%SIZE] != n){
    precalc[n%SIZE] =  fatorial(n-1) * n;
    cur_n[n%SIZE] = n;
  }
  sem_post(&lock[n%SIZE]);
  cout << n << " " << n%SIZE << "  "<< precalc[n%SIZE] << "  deoiszn\n" ;
  return precalc[n%SIZE];
}
