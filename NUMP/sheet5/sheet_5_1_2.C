#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "header.h"

// size of A, b and so on
const long int N = 15;
const long int n = 2*N + 1;
const double R = 10;
// matrix A (elements will be modified during computation)
double A[n*n][n*n];
// vector (elements will be modified during computation)
double b[n*n];
// solution
double x[n*n];
// permutation of rows due to pivoting
int p[n*n];
// factor a
const double a = (double)(2.*R)/(double)n;
// **********
// print A | b
void Print(){
  int i, j;
  for(i = 0; i < n*n; i++){
    for(j = 0; j < n*n; j++){
      fprintf(stdout, "%+5.2lf ", A[p[i]][j]);
    }
    fprintf(stdout, "| %+5.2lf\n", b[p[i]]);
  }
  fprintf(stdout, "\n");
}
// **********


void sheet_5_1_2(void){
  long int i, j, k;
  double d1, d2, d3;
  srand((unsigned int)time(NULL));

  // generate A and b:
  for (i = 0; i < n*n; i++) {
    for (j = 0; j < n*n; j++) {
      // diagonal
      if(i == j){
        A[i][j] = -4./(a*a);
      }
      // one above and below diagonal for rest of d^2/dx^2
      else if(i+1 == j && i%n != 0){
        A[i][j] = +1./(a*a);
      }
      else if(i-1 == j && j%n != 0){
        A[i][j] = +1./(a*a);
      }
      // two of diagonals for rest of d^2/dy^2
      else if(i == j+n || i == j-n){
        A[i][j] = +1./(a*a);
      }
      else{
        A[i][j] = 0;
      }
    }
    // b as delta distribution or so
    // at (0,0)
    if(i == (n*n)/2){
      b[i] = -1./(a); // normalization needs to be checked!
    }
    else{
      b[i] = 0;
    }
  }

  //////////////////////////////////////////////////////////////////////////////

  // initialize permutation of rows
  for(i = 0; i < n*n; i++){
    p[i] = i;
  }
  // Print();
  // *****
  // copy matrix A und vektor b (needed at the end to investigate roundoff errors)
  double A_org[n*n][n*n];
  double b_org[n*n];
  for(i = 0; i < n*n; i++){
    for(j = 0; j < n*n; j++){
      A_org[i][j] = A[i][j];
    }
    b_org[i] = b[i];
  }
  // *****
  // elimination
  // store maximum of each row of A, before elements are modified
  double A_ij_max[n*n];
  for(i = 0; i < n*n; i++){
    A_ij_max[i] = fabs(A[i][0]);
    for(j = 1; j < n*n; j++){
      if(fabs(A[i][j]) > A_ij_max[i]){
        A_ij_max[i] = fabs(A[i][j]);
      }
    }
  }
  for(i = 0; i < n*n-1; i++){
    // n*n-1 elimination steps
    // determine "optimal row" according to pivoting strategy
    int index = i;
    d1 = fabs(A[p[i]][i]) / A_ij_max[p[i]];
    for(j = i+1; j < n*n; j++){
      d2 = fabs(A[p[j]][i]) / A_ij_max[p[j]];
      if(d2 > d1){
        index = j;
      }
    }
    j = p[i];
    p[i] = p[index];
    p[index] = j;
    // ***
    for(j = i+1; j < n*n; j++){
      // for all remaining rows ...
      d1 = A[p[j]][i] / A[p[i]][i];
      A[p[j]][i] = 0.0;
      for(k = i+1; k < n*n; k++){
        A[p[j]][k] -= d1 * A[p[i]][k];
      }
      b[p[j]] -= d1 * b[p[i]];
    }
    // Print();
  }
  // *****
  // backward substitution
  for(i = n*n-1; i >= 0; i--){
  // Fr alle Komponenten von x ...
    x[i] = b[p[i]];
    for(j = i+1; j < n*n; j++){
      x[i] -= A[p[i]][j] * x[j];
    }
    x[i] /= A[p[i]][i];
  }
  // fprintf(stdout, "phi = ( ");
  for(i = 0; i < n*n-1; i++){
    // fprintf(stdout, "%+5.2lf ", x[i]);
  }
  // fprintf(stdout, "%+5.2lf ).\n\n", x[n*n-1]);
  // *****
  // check solution, investigate roundoff errors
  double b_check[n*n];
  for(i = 0; i < n*n; i++){
    b_check[i] = 0.0;
    for(j = 0; j < n*n; j++){
      b_check[i] += A_org[i][j] * x[j];
    }
  }
  // fprintf(stdout, "b_check = ( ");
  for(i = 0; i < n*n-1; i++){
    // fprintf(stdout, "%+5.2lf ", b_check[i]);
  }
  // fprintf(stdout, "%+5.2lf ).\n\n", b_check[n*n-1]);
  // fprintf(stdout, "b_check - b = ( ");
  // discrepancy between original b and reconstructed b for each element
  for(i = 0; i < n*n-1; i++){
    // fprintf(stdout, "%+.1e ", b_check[i] - b_org[i]);
  }
  // fprintf(stdout, "%+.1e ).\n\n", b_check[n*n-1] - b_org[n*n-1]);
  // norm of the discrepancy
  double norm = 0.0;
  for(i = 0; i < N; i++){
    norm += pow(b_check[i] - b_org[i], 2.0);
  }
  norm = sqrt(norm);
  fprintf(stdout, "|b_check - b| = %+.5e.\n", norm);


  // output
  ofstream myfile2D;
  myfile2D.open(Form("PoissonEq2DWith%listpes.txt",n*n));
  for(i = 0; i < n*n; i++){
    myfile2D << ((i%n)-(int)n/2)*a << "\t" << ((i/n)-(int)n/2)*a << "\t" << x[i] << endl;
  }
  myfile2D.close();

  // plotting
  //***************************************************************************
  //Drawing the obtained solution:
  TCanvas* c1 = new TCanvas("c1","",1600,900);
  SetCanvasStandardSettings(c1);
  c1->SetRightMargin(0.1);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.05);

  TLegend* t1 = new TLegend(0.25,0.70,0.65,0.80);
  t1->SetFillStyle(0);
  t1->SetBorderSize(0);
  t1->SetTextFont(43);
  t1->SetTextSize(40);

  TGraph2D* PoissonEq = new TGraph2D(Form("PoissonEq2DWith%listpes.txt",n*n));
  PoissonEq->SetTitle("; #hat{x};#hat{y}; #phi(#hat{x},#hat{y})");
  PoissonEq->SetMarkerStyle(20);
  PoissonEq->SetMarkerSize(1);
  PoissonEq->SetMarkerColor(kBlue);
  PoissonEq->SetLineColor(kBlack);
  PoissonEq->SetLineWidth(1);


  c1->cd();
  PoissonEq->Draw("surf1");
  t1->AddEntry(PoissonEq, "potential #hat{#phi} (#hat{x},#hat{y}) for the poisson eq.", "p");
  t1->Draw("SAME");
  c1->Update();
  c1->SaveAs(Form("sheet5/2D_PoissonEqWith%listpes.png",n*n));

  t1->Delete();
  PoissonEq->Delete();
  delete c1;
}
