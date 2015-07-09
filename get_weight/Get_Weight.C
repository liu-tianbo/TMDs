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
	//const int N_Replica = 10000;
	const int N_Replica = 2000;
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

   	double Z[500], xB[500], Q2[500], Pt[500], Sigma_Unp[500], Asym[500], Asym_Err[500];
	double deltaU[500], deltaD[500], deltaU_SoLID[500], deltaD_SoLID[500];
	int Bin[500];

	double Scale_Factor = 0.0; cerr<<"--- Scale the Astat = "; cin >> Scale_Factor;
	int N_Count =0;
	TString FileName;
	double ChiSQ_Sum=0, Weight_Sum=0;
	for(int j=0;j<N_Replica;j++){
		i=0;
		FileName = Form("../collins/results/solid_data_3he_%s_%d.dat",Particle.Data(),j);
		ifstream infile(FileName);
		if(infile){
			//cerr<<"---- Reading file-->"<<FileName.Data()<<"\r";
			Z[i] = 0.0;  xB[i] = 0.0;  Q2[i] = 0.0; Pt[i] = 0.0; Asym[i] = 0.0; Asym_Err[i] = 0.0; 
			deltaU[i] = 0.0;   deltaD[i] = 0.0;	deltaU_SoLID[i] = 0.0;  deltaD_SoLID[i] = 0.0; 
			while(
				infile >> Bin[i]>> Z[i]>> xB[i]>> Q2[i] >> Pt[i] 
					>> Sigma_Unp[i] >> Asym[i] >> Asym_Err[i] 
					>> deltaU[i] >> deltaD[i] >> deltaU_SoLID[i] >> deltaD_SoLID[i]){
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
				//ChiSQ[j] += pow((Asym_New0[k]-Asym[k])/(Asym_Err0[k]*Scale_Factor),2);
				ChiSQ[j] += pow((Asym0[k]-Asym[k])/(Asym_Err0[k]*Scale_Factor),2);
				//cerr<<Form("--- N=%d, k=%d, Asym0 = %10.4e, Asym = %10.4e, Asym_Err = %10.4e, ChiSQ=%f",
				//		j,k, Asym_New0[k], Asym[k], Asym_Err[k], ChiSQ[j])<<endl;
			}
			ChiSQ_Sum+=ChiSQ[j];
			Weight[j] = TMath::Exp(-0.5 * ChiSQ[j]);
			Weight_Sum += Weight[j];
			//if(ChiSQ[j] > 1e3) continue;
			cerr<<Form("--- j=%10d, ChiSQ = %10.4f, Weight = %10.4f",j,ChiSQ[j], Weight[j])<<"\r";//<<endl;

			h1->Fill(Weight[j]);
			h2->Fill(j,Weight[j]);
			N_Count++;
		}else
			cerr<<Form("*** File %s doesn't exist, skip!", FileName.Data())<<endl;
	}
	cerr<<"--- Total valide replica = "<< N_Count<<endl;
	/*}}}*/
	
	/*Fill into ROOT trees{{{*/
	double iAsym,iAsymErr,iChiSQ,iW,iD,iU,iZ,iX,iQ2,iPt,iD_SoLID,iU_SoLID,iSigma, iHu, iHd;
	int iBin, iN;
	TFile *file = new TFile(Form("Weight_F%d_new.root",(int)(Scale_Factor)),"recreate");
	TTree *T = new TTree("T","T");
	TTree *W = new TTree("W","W");
	TTree *H = new TTree("H","H");
	T->Branch("iAsym", &iAsym, "iAsym/D");
	T->Branch("iAsymErr", &iAsymErr, "iAsymErr/D");
	T->Branch("iBin", &iBin, "iBin/I");
	T->Branch("iN", &iN, "iN/I");
	T->Branch("iZ", &iZ, "iZ/D");
	T->Branch("iX", &iX, "iX/D");
	T->Branch("iQ2", &iQ2, "iQ2/D");
	T->Branch("iPt", &iPt, "iPt/D");
	T->Branch("iSigma", &iSigma, "iSigma/D");
	T->Branch("iU", &iU, "iU/D");
	T->Branch("iD", &iD, "iD/D");
	T->Branch("iU_SoLID", &iU_SoLID, "iU_SoLID/D");
	T->Branch("iD_SoLID", &iD_SoLID, "iD_SoLID/D");
	T->Branch("iW", &iW, "iW/D");

	W->Branch("iChiSQ", &iChiSQ, "iChiSQ/D");
	W->Branch("iW", &iW, "iW/D");
	W->Branch("iU", &iU, "iU/D");
	W->Branch("iD", &iD, "iD/D");

	H->Branch("iHu", &iHu, "iHu/D");
	H->Branch("iHd", &iHd, "iHd/D");
	H->Branch("iX", &iX, "iX/D");
	H->Branch("iW", &iW, "iW/D");
	H->Branch("iN", &iN, "iN/I");

	for(int j=0;j<N_Replica;j++){
		Weight[j] /=Weight_Sum;
		iChiSQ = ChiSQ[j];
		iW = Weight[j];
		iU = deltaU_Cal[j];
		iD = deltaD_Cal[j];
		W->Fill();
			
		outfile<<Form("%10d %10.4f %10.4f %10.4e %10.4e %10.4e %10.4e",j,ChiSQ[j], Weight[j],deltaU_Cal[j],deltaD_Cal[j],deltaU_SoLID_Cal[j],deltaD_SoLID_Cal[j])<<endl;
		cerr<<Form("--- j=%10d, ChiSQ = %10.4f, Weight = %10.4f",j,ChiSQ[j], Weight[j])<<"\r";//<<endl;
	}

	for(int j=0;j<N_Replica;j++){
		i=0;

		FileName = Form("../collins/results/solid_data_3he_%s_%d.dat",Particle.Data(),j);
		ifstream infile(FileName);
		if(infile){
			//cerr<<"---- Reading file-->"<<FileName.Data()<<endl;
			Z[i] = 0.0;  xB[i] = 0.0;  Q2[i] = 0.0; Pt[i] = 0.0; Asym[i] = 0.0; Asym_Err[i] = 0.0; 
			deltaU[i] = 0.0;   deltaD[i] = 0.0;	deltaU_SoLID[i] = 0.0;  deltaD_SoLID[i] = 0.0; 
			while(infile >> Bin[i]>> Z[i]>> xB[i]>> Q2[i] >> Pt[i] 
					>> Sigma_Unp[i] >> Asym[i] >> Asym_Err[i] 
					>> deltaU[i] >> deltaD[i] >> deltaU_SoLID[i] >> deltaD_SoLID[i]){
				iBin = Bin[i];
				iN = j;
				iZ = Z[i];
				iX = xB[i];
				iQ2 = Q2[i];
				iPt = Pt[i];
				iSigma = Sigma_Unp[i];
				iAsym = Asym[i];
				iAsymErr = Asym_Err[i];
				iU = deltaU[i];
				iD = deltaD[i];
				iU_SoLID = deltaU_SoLID[i];
				iD_SoLID = deltaD_SoLID[i];
				iW = Weight[j];
				T->Fill();
				i++;
			}
			infile.close();
		}
	}

	for(int j=0;j<N_Replica;j++){
		i=0;
		iN=0;
		FileName = Form("../collins/results/transversity_u_%d.dat",j);
		ifstream infile0(FileName);
		FileName = Form("../collins/results/transversity_d_%d.dat",j);
		ifstream infile1(FileName);
		if(infile0){
			//while(!(infile0.eof())){
			for(int l=0;l<101;l++){
				infile0 >> iX >> iHu;
				infile1 >> iX >> iHd;
				iN = j;
				iW = Weight[j];
				H->Fill();
			}
		}
		infile0.close(); infile1.close();
	}

	T->Write();H->Write(); W->Write();file->Close();
	/*}}}*/

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
	cerr<<Form("  All: dU = %8.5f, du_V = %8.5f, dD=%8.5f, dD_V=%8.5f", deltaU_Exp,deltaU_Vol, deltaD_Exp,deltaD_Vol)<<endl;
	cerr<<Form("SoLID: dU = %8.5f, du_V = %8.5f, dD=%8.5f, dD_V=%8.5f", deltaU_Exp_SoLID,deltaU_Vol_SoLID, deltaD_Exp_SoLID,deltaD_Vol_SoLID)<<endl;
	/*}}}*/

	/*Plotting{{{*/
	/*
	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	c1->Divide(1,2);
	c1->cd(1); h1->Draw();
	c1->cd(2); h2->Draw();

	/*}}}*/
}
