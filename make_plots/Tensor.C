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
	/*Define{{{*/
	//const int N=17;
	//double Scale[N]={1000.,900.,800.,700.,600.,500.,400.,300.,200.,100.,90.,80.,70.,60.,50.,40.,30.};
	const int N=10;
	const double Scale[N]={100.,90.,80.,70.,60.,50.,40.,30.,20.,10.};
	double Zero[N]={N*0.};

    int Bin[N];	
	double Scale_Temp[N], deltaU_Exp[N], deltaD_Exp[N];
	double deltaU_Vol[N], deltaD_Vol[N];
	double deltaU_Exp_New[N], deltaD_Exp_New[N];
	double deltaU_Vol_New[N], deltaD_Vol_New[N];
	double deltaU_R_New[N], deltaD_R_New[N];
	double deltaU_Exp_SoLID[N], deltaD_Exp_SoLID[N];
	double deltaU_Vol_SoLID[N], deltaD_Vol_SoLID[N];
	double deltaU_R_SoLID[N], deltaD_R_SoLID[N];
	/*}}}*/

    TString Particle=""; cerr<<"--- Particle = (pip or pim) "; cin>>Particle;
	ifstream tensor(Form("tensor_charge_%s.dat",Particle.Data()));
	cerr<<"--- Reading Data ..."<<endl;

	/*Tensor Charge{{{*/
	int i=0;
	while(!(tensor.eof())){
		deltaU_Exp[i]=0.0; deltaD_Exp[i]=0.0;
		deltaU_Vol[i]=0.0; deltaD_Vol[i]=0.0;
		deltaU_Exp_SoLID[i]=0.0; deltaD_Exp_SoLID[i]=0.0;
		deltaU_Vol_SoLID[i]=0.0; deltaD_Vol_SoLID[i]=0.0;
		tensor >> Bin[i] >> Scale_Temp[i] 
			>> deltaU_Exp[i] >> deltaU_Vol[i] >> deltaD_Exp[i] >> deltaD_Vol[i]
			>> deltaU_Exp_New[i] >> deltaU_Vol_New[i] >> deltaD_Exp_New[i] >> deltaD_Vol_New[i]
			>> deltaU_Exp_SoLID[i] 
			>> deltaU_Vol_SoLID[i]
			>> deltaD_Exp_SoLID[i] 
			>> deltaD_Vol_SoLID[i];
		deltaU_R_New[i] =deltaU_Vol_New[i]/deltaU_Vol[i];
		deltaD_R_New[i] =deltaD_Vol_New[i]/deltaD_Vol[i];
		deltaU_R_SoLID[i] =deltaU_Vol_SoLID[i]/deltaU_Vol[i];
		deltaD_R_SoLID[i] =deltaD_Vol_SoLID[i]/deltaD_Vol[i];
			//cerr<<Form("=== I=%2d, dR=%e, dU_Err=%e/%e, dR=%e, dD_Err=%e/%e", i, deltaU_R_SoLID[i],deltaU_Vol_SoLID[i],deltaU_Vol[i],deltaD_R_SoLID[i],deltaD_Vol_SoLID[i],deltaD_Vol[i])<<endl;
		i++;
	}
	tensor.close(); 
	/*}}}*/

	/*Plot Tensor Charge{{{*/
	cerr<<"--- Making Plots ..."<<endl;
	TCanvas *c0 = new TCanvas("c0","c0",800,600);
	c0->Divide(2,2);
	c0->cd(1);	
//	TH2D *h1 = new TH2D("h1","Tensor Charge vs Scale", 100, 0.0, 8.0, 100, 0, 0.7);
//	h1->SetXTitle("Beam-Time (Days)");
	TH2D *h1 = new TH2D("h1","Tensor Charge vs Scale", 100, 0.0, 110.0, 100, 0.3, 0.5);
	h1->SetXTitle("Scale");
	h1->SetYTitle("#delta U");
	h1->Draw();
	TGraphErrors *gr1 = new TGraphErrors(N, Scale, deltaU_Exp_SoLID,Zero, deltaU_Vol_SoLID);
	//TGraphErrors *gr1 = new TGraphErrors(N, Scale, deltaU_Exp_New,Zero, deltaU_Vol_New);
	gr1->SetMarkerStyle(20);
	gr1->SetMarkerColor(2);
	gr1->Draw("p");

	c0->cd(2);
	//TH2D *h11 = new TH2D("h11","Tensor Charge vs Scale", 100, 0.0, 8.0, 100, -0.50, 0.10);
	//h11->SetXTitle("Beam-Time (Days)");
	TH2D *h11 = new TH2D("h11","Tensor Charge vs Scale", 100, 0.0, 110.0, 100, -0.30,-0.10);
	h11->SetXTitle("Scale");
	h11->SetYTitle("#delta D");
	h11->Draw();
	TGraphErrors *gr2 = new TGraphErrors(N, Scale, deltaD_Exp_SoLID,Zero, deltaD_Vol_SoLID);
	//TGraphErrors *gr2 = new TGraphErrors(N, Scale, deltaD_Exp_New,Zero, deltaD_Vol_New);
	gr2->SetMarkerStyle(21);
	gr2->SetMarkerColor(4);
	gr2->Draw("p");

	c0->cd(3);
	TH2D *h2 = new TH2D("h2","Tensor Charge vs Scale", 100, 0.0, 110.0, 100, 0, 1.);
	h2->SetXTitle("Scale");
	h2->SetYTitle("#sigma(#delta U)^{SoLID}/#sigma(#delta U)^{Data}");
	h2->Draw();
	TGraphErrors *gr3 = new TGraphErrors(N, Scale, deltaU_R_SoLID,Zero, Zero);
	gr3->SetMarkerStyle(20);
	gr3->SetMarkerColor(2);
	gr3->Draw("p");
	gr3->Fit("pol2","","",19,101);

	c0->cd(4);	
	TH2D *h21 = new TH2D("h21","Tensor Charge vs Scale", 100, 0.0, 110.0, 100, 0, 1.);
	h21->SetYTitle("#sigma(#delta U)^{SoLID}/#sigma(#delta U)^{Data}");
	h21->Draw();
	TGraphErrors *gr4 = new TGraphErrors(N, Scale, deltaD_R_SoLID,Zero, Zero);
	gr4->SetMarkerStyle(21);
	gr4->SetMarkerColor(4);
	gr4->Draw("p");
	gr4->Fit("pol2","","",19,101);
	c0->Print(Form("Resol_Tensor_Charge_%s.png", Particle.Data()));
	/*}}}*/
}
