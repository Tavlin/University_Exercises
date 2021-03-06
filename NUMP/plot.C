#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "header.h"

// #define oneD
#define twoD

void plot(){
  #ifdef oneD
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

  TGraph* PoissonEq = new TGraph("PoissonEq1D.txt");
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
  c1->SaveAs("sheet5/1D_PoissonEq.png");

  t1->Delete();
  PoissonEq->Delete();
  delete c1;
  #endif

  #ifdef twoD
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

  TGraph2D* PoissonEq = new TGraph2D("PoissonEq2D.txt");
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
  c1->SaveAs("sheet5/2D_PoissonEqWith.png");

  t1->Delete();
  PoissonEq->Delete();
  delete c1;
  #endif



}
