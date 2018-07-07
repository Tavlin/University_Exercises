#include "header.h"

void chi2(void){

  TFitResultPtr r;
  TCanvas* c1 = new TCanvas("c1","",1000,1000);
  c1->SetFillColor(42);
  c1->SetGrid();
  c1->SetFillColor(21);
  c1->SetBorderSize(12);
  c1->cd();

  TF1* f1 = new TF1("f1","[0]+[1]/x+[2]*x",3.,10.);
  TLatex* tex = new TLatex();
  tex->SetTextSize(0.03);
  tex->SetTextFont(42);

  TGraphErrors* gr = new TGraphErrors("V.dat");
  gr->SetTitle("static potential; #hat{r}; #hat{V}");
  gr->SetMarkerColor(4);
  gr->SetMarkerStyle(21);
  gr->SetLineWidth(3);
  gr->Draw("ALP");
  r = gr->Fit("f1","MS0","",3.,10.);
  f1->Draw("same");
  tex->DrawLatexNDC(0.2,0.8, Form("#hat{V}_{0} = %+lf",f1->GetParameter(0)));
  tex->DrawLatexNDC(0.2,0.75, Form("#hat{#alpha} = %+lf",f1->GetParameter(1)));
  tex->DrawLatexNDC(0.2,0.7, Form("#hat{#sigma} = %+lf",f1->GetParameter(2)));
  tex->DrawLatexNDC(0.2,0.65, Form("#chi^{2}/d.o.f. = %+lf",r->Chi2()/r->Ndf()));

  c1->SaveAs("RootChi2Fit.png");
  c1->Clear();

  TGraph* g = new TGraph("lagrange_pol.txt");
  g->SetTitle("static potential; #hat{r}; #hat{V}");
  g->SetMarkerColor(kRed);
  g->SetMarkerStyle(24);
  g->SetMarkerSize(1);
  gr->Draw("ALP");
  g->Draw("LP");

  c1->SaveAs("LagrangePolFit.png");

  delete c1;
  delete f1;
  delete tex;
  delete gr;
  delete g;
}
