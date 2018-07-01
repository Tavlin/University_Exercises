#include "header.h"
#include "TImage.h"

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

  for(int i = 0; i <= 30; i++){

    TH2D* h = new TH2D("h", "", 7, 0, 0.6, 7, 0., 0.6);
    TGraph2D* graph15 = new TGraph2D(Form("Output%d.txt",i));
    graph15->SetTitle("; #hat{y}; #hat{z}; #hat{x}");
    graph15->GetZaxis()->SetRangeUser(-1.,1.);
    graph15->SetMarkerStyle(20);
    graph15->SetMarkerSize(1);
    graph15->SetMarkerColor(kBlue);
    graph15->SetLineColor(kBlack);
    graph15->SetLineWidth(1);
    graph15->SetHistogram(h);

    h->GetZaxis()->SetRangeUser(-1.,1.);


    c1->cd();
    h->Draw("surf1");
    graph15->Draw("surf2");
    // t1->AddEntry(graph15, "Kristall Oszi", "p");
    // t1->Draw("SAME");
    c1->Update();
    c1->SaveAs(Form("x%d.png", i));
    c1->Clear();
    graph15->Delete();
    h->Delete();
  }

  t1->Delete();
  delete c1;



  {
     TImage *img = 0;
     gSystem->Unlink("anim.gif");  // delete existing file
     for (int i = 1; i <= 30; i++) {
        delete img; // delete previous image
        // Read image data. Image can be in any format, e.g. png, gif, etc.
        img = TImage::Open(Form("x%d.png", i));
        if (i < 30) {
           img->WriteImage("anim.gif+10"); // 10 centiseconds delay
        } else { // the last image written.  "++" stands for infinit animation.
           img->WriteImage("anim.gif++10++"); // 10 centiseconds delay of last image
        }
     }
  }
  cout << "done" << endl;
}
