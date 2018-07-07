#include "TLatex.h"
#include "TLegend.h"
#include "TObject.h"
#include "TCanvas.h"
#include "TFitResultPtr.h"
#include "TFitResult.h"
#include "TF1.h"
#include "TStyle.h"
#include "TString.h"
#include "TMath.h"
#include "TGaxis.h"
#include "TFile.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TH2F.h"
#include "TTree.h"
#include "TRandom.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include <TGraph2D.h>
#include <TSystem.h>
#include <iostream>


void SetCanvasStandardSettings(TCanvas *cCanv){
  gStyle->SetOptStat(0); // <- das hier macht dies box rechts oben weg
  cCanv->SetTopMargin(0.025);
  cCanv->SetBottomMargin(0.15);
  cCanv->SetRightMargin(0.15);
  cCanv->SetLeftMargin(0.15);
  cCanv->SetTickx();
  cCanv->SetTicky();
  cCanv->SetLogy(0); //counts besser log, da sonst nicht anschaulich
  cCanv->SetLogx(0);
}


void SetHistoStandardSettings(TH1* histo, Double_t XOffset = 1.2, Double_t YOffset = 1.){
  histo->GetXaxis()->SetTitleOffset(XOffset);
  histo->GetYaxis()->SetTitleOffset(YOffset);
  histo->GetXaxis()->SetTitleSize(30);
  histo->GetYaxis()->SetTitleSize(30);
  histo->GetXaxis()->SetLabelSize(30);
  histo->GetYaxis()->SetLabelSize(30);
  histo->GetXaxis()->SetLabelFont(43);
  histo->GetYaxis()->SetLabelFont(43);
  histo->GetYaxis()->SetTitleFont(43);
  histo->GetXaxis()->SetTitleFont(43);




  histo->SetMarkerStyle(20);
  histo->SetMarkerSize(1.5);
  histo->SetLineWidth(2);
  histo->SetLineColor(kBlack);
  histo->SetMarkerColor(kBlack);
}

void SetHistoStandardSettings2(TH2* histo, Double_t XOffset = 1.2, Double_t YOffset = 1.){
  histo->GetXaxis()->SetTitleOffset(XOffset);
  histo->GetYaxis()->SetTitleOffset(YOffset);
  histo->GetXaxis()->SetTitleSize(30);
  histo->GetYaxis()->SetTitleSize(30);
  histo->GetZaxis()->SetTitleSize(30);
  histo->GetXaxis()->SetLabelSize(30);
  histo->GetYaxis()->SetLabelSize(30);
  histo->GetZaxis()->SetLabelSize(20);
  histo->GetXaxis()->SetLabelFont(43);
  histo->GetYaxis()->SetLabelFont(43);
  histo->GetZaxis()->SetLabelFont(43);
  histo->GetYaxis()->SetTitleFont(43);
  histo->GetXaxis()->SetTitleFont(43);
  histo->GetZaxis()->SetTitleFont(43);
}


void SetLegendSettigns(TLegend* leg){
  leg->SetTextSize(50);
  leg->SetTextFont(43);
  leg->SetFillColor(0);
  leg->SetFillStyle(0);
  leg->SetLineWidth(0);
  leg->SetLineColor(0);
  leg->SetMargin(0.15);
}
