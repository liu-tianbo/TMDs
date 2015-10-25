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

void Tensor(){
//int main(){
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(1);
	const int N=15;
	const double Scale[N]={1000,900,800,700,600,500,400,300,200,100,80,60,40,20,1};
	double Zero[N]={N*0.};

	/*Define{{{*/
    int Bin[N];	
	double Scale0[N],Scale_Temp[N];
	double deltaU_Exp[N], deltaD_Exp[N];
	double deltaU_Vol[N], deltaD_Vol[N];
	double deltaU_Exp_New[N], deltaD_Exp_New[N];
	double deltaU_Vol_New[N], deltaD_Vol_New[N];
	double deltaU_R[N], deltaD_R[N];

	double deltaU_Exp_SoLID[N], deltaD_Exp_SoLID[N];
	double deltaU_Vol_SoLID[N], deltaD_Vol_SoLID[N];
	double deltaU_Exp_SoLID_New[N], deltaD_Exp_SoLID_New[N];
	double deltaU_Vol_SoLID_New[N], deltaD_Vol_SoLID_New[N];
	double deltaU_R_SoLID[N], deltaD_R_SoLID[N];
	/*}}}*/

	TString Experiment=""; cerr<<"--- Experiment = (solid or clas) "; cin >> Experiment;
	TString Target=""; cerr<<"--- Target = (p or 3he) "; cin >> Target;
    TString Particle=""; cerr<<"--- Particle = (pip or pim) "; cin>>Particle;

	ifstream tensor(Form("%s_tensor_charge_%s_%s.dat",Experiment.Data(),Target.Data(),Particle.Data()));
	cerr<<"--- Reading Data ..."<<endl;

	/*Tensor Charge{{{*/
	double dum; int dum_int;
	tensor >> dum_int >> dum_int >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum >> dum ;
	int i=0;
	while(!(tensor.eof())){
		deltaU_Exp[i]=0.0; deltaD_Exp[i]=0.0;
		deltaU_Vol[i]=0.0; deltaD_Vol[i]=0.0;
		deltaU_Exp_SoLID[i]=0.0; deltaD_Exp_SoLID[i]=0.0;
		deltaU_Vol_SoLID[i]=0.0; deltaD_Vol_SoLID[i]=0.0;
		tensor >> Bin[i] >> Scale_Temp[i] 
			>> deltaU_Exp[i] >> deltaU_Vol[i] >> deltaD_Exp[i] >> deltaD_Vol[i]
			>> deltaU_Exp_New[i] >> deltaU_Vol_New[i] >> deltaD_Exp_New[i] >> deltaD_Vol_New[i]
			>> deltaU_Exp_SoLID[i] >> deltaU_Vol_SoLID[i] >> deltaD_Exp_SoLID[i] >> deltaD_Vol_SoLID[i] 
			>> deltaU_Exp_SoLID_New[i] >> deltaU_Vol_SoLID_New[i] >> deltaD_Exp_SoLID_New[i] >> deltaD_Vol_SoLID_New[i];
		deltaU_R_SoLID[i] =deltaU_Vol_SoLID_New[i]/deltaU_Vol_SoLID[i];
		deltaD_R_SoLID[i] =deltaD_Vol_SoLID_New[i]/deltaD_Vol_SoLID[i];
		deltaU_R[i] =deltaU_Vol_New[i]/deltaU_Vol[i];
		deltaD_R[i] =deltaD_Vol_New[i]/deltaD_Vol[i];
		//cerr<<Form("=== I=%2d, dR=%e, dU_Err=%e/%e, dR=%e, dD_Err=%e/%e", i, deltaU_R_SoLID[i],deltaU_Vol_SoLID[i],deltaU_Vol[i],deltaD_R_SoLID[i],deltaD_Vol_SoLID[i],deltaD_Vol[i])<<endl;
		Scale0[i] = Scale_Temp[i]+5;
		i++;
	}
	tensor.close(); 
	/*}}}*/

	/*Plot Tensor Charge{{{*/
    TString Par = "";
	if(Particle=="pip") Par = "#pi^{+}";
	if(Particle=="pim") Par = "#pi^{-}";

	cerr<<"--- Making Plots ..."<<endl;
	TCanvas *c0 = new TCanvas("c0","c0",800,600);
	c0->Divide(2,2);
	c0->cd(1);	
//	TH2D *h1 = new TH2D("h1","Tensor Charge vs Scale", 100, 0.0, 8.0, 100, 0, 0.7);
//	h1->SetXTitle("Beam-Time (Days)");
	TH2D *h1 = new TH2D("h1",Form("%s(e,e')%s: Tensor Charge (U) vs Scale",Target.Data(),Par.Data()), 100, 0.0, 1005.0, 100, 0.2, 0.5);
	h1->SetXTitle("Scale");
	h1->SetYTitle("#delta U");
	h1->GetXaxis()->CenterTitle(1);
	h1->GetYaxis()->CenterTitle(1);
	h1->Draw();
	TGraphErrors *gr01 = new TGraphErrors(N, Scale0, deltaU_Exp_New,Zero, deltaU_Vol_New);
	gr01->SetMarkerStyle(20);
	gr01->SetMarkerColor(4);
	gr01->SetLineColor(4);
	gr01->Draw("p");

	TGraphErrors *gr1 = new TGraphErrors(N, Scale, deltaU_Exp_SoLID_New,Zero, deltaU_Vol_SoLID_New);
	gr1->SetMarkerStyle(20);
	gr1->SetMarkerColor(2);
	gr1->SetLineColor(2);
	gr1->Draw("p");


	c0->cd(2);
	//TH2D *h11 = new TH2D("h11","Tensor Charge vs Scale", 100, 0.0, 8.0, 100, -0.50, 0.10);
	//h11->SetXTitle("Beam-Time (Days)");
	TH2D *h11 = new TH2D("h11",Form("%s(e,e')%s: Tensor Charge (D) vs Scale",Target.Data(),Par.Data()), 100, 0.0, 1005.0, 100, -0.25, -0.05);
	h11->SetXTitle("Scale");
	h11->SetYTitle("#delta D");
	h11->GetXaxis()->CenterTitle(1);
	h11->GetYaxis()->CenterTitle(1);
	h11->Draw();
	TGraphErrors *gr02 = new TGraphErrors(N, Scale0, deltaD_Exp_New,Zero, deltaD_Vol_New);
	gr02->SetMarkerStyle(21);
	gr02->SetMarkerColor(2);
	gr02->SetLineColor(2);
	gr02->Draw("p");

	TGraphErrors *gr2 = new TGraphErrors(N, Scale, deltaD_Exp_SoLID_New,Zero, deltaD_Vol_SoLID_New);
	gr2->SetMarkerStyle(21);
	gr2->SetMarkerColor(4);
	gr2->SetLineColor(4);
	gr2->Draw("p");


	c0->cd(3);
	TH2D *h2 = new TH2D("h2",Form("%s(e,e')%s: Improve (#delta U) vs Scale",Target.Data(),Par.Data()), 100, 0.0, 1005.0, 100, 0, 1.5);
	h2->SetXTitle("Scale");
	h2->SetYTitle("#sigma(#delta U)^{SoLID}/#sigma(#delta U)^{Data}");
	h2->GetXaxis()->CenterTitle(1);
	h2->GetYaxis()->CenterTitle(1);
	h2->Draw();
	TGraph *gr3 = new TGraph(N, Scale, deltaU_R_SoLID);
	//TGraph *gr3 = new TGraph(N, Scale, deltaU_R);
	gr3->SetMarkerStyle(20);
	gr3->SetMarkerColor(1);
	gr3->Draw("p");
	//gr3->Fit("pol2","","",200,1000);
	gr3->Fit("pol2","","",40,100);

	c0->cd(4);	
	TH2D *h21 = new TH2D("h21",Form("%s(e,e')%s: Improve (#delta D) vs Scale",Target.Data(),Par.Data()), 100, 0.0, 1005.0, 100, 0, 1.5);
	h21->SetXTitle("Scale");
	h21->SetYTitle("#sigma(#delta U)^{SoLID}/#sigma(#delta U)^{Data}");
	h21->GetXaxis()->CenterTitle(1);
	h21->GetYaxis()->CenterTitle(1);
	h21->Draw();
	TGraph *gr4 = new TGraph(N, Scale, deltaD_R_SoLID);
	//TGraph *gr4 = new TGraph(N, Scale, deltaD_R);
	gr4->SetMarkerStyle(20);
	gr4->SetMarkerColor(1);
	gr4->Draw("p");
	//gr4->Fit("pol2","","",200,1000);
	gr4->Fit("pol2","","",40,100);
	c0->Print(Form("less_%s_Resol_Tensor_Charge_%s_%s.png", Experiment.Data(), Target.Data(), Particle.Data()));
	/*}}}*/
}
