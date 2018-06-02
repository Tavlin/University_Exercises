// solve
// A x = b
// using Gauss elimination with backward substitution and scaled partial pivoting
// **********
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// **********
// **********
// size of A, b and x
const int N = 1e2;
const int npo = N + 1;
const double R = 100;
// matrix A (elements will be modified during computation)
double A[npo][npo];
// vector (elements will be modified during computation)
double b[npo];
// solution
double x[npo];
// permutation of rows due to pivoting
int p[npo];
// factor a
const double a = 2*R/(2*N+1);
// **********
// generates a uniformly distributed random number in [min,max]
double DRand(double min, double max)
{
return min + (max-min) * ( (rand() + 0.5) / (RAND_MAX + 1.0) );
}
// **********
// print A | b
void Print(){
  int i1, i2;
  for(i1 = 0; i1 < npo; i1++){
    for(i2 = 0; i2 < npo; i2++){
      fprintf(stdout, "%+5.2lf ", A[p[i1]][i2]);
    }
    fprintf(stdout, "| %+5.2lf\n", b[p[i1]]);
  }
  fprintf(stdout, "\n");
}
// **********
int main(int argc, char **argv){
  double d1, d2, d3;
  int i1, i2, i3;
  srand((unsigned int)time(NULL));
  // *****
  // generate matrix A and vector b
  for(i1 = 0; i1 < npo; i1++){
    for(i2 = 0; i2 < npo; i2++){
      // diagonal elements of A
      if(i2 == i1){
        A[i1][i2] = -2./pow(a,2);
      }
      // ofdiagonal elements of A
      else if (i2 == i1-1 || i2 == i1 +1){
          A[i1][i2] = +1./pow(a,2);
      }
      else{
        A[i1][i2] = 0;
      }
    }
    if(i1 == (int)npo/2){
      b[i1] = 1;
    }
    else{
      b[i1] = 0;
    }

  }
  // initialize permutation of rows
  for(i1 = 0; i1 < npo; i1++){
    p[i1] = i1;
  }
  // Print();
  // *****
  // copy matrix A und vektor b (needed at the end to investigate roundoff errors)
  double A_org[npo][npo];
  double b_org[npo];
  for(i1 = 0; i1 < npo; i1++){
    for(i2 = 0; i2 < npo; i2++){
      A_org[i1][i2] = A[i1][i2];
    }
    b_org[i1] = b[i1];
  }
  // *****
  // elimination
  // store maximum of each row of A, before elements are modified
  double A_ij_max[npo];
  for(i1 = 0; i1 < npo; i1++){
    A_ij_max[i1] = fabs(A[i1][0]);
    for(i2 = 1; i2 < npo; i2++){
      if(fabs(A[i1][i2]) > A_ij_max[i1]){
        A_ij_max[i1] = fabs(A[i1][i2]);
      }
    }
  }
  for(i1 = 0; i1 < npo-1; i1++){
    // npo-1 elimination steps
    // determine "optimal row" according to pivoting strategy
    int index = i1;
    d1 = fabs(A[p[i1]][i1]) / A_ij_max[p[i1]];
    for(i2 = i1+1; i2 < npo; i2++){
      d2 = fabs(A[p[i2]][i1]) / A_ij_max[p[i2]];
      if(d2 > d1){
        index = i2;
      }
    }
    i2 = p[i1];
    p[i1] = p[index];
    p[index] = i2;
    // ***
    for(i2 = i1+1; i2 < npo; i2++){
      // for all remaining rows ...
      d1 = A[p[i2]][i1] / A[p[i1]][i1];
      A[p[i2]][i1] = 0.0;
      for(i3 = i1+1; i3 < npo; i3++){
        A[p[i2]][i3] -= d1 * A[p[i1]][i3];
      }
      b[p[i2]] -= d1 * b[p[i1]];
    }
    // Print();
  }
  // *****
  // backward substitution
  for(i1 = npo-1; i1 >= 0; i1--){
  // Fr alle Komponenten von x ...
    x[i1] = b[p[i1]];
    for(i2 = i1+1; i2 < npo; i2++){
      x[i1] -= A[p[i1]][i2] * x[i2];
    }
    x[i1] /= A[p[i1]][i1];
  }
  fprintf(stdout, "phi = ( ");
  for(i1 = 0; i1 < npo-1; i1++){
    fprintf(stdout, "%+5.2lf ", x[i1]);
  }
  fprintf(stdout, "%+5.2lf ).\n\n", x[npo-1]);
  // *****
  // check solution, investigate roundoff errors
  double b_check[npo];
  for(i1 = 0; i1 < npo; i1++){
    b_check[i1] = 0.0;
    for(i2 = 0; i2 < npo; i2++){
      b_check[i1] += A_org[i1][i2] * x[i2];
    }
  }
  fprintf(stdout, "b_check = ( ");
  for(i1 = 0; i1 < npo-1; i1++){
    fprintf(stdout, "%+5.2lf ", b_check[i1]);
  }
  fprintf(stdout, "%+5.2lf ).\n\n", b_check[npo-1]);
  fprintf(stdout, "b_check - b = ( ");
  // discrepancy between original b and reconstructed b for each element
  for(i1 = 0; i1 < npo-1; i1++){
    fprintf(stdout, "%+.1e ", b_check[i1] - b_org[i1]);
  }
  fprintf(stdout, "%+.1e ).\n\n", b_check[npo-1] - b_org[npo-1]);
  // norm of the discrepancy
  double norm = 0.0;
  for(i1 = 0; i1 < N; i1++){
    norm += pow(b_check[i1] - b_org[i1], 2.0);
  }
  norm = sqrt(norm);
  fprintf(stdout, "|b_check - b| = %+.5e.\n", norm);
  // *****
  return EXIT_SUCCESS;
}
