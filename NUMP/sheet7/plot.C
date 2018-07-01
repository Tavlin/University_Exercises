#include "header.h"

void plot(){
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

  TGraph* graph15 = new TGraph("Output0.txt");
  graph15->SetTitle("; #hat{t}; #hat{x}(#hat{t})");
  graph15->SetMarkerStyle(20);
  graph15->SetMarkerSize(1);
  graph15->SetMarkerColor(kBlue);
  graph15->SetLineColor(kBlack);
  graph15->SetLineWidth(1);


  c1->cd();
  graph15->Draw("APL");
  t1->AddEntry(graph15, "Kristall Oszi", "p");
  t1->Draw("SAME");
  c1->Update();
  c1->SaveAs("x0.png");

  t1->Delete();
  graph15->Delete();
  delete c1;
}
