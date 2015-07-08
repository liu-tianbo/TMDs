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

void Get_Weight(){
	/*Load the best fit values{{{*/
	TString Particle = ""; cerr<<"Particle = (pip or pim)"; cin >> Particle;
	const int N_Replica = 10000;
	ifstream infile0(Form("new_solid_data_3he_%s_0.dat",Particle.Data()));
	double Z0[500], xB0[500], Q20[500], Pt0[500], Sigma_Unp0[500], Asym0[500], Asym_New0[500], Asym_Err0[500];
	double deltaU0[500], deltaD0[500], deltaU_SoLID0[500], deltaD_SoLID0[500];
	int Bin0[500];
	int i=0;
	//while(!(infile0.eof())){
	while(infile0 >> Bin0[i]>> Z0[i]>> xB0[i]>> Q20[i] >> Pt0[i] 
			>> Sigma_Unp0[i] >> Asym0[i] >> Asym_New0[i] >> Asym_Err0[i] 
			>> deltaU0[i] >> deltaD0[i] >> deltaU_SoLID0[i] >> deltaD_SoLID0[i]){
		cerr<<"---- Reading A0 data "<<i<<"\r";
		
		i++;
	}
	cerr<<"Done~!"<<endl;
	infile0.close();
	/*}}}*/

	/*Load replica and calculate weight{{{*/
	ofstream outfile(Form("weight_solid_data_3he_%s.dat",Particle.Data()));
	gRandom->SetSeed(0);
	TH1D *h1 = new TH1D("h1","",1000, 0, 1.0);
	TH2D *h2 = new TH2D("h2","",1000,0,1000,1000, 0, 1.0);
	double Weight[N_Replica], ChiSQ[N_Replica];
	double deltaU_Cal[N_Replica], deltaD_Cal[N_Replica];
	double deltaU_SoLID_Cal[N_Replica], deltaD_SoLID_Cal[N_Replica];

   	double iAsym, iChiSQ,iW,W,iD,iU;
	int iBin, iN;
	TFile *file = new TFile("test.root","recreate");
	TTree *T = new TTree("T","T");
	TTree *T1 = new TTree("T1","T1");
	T->Branch("iAsym", &iAsym, "iAsym/D");
	T->Branch("iBin", &iBin, "iBin/I");
	T->Branch("iN", &iN, "iN/I");
	T->Branch("W", &W, "W/D");
	T1->Branch("iChiSQ", &iChiSQ, "iChiSQ/D");
	T1->Branch("iW", &iW, "iW/D");
	T1->Branch("iU", &iU, "iU/D");
	T1->Branch("iD", &iD, "iD/D");

	double Z[500], xB[500], Q2[500], Pt[500], Sigma_Unp[500], Asym[500], Asym_Err[500];
	double deltaU[500], deltaD[500], deltaU_SoLID[500], deltaD_SoLID[500];
	int Bin[500];

	int N_Count =0;
	TString FileName;
	//for(int j=0;j<N_Replica;j++){
	double ChiSQ_Sum=0;
	double Weight_Sum=0;
	for(int j=0;j<2000;j++){
		i=0;
		FileName = Form("../collins/results/solid_data_3he_%s_%d.dat",Particle.Data(),j);
		ifstream infile(FileName);
		if(infile){
			//cerr<<"---- Reading file-->"<<FileName.Data()<<endl;
			Z[j] = 0.0;  xB[j] = 0.0;  Q2[j] = 0.0; Pt[j] = 0.0; Asym[j] = 0.0; Asym_Err[j] = 0.0; 
			deltaU[j] = 0.0;   deltaD[j] = 0.0;	deltaU_SoLID[j] = 0.0;  deltaD_SoLID[j] = 0.0; 
			while(
				infile >> Bin[i]>> Z[i]>> xB[i]>> Q2[i] >> Pt[i] 
					>> Sigma_Unp[i] >> Asym[i] >> Asym_Err[i] 
					>> deltaU[i] >> deltaD[i] >> deltaU_SoLID[i] >> deltaD_SoLID[i]){
				iBin = i;
				iN = j;
				iAsym = Asym[i];
				//T->Fill();
				
				i++;
			}
			infile.close();
			int Bin_Total = i-1;

			deltaU_Cal[j]=deltaU[Bin_Total];
			deltaD_Cal[j]=deltaD[Bin_Total];
			deltaU_SoLID_Cal[j]=deltaU_SoLID[Bin_Total];
			deltaD_SoLID_Cal[j]=deltaD_SoLID[Bin_Total];

			ChiSQ[j] = 0;
			for(int k=0;k<Bin_Total;k++){
				ChiSQ[j] += pow((Asym_New0[k]-Asym[k])/Asym_Err0[k]/1e3,2);
				//cerr<<Form("--- N=%d, k=%d, Asym0 = %10.4e, Asym = %10.4e, Asym_Err = %10.4e, ChiSQ=%f",
				//		j,k, Asym_New0[k], Asym[k], Asym_Err[k], ChiSQ[j])<<endl;
			}
			ChiSQ_Sum+=ChiSQ[j];
			Weight[j] = TMath::Exp(-0.5 * ChiSQ[j]);
			Weight_Sum += Weight[j];
			//ChiSQ = sqrt(ChiSQ);
			//if(ChiSQ[j] > 1e3) continue;
			cerr<<Form("--- j=%10d, ChiSQ = %10.4f, Weight = %10.4f",j,ChiSQ[j], Weight[j])<<"\r";//<<endl;

			outfile<<Form("%10d %10.4f %10.4f %10.4e %10.4e %10.4e %10.4e",j,ChiSQ[j], Weight[j],deltaU_Cal[j],deltaD_Cal[j],deltaU_SoLID_Cal[j],deltaD_SoLID_Cal[j])<<endl;

			h1->Fill(Weight[j]);
			h2->Fill(j,Weight[j]);
			N_Count++;
		}else
			cerr<<Form("*** File %s doesn't exist, skip!", FileName.Data())<<endl;
	}
	cerr<<"--- Total valide replica = "<< N_Count<<endl;
	/*}}}*/
	
	/*Load replica and calculate weight{{{*/
	for(int j=0;j<2000;j++){
		i=0;
		FileName = Form("../collins/results/solid_data_3he_%s_%d.dat",Particle.Data(),j);
		ifstream infile(FileName);
		if(infile){
			//cerr<<"---- Reading file-->"<<FileName.Data()<<endl;
			Z[j] = 0.0;  xB[j] = 0.0;  Q2[j] = 0.0; Pt[j] = 0.0; Asym[j] = 0.0; Asym_Err[j] = 0.0; 
			deltaU[j] = 0.0;   deltaD[j] = 0.0;	deltaU_SoLID[j] = 0.0;  deltaD_SoLID[j] = 0.0; 
			while(
					infile >> Bin[i]>> Z[i]>> xB[i]>> Q2[i] >> Pt[i] 
					>> Sigma_Unp[i] >> Asym[i] >> Asym_Err[i] 
					>> deltaU[i] >> deltaD[i] >> deltaU_SoLID[i] >> deltaD_SoLID[i]){
				iBin = i;
				iN = j;
				iAsym = Asym[i];
				W = Weight[j];
				T->Fill();

				i++;
			}
			infile.close();
		}
	}
	cerr<<"--- Total valide replica = "<< N_Count<<endl;
	/*}}}*/
    
	for(int j=0;j<2000;j++){
		Weight[j] /=Weight_Sum;
		iChiSQ = ChiSQ[j];
		iW = Weight[j];
		iU = deltaU_Cal[j];
		iD = deltaD_Cal[j];
		T1->Fill();

	}
	T->Write(); T1->Write();file->Close();

	/*Calculate observables{{{*/
	double deltaU_Exp=0.0, deltaD_Exp=0.0;
	double deltaU_Vol=0.0, deltaD_Vol=0.0;
	double deltaU_Exp_SoLID=0.0, deltaD_Exp_SoLID=0.0;
	double deltaU_Vol_SoLID=0.0, deltaD_Vol_SoLID=0.0;
	for(int j=0;j<N_Count;j++){
		deltaU_Exp += 1/N_Count * deltaU_Cal[j];	
		deltaD_Exp += 1/N_Count * deltaD_Cal[j];	
		deltaU_Exp_SoLID += Weight[j] * deltaU_Cal[j];	
		deltaD_Exp_SoLID += Weight[j] * deltaD_Cal[j];	
	}

	for(int j=0;j<N_Count;j++){
		deltaU_Vol += 1./N_Count* pow((deltaU_Cal[j]-deltaU_Exp),2);
		deltaD_Vol += 1./N_Count* pow((deltaD_Cal[j]-deltaD_Exp),2);
		deltaU_Vol_SoLID += Weight[j] * pow((deltaU_Cal[j]-deltaU_Exp),2);
		deltaD_Vol_SoLID += Weight[j] * pow((deltaD_Cal[j]-deltaD_Exp),2);
	}
	/*}}}*/

	/*Plotting{{{*/
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	c1->Divide(1,2);
	c1->cd(1); h1->Draw();
	c1->cd(2); h2->Draw();
	/*}}}*/
}
