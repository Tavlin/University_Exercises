#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "header.h"

////////////////////////////////////////////////////////////////////////////////
const int N = 4; //Number of needed Dimensions
const int num_steps = 1.e3; //Number of steps
const double tau = 1.e-2; // Stepsize
const double eps = 0.5; //excentricity (for ellipse between 0 and 1!)

double y[N][num_steps+1]; // array of 2D points forming the Trajectory
double y_0[N] = {1.-eps, 0, 0, sqrt((1.+eps)/(1.-eps))};
////////////////////////////////////////////////////////////////////////////////
// define r^3 function:
double r_3(double x, double y){
  return pow(sqrt(x*x+y*y),3.);
}

////////////////////////////////////////////////////////////////////////////////
void sheet_3_1(void){
  int i,j;

  //Initial Conditions
  for (i = 0; i < N; i++) {
    y[i][0] = y_0[i];
  }

  //RK 4th Order
  for (i = 1; i <= num_steps; i++) {
    double k1[N], k2[N], k3[N], k4[N];
    k1[0] = y[2][i-1]*tau;
    k1[1] = y[3][i-1]*tau;
    k1[2] = -y[0][i-1]/r_3(y[0][i-1],y[1][i-1]) *tau;
    k1[3] = -y[1][i-1]/r_3(y[0][i-1],y[1][i-1]) *tau;

    k2[0] = (y[2][i-1]+0.5*k1[2])*tau;
    k2[1] = (y[3][i-1]+0.5*k1[3])*tau;
    k2[2] = -(y[0][i-1]+0.5*k1[0])/r_3((y[0][i-1]+0.5*k1[0]),(y[1][i-1]+0.5*k1[1]))*tau;
    k2[3] = -(y[1][i-1]+0.5*k1[1])/r_3((y[0][i-1]+0.5*k1[0]),(y[1][i-1]+0.5*k1[1]))*tau;

    k3[0] = (y[2][i-1]+0.5*k2[2])*tau;
    k3[1] = (y[3][i-1]+0.5*k2[3])*tau;
    k3[2] = -(y[0][i-1]+0.5*k2[0])/r_3((y[0][i-1]+0.5*k2[0]),(y[1][i-1]+0.5*k2[1]))*tau;
    k3[3] = -(y[1][i-1]+0.5*k2[1])/r_3((y[0][i-1]+0.5*k2[0]),(y[1][i-1]+0.5*k2[1]))*tau;

    k4[0] = (y[2][i-1]+k3[2])*tau;
    k4[1] = (y[3][i-1]+k3[3])*tau;
    k4[2] = -(y[0][i-1]+k3[0])/r_3((y[0][i-1]+k3[0]),(y[1][i-1]+k3[1]))*tau;
    k4[3] = -(y[1][i-1]+k3[1])/r_3((y[0][i-1]+k3[0]),(y[1][i-1]+k3[1]))*tau;

    for (j = 0; j < N; j++) {
      y[j][i] = y[j][i-1] + 1./6.*(k1[j]+2*k2[j]+2*k3[j]+k4[j]);
    }
  }
  //////////////////////////////////////////////////////////////////////////////
  // output into a file
  ofstream myfile;
  myfile.open("kepler2D.txt");

  for(i = 0; i <= num_steps; i++){
    double t = i * tau;
    // printf("%9.6lf %9.6lf\n", t, y[0][i]);
    myfile << y[0][i] << "\t" << y[1][i] << "\t" << t  << endl;
  }
  myfile.close();

  ofstream myfile2;
  myfile2.open("kepler.txt");

  for(i = 0; i <= num_steps; i++){
    // double t = i * tau;
    myfile2 << y[0][i] << "\t" << y[1][i]  << endl;
  }
  myfile2.close();


  //Drawing the obtained solution:
  TCanvas* c1 = new TCanvas("c1","",1600,900);
  SetCanvasStandardSettings(c1);
  c1->SetRightMargin(0.1);
  c1->SetLeftMargin(0.1);

  TLegend* t1 = new TLegend(0.35,0.00,0.75,0.10);
  t1->SetFillStyle(0);
  t1->SetBorderSize(0);
  t1->SetTextFont(43);
  t1->SetTextSize(40);

  TGraph2D* gpendulum2D = new TGraph2D("kepler2D.txt");
  gpendulum2D->SetTitle("; x; y; t");
  gpendulum2D->SetMarkerStyle(20);
  gpendulum2D->SetMarkerSize(1);
  gpendulum2D->SetMarkerColor(kBlue);
  gpendulum2D->SetLineColor(kBlack);
  gpendulum2D->SetLineWidth(1);

  TGraph* gpendulum = new TGraph("kepler.txt");
  gpendulum->SetTitle("; x; y");
  gpendulum->SetMarkerStyle(20);
  gpendulum->SetMarkerSize(1);
  gpendulum->SetMarkerColor(kBlue);
  gpendulum->SetLineColor(kBlack);
  gpendulum->SetLineWidth(1);


  c1->cd();
  gpendulum2D->Draw("P0");
  // t1->AddEntry(gpendulum2D, "angle #phi (t) for a pendulum", "p");
  // t1->Draw("SAME");
  c1->Update();
  c1->SaveAs(Form("Kepler/Kepler2D_RK4.png"));

  c1->Clear();
  gpendulum->Draw("APL");
  // t1->AddEntry(gpendulum2D, "angle #phi (t) for a pendulum", "p");
  // t1->Draw("SAME");
  c1->Update();
  c1->SaveAs(Form("Kepler/Kepler_RK4.png"));

  t1->Delete();
  gpendulum->Delete();
  gpendulum2D->Delete();
  delete c1;
















}
