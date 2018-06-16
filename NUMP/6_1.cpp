#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

// #define oneD
#define twoD

const int MAX_ITER = 1.0e4;            // maximum number of iterations
const double NEARZERO = 1.0e-10;       // interpretation of "zero"
const double error_margin = 1.0e-10;   // min error
const int N = 50;                     // Number of lattive points in 1D > 0
const int n = 2*N + 1;                 // Number of lattice points in 1D
const double R = 10;                   // radius of the sphere/ whatever
const double a = 2.*R/(double)n;       // gap between to lattice points

using vec    = vector<double>;         // vector
using matrix = vector<vec>;            // matrix

////////////////////////////////////////////////////////////////////////////////
// function declaration (and definition)

// calculate vector addition
vec vec_plus_vec(vec &a, vec &b){
  vec x(a.size());
  for (int i = 0; i < a.size(); i++) {
    x[i] = a[i] + b[i];
  }
  return x;
}

// calculate vector substraction
vec vec_minus_vec(vec &a, vec &b){
  vec x(a.size());
  for (int i = 0; i < a.size(); i++) {
    x[i] = a[i] - b[i];
  }
  return x;
}

// calculate vector a times scalar s
vec vec_times_scalar(vec &a, double s){
  vec x(a.size());
  for (int i = 0; i < a.size(); i++) {
    x[i] = s*a[i];
  }
  return x;
}

// calculate inner product of two vectors a and b
double vec_times_vec(vec &a, vec &b){
  double x = inner_product(a.begin(), a.end(), b.begin(), 0.0);
  return x;
}

// calculate matrix A times vector y
vec matrix_times_vec(matrix &A, vec &y){
  int size = y.size();
  vec x(size);

  for (int i = 0; i < size; i++) {
    x[i] = inner_product(A[i].begin(), A[i].end(), y.begin(), 0.0);
  }
  return x;
}

// conjugate gradient method
vec conjugate_gradient_method(matrix A, vec b){
  double alpha, beta;
  int k = 0;

  // obtaining the dimnesion this is done with
  int dim = b.size();
  vec x_new(dim);
  vec r_new(dim);
  vec p_new(dim);
  vec temp(dim);

  // starting x-vector, only 0, can be changed to only 1 or whatever
  vec x(dim, 0.0);

  //calculating A * x_0
  vec w = matrix_times_vec(A,x);

  // starting r
  vec r(dim);
  for(int i = 0; i < dim; i++){
    r[i] = b[i] - w[i];
  }

  // starting p
  vec p = r;
  //calculating A * p_0
  vec z = matrix_times_vec(A,p);

  // actual calculation
  for (k = 0; k < MAX_ITER; k++) {
    alpha = vec_times_vec(r,r)/max(vec_times_vec(p,z), NEARZERO);

    temp = vec_times_scalar(p, alpha);
    x_new = vec_plus_vec(x, temp);

    temp = vec_times_scalar(z, alpha);
    r_new = vec_minus_vec(r, temp);
    if(sqrt(vec_times_vec(r_new, r_new)) < error_margin){
      break;
    }
    beta = vec_times_vec(r_new,r_new)/max(vec_times_vec(r,r),NEARZERO);
    temp = vec_times_scalar(p, beta);
    p_new = vec_plus_vec(r_new, temp);
    x = x_new;
    p = p_new;
    r = r_new;
    z = matrix_times_vec(A,p);
    if(k%10 == 0){
      printf("k = %i\n", k);
    }
  }
  printf("Anzahl Iterationen: %i\n", k);
  return x_new;
}

////////////////////////////////////////////////////////////////////////////////

int main()
{
  int i1, i2, i3;

  #ifdef oneD
  vec b(n, 0.0);
  matrix A(n);
  for (int i = 0 ; i < n ; i++)
   A[i].resize(n,0);
   // generate matrix A and vector b
   for(i1 = 0; i1 < n; i1++){
     for(i2 = 0; i2 < n; i2++){
       // diagonal elements of A
       if(i2 == i1){
         A[i1][i2] = +2./pow(a,2);
       }
       // ofdiagonal elements of A
       else if (i2 == i1-1 || i2 == i1 +1){
           A[i1][i2] = -1./pow(a,2);
       }
     }
     // place of the charged particle
     if(i1 == int(n)/2){
       b[i1] = -1./a;
     }
   }
  #endif

  #ifdef twoD
  vec b(n*n, 0.0);
  matrix A(n*n);
  for (int i = 0 ; i < n*n ; i++)
   A[i].resize(n*n,0);

  // generate A and b:
  for (int i = 0; i < n*n; i++) {
    for (int j = 0; j < n*n; j++) {
      // diagonal
      if(i == j){
        A[i][j] = +4./(a*a); // changed - to +
      }
      // one above and below diagonal for rest of d^2/dx^2
      else if(i+1 == j && i%n != 0){
        A[i][j] = -1./(a*a);  // changed + to -
      }
      else if(i-1 == j && j%n != 0){
        A[i][j] = -1./(a*a);  // changed + to -
      }
      // two of diagonals for rest of d^2/dy^2
      else if(i == j+n || i == j-n){
        A[i][j] = -1./(a*a);  // changed + to -
      }
    }
    // b as delta distribution or so
    // at (0,0)
    if(i == (n*n)/2){
      b[i] = -1./(a); // normalization needs to be checked!
    }
  }
  #endif

   vec x = conjugate_gradient_method(A, b);

  #ifdef oneD
   // output
   ofstream myfile;
   myfile.open("PoissonEq1D.txt");
   for(i1 = 0; i1 < x.size(); i1++){
     myfile << (i1-(int)x.size()/2)*a << "\t" << x[i1] << endl;
   }
   myfile.close();
  #endif

  #ifdef twoD
  // output
  ofstream myfile2D;
  myfile2D.open("PoissonEq2D.txt");
  for(i1 = 0; i1 < n*n; i1++){
    myfile2D << ((i1%n)-(int)n/2)*a << "\t" << ((i1/n)-(int)n/2)*a << "\t" << x[i1] << endl;
  }
  myfile2D.close();
  #endif
}
