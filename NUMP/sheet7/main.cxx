#include "JacobiRotation.h"
#include "GetSolution.h"
#include <iostream>
#include <fstream>

using namespace std;

#define FBC
// #define PBC

using vec    = vector<double>;         // vector
using matrix = vector<vec>;            // matrix
double t = 0;                          // initial time
double dt = 0.01;                      //stepsize in t

int main(void){
  int N1 = 7;
  int N2 = 7;
  int N = N1*N2;
  matrix A(N);
  matrix B(N);
  for (int i = 0; i < N; i++) {
    A[i].resize(N,0);
    B[i].resize(N,0);
  }
  #ifdef PBC
  // ========================
  // initialize matrix A and B with periodic BC
  for(int i1 = 0; i1 < N; i1++)
  {
    A[i1][i1] = 4.0;
    B[i1][i1] = 1.;
    if( (i1+1) % N1 != 0) A[i1 + 1         ][i1] = -1.0;  // right edge
    else                  A[i1 + 1 - N1    ][i1] = -1.0;
    if( i1 % N1 != 0)     A[i1 - 1         ][i1] = -1.0;  // left edge
    else                  A[i1 - 1 + N1    ][i1] = -1.0;
    if( i1 + N1 < N)      A[i1 + N1        ][i1] = -1.0;  // top edge
    else                  A[i1 % N1        ][i1] = -1.0;
    if( i1 - N1 >= 0)     A[i1 - N1        ][i1] = -1.0;  // bottom edge
    else                  A[(N2-1)*N1 + i1 ][i1] = -1.0;
  }
  #endif
  // ========================
  #ifdef FBC
  // initialize matrix A and B with free BC only of N1xN1
  for(int i1 = 0; i1 < N; i1++)
  {
    A[i1][i1] = 4.0;
    B[i1][i1] = 1.;
    if(i1 < N-1){
      A[i1+1][i1] = -1.;
      A[i1][i1+1] = -1.;
    }
    if(i1 < (N-N1)){
      A[i1+N1][i1] = -1.;
      A[i1][i1+N1] = -1.;
    }

  }
  #endif
  // ========================



  JacobiRotation(A,B);
  for (int i = 0; i < N; i++) {
    cout << "eigenvalue " << i+1 << " = " << A[i][i] << endl;
  //   for (int k = 0; k < N; k++) {
  //     if(k == 0){
  //       cout << "Eigenvector: " << endl << "(";
  //     }
  //     cout << B[i][k] << "; ";
  //     if(k == N-1){
  //       cout << ")" << endl;
  //     }
  //   }
  }

  // preparing for output
  matrix* pA = &A;
  matrix* pQ = &B;
  vec x(0,N);

  // output
  ofstream output;
  output.open("Output.txt");
  for (int i = 0; i < 3001; i++) {
    t = i*dt;
    x = GetSolution(pA, pQ, t);
    output << t << "\t" << x[48] << endl;
  }
  output.close();

  return 0;
}
