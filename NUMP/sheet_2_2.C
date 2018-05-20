//Pendulum with RK 4th Order
// \vec{F} = -mge_{z}
// \phi(t=0) = \phi_{0}

//EOM:
//d^{2}\phi/dt^2 = -sin(\phi)

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "header.h"

////////////////////////////////////////////////////////////////////////////////
const int N = 2; //Number of needed Dimensions
const int num_steps = 1.e4; //Number of steps
const double tau = 1.e-3; // Stepsize

double y[N][num_steps+1]; // array of 2D points forming the Trajectory
////////////////////////////////////////////////////////////////////////////////
void sheet_2_2(void){

  //Initial Conditions
  y[0][0] = M_PI/8; //starting angle
  y[1][0] = 0; //starting velocity
  /////////////////////////////////////////////////////////////////////////////
  int i,j;

  //RK 4th Order
  for (i = 1; i <= num_steps; i++) {
    double k1[N], k2[N], k3[N], k4[N];
    k1[0] = y[1][i-1]*tau;
    k1[1] = -sin(y[0][i-1])*tau;

    k2[0] = (y[1][i-1]+0.5*k1[1])*tau;
    k2[1] = (-sin(y[0][i-1]+0.5*k1[0]))*tau;

    k3[0] = (y[1][i-1]+0.5*k2[1])*tau;
    k3[1] = (-sin(y[0][i-1]+0.5*k2[0]))*tau;

    k4[0] = (y[1][i-1]+k3[1])*tau;
    k4[1] = (-sin(y[0][i-1]+k3[0]))*tau;
    for (j = 0; j < 2; j++) {
      y[j][i] = y[j][i-1] + 1./6.*(k1[j]+2*k2[j]+2*k3[j]+k4[j]);
    }
  }
  //////////////////////////////////////////////////////////////////////////////
  // output into a file
  ofstream myfile;
  myfile.open("pendulum.txt");

  for(i = 0; i <= num_steps; i++){
    double t = i * tau;
    // printf("%9.6lf %9.6lf\n", t, y[0][i]);
    myfile << t << "\t" << y[0][i] << endl;
  }
  myfile.close();

  //Drawing the obtained solution:
  TCanvas* c1 = new TCanvas("c1","",1600,900);
  SetCanvasStandardSettings(c1);
  c1->SetRightMargin(0.075);
  c1->SetLeftMargin(0.05);

  TLegend* t1 = new TLegend(0.35,0.00,0.75,0.10);
  t1->SetFillStyle(0);
  t1->SetBorderSize(0);
  t1->SetTextFont(43);
  t1->SetTextSize(40);

  TGraph* gpendulum = new TGraph("pendulum.txt");
  gpendulum->SetTitle("; #hat{t}; #hat{#phi}");
  gpendulum->SetMarkerStyle(20);
  gpendulum->SetMarkerSize(1);
  gpendulum->SetMarkerColor(kBlue);
  gpendulum->SetLineColor(kBlack);
  gpendulum->SetLineWidth(1);

  c1->cd();
  gpendulum->Draw("LPA");
  t1->AddEntry(gpendulum, "angle #phi (t) for a pendulum", "p");
  t1->Draw("SAME");
  c1->Update();
  c1->SaveAs(Form("Pendulum/Pendulum_RK4.png"));
  t1->Delete();
  gpendulum->Delete();
  delete(c1);

}
