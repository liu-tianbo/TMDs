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

void Trans(){
//int main(){
	/*Define{{{*/
	//const int N=17;
	//double Scale[N]={1000.,900.,800.,700.,600.,500.,400.,300.,200.,100.,90.,80.,70.,60.,50.,40.,30.};
	const int N=9;
	const double Scale[N]={1000.,900.,800.,700.,600.,500.,400.,300.,200.};
	double Zero[N]={N*0.};
	double Scale_Temp[N];
	int Bin[N],Con[N][101]; //double Scale[N];
	double X[N][101], Hu_Exp[N][101], Hd_Exp[N][101];
	double Hu_Vol[N][101], Hd_Vol[N][101];
	double Hu_Exp_SoLID[N][101], Hd_Exp_SoLID[N][101];
	double Hu_Vol_SoLID[N][101], Hd_Vol_SoLID[N][101];
   	double Hu_R_SoLID[101], Hd_R_SoLID[101];
	double Hu_Org[101], Hd_Org[101];
    /*}}}*/

    TString Particle=""; cerr<<"--- Particle = (pip or pim) "; cin>>Particle;
	ifstream trans(Form("transversity_%s.dat",Particle.Data()));
	cerr<<"--- Reading Data ..."<<endl;
	
	/*101 Transversity Values{{{*/
	int iN=0, iB=0;
	while(!(trans.eof())){
		trans>>	iN>> iB;
		X[iN][iB] =0.0;
		Hu_Exp[iN][iB]=0; Hd_Exp[iN][iB]=0;
		Hu_Vol[iN][iB]=0; Hd_Vol[iN][iB]=0;
		Hu_Exp_SoLID[iN][iB]=0; Hd_Exp_SoLID[iN][iB]=0;
		Hu_Vol_SoLID[iN][iB]=0; Hd_Vol_SoLID[iN][iB]=0;
		trans>>Scale_Temp[iN]>>X[iN][iB] 
			>>Hu_Exp[iN][iB]
			>>Hu_Vol[iN][iB]
			>>Hd_Exp[iN][iB]
			>>Hd_Vol[iN][iB]
			>>Hu_Exp_SoLID[iN][iB]
			>>Hu_Vol_SoLID[iN][iB]
			>>Hd_Exp_SoLID[iN][iB]
			>>Hd_Vol_SoLID[iN][iB]
			>>Hu_Org[iB] >> Hd_Org[iB];
	}
	trans.close();
	/*}}}*/

	/*Plot Transversity{{{*/	
	cerr<<"--- Making Plots ..."<<endl;
	TCanvas *c3 = new TCanvas("c3","c3",800,600);
	TH2D* h3 = new TH2D("h3","Transversity",100, 0., 1100.0, 100, 0.,0.14);
	h3->SetXTitle("x");
	h3->SetYTitle("#sigma(h^{d}_{1}(x))");
	h3->Draw("");

	ofstream outfile(Form("trans_fit_%s",Particle.Data()));
	double X1[101], Hu1[N], Hd1[N], Hu_Vol1[N],Hd_Vol1[N];
	for(int k=0;k<101;k++)
		  X1[k] = X[0][k];
	TGraphErrors *grh;
	TGraphErrors *grh_SoLID[N];
	for(int k=0;k<100;k++){
		for(int l=0;l<N;l++){
			//X1[k] = X[l][k];
			Hu1[l] = Hu_Exp_SoLID[l][k];
			Hd1[l] = Hd_Exp_SoLID[l][k];
			Hu_Vol1[l] = Hu_Vol_SoLID[l][k];
			Hd_Vol1[l] = Hd_Vol_SoLID[l][k];
			cerr<<Form("-- s = %f,   Hu=%f", Scale[l],Hd_Vol1[l])<<endl;
		}

		c3->Clear();
		h3->Draw();	
		grh = new TGraphErrors(N, Scale, Hd_Vol1, Zero, Zero);
		grh->SetMarkerColor(20);
		grh->SetMarkerColor(4);
		grh->Draw("P");
		grh->Fit("pol1");
		c3->Print(Form("./plots/trans_fit_%d.png", k));
		TF1 *myfit = grh->GetFunction("pol1");
		double sigma = myfit->GetParameter(0)+myfit->GetParameter(1);
		outfile<<Form("%10.6f %10.6f", X1[k], sigma)<<endl;;
	}
	/*
	   TGraphErrors *grh0;
	   grh0 = new TGraphErrors(101, X1, Hu_Org, Zero, Zero);
	   grh0->SetMarkerColor(22);
	   grh0->SetMarkerColor(4);
	   grh0->SetFillColor(i);
	   grh0->Draw("P");
	   */
	/*}}}*/
}
