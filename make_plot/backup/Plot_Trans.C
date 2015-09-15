/*C/C++ Includes{{{*/
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
/*}}}*/

/*ROOT Includes{{{*/
#include <TSystem.h>
#include <TString.h>
#include <TStyle.h>
#include <Riostream.h>
#include "TObjString.h"
#include <TNamed.h>
#include <TPRegexp.h>
#include <TObjArray.h>
#include <TChain.h>
#include <TMath.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TLatex.h>
#include <TROOT.h>
#include <TF1.h>
#include <TLine.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TCanvas.h>
#include <TDatime.h>
#include <TError.h>
#include <TVirtualFitter.h>
#include <TSQLServer.h>
#include <TSQLResult.h>
#include <TSQLRow.h>
#include <TCut.h>
#include <TMultiGraph.h>
#include <TCutG.h>
#include <TLorentzVector.h>
#include <TMath.h>
#include <TRandom3.h>
//#include <TMatrix.h>
/*}}}*/
using namespace std;

void Plot_Trans(){
	gStyle->SetOptStat(0);

    /*Read in Data{{{*/
	ifstream infile("data_transversity.dat");
	Double_t U_X_Err[100], U_Err[100], U_X_Q2_1000[100], U_Q2_1000[100], U_X_Q2_10[100], U_Q2_10[100], U_X_Q2_24[100], U_Q2_24[100];
	Double_t D_X_Err[100], D_Err[100], D_X_Q2_1000[100], D_Q2_1000[100], D_X_Q2_10[100], D_Q2_10[100], D_X_Q2_24[100], D_Q2_24[100];

	TString TC, Com;
    int bin; double x,y;	
	//u_err
    /*
	for(int i=0;i<100;i++){
      infile >> TC >> Com >> bin >> x >> y;	
	  if(bin==i){
	     U_X_Err[i] = x;
		 U_Err[i] = y;
		 //cerr<<Form("U-Error: #%d  x = %6.5f, U = %10.4e", bin, x, y)<<endl;
	  }
	}
	Double_t x_u_up[50], x_u_down[50], err_u_up[50], err_u_down[50];
    for(int i=0;i<50;i++){
	    x_u_up[i] = U_X_Err[i];
	    x_u_down[i] = U_X_Err[99-i];
	    err_u_up[i] = U_Err[i];
	    err_u_down[i] = U_Err[99-i];
	}*/

	//u_q2=1000
	for(int i=0;i<100;i++){
      infile >> TC >> Com >> bin >> x >> y;	
	  if(bin==i){
	     U_X_Q2_1000[i] = x;
		 U_Q2_1000[i] = y;
		 //cerr<<Form("U-Q2=1000: #%d  x = %6.5f, U = %10.4e",bin, x, y)<<endl;
	  }
	}
	//u_q2=10
	for(int i=0;i<100;i++){
      infile >> TC >> Com >> bin >> x >> y;	
	  if(bin==i){
	     U_X_Q2_10[i] = x;
		 U_Q2_10[i] = y;
		 //cerr<<Form("U-Q2=10: #%d  x = %6.5f, U = %10.4e", bin,x, y)<<endl;
	  }
	}
	//u_q2=2.4
	for(int i=0;i<100;i++){
      infile >> TC >> Com >> bin >> x >> y;	
	  if(bin==i){
	     U_X_Q2_24[i] = x;
		 U_Q2_24[i] = y;
		 //cerr<<Form("U-Q2=2.4: #%d  x = %6.5f, U = %10.4e",bin, x, y)<<endl;
	  }
	}			
	//d_err
	for(int i=0;i<100;i++){
      infile >> TC >> Com >> bin >> x >> y;	
	  if(bin==i){
	     D_X_Err[i] = x;
		 D_Err[i] = y;
		 //cerr<<Form("D-Error: #%d  x = %6.5f, U = %10.4e",bin, x, y)<<endl;
	  }
	}
	Double_t x_d_up[50], x_d_down[50], err_d_up[50], err_d_down[50];
    for(int i=0;i<50;i++){
	    x_d_up[i] = D_X_Err[i];
	    x_d_down[i] = D_X_Err[99-i];
	    err_d_up[i] = D_Err[i];
	    err_d_down[i] = D_Err[99-i];
	}

	//d_q2=1000
	for(int i=0;i<100;i++){
      infile >> TC >> Com >> bin >> x >> y;	
	  if(bin==i){
	     D_X_Q2_1000[i] = x;
		 D_Q2_1000[i] = y;
		 //cerr<<Form("D-Q2=1000: #%d  x = %6.5f, U = %10.4e",bin, x, y)<<endl;
	  }
	}
	//d_q2=10
	for(int i=0;i<100;i++){
      infile >> TC >> Com >> bin >> x >> y;	
	  if(bin==i){
	     D_X_Q2_10[i] = x;
		 D_Q2_10[i] = y;
		 //cerr<<Form("D-Q2=10: #%d  x = %6.5f, U = %10.4e",bin, x, y)<<endl;
	  }
	}
	//d_q2=2.4
	for(int i=0;i<100;i++){
      infile >> TC >> Com >> bin >> x >> y;	
	  if(bin==i){
	     D_X_Q2_24[i] = x;
		 D_Q2_24[i] = y;
		 //cerr<<Form("D-Q2=2.4: #%d  x = %6.5f, U = %10.4e",bin, x, y)<<endl;
	  }
	}		
    infile.close();	
    /*}}}*/

    TCanvas *c1 = new TCanvas("c1","c1", 800,1000);
	c1->Divide(1,2);

	//////////////////////////////////
	//Transversity-u
	//////////////////////////////////
	/*U{{{*/
 	c1->cd(1);
	gPad->SetBottomMargin(0.002);
	TH2F *hu = new TH2F("hu","",1000, 0.,1.0, 100, -0.01, 0.35);
	hu->SetYTitle("xh_{1}^{u}(x, Q^{2})");
	hu->GetYaxis()->CenterTitle(1);
	hu->GetYaxis()->SetTitleSize(0.09);
	hu->GetYaxis()->SetTitleOffset(0.6);
	hu->GetYaxis()->SetNdivisions(4);
	hu->GetXaxis()->SetNdivisions(0);
	hu->Draw();

	/*transversity-u errors {{{*/
	TGraph* grapherror = new TGraph(100, U_X_Err, U_Err);
	grapherror->SetFillColor(8);
	grapherror->SetLineColor(1);
    grapherror->Draw("f");

	/*}}}*/

	/* Q2 = 1000 {{{*/ 
	TGraph *graph_u_1000 = new TGraph(100, U_X_Q2_1000, U_Q2_1000);
	graph_u_1000->SetName("Graph_u_1000");
	graph_u_1000->SetTitle("");
	graph_u_1000->SetFillColor(1);
	graph_u_1000->SetLineColor(1);
	graph_u_1000->SetLineWidth(3);
	graph_u_1000->SetLineStyle(9);
	graph_u_1000->Draw("c");
	/*}}}*/

	/* Q2 = 10 {{{*/ 
	TGraph *graph_u_10 = new TGraph(100, U_X_Q2_10, U_Q2_10);
	graph_u_10->SetName("Graph_u_10");
	graph_u_10->SetTitle("");
	graph_u_10->SetFillColor(1);
	graph_u_10->SetLineColor(2);
	graph_u_10->SetLineWidth(3);
	graph_u_10->Draw("c");
	/*}}}*/

	/* Q2 = 2.4{{{*/ 
	TGraph *graph_u_24 = new TGraph(100, U_X_Q2_24, U_Q2_24);
	graph_u_24->SetName("Graph_u_24");
	graph_u_24->SetTitle("");
	graph_u_24->SetFillColor(1);
	graph_u_24->SetLineColor(1);
	graph_u_24->SetLineWidth(3);
	graph_u_24->SetLineStyle(2);
	graph_u_24->Draw("c");
	/*}}}*/
    /*}}}*/

	//////////////////////////////////
	//Transversity-d
	//////////////////////////////////
	/*D{{{*/
 	c1->cd(2);
	gPad->SetTopMargin(0.002);
    TH2F *hd = new TH2F("hd","",100, 0.,1.0, 100, -0.16, 0.09);
	hd->SetYTitle("xh_{1}^{d}(x, Q^{2})");
	hd->GetYaxis()->CenterTitle(1);
	hd->GetYaxis()->SetTitleSize(0.09);
	hd->GetYaxis()->SetNdivisions(4);
	hd->GetYaxis()->SetTitleOffset(0.6);
	hd->GetXaxis()->SetTitleOffset(0.6);
	hd->GetXaxis()->SetTitleSize(0.09);
	hd->SetXTitle("x");
	hd->GetXaxis()->CenterTitle(1);
	hd->Draw();

	/*transversity-d errors {{{*/
	TGraph* grapherror_d = new TGraph(100, D_X_Err, D_Err);
	grapherror_d->SetFillColor(8);
	grapherror_d->SetLineColor(1);
	grapherror_d->Draw("f");
	/*}}}*/

	/* Q2 = 1000 {{{*/ 
	TGraph *graph_d_1000 = new TGraph(100, D_X_Q2_1000, D_Q2_1000);
	graph_d_1000->SetName("Graph_d_1000");
	graph_d_1000->SetTitle("");
	graph_d_1000->SetFillColor(1);
	graph_d_1000->SetLineColor(1);
	graph_d_1000->SetLineWidth(3);
	graph_d_1000->SetLineStyle(9);
	graph_d_1000->Draw("c");
	/*}}}*/

	/* Q2 = 10 {{{*/ 
	TGraph *graph_d_10 = new TGraph(100, D_X_Q2_10, D_Q2_10);
	graph_d_10->SetName("Graph_d_10");
	graph_d_10->SetTitle("");
	graph_d_10->SetFillColor(1);
	graph_d_10->SetLineColor(2);
	graph_d_10->SetLineWidth(3);
	graph_d_10->Draw("c");
	/*}}}*/

	/* Q2 = 2.4{{{*/ 
	TGraph *graph_d_24 = new TGraph(100, D_X_Q2_24, D_Q2_24);
	graph_d_24->SetName("Graph_d_24");
	graph_d_24->SetTitle("");
	graph_d_24->SetFillColor(1);
	graph_d_24->SetLineColor(1);
	graph_d_24->SetLineWidth(3);
	graph_d_24->SetLineStyle(2);
	graph_d_24->Draw("c");
	/*}}}*/
    /*}}}*/

	/*Draw Lines{{{ */
	TLine *line = new TLine(0,0,1.0449,0);
	line->Draw();

	// LINE Q2 = 2.4 
	line = new TLine(0.4,-0.05,0.55,-0.05);
	line->SetLineColor(1);
	line->SetLineStyle(2);
	line->SetLineWidth(3);
	line->Draw();


	TLatex* tex = new TLatex(0.55,-0.05,"Q^{2} = 2.4 GeV^{2}");
	tex->SetLineWidth(2);
	tex->SetTextSize(0.08);
	tex->Draw();

	// LINE Q2 = 10 
	line = new TLine(0.4,-0.08,0.55,-0.08);
	line->SetLineColor(2);
	line->SetLineStyle(1);
	line->SetLineWidth(3);
	line->Draw();


	tex = new TLatex(0.55,-0.08,"Q^{2} = 10 GeV^{2}");
	tex->SetLineWidth(2);
	tex->SetTextSize(0.08);
	tex->Draw();


	// LINE Q2 = 1000 
	line = new TLine(0.4,-0.11,0.55,-0.11);
	line->SetLineColor(1);
	line->SetLineStyle(9);
	line->SetLineWidth(3);
	line->Draw();


	tex = new TLatex(0.55,-0.11,"Q^{2} = 1000 GeV^{2}");
	tex->SetLineWidth(2);
	tex->SetTextSize(0.08);
	tex->Draw();

	/*}}}*/

	/*Optimize x-bins{{{*/
	/*
	Double_t x_u_new[100];
	Double_t x_d_new[100];

	ifstream trans("transversity_u_0.dat");
	int k=0; double dummy;
	while(trans>>x_u_new[k]>>dummy)
		k++;

	TCanvas *c2 = new TCanvas("c2","c2",800,800);
	c2->Divide(2,2);

	gStyle->SetOptStat(1);	
	gStyle->SetOptFit(1);	
	c2->cd(1);
	TH2F *h1 = new TH2F("h1","",1000,0.,1.0, 1000, 0.0, 0.4);
	h1->Draw();
	TGraph* gr1 = new TGraph(50, x_u_up, err_u_up);
	gr1->SetMarkerStyle(20);
	gr1->Draw("p");
	gr1->Fit("pol7","","",0.001,0.9);
	TF1* func1 = gr1->GetFunction("pol7");

	c2->cd(2);
	TH2F *h2 = new TH2F("h2","",1000,0.,1.0, 1000, 0.0, 0.4);
	h2->Draw();
	TGraph* gr2 = new TGraph(50, x_u_down, err_u_down);
	gr2->SetMarkerStyle(20);
	gr2->Draw("p");
	gr2->Fit("pol7","","",0.001,0.9);
	TF1* func2 = gr2->GetFunction("pol7");

	c2->cd(3);
	TH2F *h3 = new TH2F("h3","",1000,0.,1.0, 1000, -0.2, 0.1);
	h3->Draw();
	TGraph* gr3 = new TGraph(50, x_d_up, err_d_up);
	gr3->SetMarkerStyle(20);
	gr3->Draw("p");
	gr3->Fit("pol7","","",0.001,0.9);
	TF1* func3 = gr3->GetFunction("pol7");

	c2->cd(4);
	TH2F *h4 = new TH2F("h4","",1000,0.,1.0, 1000,-0.2, 0.1);
	h4->Draw();
	TGraph* gr4 = new TGraph(50, x_d_down, err_d_down);
	gr4->SetMarkerStyle(20);
	gr4->Draw("p");
	gr4->Fit("pol7","","",0.001,0.9);
	TF1* func4 = gr4->GetFunction("pol7");

	ofstream outf_u("hu_err.dat");
	ofstream outf_d("hd_err.dat");
	Double_t err_u_up_new[100], err_u_down_new[100];
	Double_t err_d_up_new[100], err_d_down_new[100];

	for(int i=0;i<100;i++){
		x = x_u_new[i]; 
		double y_u_up = func1->GetParameter(0) * pow(x,0)
			+ func1->GetParameter(1) * pow(x,1)
			+ func1->GetParameter(2) * pow(x,2)
			+ func1->GetParameter(3) * pow(x,3)
			+ func1->GetParameter(4) * pow(x,4)
			+ func1->GetParameter(5) * pow(x,5)
			+ func1->GetParameter(6) * pow(x,6)
			;

		double y_u_down =  func2->GetParameter(0) * pow(x,0)
			+ func2->GetParameter(1) * pow(x,1)
			+ func2->GetParameter(2) * pow(x,2)
			+ func2->GetParameter(3) * pow(x,3)
			+ func2->GetParameter(4) * pow(x,4)
			+ func2->GetParameter(5) * pow(x,5)
			+ func2->GetParameter(6) * pow(x,6)
			;
		double y_d_up = func3->GetParameter(0) * pow(x,0)
			+ func3->GetParameter(1) * pow(x,1)
			+ func3->GetParameter(2) * pow(x,2)
			+ func3->GetParameter(3) * pow(x,3)
			+ func3->GetParameter(4) * pow(x,4)
			+ func3->GetParameter(5) * pow(x,5)
			+ func3->GetParameter(6) * pow(x,6)
            ;
		double y_d_down =  func4->GetParameter(0) * pow(x,0)
			+ func4->GetParameter(1) * pow(x,1)
			+ func4->GetParameter(2) * pow(x,2)
			+ func4->GetParameter(3) * pow(x,3)
			+ func4->GetParameter(4) * pow(x,4)
			+ func4->GetParameter(5) * pow(x,5)
			+ func4->GetParameter(6) * pow(x,6)
			;
		err_u_up_new[i]=y_u_up;
		err_d_up_new[i]=y_d_up;
		err_u_down_new[i]=y_u_down;
		err_d_down_new[i]=y_d_down;
		outf_u << Form("%16.4f  %10.4e  %10.4e", x, y_u_up, y_u_down)<<endl;	
		outf_d << Form("%16.4f  %10.4e  %10.4e", x, y_d_up, y_d_down)<<endl;	
	}
	outf_u.close();
	outf_d.close();
	*/
	/*}}}*/

}
