// compute all eigenvalues lambda and eigenvectors v of a real symmetrix matrix A,
// A v = lambda v ,
// using the Jacobi method
// **********
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// **********
const int N = 3; // size of A
// real symmetric matrix; will be overwritten; diagonal elements will correspond to eigenvalues
double A[N][N];
// matrix of eigenvectors (product of Jacobi rotations); columns will correspond to eigenvectors
double V[N][N];
const double epsilon = 1.0e-20; // stop iterations, if S < epsilion
// **********
int main(int argc, char **argv){
  FILE *file1;
  int i1, i2, i3;
  char string1[1000];
  // *****
  // initialize matrix A
  for(i1 = 0; i1 < N; i1++){
    for(i2 = 0; i2 < N; i2++){
      A[i1][i2] = 0.0;
    }
  }
  for(i1 = 0; i1 < N-1; i1++){
    A[i1 ][i1 ] += 1.0;
    A[i1 ][i1+1] -= 1.0;
    A[i1+1][i1 ] -= 1.0;
    A[i1+1][i1+1] += 1.0;
  }
  // /*
  for(i1 = 0; i1 < N; i1++){
    for(i2 = 0; i2 < N; i2++){
      fprintf(stderr, "%+4.2lf ", A[i1][i2]);
    }
    fprintf(stderr, "\n");
  }
  // */
  // initialize eigenvector matrix
  for(i1 = 0; i1 < N; i1++){
    for(i2 = 0; i2 < N; i2++){
      if(i1 == i2) V[i1][i2] = 1.0;

      else V[i1][i2] = 0.0;
    }
  }
  // *****
  // Jacobi method
  int ctr = 0;
  while(1){
    // deviation from diagonal matrix
    double S = 0.0;
    for(i1 = 0; i1 < N; i1++){
      for(i2 = 0; i2 < i1; i2++){
        S += pow(A[i1][i2], 2.0);
      }
    }
    S *= 2.0;
    fprintf(stderr, "S = %.5e.\n", S);
    if(S <= epsilon){
      break;
    }
    // *****
    ctr++;
    fprintf(stderr, "sweep %4d ...\n", ctr);
    // sweep over all off-diagonal elements ...
    for(i1 = 0; i1 < N; i1++){
      for(i2 = 0; i2 < i1; i2++){
        if(fabs(A[i1][i2]) < epsilon / (double)(N*N)){
        // avoid divison by "almost 0.0"
          continue;
        }
        // theta
        double theta = 0.5 * (A[i2][i2] - A[i1][i1]) / A[i1][i2];
        // t
        double t = 1.0 / (fabs(theta) + sqrt(pow(theta, 2.0) + 1.0));
        if(theta < 0.0){
          t = -t;
        }
        // c, s
        double c = 1.0 / sqrt(pow(t, 2.0) + 1.0);
        double s = t * c;
        // tau
        double tau = s / (1.0 + c);
        // Jacobi rotation
        // matrix A
        double A_pp = A[i1][i1] - t * A[i1][i2];
        double A_qq = A[i2][i2] + t * A[i1][i2];
        double A_rp[N], A_rq[N];
        for(i3 = 0; i3 < N; i3++){
          if(i3 != i1 && i3 != i2){
            A_rp[i3] = A[i3][i1] - s * (A[i3][i2] + tau * A[i3][i1]);
            A_rq[i3] = A[i3][i2] + s * (A[i3][i1] - tau * A[i3][i2]);
          }
        }
        A[i1][i2] = 0.0;
        A[i2][i1] = 0.0;
        A[i1][i1] = A_pp;
        A[i2][i2] = A_qq;
        for(i3 = 0; i3 < N; i3++){
        if(i3 != i1 && i3 != i2){
            A[i3][i1] = A_rp[i3];
            A[i1][i3] = A_rp[i3];
            A[i3][i2] = A_rq[i3];
            A[i2][i3] = A_rq[i3];
          }
        }
        // eigenvector matrix
        double V_rp[N], V_rq[N];
        for(i3 = 0; i3 < N; i3++){
          V_rp[i3] = V[i3][i1] - s * (V[i3][i2] + tau * V[i3][i1]);
          V_rq[i3] = V[i3][i2] + s * (V[i3][i1] - tau * V[i3][i2]);
        }
        for(i3 = 0; i3 < N; i3++){
          V[i3][i1] = V_rp[i3];
          V[i3][i2] = V_rq[i3];
        }
      }
    }
    // /*
    for(i1 = 0; i1 < N; i1++){
      for(i2 = 0; i2 < N; i2++){
        fprintf(stderr, "%+4.2lf ", A[i1][i2]);
      }
      fprintf(stderr, "\n");
    }
  // */
  }
  // *****
  for(i1 = 0; i1 < N; i1++){
    fprintf(stderr, "\nlambda_%02d = %+10.6lf.\n", i1, A[i1][i1]);
    fprintf(stderr, "v_%02d = ( ", i1);
    for(i2 = 0; i2 < N; i2++){
      fprintf(stderr, "%+5.2lf", V[i2][i1]);
      if(i2 < N-1) fprintf(stderr, " , ");

      else fprintf(stderr, " ).\n");
    }
  }
  // *****
  return EXIT_SUCCESS;
}
