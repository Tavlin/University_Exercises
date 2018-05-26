#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "header.h"
// **********
// physics parameters and functions
// **********
// y = (\psi , \phi , E)
// f = (\phi , (x^2+x^4-E) \psi , 0)
const int N = 3; // number of components of \vec{y} and \vec{f}
double y_0[N] = { 0.0 , 1.0 , 0.0 }; // Anfangsbedingungen y(L/a=0).
// function computing f(y(t),t) * tau
void f_times_tau(double *y_t, double x, double *f_times_tau_, double tau){
  if(N != 3){
    fprintf(stderr, "Error: N != 3!\n");
    exit(EXIT_FAILURE);
  }
  f_times_tau_[0] = y_t[1] * tau;
  f_times_tau_[1] = (pow(x,2.) + 0.1*pow(x,4.)-y_t[2]) * y_t[0] * tau;
  f_times_tau_[2] = 0.0;
}
// **********
// RK parameters
// **********
// number of steps
const int num_steps = 1.e4;
// compute trajectory (= wave function) from t = x_0 to T = t_1
const double x_0 = 6.0; // = L/a
const double x_1 = 0.0; // = 0 needed for the Newton Raphson method to be able to calculate E
double tau = (x_1 - x_0) / (double)num_steps; // step size
double h = 0.000001; // finite difference for numerical derivative
double dE_min = 0.0000001; // Newton-Raphson accuracy
// **********

// RK step (2nd order), step size tau
void RK_step(double *y_t, double x, double *y_t_plus_tau, double tau){
  int i1;
  // *****
  // k1 = f(y(t),t) * tau
  double k1[N];
  f_times_tau(y_t, x, k1, tau);
  // *****
  // k2 = f(y(t)+(1/2)*k1 , t+(1/2)*tau) * tau
  double y_k1[N];
  for(i1 = 0; i1 < N; i1++){
    y_k1[i1] = y_t[i1] + 0.5*k1[i1];
  }
  double k2[N];
  f_times_tau(y_k1, x + 0.5*tau, k2, tau);
  // *****
  // k3 = f(y(t)+(1/2)*k2 , t+(1/2)*tau) * tau
  double y_k2[N];
  for(i1 = 0; i1 < N; i1++){
    y_k2[i1] = y_t[i1] + 0.5*k2[i1];
  }
  double k3[N];
  f_times_tau(y_k2, x + 0.5*tau, k3, tau);
  // *****
  // k4 = f(y(t)+k3 , t+(1/2)*tau) * tau
  double y_k3[N];
  for(i1 = 0; i1 < N; i1++){
    y_k3[i1] = y_t[i1] + k3[i1];
  }
  double k4[N];
  f_times_tau(y_k3, x + tau, k4, tau);
  // *****
  for(i1 = 0; i1 < N; i1++){
    y_t_plus_tau[i1] = y_t[i1] + 1./6. * (k1[i1] + 2*k2[i1] + 2*k3[i1] + k4[i1]);
  }
}
// **********
// RK computation of the trajectory (= wave function)
double x[num_steps+1]; // discretized time
double y[num_steps+1][N]; // discretized trajectories

// RK function which returns psi for Newton Raphso for odd parity
double RK_1(bool output = false){
  double d1;
  int i1, i2;
  // *****
  // RK steps
  for(i1 = 0; i1 < num_steps; i1++){
    // y(t) --> y(t+\tau)
    RK_step(y[i1], x[i1], y[i1+1], tau);
    x[i1+1] = x[i1] + tau;
  }
  // *****
  if(output == true){

    // output
    ofstream myfile;
    myfile.open("QM_HO_Even.txt");
    for(i1 = 0; i1 <= num_steps; i1++){
      myfile << x[i1] << "\t" << y[i1][0] << endl;
      // cout << x[i1] << "\t" << y[i1][0] << endl;
    }
    myfile.close();
  }
  // *****
  return y[num_steps][0];
}

// RK which returns phi for Newton Raphso for even parity
double RK_0(bool output = false){
  double d1;
  int i1, i2;
  // *****
  // RK steps
  for(i1 = 0; i1 < num_steps; i1++){
    // y(t) --> y(t+\tau)
    RK_step(y[i1], x[i1], y[i1+1], tau);
    x[i1+1] = x[i1] + tau;
  }
  // *****
  if(output == true){

    // output
    ofstream myfile;
    myfile.open("QM_HO_Even.txt");
    for(i1 = 0; i1 <= num_steps; i1++){
      myfile << x[i1] << "\t" << y[i1][0] << endl;
      // cout << x[i1] << "\t" << y[i1][0] << endl;
    }
    myfile.close();
  }
  // *****
  return y[num_steps][1]; // to return phi for Newton Raphson method
}
// **********
void sheet_4_1(void){
  int i1;
  int mode = 1; // 0 = even, 1 == odd
  // *****
  // initialize trajectories with initial conditions
    x[0] = x_0;
    for(i1 = 0; i1 < N; i1++){
      y[0][i1] = y_0[i1];
    }

  // **********
  // shooting method
  // **********
  // /*
  // intial condition (energy)
  double E = 1; // vary this shit and see if something reasonable comes out
  // double E = 40.0;
  // double E = 90.0;
  fprintf(stderr, "E_num = %+10.6lf\n", E);
  if(mode == 0){
    while(1){
      // change initial condition (energy)
      y[0][N-1] = E;
      // RK computation of the trajectory (= wave function)
      double phi_1_E = RK_0(false);
      // *****
      // numerical derivative (d/dh) phi(x=0)
      y[0][N-1] = E-h;
      double phi_1_E_mi_h = RK_0(false);
      y[0][N-1] = E+h;
      double phi_1_E_pl_h = RK_0(false);
      double dphi_1_E = (phi_1_E_pl_h - phi_1_E_mi_h) / (2.0 * h);
      // *****
      // Newton-Raphson step
      double dE = (-1)* phi_1_E / dphi_1_E;
      if(fabs(dE) < dE_min){
        break;
      }
      E = E + dE;
      fprintf(stderr, "E_num = %+10.6lf\n", E);
    }
  }

  if(mode == 1){
    while(1){
      // change initial condition (energy)
      y[0][N-1] = E;
      // RK computation of the trajectory (= wave function)
      double psi_1_E = RK_1(false);
      // *****
      // numerical derivative (d/dh) psi(x=0)
      y[0][N-1] = E-h;
      double psi_1_E_mi_h = RK_1(false);
      y[0][N-1] = E+h;
      double psi_1_E_pl_h = RK_1(false);
      double dpsi_1_E = (psi_1_E_pl_h - psi_1_E_mi_h) / (2.0 * h);
      // *****
      // Newton-Raphson step
      double dE =  (-1)* psi_1_E / dpsi_1_E;
      if(fabs(dE) < dE_min){
        break;
      }
      E = E + dE;
      fprintf(stderr, "E_num = %+10.6lf\n", E);
    }
  }
  // output
  if(mode == 1){
    RK_0(true);
  }
  if(mode == 0){
    RK_0(true);
  }

  //Drawing the obtained solution:
  TCanvas* c1 = new TCanvas("c1","",1600,900);
  SetCanvasStandardSettings(c1);
  c1->SetRightMargin(0.1);
  c1->SetLeftMargin(0.1);
  c1->SetTopMargin(0.05);

  TLegend* t1 = new TLegend(0.35,0.00,0.75,0.10);
  t1->SetFillStyle(0);
  t1->SetBorderSize(0);
  t1->SetTextFont(43);
  t1->SetTextSize(40);

  TGraph* QM_HO_Even = new TGraph("QM_HO_Even.txt");
  QM_HO_Even->SetTitle("; #hat{x}; #psi(#hat{x})");
  QM_HO_Even->SetMarkerStyle(20);
  QM_HO_Even->SetMarkerSize(1);
  QM_HO_Even->SetMarkerColor(kBlue);
  QM_HO_Even->SetLineColor(kBlack);
  QM_HO_Even->SetLineWidth(1);


  c1->cd();
  QM_HO_Even->Draw("APL");
  // t1->AddEntry(gpendulum2D, "angle #phi (t) for a pendulum", "p");
  // t1->Draw("SAME");
  c1->Update();
  if(mode == 1){
    c1->SaveAs(Form("QM_with_Potential/QM_HO_Odd.png"));
  }
  if(mode == 0){
    c1->SaveAs(Form("QM_with_Potential/QM_HO_Even.png"));
  }

  t1->Delete();
  QM_HO_Even->Delete();
  delete c1;
}
