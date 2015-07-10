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

void GetData(){
//int main(){
	const int N_Replica=10000;
	//const int N=17;
	//double Scale[N]={1000.,900.,800.,700.,600.,500.,400.,300.,200.,100.,90.,80.,70.,60.,50.,40.,30.};
	const int N=9;
	double Scale[N]={1000.,900.,800.,700.,600.,500.,400.,300.,200.};
	double Zero[N]={N*0.};

	double deltaU_Exp[N], deltaD_Exp[N];
	double deltaU_Vol[N], deltaD_Vol[N];
	double deltaU_Exp_New[N], deltaD_Exp_New[N];
	double deltaU_Vol_New[N], deltaD_Vol_New[N];
	double deltaU_Exp_SoLID[N], deltaD_Exp_SoLID[N];
	double deltaU_Vol_SoLID[N], deltaD_Vol_SoLID[N];

	double X_Temp[N_Replica][101], Hu[N_Replica][101], Hd[N_Replica][101], Weight[N_Replica][101];
	double X[101], Hu_Exp[N][101], Hd_Exp[N][101], Hu_Vol[N][101], Hd_Vol[N][101];
	double Hu_Org[101], Hd_Org[101];
	double Hu_Exp_SoLID[N][101], Hd_Exp_SoLID[N][101];
	double Hu_Vol_SoLID[N][101], Hd_Vol_SoLID[N][101];

	/*Readin Data{{{*/
    TString Particle=""; cerr<<"--- Particle = (pip or pim) "; cin>>Particle;
	ofstream tensor(Form("tensor_charge_%s.dat",Particle.Data()));
	ofstream trans(Form("transversity_%s.dat",Particle.Data()));

	cerr<<"--- Reading Data ..."<<endl;
	TString FileName = "";
	for(int i=0;i<N;i++){
		FileName = Form("../get_weight/Weight_F%d_%s.root",(int)(Scale[i]),Particle.Data());
		cerr<<"--- Reading File = "<<FileName.Data()<<endl;
		TFile *file = new TFile(FileName.Data(),"r");
		/*Define Trees{{{*/
		double iAsym,iAsymErr,iChiSQ,iW,iD,iU,iZ,iX,iQ2,iPt,iD_SoLID,iU_SoLID,iSigma, iHu, iHd;
		int iBin, iN;
		TTree *T = (TTree*) file->Get("T");
		TTree *W = (TTree*) file->Get("W");
		TTree *H = (TTree*) file->Get("H");
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
		T->SetBranchAddress("iU_SoLID", &iU_SoLID);
		T->SetBranchAddress("iD_SoLID", &iD_SoLID);
		T->SetBranchAddress("iW", &iW);

		W->SetBranchAddress("iChiSQ", &iChiSQ);
		W->SetBranchAddress("iW", &iW);
		W->SetBranchAddress("iU", &iU);
		W->SetBranchAddress("iD", &iD);
		W->SetBranchAddress("iU_SoLID", &iU_SoLID);
		W->SetBranchAddress("iD_SoLID", &iD_SoLID);
		W->SetBranchAddress("iN", &iN);
		int N_W = W->GetEntries();

		H->SetBranchAddress("iHu", &iHu);
		H->SetBranchAddress("iHd", &iHd);
		H->SetBranchAddress("iX", &iX);
		H->SetBranchAddress("iW", &iW);
		H->SetBranchAddress("iN", &iN);
		H->SetBranchAddress("iBin", &iBin);
		int N_H = H->GetEntries();
		/*}}}*/

		/*Tensor Charge{{{*/
		deltaU_Exp[i]=0.0; deltaD_Exp[i]=0.0;
		deltaU_Vol[i]=0.0; deltaD_Vol[i]=0.0;
		deltaU_Exp_SoLID[i]=0.0; deltaD_Exp_SoLID[i]=0.0;
		deltaU_Vol_SoLID[i]=0.0; deltaD_Vol_SoLID[i]=0.0;

		for(int j=0;j<N_W;j++){
			W->GetEntry(j);
			deltaU_Exp[i] += 1./N_Replica * iU;	
			deltaD_Exp[i] += 1./N_Replica * iD;	
			deltaU_Exp_New[i] += iW * iU;	
			deltaD_Exp_New[i] += iW * iD;	
//			deltaU_Exp_SoLID[i] += iW * iU_SoLID;	
//			deltaD_Exp_SoLID[i] += iW * iD_SoLID;	
			deltaU_Exp_SoLID[i] += iW * iU;	
			deltaD_Exp_SoLID[i] += iW * iD;	
			}
		for(int j=0;j<N_W;j++){
			W->GetEntry(j);
			deltaU_Vol[i] += 1./N_W* pow((iU-deltaU_Exp[i]),2);
			deltaD_Vol[i] += 1./N_W* pow((iD-deltaD_Exp[i]),2);
			deltaU_Vol_New[i] += iW * pow((iU-deltaU_Exp_New[i]),2);
			deltaD_Vol_New[i] += iW * pow((iD-deltaD_Exp_New[i]),2);
			//deltaU_Vol_SoLID[i] += iW * pow((iU_SoLID-deltaU_Exp_SoLID[i]),2);
			//deltaD_Vol_SoLID[i] += iW * pow((iD_SoLID-deltaD_Exp_SoLID[i]),2);
			deltaU_Vol_SoLID[i] += iW * pow((iU-deltaU_Exp_SoLID[i]),2);
			deltaD_Vol_SoLID[i] += iW * pow((iD-deltaD_Exp_SoLID[i]),2);
			}
		deltaU_Vol[i] = sqrt(deltaU_Vol[i] );
		deltaD_Vol[i] = sqrt(deltaD_Vol[i] );
		deltaU_Vol_New[i] = sqrt(deltaU_Vol_New[i] );
		deltaD_Vol_New[i] = sqrt(deltaD_Vol_New[i] );
		deltaU_Vol_SoLID[i] = sqrt(deltaU_Vol_SoLID[i] );
		deltaD_Vol_SoLID[i] = sqrt(deltaD_Vol_SoLID[i] );
		cerr<<Form("  All: dU = %8.5f +/- %8.5f, dD=%8.5f +/- %8.5f", deltaU_Exp[i],deltaU_Vol[i], deltaD_Exp[i],deltaD_Vol[i])<<endl;
		cerr<<Form("SoLID: dU = %8.5f +/- %8.5f, dD=%8.5f +/- %8.5f", deltaU_Exp_SoLID[i],deltaU_Vol_SoLID[i], deltaD_Exp_SoLID[i],deltaD_Vol_SoLID[i])<<endl;
		
		tensor<<Form("%5d %10d %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e", 
				i, (int)(Scale[i]), 
				deltaU_Exp[i], deltaU_Vol[i],deltaD_Exp[i], deltaD_Vol[i],
				deltaU_Exp_New[i], deltaU_Vol_New[i],deltaD_Exp_New[i], deltaD_Vol_New[i],
				deltaU_Exp_SoLID[i], deltaU_Vol_SoLID[i],deltaD_Exp_SoLID[i], deltaD_Vol_SoLID[i])<<endl;
		/*}}}*/

		/*101 Transversity Values{{{*/
		for(int l=0;l<101;l++){
			X[l] =0.0;
			Hu_Exp[i][l]=0; Hd_Exp[i][l]=0;
			Hu_Vol[i][l]=0; Hd_Vol[i][l]=0;
			Hu_Exp_SoLID[i][l]=0; Hd_Exp_SoLID[i][l]=0;
			Hu_Vol_SoLID[i][l]=0; Hd_Vol_SoLID[i][l]=0;
			for(int k=0;k<N_Replica;k++){
				Hu[k][l]=0;  Hd[k][l]=0;
				Weight[k][l]=0;
			}
		}
		for(int j=0;j<N_H;j++){
			H->GetEntry(j);
			Hu[iN][iBin] = iHu;
			Hd[iN][iBin] = iHd;
			Weight[iN][iBin] = iW;
			X_Temp[iN][iBin] = iX;
			//cerr<<Form("%4d %4d %10.6f  %10.6f", iN, iBin, X_Temp[iN][iBin], Hu[iN][iBin],Hd[iN][iBin])<<endl;
		}
		for(int l=0;l<101;l++){
			for(int j=0;j<N_Replica;j++){
				Hu_Exp[i][l] += 1./N_Replica* Hu[j][l];	
				Hd_Exp[i][l] += 1./N_Replica * Hd[j][l];	
				Hu_Exp_SoLID[i][l] += Weight[j][l] * Hu[j][l];	
				Hd_Exp_SoLID[i][l] += Weight[j][l] * Hd[j][l];	
			}
			X[l] = X_Temp[0][l];
	        Hu_Org[l] = Hu[0][l];	
	        Hd_Org[l] = Hd[0][l];	
		}
		for(int l=0;l<101;l++){
			for(int j=0;j<N_Replica;j++){
				Hu_Vol[i][l] += 1./N_Replica* pow((Hu[l][j]-Hu_Exp[i][l]),2);
				Hd_Vol[i][l] += 1./N_Replica* pow((Hd[l][j]-Hd_Exp[i][l]),2);
				Hu_Vol_SoLID[i][l] += Weight[l][j] * pow((Hu[l][j]-Hu_Exp_SoLID[i][l]),2);
				Hd_Vol_SoLID[i][l] += Weight[l][j] * pow((Hd[l][j]-Hd_Exp_SoLID[i][l]),2);
			}
			Hu_Vol[i][l] = sqrt(Hu_Vol[i][l] );
			Hd_Vol[i][l] = sqrt(Hd_Vol[i][l] );
			Hu_Vol_SoLID[i][l] = sqrt(Hu_Vol_SoLID[i][l] );
			Hd_Vol_SoLID[i][l] = sqrt(Hd_Vol_SoLID[i][l] );
		}
		for(int l=0;l<101;l++)
			trans<<Form("%5d %5d %5d %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e", 
					i, l, (int)(Scale[i]), X[l], Hu_Exp[i][l], Hu_Vol[i][l],Hd_Exp[i][l], Hd_Vol[i][l],
					Hu_Exp_SoLID[i][l], Hu_Vol_SoLID[i][l],Hd_Exp_SoLID[i][l], Hd_Vol_SoLID[i][l], Hu_Org[l], Hd_Org[l])<<endl;
		/*}}}*/

		file->Close();
	}
	tensor.close(); trans.close();
	/*}}}*/

}
