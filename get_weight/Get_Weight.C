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

void Get_Weight(TString Experiment,TString Target,TString Particle, int Scale_Factor=0){
	const int N_Replica = 170000;
	//TString Particle = ""; cerr<<"Particle = (pip or pim)"; cin >> Particle;
	
	/*Load the best fit values{{{*/
    //TString infile_name0 = Form("../psudo_data/new_%s_data_%s_%s_0.dat",Experiment.Data(),Target.Data(),Particle.Data());
    TString infile_name0 = Form("../psudo_data/new_%s_data_%s_%s_0.dat",Experiment.Data(),Target.Data(),Particle.Data());
	ifstream infile0(infile_name0.Data());
	double Z0[2000], xB0[2000], Q20[2000], Pt0[2000], Sigma_Unp0[2000], Asym0[2000], Asym_New0[2000], Asym_Err0[2000];
	double deltaU0[2000], deltaD0[2000], deltaU_EX0[2000], deltaD_EX0[2000];
	int Bin0[2000];
	int i=0;
	//while(!(infile0.eof())){
	while(infile0 >> Bin0[i]>> Z0[i]>> xB0[i]>> Q20[i] >> Pt0[i] 
			>> Sigma_Unp0[i] >> Asym0[i] >> Asym_New0[i] >> Asym_Err0[i] 
			>> deltaU0[i] >> deltaD0[i] >> deltaU_EX0[i] >> deltaD_EX0[i]){
		cerr<<"---- Reading A0 data "<<infile_name0.Data()<<"  #"<<i<<"\r";
		
		i++;
	}
	cerr<<"Done~!"<<endl;
	infile0.close();
	/*}}}*/

	/*Load replica and calculate weight{{{*/
	ofstream outfile(Form("./results/weight_%s_%s_%s_%d.dat",Experiment.Data(),Target.Data(),Particle.Data(),Scale_Factor));
	gRandom->SetSeed(0);
	static double Weight[N_Replica], ChiSQ[N_Replica];
	static double deltaU_Cal[N_Replica], deltaD_Cal[N_Replica];
	static double deltaU_EX_Cal[N_Replica], deltaD_EX_Cal[N_Replica];

   	double Z[2000], xB[2000], Q2[2000], Pt[2000], Sigma_Unp[2000], Asym[2000], Asym_Err[2000];
	double deltaU[2000], deltaD[2000], deltaU_EX[2000], deltaD_EX[2000];
	int Bin[2000];

//	double Scale_Factor = 0.0; cerr<<"--- Scale the Astat = "; cin >> Scale_Factor;
	int N_Count =0;
	TString FileName;
	double ChiSQ_Sum=1e-308;
	double Weight_Sum=1e-308;//always starting from the smallest number to reduce round-up errors
	for(int j=0;j<N_Replica;j++){
		i=0;
		FileName = Form("/volatile/halla/solid/yez/TMDs/collins_clean/%s_%s_%s/new_%s_data_%s_%s_%d.dat",Experiment.Data(),Target.Data(),Particle.Data(),Experiment.Data(),Target.Data(),Particle.Data(),j);
		ifstream infile(FileName);
		if(infile){
			//cerr<<"---- Reading file-->"<<FileName.Data()<<"\r";
			Z[i] = 0.0;  xB[i] = 0.0;  Q2[i] = 0.0; Pt[i] = 0.0; Asym[i] = 0.0; Asym_Err[i] = 0.0; 
			deltaU[i] = 0.0;   deltaD[i] = 0.0;	deltaU_EX[i] = 0.0;  deltaD_EX[i] = 0.0; 
			while(
				infile >> Bin[i]>> Z[i]>> xB[i]>> Q2[i] >> Pt[i] 
					>> Sigma_Unp[i] >> Asym[i] >> Asym_Err[i] 
					>> deltaU[i] >> deltaD[i] >> deltaU_EX[i] >> deltaD_EX[i]){
				i++;
			}
			infile.close();
			int Bin_Total = i-1;
	
			//Only one set of value for each replica	
			deltaU_Cal[j]=deltaU[0];
			deltaD_Cal[j]=deltaD[0];
			deltaU_EX_Cal[j]=deltaU_EX[0];
			deltaD_EX_Cal[j]=deltaD_EX[0];

			ChiSQ[j] = 0;
			for(int k=0;k<Bin_Total;k++){
				ChiSQ[j] += pow( (Asym_New0[k]-Asym[k])/(Asym_Err0[k]*Scale_Factor),2);
				//cerr<<Form("--- N=%d, k=%d, Asym0 = %10.4e, Asym = %10.4e, Asym_Err = %10.4e, ChiSQ=%f",
				//		j,k, Asym_New0[k], Asym[k], Asym_Err[k], ChiSQ[j])<<endl;
			}
			ChiSQ_Sum+=ChiSQ[j];
			Weight[j] = TMath::Exp(-0.5 * ChiSQ[j]);
			Weight_Sum += Weight[j];
			
			cerr<<Form("--- j=%10d, ChiSQ = %10.6e, Weight = %10.6e",j,ChiSQ[j], Weight[j])<<"\r";//<<endl;

			N_Count++;
		}else{
			//cerr<<Form("*** File %s doesn't exist, skip!", FileName.Data())<<endl;
	       	deltaU_Cal[j]=1e-308;
			deltaD_Cal[j]=1e-308;
			deltaU_EX_Cal[j]=1e-308;
			deltaD_EX_Cal[j]=1e-308;
			ChiSQ[j] = 1e-308;
			Weight[j] = -1e3;
		}
	}
	cerr<<"--- Total valide replica = "<< N_Count<<endl;
	/*}}}*/
	
	/*Fill into ROOT trees{{{*/
	cerr<<endl<<endl<<"--- Start to fill data into trees ..."<<endl;
	double iAsym,iAsymErr,iChiSQ,iW,iD,iU,iD0,iU0,iZ,iX,iQ2,iPt,iD_EX,iU_EX,iD_EX0,iU_EX0,iSigma, iHu, iHd, iHu0, iHd0;
	int iBin, iN,iCount;

	TFile *file = new TFile(Form("./results/Weight_%s_%s_%s_F%d.root",Experiment.Data(),Target.Data(),Particle.Data(),Scale_Factor),"recreate");
	TTree *T = new TTree("T","T");
	TTree *W = new TTree("W","W");
	TTree *H = new TTree("H","H");
	T->Branch("iAsym", &iAsym, "Asym/D");
	T->Branch("iAsymErr", &iAsymErr, "AsymErr/D");
	T->Branch("iBin", &iBin, "Bin/I");
	T->Branch("iN", &iN, "N/I");
	T->Branch("iZ", &iZ, "Z/D");
	T->Branch("iX", &iX, "X/D");
	T->Branch("iQ2", &iQ2, "Q2/D");
	T->Branch("iPt", &iPt, "Pt/D");
	T->Branch("iSigma", &iSigma, "Sigma/D");
	T->Branch("iU", &iU, "U/D");
	T->Branch("iD", &iD, "D/D");
	T->Branch("iU0", &iU0, "U0/D");
	T->Branch("iD0", &iD0, "D0/D");
	T->Branch("iU_EX", &iU_EX, "U_EX/D");
	T->Branch("iD_EX", &iD_EX, "D_EX/D");
	T->Branch("iU_EX0", &iU_EX0, "U_EX0/D");
	T->Branch("iD_EX0", &iD_EX0, "D_EX0/D");
	T->Branch("iW", &iW, "W/D");
	T->Branch("iCount", &iCount, "Count/I");

	W->Branch("iChiSQ", &iChiSQ, "ChiSQ/D");
	W->Branch("iW", &iW, "W/D");
	W->Branch("iU", &iU, "U/D");
	W->Branch("iD", &iD, "D/D");
	W->Branch("iU0", &iU0, "U0/D");
	W->Branch("iD0", &iD0, "D0/D");
	W->Branch("iU_EX", &iU_EX, "U_EX/D");
	W->Branch("iD_EX", &iD_EX, "D_EX/D");
	W->Branch("iU_EX0", &iU_EX0, "U_EX0/D");
	W->Branch("iD_EX0", &iD_EX0, "D_EX0/D");
	W->Branch("iN", &iN, "N/I");
	W->Branch("iCount", &iCount, "Count/I");

	H->Branch("iHu", &iHu, "Hu/D");
	H->Branch("iHd", &iHd, "Hd/D");
	H->Branch("iHu0", &iHu0, "Hu0/D");
	H->Branch("iHd0", &iHd0, "Hd0/D");
	H->Branch("iX", &iX, "X/D");
	H->Branch("iW", &iW, "W/D");
	H->Branch("iN", &iN, "N/I");
	H->Branch("iBin", &iBin, "Bin/I");
	H->Branch("iCount", &iCount, "Count/I");

	iCount = N_Count;

	for(int j=0;j<N_Replica;j++){
		//Note: weights have been normalized here; Don't normalized again.
		if(Weight[j]>-1.)
			Weight[j] /=Weight_Sum;
		iW = Weight[j];
		iChiSQ = ChiSQ[j];
		iU = deltaU_Cal[j];
		iD = deltaD_Cal[j];
		iU0 = deltaU_Cal[0];
		iD0 = deltaD_Cal[0];
		iU_EX = deltaU_EX_Cal[j];
		iD_EX = deltaD_EX_Cal[j];
		iN = j;
		W->Fill();
			
		outfile<<Form("%10d %10.4e %10.4e %10.4e %10.4e %10.4e %10.4e",j,ChiSQ[j], Weight[j],deltaU_Cal[j],deltaD_Cal[j],deltaU_EX_Cal[j],deltaD_EX_Cal[j])<<endl;
		cerr<<Form("--- j=%10d, ChiSQ = %10.4e, Weight = %10.4e",j,ChiSQ[j], Weight[j])<<"\r";//<<endl;
	}

	for(int j=0;j<N_Replica;j++){
		i=0;

		FileName = Form("/volatile/halla/solid/yez/TMDs/collins_clean/%s_%s_%s/new_%s_data_%s_%s_%d.dat",Experiment.Data(),Target.Data(),Particle.Data(),Experiment.Data(),Target.Data(),Particle.Data(),j);
		//FileName = Form("../collins_clean/%s_%s_%s/new_%s_data_%s_%s_%d.dat",Experiment.Data(),Target.Data(),Particle.Data(),Experiment.Data(),Target.Data(),Particle.Data(),j);
		ifstream infile(FileName);
		if(infile){
			//cerr<<"---- Reading file-->"<<FileName.Data()<<endl;
			Z[i] = 0.0;  xB[i] = 0.0;  Q2[i] = 0.0; Pt[i] = 0.0; Asym[i] = 0.0; Asym_Err[i] = 0.0; 
			deltaU[i] = 0.0;   deltaD[i] = 0.0;	deltaU_EX[i] = 0.0;  deltaD_EX[i] = 0.0; 
			while(infile >> Bin[i]>> Z[i]>> xB[i]>> Q2[i] >> Pt[i] 
					>> Sigma_Unp[i] >> Asym[i] >> Asym_Err[i] 
					>> deltaU[i] >> deltaD[i] >> deltaU_EX[i] >> deltaD_EX[i]){
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
				iU0 = deltaU[0];
				iD0 = deltaD[0];
				iU_EX = deltaU_EX[i];
				iD_EX = deltaD_EX[i];
				iU_EX0 = deltaU_EX[0];
				iD_EX0 = deltaD_EX[0];
				iW = Weight[j];
				T->Fill();
				i++;
			}
			infile.close();
		}
	}

	double iHu00[100],iHd00[100];
	for(int j=0;j<N_Replica;j++){
		i=0;
		iN=0;
		FileName = Form("/volatile/halla/solid/yez/TMDs/collins_clean/%s_%s_%s/new_transversity_u_%d.dat",Experiment.Data(),Target.Data(), Particle.Data(),j);
		ifstream infile0(FileName);
		FileName = Form("/volatile/halla/solid/yez/TMDs/collins_clean/%s_%s_%s/new_transversity_d_%d.dat",Experiment.Data(),Target.Data(), Particle.Data(),j);
		ifstream infile1(FileName);
		if(infile0){
			//while(!(infile0.eof())){
			for(int l=0;l<100;l++){
				infile0 >> iX >> iHu;
				infile1 >> iX >> iHd;
				if(j==0){
					iHu00[l] = iHu;	iHd00[l] = iHd;	
				}
				iHu0 = iHu00[l];
				iHd0 = iHd00[l];
				iN = j;
				iBin = l;
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
	double deltaU_Exp_EX=0.0, deltaD_Exp_EX=0.0;
	double deltaU_Vol_EX=0.0, deltaD_Vol_EX=0.0;
	for(int j=0;j<N_Count;j++){
		deltaU_Exp += 1./N_Count * deltaU_Cal[j];	
		deltaD_Exp += 1./N_Count * deltaD_Cal[j];	
		deltaU_Exp_EX += Weight[j] * deltaU_EX_Cal[j];	
		deltaD_Exp_EX += Weight[j] * deltaD_EX_Cal[j];	
	}

	for(int j=0;j<N_Count;j++){
		deltaU_Vol += 1./N_Count* pow((deltaU_Cal[j]-deltaU_Exp),2);
		deltaD_Vol += 1./N_Count* pow((deltaD_Cal[j]-deltaD_Exp),2);
		deltaU_Vol_EX += Weight[j] * pow((deltaU_EX_Cal[j]-deltaU_Exp_EX),2);
		deltaD_Vol_EX += Weight[j] * pow((deltaD_EX_Cal[j]-deltaD_Exp_EX),2);
	}
	cerr<<Form("  All: dU = %8.5f, du_V = %8.5f, dD=%8.5f, dD_V=%8.5f", deltaU_Exp,deltaU_Vol, deltaD_Exp,deltaD_Vol)<<endl;
	cerr<<Form("EX: dU = %8.5f, du_V = %8.5f, dD=%8.5f, dD_V=%8.5f", deltaU_Exp_EX,deltaU_Vol_EX, deltaD_Exp_EX,deltaD_Vol_EX)<<endl;
	/*}}}*/
}

char* gExperiment; char* gTarget; char* gParticle; int gScale;
/*int getargs(int argc,char** argv){{{*/
int getargs(int argc,char** argv)
{
	char* argptr;
	bool noStop;  
	int err=-1;

	for(int i=0;i<argc;i++){
		argptr = argv[i];
		if(*argptr=='-'){
			argptr++;
			switch (*argptr){
				case 'E':
					if(*(++argptr))
						gExperiment = argptr;
					err=0;
					break;
				case 'T':
					if(*(++argptr))
						gTarget = argptr;
					err=0;
					break;
				case 'P':
					if(*(++argptr))
						gParticle = argptr;
					err=0;
					break;
				case 'N':
					if(*(++argptr))
						gScale = atoi(argptr);
					err=0;
					break;
				case 'h':
					cerr <<"================================================"<<endl;
					cerr <<"Option: " <<endl;
					cerr <<"-E[solid or clas or sbs] Target " <<endl;
					cerr <<"-T[p or 3he] Target " <<endl;
					cerr <<"-P[pip or pim] Particle"<<endl;
					cerr <<"-N[10,20,...,100] Scale"<<endl;
					cerr <<endl<<"================================================"<<endl;
					noStop=false;
					err=-1;
					goto OUT;
					break;
				default:
					cerr <<"================================================"<<endl;
					cerr <<"Option: " <<endl;
					cerr <<"-E[solid or clas or sbs] Target " <<endl;
					cerr <<"-T[p or 3he] Target " <<endl;
					cerr <<"-P[pip or pim] Particle"<<endl;
					cerr <<"-N[10,20,...,100] Scale"<<endl;
					cerr <<endl<<"================================================"<<endl;
					break;
			}

		}
		noStop=true;
OUT:if(!noStop){break;}
	continue;
	}
	return err; 
}
/*}}}*/		

int main(int argc, char**argv){
	//TString Target = ""; cerr<<"--- Target= (p or 3he)"; cin >> Target;
	//TString Particle =""; cerr<<"--- Particle= (pip or pim) "; cin >> Particle;	
	//int Scale = 0; cerr<<"--- Scale (10,20~100) "; cin >> Scale;	
	
	int pserr = getargs(argc,argv);
    TString Experiment= gExperiment;
	if(Experiment!="solid" && Experiment!="clas"&& Experiment!="sbs"){
	    cerr<<"***ERROR, Unknown Experiment"<<endl;
		return -1;
	}
    TString Target= gTarget;
	if(Target!="3he" && Target!="p"){
	    cerr<<"***ERROR, Unknown Target"<<endl;
		return -2;
	}
	TString Particle =gParticle;
	if(Particle!="pip" && Particle!="pim"){
	    cerr<<"***ERROR, Unknown PID"<<endl;
		return -3;
	}
	int Scale = gScale;
	
	Get_Weight(Experiment.Data(),Target.Data(),Particle.Data(),Scale);

	//double Scale[9]={1000,900,800,700,600,500,400,300,200};
	//double Scale[7]={140,120,100,80,60,40,20};

	//for(int i=0;i<7;i++){
	//	Get_Weight(Target.Data(),Particle.Data(),Scale[i]);
	//}
}
