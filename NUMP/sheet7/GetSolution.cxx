#include "GetSolution.h"
using namespace std;

using vec    = vector<double>;         // vector
using matrix = vector<vec>;            // matrix

vec GetSolution(matrix* A ,matrix* Q, double t){
  int size = (*Q)[0].size();

  int N = sqrt(size);

  vec omega(size,0);
  vec x(size,0);

  //============================================================================
  // getting all the eigenvalues from matrix A
  for (int i = 0; i < size; i++) {
    omega[i] = (*A)[i][i];
  }
//==============================================================================
for (int j = 0; j < size ; j++) {
  double sum = 0;
  for (int n1 = 0; n1 < N; n1++) {
    for (int n2 = 0; n2 < N; n2++) {
      sum += (*Q)[(n1*N)+n2][j]*(*Q)[n1*N+n2][0]*cos(sqrt(omega[n2+(n1*N)])*t);
    }
  }
  x[j] = sum;
}


  return x;
}
