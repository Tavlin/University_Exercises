// solve
// A x = b
// using Gauss elimination with backward substitution and scaled partial pivoting
// **********
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "header.h"
// **********
// **********
// size of A, b and x
const int N = 500;
const int npo = 2*N + 1;
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
int sheet_5_1(void){
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
    // place of the charged particle
    if(i1 == int(npo)/4){
      b[i1] = 1./a;
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

  // output
  ofstream myfile;
  myfile.open(Form("PoissonEqWith%istpes.txt",npo));
  for(i1 = 0; i1 < npo; i1++){
    myfile << (i1-(int)npo/2)*a << "\t" << x[i1] << endl;
  }
  myfile.close();

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

  TGraph* PoissonEq = new TGraph(Form("PoissonEqWith%istpes.txt",npo));
  PoissonEq->SetTitle("; #hat{x}; #phi(#hat{x})");
  PoissonEq->SetMarkerStyle(20);
  PoissonEq->SetMarkerSize(1);
  PoissonEq->SetMarkerColor(kBlue);
  PoissonEq->SetLineColor(kBlack);
  PoissonEq->SetLineWidth(1);


  c1->cd();
  PoissonEq->Draw("APL");
  t1->AddEntry(PoissonEq, "potential #hat{#phi} (#hat{x}) for the poisson eq.", "p");
  t1->Draw("SAME");
  c1->Update();
  c1->SaveAs(Form("sheet5/1D_PoissonEqWith%istpes.png",npo));

  t1->Delete();
  PoissonEq->Delete();
  delete c1;
}
