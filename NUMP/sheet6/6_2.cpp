////////////////////////////////////////////////////////////////////////////////
// Monte Carlo integration of d-dim. spheres

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <omp.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;


const int d = 2;                       // define the current dimension
const int N = 1.0e8;                   // define number of points for MC

using vec    = vector<double>;         // vector

////////////////////////////////////////////////////////////////////////////////
// declaration of the used functions

double heavyside(const int d, vec x);
double MC(const int N, const int d);

int main(void){

  // seeding rand with current time
  srand(time(NULL));

  double x = MC(N, d);
  printf("the Volume of the %i-d sphere =  %lf\n", d, x);
  return 0;
}


double heavyside(const int d, vec x){

  double temp = 0;

  // #pragma omp parallel for
  for (int i = 0; i < d; i++) {
    temp += pow(x[i],2);
  }

  if(temp > 1){
    return 0;
  }

  else{
    return 1;
  }
}
double MC(const int N, const int d){

  // define needed values and vector x
  vec x(d);
  double temp = 0;
  double avg = 0;
  double avg_sq = 0;
  double errorestimate = 0;
  double V = pow(2,d);

  // #pragma omp parallel for
  for (int i = 0; i < N; i++){
    // set random values for x
    for (int j = 0; j < d; j++) {
      x[j] =  (rand()*2.)/(double)RAND_MAX -1;
    }
    avg += heavyside(d, x);
    avg_sq += pow(heavyside(d, x),2.);
  }
  avg /= (double)N;
  avg_sq /= (double)N;

  temp = V * avg;
  errorestimate = (V* sqrt((avg_sq - pow(avg,2.))/(double)(N-1.)));

  printf("delta I = %.6lf\n", errorestimate);

  return temp;
}
