{
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(14);
  
  TCanvas *c1 = new TCanvas("c1","c1",1200,800);
  c1->Divide(3,1);

  c1->cd(1);
 
  gPad->SetRightMargin(0.01);
  gPad->SetLeftMargin(0.05);
  TH2F* h1 = new TH2F("h1","",100, 0,0.7, 100, -7.,0.);
  h1->GetYaxis()->SetLabelSize(0);
  h1->GetYaxis()->SetNdivisions(0);
  h1->GetXaxis()->SetNdivisions(4);
  h1->GetXaxis()->SetLabelSize(0.08);
  h1->GetXaxis()->SetLabelOffset(-0.02);
  h1->Draw();

  TLatex* tu = new TLatex();
  tu->SetNDC();
  tu->SetTextSize(0.1);
  tu->DrawLatex(0.5,0.89,"#delta u^{[0,1]}");

  TGraphAsymmErrors *gre_u = new TGraphAsymmErrors(1);
  gre_u->SetMarkerStyle(8);
  gre_u->SetMarkerSize(2.0);
  gre_u->SetMarkerColor(1);
  gre_u->SetLineColor(1);
  gre_u->SetLineWidth(2);

  //#0: Anselmino et al (2013)
  gre_u->SetPoint(0, 0.31,-1);
  gre_u->SetPointError(0,0.12,0.16,0,0);

  //#1: Anselmino et al (2013)
  gre_u->SetPoint(1, 0.39,-2);
  gre_u->SetPointError(1,0.12,0.18,0,0);

  //#2: Radici et al (2015)
  gre_u->SetPoint(2, 0.39,-3);
  gre_u->SetPointError(2,0.15,0.15,0,0);

  gre_u->Draw("p");
  
  //#3: Kang et al (2015)
  TGraphAsymmErrors *gre_u_alex = new TGraphAsymmErrors(1);
  gre_u_alex->SetMarkerStyle(8);
  gre_u_alex->SetMarkerSize(2.0);
  gre_u_alex->SetLineWidth(2);
  gre_u_alex->SetMarkerColor(8);
  gre_u_alex->SetLineColor(8);

  gre_u_alex->SetPoint(0, 0.39,-4);
  gre_u_alex->SetPointError(0,0.2,0.16,0,0);
  gre_u_alex->Draw("p");
 

  //#4: CLAS12 -U
  TGraphAsymmErrors *gre_u_clas = new TGraphAsymmErrors(1);
  gre_u_clas->SetMarkerStyle(8);
  gre_u_clas->SetMarkerSize(2.0);
  gre_u_clas->SetLineWidth(2);
  gre_u_clas->SetMarkerColor(2);
  gre_u_clas->SetLineColor(2);

  gre_u_clas->SetPoint(0, 0.39,-5);
  gre_u_clas->SetPointError(0,0.2*0.68,0.16*0.68,0,0);
  gre_u_clas->Draw("p");
 

  //#5: SoLID
  TGraphAsymmErrors *gre_u_solid = new TGraphAsymmErrors(1);
  gre_u_solid->SetMarkerStyle(8);
  gre_u_solid->SetMarkerSize(2.0);
  gre_u_solid->SetLineWidth(2);
  gre_u_solid->SetMarkerColor(4);
  gre_u_solid->SetLineColor(4);

  gre_u_solid->SetPoint(0, 0.39,-6);
  gre_u_solid->SetPointError(0,0.2*0.05,0.16*0.05,0,0);

  gre_u_solid->Draw("p");


  c1->cd(2);
  gPad->SetRightMargin(0.05);
  gPad->SetLeftMargin(0.01);
   TH2F* h2 = new TH2F("h2","",100, -1.10,0.3, 100, -7.,0.);
  h2->GetYaxis()->SetLabelSize(0);
  h2->GetYaxis()->SetNdivisions(0);
  h2->GetXaxis()->SetNdivisions(4);
  h2->GetXaxis()->SetLabelSize(0.08);
  h2->GetXaxis()->SetLabelOffset(-0.02);
  h2->Draw();

  TLatex* td = new TLatex();
  td->SetNDC();
  td->SetTextSize(0.1);
  td->DrawLatex(0.5,0.89,"#delta d^{[0,1]}");
 

  TGraphAsymmErrors *gre_d = new TGraphAsymmErrors(1);
  gre_d->SetMarkerStyle(8);
  gre_d->SetMarkerSize(2.0);
  gre_d->SetMarkerColor(1);
  gre_d->SetLineColor(1);
  gre_d->SetLineWidth(2);

  //#0: Anselmino et al (2013)
  gre_d->SetPoint(0, -0.27,-1);
  gre_d->SetPointError(0,0.1,0.1,0,0);

  //#1: Anselmino et al (2013)
  gre_d->SetPoint(1,-0.25,-2);
  gre_d->SetPointError(1,0.1,0.3,0,0);

  //#2: Radici et al (2015)
  gre_d->SetPoint(2, -0.41,-3);
  gre_d->SetPointError(2,0.52,0.52,0,0);
  
  gre_d->Draw("p");
 

  //#3: Kang et al (2015)
  TGraphAsymmErrors *gre_d_alex = new TGraphAsymmErrors(1);
  gre_d_alex->SetMarkerStyle(8);
  gre_d_alex->SetMarkerSize(2.0);
  gre_d_alex->SetLineWidth(2);
  gre_d_alex->SetMarkerColor(8);
  gre_d_alex->SetLineColor(8);

  gre_d_alex->SetPoint(0, -0.22,-4);
  gre_d_alex->SetPointError(0,0.10,0.31,0,0);
  gre_d_alex->Draw("p");

  //#4: CLAS12 
  TGraphAsymmErrors *gre_d_clas = new TGraphAsymmErrors(1);
  gre_d_clas->SetMarkerStyle(8);
  gre_d_clas->SetMarkerSize(2.0);
  gre_d_clas->SetLineWidth(2);
  gre_d_clas->SetMarkerColor(2);
  gre_d_clas->SetLineColor(2);

  gre_d_clas->SetPoint(0, -0.22,-5);
  gre_d_clas->SetPointError(0,0.1*1.,0.31*1.,0,0);
  gre_d_clas->Draw("p");
 

  //#5: SoLID
  TGraphAsymmErrors *gre_d_solid = new TGraphAsymmErrors(1);
  gre_d_solid->SetMarkerStyle(8);
  gre_d_solid->SetMarkerSize(2.0);
  gre_d_solid->SetMarkerColor(4);
  gre_d_solid->SetLineColor(4);
  gre_d_solid->SetLineWidth(2);

  gre_d_solid->SetPoint(0,-0.22,-6);
  gre_d_solid->SetPointError(0,0.1*0.26,0.31*0.26,0,0);

  gre_d_solid->Draw("p");

  const Int_t ny = 6;
  char *label[ny] = {"Anselmino et al (2013)","Anselmino et al (2013)","Radici et al (2015)","Kang et al (2015)","CLAS12 Projection","SoLID Projection"};

  c1->cd(3);
  Float_t x, y;
  TLatex *t = new TLatex();
  t->SetNDC();
  t->SetTextSize(0.09);

  x = 0.01;
  for (int i=0;i<ny;i++) {
      y = 0.115*(7.2-i);
	  t->DrawLatex(x,y,label[i]);
	  if(i==2)
		  t->SetTextColor(8);
	  if(i==3)
		  t->SetTextColor(2);
	  if(i==4)
		  t->SetTextColor(4);
	  //cout << y << endl;
  }

  c1->Print("Tensor_Charge_SoLID_CLAS.pdf");
  c1->Print("Tensor_Charge_SoLID_CLAS.png");
}
