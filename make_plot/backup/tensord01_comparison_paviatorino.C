{
//=========Macro generated from canvas: c1/distribution
//=========  (Mon Sep 29 14:06:05 2014) by ROOT version5.34/21
  gROOT->SetStyle("Plain");
  gStyle->Reset();
  gStyle->SetTextFont(132);
  gStyle->SetLabelFont(132,"xyz");
   gStyle->SetEndErrorSize(19.);

 




 
   TCanvas *c2 = new TCanvas("tensor charge", "tensor charge",130,95,600,600);
   c2->SetHighLightColor(2);
   c2->Range(0,0,1,1);
   c2->SetFillColor(0);
   c2->SetFillStyle(4000);
   c2->SetBorderMode(0);
   c2->SetBorderSize(2);
   c2->SetFrameFillStyle(0);
   c2->SetFrameLineWidth(0);
   c2->SetFrameBorderMode(0);
   TLatex *   tex = new TLatex(0.08,0.57,"#delta d^{[0,1]}");
   tex->SetTextAngle(90);
   tex->SetLineWidth(2);
   tex->SetTextSize(0.08);
   tex->Draw();
          tex = new TLatex(0.5,0.03,"");
   tex->SetLineWidth(2);
   tex->SetTextSize(0.085);
   tex->Draw();
   c2->cd();
  
   nemo_1 = new TPad("nemo_1", "This is nemo_1",0.1,0.1,1.,1.);
   nemo_1->Draw();
   nemo_1->cd();
   nemo_1->Range(-0.1766028,0,1.295087,0.160371);
   nemo_1->SetFillColor(0);
   nemo_1->SetFillStyle(4000);
   nemo_1->SetBorderMode(0);
   nemo_1->SetBorderSize(2);
   nemo_1->SetLeftMargin(0.12);
   nemo_1->SetRightMargin(0.01);
   nemo_1->SetTopMargin(0.03);
   nemo_1->SetBottomMargin(0.1);
   nemo_1->SetFrameFillStyle(0);
   nemo_1->SetFrameLineWidth(0);
   nemo_1->SetFrameBorderMode(0);
   nemo_1->SetFrameFillStyle(0);
   nemo_1->SetFrameLineWidth(0);
   nemo_1->SetFrameBorderMode(0);

   //our data point for tensor d:
   TGraphAsymmErrors *gre = new TGraphAsymmErrors(1);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillColor(2);
   gre->SetLineColor(2);
   gre->SetLineWidth(5);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(3.);
   gre->SetPoint(0,1,-0.22);
   gre->SetPointError(0,0,0,0.10,0.31);
   
 


   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","",100,0.55,4.5);
   Graph_Graph1->SetMinimum(-1.05);
   Graph_Graph1->SetMaximum(0.25);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);
   Graph_Graph1->GetXaxis()->SetNdivisions(4);
   Graph_Graph1->GetXaxis()->SetLabelFont(42);
   Graph_Graph1->GetXaxis()->SetLabelOffset(0.02);
   Graph_Graph1->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetXaxis()->SetTitleColor(0);
   Graph_Graph1->GetXaxis()->SetTitleFont(42);
   Graph_Graph1->GetYaxis()->SetNdivisions(4);
   Graph_Graph1->GetYaxis()->SetLabelFont(42);
   Graph_Graph1->GetYaxis()->SetLabelOffset(0.02);
   Graph_Graph1->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1);

   
   gre->Draw("ape1");

   // Radici:
   //our data point for tensor d:
   TGraphAsymmErrors *gre = new TGraphAsymmErrors(1);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillColor(4);
   gre->SetLineColor(4);
   gre->SetLineWidth(5);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(3.);
   gre->SetPoint(0,2,-0.41);
   gre->SetPointError(0,0,0,0.52,0.52);


 
   gre->Draw("pl");

   //Torino 1:
   //#delta_{} d = -0.25^{ +0.3}_{  -0.1}
   TGraphAsymmErrors *gre = new TGraphAsymmErrors(1);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillColor(4);
   gre->SetLineColor(4);
   gre->SetLineWidth(5);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(3.);
   gre->SetPoint(0,3,-0.25);
   gre->SetPointError(0,0,0,0.1,0.3);

   gre->Draw("pl");


   //Torino 1:
   // #delta_{} d = -0.27^{ +0.1}_{  -0.1}"
   TGraphAsymmErrors *gre = new TGraphAsymmErrors(1);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillColor(4);
   gre->SetLineColor(4);
   gre->SetLineWidth(5);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(3.);
   gre->SetPoint(0,4,-0.27);
   gre->SetPointError(0,0,0,0.1,0.1);

   gre->Draw("pl");


   //lines:
   TLine t(0.55,0,4.5,0);
   t.SetLineStyle(1);
   t.Draw();  



}
