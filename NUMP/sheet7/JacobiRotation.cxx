#include "JacobiRotation.h"
#include "iostream"

using namespace std;

#define FBC
// #define PBC

using vec    = vector<double>;         // vector
using matrix = vector<vec>;            // matrix

void JacobiRotation(matrix& A, matrix& Q){
  int size = A.size();
  vec A_hk(size);
  vec A_hl(size);

  while(true){
    double S = 0;

    // #pragma omp parallel for
    for (int k = 0; k < size; k++) {
      for (int l = 0; l < k; l++) {
        S += pow(A[k][l], 2.0);
      }
    }
    S *= 2.;
    if(S <= epsilon){
      break;
    }

    // #pragma omp parallel for
    for (int k = 0; k < size; k++) {
      for (int l = 0; l < k; l++) {
        // beta
        double beta = 0.5 * (A[l][l] - A[k][k]) / A[k][l];
        // t
        double t = 1.0 / (fabs(beta) + sqrt(pow(beta, 2.0) + 1.0));
        if(beta < 0.0){
          t = -t;
        }
        // c, s
        double c = 1.0 / sqrt(pow(t, 2.0) + 1.0);
        double s = t * c;
        // rho
        double rho = s / (1.0 + c);
        // Jacobi rotation
        // matrix A
        double A_kk = A[k][k] - t * A[k][l];
        double A_ll = A[l][l] + t * A[k][l];
        vec A_hk(size);
        vec A_rq(size);
        for(int h = 0; h < size; h++){
          if(h != k && h != l){
            A_hk[h] = A[h][k] - s * (A[h][l] + rho * A[h][k]);
            A_rq[h] = A[h][l] + s * (A[h][k] - rho * A[h][l]);
          }
        }
        A[k][l] = 0.0;
        A[l][k] = 0.0;
        A[k][k] = A_kk;
        A[l][l] = A_ll;
        for(int h = 0; h < size; h++){
        if(h != k && h != l){
            A[h][k] = A_hk[h];
            A[k][h] = A_hk[h];
            A[h][l] = A_rq[h];
            A[l][h] = A_rq[h];
          }
        }
        // eigenvector matrix
        vec Q_hk(size);
        vec Q_hl(size);
        for(int h = 0; h < size; h++){
          Q_hk[h] = Q[h][k] - s * (Q[h][l] + rho * Q[h][k]);
          Q_hl[h] = Q[h][l] + s * (Q[h][k] - rho * Q[h][l]);
        }
        for(int h = 0; h < size; h++){
          Q[h][k] = Q_hk[h];
          Q[h][l] = Q_hl[h];
        }
      }
    }
  }
}

int main(void){
  int N1 = 4;
  int N2 = 4;
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
  // initialize matrix A and B with free BC
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



  JacobiRotation(A,B);
  for (int i = 0; i < N; i++) {
    cout << "eigenvalue " << i+1 << " = " << A[i][i] << endl;
    for (int k = 0; k < N; k++) {
      if(k == 0){
        cout << "Eigenvector: " << endl << "(";
      }
      cout << B[i][k] << "; ";
      if(k == N-1){
        cout << ")" << endl;
      }
    }
  }
  for (int i = 0; i < N; i++) {
    for (int k = 0; k < N; k++) {

    }
  }
  return 0;
}
