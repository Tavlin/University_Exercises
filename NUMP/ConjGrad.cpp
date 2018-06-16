#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

const double NEARZERO = 1.0e-10;       // interpretation of "zero"
const int N = 200;
const int n = 2*N + 1;
const double R = 10;
const double a = 2.*R/(double)n;

using vec    = vector<double>;         // vector
using matrix = vector<vec>;            // matrix (=collection of (row) vectors)

// Prototypes
void print( string title, const vec &V );
void print( string title, const matrix &A );
vec matrixTimesVector( const matrix &A, const vec &V );
vec vectorCombination( double a, const vec &U, double b, const vec &V );
double innerProduct( const vec &U, const vec &V );
double vectorNorm( const vec &V );
vec conjugateGradientSolver( const matrix &A, const vec &B );


//======================================================================


int main()
{
  int i1, i2, i3;
  vec B(n, 0.0);
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
      // else{
      //   A[i1][i2] = 0;
      // }
    }
    // place of the charged particle
    if(i1 == int(n)/2){
      B[i1] = -1./a;
    }
    // else{
    //   B[i1] = 0;
    // }

  }
   // matrix A = { { 4, 1 }, { 1, 3 } };
   // vec B = { 1, 2 };

   vec X = conjugateGradientSolver( A, B );

   cout << "Solves Ax = b\n";
   // print( "\nA:", A );
   // print( "\nb:", B );
   print( "\nx:", X );
   print( "\nCheck Ax:", matrixTimesVector( A, X ) );

   // output
   ofstream myfile;
   myfile.open("PoissonEq.txt");
   for(i1 = 0; i1 < n; i1++){
     myfile << (i1-(int)n/2)*a << "\t" << X[i1] << endl;
   }
   myfile.close();
}


//======================================================================


void print( string title, const vec &V )
{
   cout << title << '\n';

   int n = V.size();
   for ( int i = 0; i < n; i++ )
   {
      double x = V[i];   if ( abs( x ) < NEARZERO ) x = 0.0;
      cout << x << '\t';
   }
   cout << '\n';
}


//======================================================================


void print( string title, const matrix &A )
{
   cout << title << '\n';

   int m = A.size(), n = A[0].size();                      // A is an m x n matrix
   for ( int i = 0; i < m; i++ )
   {
      for ( int j = 0; j < n; j++ )
      {
         double x = A[i][j];   if ( abs( x ) < NEARZERO ) x = 0.0;
         cout << x << '\t';
      }
      cout << '\n';
   }
}


//======================================================================


vec matrixTimesVector( const matrix &A, const vec &V )     // Matrix times vector
{
   int n = A.size();
   vec C( n );
   for ( int i = 0; i < n; i++ ) C[i] = innerProduct( A[i], V );
   return C;
}


//======================================================================


vec vectorCombination( double a, const vec &U, double b, const vec &V )        // Linear combination of vectors
{
   int n = U.size();
   vec W( n );
   for ( int j = 0; j < n; j++ ) W[j] = a * U[j] + b * V[j];
   return W;
}


//======================================================================


double innerProduct( const vec &U, const vec &V )          // Inner product of U and V
{
   return inner_product( U.begin(), U.end(), V.begin(), 0.0 );
}


//======================================================================


double vectorNorm( const vec &V )                          // Vector norm
{
   return sqrt( innerProduct( V, V ) );
}


//======================================================================


vec conjugateGradientSolver( const matrix &A, const vec &B )
{
   double TOLERANCE = 1.0e-10;

   int n = A.size();
   vec X( n, 0.0 );

   vec R = B;
   vec P = R;
   int k = 0;

   while ( k < n )
   {
      vec Rold = R;                                         // Store previous residual
      vec AP = matrixTimesVector( A, P );

      double alpha = innerProduct( R, R ) / max( innerProduct( P, AP ), NEARZERO );
      X = vectorCombination( 1.0, X, alpha, P );            // Next estimate of solution
      R = vectorCombination( 1.0, R, -alpha, AP );          // Residual

      if ( vectorNorm( R ) < TOLERANCE ) break;             // Convergence test

      double beta = innerProduct( R, R ) / max( innerProduct( Rold, Rold ), NEARZERO );
      P = vectorCombination( 1.0, R, beta, P );             // Next gradient
      k++;
   }

   return X;
}
