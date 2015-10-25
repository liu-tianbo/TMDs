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
   TLatex *   tex = new TLatex(0.08,0.57,"");
   tex->SetTextAngle(90);
   tex->SetLineWidth(2);
   tex->SetTextSize(0.08);
   tex->Draw();
          tex = new TLatex(0.6,0.03,"#delta u^{[0,1]}");
   tex->SetLineWidth(2);
   tex->SetTextSize(0.085);
   tex->Draw();
   c2->cd();
  
   nemo_1 = new TPad("nemo_1", "This is nemo_1",0.,0.1,1.,1.);
   nemo_1->Draw();
   nemo_1->cd();
   nemo_1->Range(-0.1766028,0,1.295087,0.160371);
   nemo_1->SetFillColor(0);
   nemo_1->SetFillStyle(4000);
   nemo_1->SetBorderMode(0);
   nemo_1->SetBorderSize(2);
   nemo_1->SetLeftMargin(0.41);
   nemo_1->SetRightMargin(0.01);
   nemo_1->SetTopMargin(0.03);
   nemo_1->SetBottomMargin(0.1);
   nemo_1->SetFrameFillStyle(0);
   nemo_1->SetFrameLineWidth(0);
   nemo_1->SetFrameBorderMode(0);
   nemo_1->SetFrameFillStyle(0);
   nemo_1->SetFrameLineWidth(0);
   nemo_1->SetFrameBorderMode(0);

    const Int_t ny = 5;
    char *label[ny] = {"SoLID Projection","Kang et al (2015)","Radici et al (2015)","Anselmino et al (2013)","Anselmino et al (2013)"};

   //our data point for tensor u:
   TGraphAsymmErrors *gre = new TGraphAsymmErrors(1);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillColor(2);
   gre->SetLineColor(2);
   gre->SetLineWidth(5);
   gre->SetMarkerColor(2);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(3.);
   gre->SetPoint(0,0.39,2);
   gre->SetPointError(0,0.2,0.16,0,0);
 


   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","",100,-0.05,0.75);
   Graph_Graph1->SetMinimum(0.55);
   Graph_Graph1->SetMaximum(5.5);
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
   Graph_Graph1->GetYaxis()->SetLabelSize(0.0);
   Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetYaxis()->SetTitleFont(42);
   Graph_Graph1->GetZaxis()->SetLabelFont(42);
   Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph1->GetZaxis()->SetTitleFont(42);
   gre->SetHistogram(Graph_Graph1);

   
 gre->Draw("acp");

    Float_t x, y;
    TText t;
    // draw labels along y
    x = nemo_1->GetUxmin() +0.1 - 0.1*gre->GetXaxis()->GetBinWidth(1);
    //cout << x << endl;
    t.SetTextAlign(32);
    t.SetTextSize(0.05);
    t.SetTextAngle(0);
    for (int i=0;i<ny;i++) {
       y = gre->GetYaxis()->GetBinCenter(i+1)+0.5;
       t.DrawText(x,y,label[i]);
       //cout << y << endl;
    }

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
   gre->SetPoint(0,0.39,3);
   gre->SetPointError(0,0.15,0.15,0,0);


 
   gre->Draw("pl");

   //Torino 1:
   //#delta_{} u = 0.39^{ +0.18}_{  -0.12}
   TGraphAsymmErrors *gre = new TGraphAsymmErrors(1);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillColor(4);
   gre->SetLineColor(4);
   gre->SetLineWidth(5);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(3.);
   gre->SetPoint(0,0.39,4);
   gre->SetPointError(0,0.12,0.18,0,0);

   gre->Draw("pl");


   //Torino 1:
   // #delta_{} u = 0.31^{ +0.16}_{  -0.12} 
   TGraphAsymmErrors *gre = new TGraphAsymmErrors(1);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillColor(4);
   gre->SetLineColor(4);
   gre->SetLineWidth(5);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(3.);
   gre->SetPoint(0,0.31,5);
   gre->SetPointError(0,0.12,0.16,0,0);

   gre->Draw("pl");

   //SoLIDo:
   // #delta_{} u = 0.31^{ +0.16}_{  -0.12} 
   TGraphAsymmErrors *gre = new TGraphAsymmErrors(1);
   gre->SetName("Graph1");
   gre->SetTitle("");
   gre->SetFillColor(8);
   gre->SetLineColor(8);
   gre->SetLineWidth(5);
   gre->SetMarkerColor(8);
   gre->SetMarkerStyle(8);
   gre->SetMarkerSize(3.);
   gre->SetPoint(0,0.39,1);
   gre->SetPointError(0,0.2*0.7139,0.16*0.7139,0,0);

   gre->Draw("pl");

}

 
