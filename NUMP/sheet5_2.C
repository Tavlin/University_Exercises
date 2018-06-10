#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "header.h"

// define size
const int N = 10; //up to 400
// define A, U, L and P
double A[N][N], U[N][N], L[N][N], P[N][N], B[N][N];
// define x and y and b
double x[N], y[N], b[N], m[N], b_check[N];

// define A*x to make multiplications with P easier later
void matrix_times_vec(void){
  for(int i = 0; i < N; i++){
    for (int j = 0; j < N; j++) {
      b[i] = b[j]*P[i][j];
    }
  }
}

// main function
void sheet5_2(void){
  double u = 0;
  double l = 0;
  int p = 0;
  double d[N];
  double diff = 0;

  srand((unsigned int)time(NULL));

  //getting A, U, L and P
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      A[i][j] = exp((double)rand()/RAND_MAX*10 -5);
      U[i][j] = A[i][j];
      if(i == j){
        P[i][j] = 1;
        L[i][j] = 1;
      }
      else{
        P[i][j] = 0;
        L[i][j] = 0;
      }
    }
    b[i] = exp((double)rand()/RAND_MAX*10 -5);
  }

  // pivoting and getting real U and L as well as P I guess?
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if(i == j){
        u = U[i][j];
      }
      else if((U[i][j] > u) && (j > i)){
        u = U[i][j];
        p = j;
      }
    }
    if(i > 0){
      l = L[i-1][i];
      L[i-1][i] = L[i-1][p];
      L[i-1][p] = l;
    }
    // swap p-th row with i-th row in P
    P[p][p] = 0;
    P[p][i] = 1;

    // swap p_th row with i-th row
    for (int k = 0; k < N; k++) {
      B[i][k] = U[i][k];
      U[i][k] = U[p][k];
      U[p][k] = B[i][k];
    }
    //get multiplication factor and set L
    for (int k = i+1; k < N; k++) {
      m[k] = U[i][k]/U[i][i];
      L[i][k] = m[k];
    }
    // subtract the rest Lines in U
    for (int k = 0; k < N; k++) {
      for (int l = i+1; l < N; l++) {
        U[k][l] -= m[l]*U[k][0];
      }
    }
  }

  // now change b with multiplication by P
  matrix_times_vec();

  //calculate y
  for (int j = 0; j < N; j++) {
    int sum = 0;
    for (int k = 0; k < j-1; k++) {
       sum += L[j][k]*y[k];
    }
    y[j] =  b[j] - sum;
  }

  //calculate x now
  for (int j = N-1; j >= 0; j--) {
    int sum = 0;
    for (int k = j+1; k < N-1; k++) {
       sum += U[j][k]*x[k];
    }
    x[j] =  (b[j] - sum)/U[j][j];
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      b_check[i] = x[j]*A[i][j];
    }
  }
  for (int i = 0; i < N; i++) {
    // cout << "| " << x[i] << " |" << endl;
    diff += pow(x[i] - b_check[i],2.);
  }
  cout << "b- b_check =  " << sqrt(diff) << endl;
}
