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

//void Get_Data(){
int main(){
	cerr<<"--- Start ..."<<endl;
	const int N_Replica=2500000;
	const int N=15;
	const int Scale[N]={1000,900,800,700,600,500,400,300,200,100,80,60,40,20,1};


	double deltaU_Exp[N], deltaD_Exp[N];
	double deltaU_Vol[N], deltaD_Vol[N];
	double deltaU_Exp_New[N], deltaD_Exp_New[N];
	double deltaU_Vol_New[N], deltaD_Vol_New[N];

	double deltaU_Exp_EX[N], deltaD_Exp_EX[N];
	double deltaU_Vol_EX[N], deltaD_Vol_EX[N];
	double deltaU_Exp_EX_New[N], deltaD_Exp_EX_New[N];
	double deltaU_Vol_EX_New[N], deltaD_Vol_EX_New[N];

	static double X_Temp[N_Replica][100];
	static double Hu[N_Replica][100]; 
	static double Hd[N_Replica][100];
	static double Weight[N_Replica][100];
	double X[100], Hu_Exp[N][100], Hd_Exp[N][100], Hu_Vol[N][100], Hd_Vol[N][100];
	double Hu_Org[100], Hd_Org[100];
	double Hu_Exp_New[N][100], Hd_Exp_New[N][100];
	double Hu_Vol_New[N][100], Hd_Vol_New[N][100];

	/*Readin Data{{{*/
	TString Experiment = ""; cerr<<"--- Experiment = (solid or clas or sbs) "; cin >> Experiment;
	//TString Target = ""; cerr<<"--- Target = (p or 3he) "; cin >> Target;
	//TString Particle=""; cerr<<"--- Particle = (pip or pim) "; cin>>Particle;
	ofstream tensor(Form("%s_tensor_charge.dat",Experiment.Data()));
	ofstream trans(Form("%s_transversity.dat",Experiment.Data()));

	cerr<<"--- Reading Data ..."<<endl;
	TString FileName = "";
	int Norm = 0;
	for(int i=0;i<N;i++){
		double iAsym,iAsymErr,iChiSQ,iW,iD,iU,iZ,iX,iQ2,iPt,iD_EX,iU_EX,iSigma, iHu, iHd;
		int iBin, iN,iCount;
		/*Define Trees{{{*/
		//TFile *file = new TFile(FileName.Data(),"r");
		//TTree *T = (TTree*) file->Get("T");
		//TTree *W = (TTree*) file->Get("W");
		//TTree *H = (TTree*) file->Get("H");
		TChain *T = new TChain("T");
		TChain *W = new TChain("W");
		TChain *H = new TChain("H");
		FileName = Form("../get_weight/results/more_Weight_%s_p_pip_F%d.root",Experiment.Data(),Scale[i]);
		T->Add(FileName.Data());
		W->Add(FileName.Data());
		H->Add(FileName.Data());
		cerr<<"--- Reading File = "<<FileName.Data()<<endl;
		FileName = Form("../get_weight/results/more_Weight_%s_p_pim_F%d.root",Experiment.Data(),Scale[i]);
		T->Add(FileName.Data());
		W->Add(FileName.Data());
		H->Add(FileName.Data());
		cerr<<"--- Reading File = "<<FileName.Data()<<endl;
		Norm = 2;
		if(Experiment=="solid"){
			FileName = Form("../get_weight/results/more_Weight_%s_3he_pip_F%d.root",Experiment.Data(),Scale[i]);
			T->Add(FileName.Data());
			W->Add(FileName.Data());
			H->Add(FileName.Data());
			cerr<<"--- Reading File = "<<FileName.Data()<<endl;
			FileName = Form("../get_weight/results/more_Weight_%s_3he_pim_F%d.root",Experiment.Data(),Scale[i]);
			T->Add(FileName.Data());
			W->Add(FileName.Data());
			H->Add(FileName.Data());
			cerr<<"--- Reading File = "<<FileName.Data()<<endl;
			Norm = 4;
		}
			
		T->SetBranchAddress("iAsym", &iAsym);
		T->SetBranchAddress("iAsymErr", &iAsymErr);
		T->SetBranchAddress("iBin", &iBin);
		T->SetBranchAddress("iN", &iN);
		T->SetBranchAddress("iZ", &iZ);
		T->SetBranchAddress("iX", &iX);
		T->SetBranchAddress("iQ2", &iQ2);
		T->SetBranchAddress("iPt", &iPt);
		T->SetBranchAddress("iSigma", &iSigma);
		T->SetBranchAddress("iU", &iU);
		T->SetBranchAddress("iD", &iD);
		T->SetBranchAddress("iU_EX", &iU_EX);
		T->SetBranchAddress("iD_EX", &iD_EX);
		T->SetBranchAddress("iW", &iW);
		T->SetBranchAddress("iCount", &iCount);

		W->SetBranchAddress("iChiSQ", &iChiSQ);
		W->SetBranchAddress("iW", &iW);
		W->SetBranchAddress("iU", &iU);
		W->SetBranchAddress("iD", &iD);
		W->SetBranchAddress("iU_EX", &iU_EX);
		W->SetBranchAddress("iD_EX", &iD_EX);
		W->SetBranchAddress("iN", &iN);
		W->SetBranchAddress("iCount", &iCount);
		int N_W = W->GetEntries();
		int N_W_Count = W->GetEntries("iW>-1.0");

		H->SetBranchAddress("iHu", &iHu);
		H->SetBranchAddress("iHd", &iHd);
		H->SetBranchAddress("iX", &iX);
		H->SetBranchAddress("iW", &iW);
		H->SetBranchAddress("iN", &iN);
		H->SetBranchAddress("iBin", &iBin);
		H->SetBranchAddress("iCount", &iCount);
		int N_H = H->GetEntries();
		int N_H_Count = H->GetEntries("iW>-1.0")/100;
		/*}}}*/

		/*Tensor Charge{{{*/
		deltaU_Exp[i]=0.0; deltaD_Exp[i]=0.0;
		deltaU_Vol[i]=0.0; deltaD_Vol[i]=0.0;
		deltaU_Exp_New[i]=0.0; deltaD_Exp_New[i]=0.0;
		deltaU_Vol_New[i]=0.0; deltaD_Vol_New[i]=0.0;
		deltaU_Exp_EX[i]=0.0; deltaD_Exp_EX[i]=0.0;
		deltaU_Vol_EX[i]=0.0; deltaD_Vol_EX[i]=0.0;
		deltaU_Exp_EX_New[i]=0.0; deltaD_Exp_EX_New[i]=0.0;
		deltaU_Vol_EX_New[i]=0.0; deltaD_Vol_EX_New[i]=0.0;

		for(int j=0;j<N_W;j++){
			W->GetEntry(j);
		    iCount *= Norm;
			if(j==0)
				cerr<<Form("  iCount = %d, N_W_Count = %d", iCount, N_W_Count)<<endl;
			iW /= iW;
			if(iW>-1.){
				deltaU_Exp[i] += 1./N_W_Count * iU;	
				deltaD_Exp[i] += 1./N_W_Count * iD;	
				deltaU_Exp_New[i] += iW * iU;	
				deltaD_Exp_New[i] += iW * iD;	

				deltaU_Exp_EX[i] += 1./N_W_Count * iU_EX;	
				deltaD_Exp_EX[i] += 1./N_W_Count * iD_EX;	
				deltaU_Exp_EX_New[i] += iW * iU_EX;	
				deltaD_Exp_EX_New[i] += iW * iD_EX;
				//cerr<<Form("iU_EX = %f,  iD_EX=%f", iU_EX, iD_EX)<<endl;	
			}
		}
		for(int j=0;j<N_W;j++){
			W->GetEntry(j);
		    iCount *= Norm;
			iW /= iW;
			if(iW>-1.){
				deltaU_Vol[i] += 1./N_W_Count* pow((iU-deltaU_Exp[i]),2);
				deltaD_Vol[i] += 1./N_W_Count* pow((iD-deltaD_Exp[i]),2);
				deltaU_Vol_New[i] += iW * pow((iU-deltaU_Exp_New[i]),2);
				deltaD_Vol_New[i] += iW * pow((iD-deltaD_Exp_New[i]),2);

				deltaU_Vol_EX[i] += 1./N_W_Count * pow((iU_EX-deltaU_Exp_EX[i]),2);
				deltaD_Vol_EX[i] += 1./N_W_Count * pow((iD_EX-deltaD_Exp_EX[i]),2);
				deltaU_Vol_EX_New[i] += iW * pow((iU_EX-deltaU_Exp_EX_New[i]),2);
				deltaD_Vol_EX_New[i] += iW * pow((iD_EX-deltaD_Exp_EX_New[i]),2);
			}
		}

		deltaU_Vol[i] = sqrt(deltaU_Vol[i] );
		deltaD_Vol[i] = sqrt(deltaD_Vol[i] );
		deltaU_Vol_New[i] = sqrt(deltaU_Vol_New[i] );
		deltaD_Vol_New[i] = sqrt(deltaD_Vol_New[i] );

		deltaU_Vol_EX[i] = sqrt(deltaU_Vol_EX[i] );
		deltaD_Vol_EX[i] = sqrt(deltaD_Vol_EX[i] );
		deltaU_Vol_EX_New[i] = sqrt(deltaU_Vol_EX_New[i] );
		deltaD_Vol_EX_New[i] = sqrt(deltaD_Vol_EX_New[i] );

		cerr<<Form("EX: dU = %8.5f +/- %8.5f, dD=%8.5f +/- %8.5f", deltaU_Exp_EX[i],deltaU_Vol_EX[i], deltaD_Exp_EX[i],deltaD_Vol_EX[i])<<endl;
		cerr<<Form("  New: dU = %8.5f +/- %8.5f, dD=%8.5f +/- %8.5f", deltaU_Exp_EX_New[i],deltaU_Vol_EX_New[i], deltaD_Exp_EX_New[i],deltaD_Vol_EX_New[i])<<endl;

		tensor<<Form("%5d %10d %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e", 
				i, Scale[i], 
				deltaU_Exp[i], deltaU_Vol[i],deltaD_Exp[i], deltaD_Vol[i],
				deltaU_Exp_New[i], deltaU_Vol_New[i],deltaD_Exp_New[i], deltaD_Vol_New[i],
				deltaU_Exp_EX[i], deltaU_Vol_EX[i],deltaD_Exp_EX[i], deltaD_Vol_EX[i],
				deltaU_Exp_EX_New[i], deltaU_Vol_EX_New[i],deltaD_Exp_EX_New[i], deltaD_Vol_EX_New[i])<<endl;
		/*}}}*/

		/*100 Transversity Values{{{*/
	/*	for(int l=0;l<100;l++){
			X[l] =0.0;
			Hu_Exp[i][l]=0; Hd_Exp[i][l]=0;
			Hu_Vol[i][l]=0; Hd_Vol[i][l]=0;
			Hu_Exp_New[i][l]=0; Hd_Exp_New[i][l]=0;
			Hu_Vol_New[i][l]=0; Hd_Vol_New[i][l]=0;
			for(int k=0;k<N_W;k++){
				Hu[k][l]=0;  Hd[k][l]=0;
				Weight[k][l]=0;
			}
		}
		for(int j=0;j<N_H;j++){
			H->GetEntry(j);
			iCount *= Norm;
			if(j==0)
				cerr<<Form("  iCount = %d, N_H_Count = %d", iCount, N_H_Count)<<endl;
			iW /= iW;
			Hu[iN][iBin] = iHu;
			Hd[iN][iBin] = iHd;
			Weight[iN][iBin] = iW;
			X_Temp[iN][iBin] = iX;
			//cerr<<Form("%4d %4d %10.6f  %10.6f", iN, iBin, X_Temp[iN][iBin], Hu[iN][iBin],Hd[iN][iBin])<<endl;
		}
		for(int l=0;l<100;l++){
			for(int j=0;j<N_W;j++){
				if(Weight[i][l]>-1.){
					Hu_Exp[i][l] += 1./N_H_Count * Hu[j][l];	
					Hd_Exp[i][l] += 1./N_H_Count * Hd[j][l];	
					Hu_Exp_New[i][l] += Weight[j][l] * Hu[j][l];	
					Hd_Exp_New[i][l] += Weight[j][l] * Hd[j][l];	
				}
			}
			X[l] = X_Temp[0][l];
			Hu_Org[l] = Hu[0][l];	
			Hd_Org[l] = Hd[0][l];	
		}
		for(int l=0;l<100;l++){
			for(int j=0;j<N_W;j++){
				if(Weight[i][l]>-1.){
					Hu_Vol[i][l] += 1./N_H_Count* pow((Hu[l][j]-Hu_Exp[i][l]),2);
					Hd_Vol[i][l] += 1./N_H_Count* pow((Hd[l][j]-Hd_Exp[i][l]),2);
					Hu_Vol_New[i][l] += Weight[l][j] * pow((Hu[l][j]-Hu_Exp_New[i][l]),2);
					Hd_Vol_New[i][l] += Weight[l][j] * pow((Hd[l][j]-Hd_Exp_New[i][l]),2);
				}
			}
			Hu_Vol[i][l] = sqrt(Hu_Vol[i][l] );
			Hd_Vol[i][l] = sqrt(Hd_Vol[i][l] );
			Hu_Vol_New[i][l] = sqrt(Hu_Vol_New[i][l] );
			Hd_Vol_New[i][l] = sqrt(Hd_Vol_New[i][l] );
			//cerr<<Form("S=%4f Bin=%4d X=%10.6f Vol=%10.6e, Vol_EX=%10.6e", Scale[i], l, X[l], Hu_Vol[i][l], Hu_Vol_New[i][l])<<endl;
		}*/
		/*}}}*/
		//file->Close();
        delete T; delete W; delete H;
	}
	tensor.close(); 

	for(int l=0;l<100;l++){
		for(int i=0;i<N;i++){
			trans<<Form("%5d %5d %5d %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e", 
					i, l, Scale[i], X[l], Hu_Exp[i][l], Hu_Vol[i][l],Hd_Exp[i][l], Hd_Vol[i][l],
					Hu_Exp_New[i][l], Hu_Vol_New[i][l],Hd_Exp_New[i][l], Hd_Vol_New[i][l], Hu_Org[l], Hd_Org[l])<<endl;
		}
	}
	trans.close();
	/*}}}*/

}
