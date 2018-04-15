#include "header.h"

void goldenratio(){

  TCanvas* cGoldenRatio = new TCanvas("cGoldenRatio","",1200,1200);
  SetCanvasStandardSettings(cGoldenRatio);
  TCanvas* cGoldenRatio2 = new TCanvas("cGoldenRatio2","",1200,1200);
  SetCanvasStandardSettings(cGoldenRatio2);
  
  TLegend* tGoldenRatio = new TLegend(0.5,0.75,0.9,0.95);
  tGoldenRatio->SetFillStyle(0);
  tGoldenRatio->SetBorderSize(0);
  tGoldenRatio->SetTextFont(43);
  tGoldenRatio->SetTextSize(40);
  
  
  TLegend* tGoldenRatio2 = new TLegend(0.5,0.75,0.9,0.95);
  tGoldenRatio2->SetFillStyle(0);
  tGoldenRatio2->SetBorderSize(0);
  tGoldenRatio2->SetTextFont(43);
  tGoldenRatio2->SetTextSize(40);
  
  TGraph* gGoldenRatio_float = new TGraph("fib_float.txt");
  gGoldenRatio_float->SetTitle("; n; #delta (n)");
  gGoldenRatio_float->SetMarkerStyle(20);
  gGoldenRatio_float->SetMarkerColor(kBlue);
  gGoldenRatio_float->SetLineColor(kBlue);
  gGoldenRatio_float->SetLineWidth(2);
  
  
  
  TGraph* gGoldenRatio_double = new TGraph("fib_double.txt");
  gGoldenRatio_double->SetMarkerStyle(21);
  gGoldenRatio_double->SetMarkerColor(kGreen+2);
  gGoldenRatio_double->SetLineColor(kGreen+2);
  gGoldenRatio_double->SetLineWidth(2);
  gGoldenRatio_double->SetTitle("; n; #delta (n)");
  
  cGoldenRatio->cd();
  gGoldenRatio_float->Draw("LAP");
  tGoldenRatio->AddEntry(gGoldenRatio_float, "#delta (n) for float", "p");
  tGoldenRatio->Draw("SAME");
  
  cGoldenRatio2->cd();
  gGoldenRatio_double->Draw("LAP");
  tGoldenRatio2->AddEntry(gGoldenRatio_double, "#delta (n) for double", "p");
  tGoldenRatio2->Draw("SAME");
  
  cGoldenRatio->SaveAs(Form("GoldenRatio/GoldenRatio.png"));
  cGoldenRatio2->SaveAs(Form("GoldenRatio/GoldenRatio2.png"));
  



}
