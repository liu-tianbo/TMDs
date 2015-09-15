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

void f_Test(){
	const int N_Replica =100;// cerr<<"   N_Replica = "; cin >> N_Replica;
	TString Experiment = "solid"; cerr<<"--- Experiment (solid or clas) "; cin >> Experiment;
	TString Target = "3he";cerr<<"--- Target (3he or p) "; cin >> Target;
	TString Particle = "pip"; cerr<<"--- PID (pip or pim) "; cin >> Particle;
	TString Norm = ""; cerr<<"   Norm = (10,100,1K,10K,20K,100K,1M)"; cin >> Norm;
	int Scale = 1;// cerr<<"   Scale = "; cin >> Scale;
	
	/*Load the best fit values{{{*/
    TString infile_name0 = Form("../psudo_data/f%s_new_%s_data_%s_%s_0.dat",Norm.Data(),Experiment.Data(),Target.Data(),Particle.Data());
	ifstream infile0(infile_name0.Data());
	double Z0[2000], xB0[2000], Q20[2000], Pt0[2000], Sigma_Unp0[2000], Asym0[2000], Asym_New0[2000], Asym_Err0[2000];
	double deltaU0[2000], deltaD0[2000], deltaU_EX0[2000], deltaD_EX0[2000];
	int Bin0[2000];
	int i=0;
	cerr<<"---- Reading A0 data "<<infile_name0.Data()<<endl;
	//while(!(infile0.eof())){
	while(infile0 >> Bin0[i]>> Z0[i]>> xB0[i]>> Q20[i] >> Pt0[i] 
			>> Sigma_Unp0[i] >> Asym0[i] >> Asym_New0[i] >> Asym_Err0[i] 
			>> deltaU0[i] >> deltaD0[i] >> deltaU_EX0[i] >> deltaD_EX0[i]){
		i++;
	}
	cerr<<"Done~!"<<endl;
	infile0.close();
	/*}}}*/

	/*Load replica and calculate weight{{{*/
	gRandom->SetSeed(0);
	static double Weight[100], ChiSQ[100];
	static double deltaU_Cal[100], deltaD_Cal[100];
	static double deltaU_EX_Cal[100], deltaD_EX_Cal[100];

   	double Z[2000], xB[2000], Q2[2000], Pt[2000], Sigma_Unp[2000], Asym[2000], Asym_Err[2000];
	double deltaU[2000], deltaD[2000], deltaU_EX[2000], deltaD_EX[2000];
	int Bin[2000];

	int N_Count =0;
	TString FileName;
	double ChiSQ_Sum=1e-308;
	double Weight_Sum=1e-308;//always starting from the smallest number to reduce round-up errors
	for(int j=0;j<N_Replica;j++){
		i=0;
		//FileName = Form("/work/halla/solid/yez/TMDs/collins_clean/%s_%s_%s/new_%s_data_%s_%s_%d.dat",Experiment.Data(),Target.Data(),Particle.Data(),Experiment.Data(),Target.Data(),Particle.Data(),j);
		FileName = Form("../collins_clean/f%s_%s_%s_%s/new_%s_data_%s_%s_%d.dat",Norm.Data(),Experiment.Data(),Target.Data(),Particle.Data(),Experiment.Data(),Target.Data(),Particle.Data(),j);
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
				ChiSQ[j] += pow( (Asym0[k]-Asym[k])/(Asym_Err0[k]*Scale),2);
				//ChiSQ[j] += pow( (Asym_New0[k]-Asym[k])/(Asym_Err0[k]*Scale),2);
			//	cerr<<Form("--- N=%d, k=%d, Asym0 = %10.4e, Asym = %10.4e, Asym_Err = %10.4e, ChiSQ=%f",
			//			j,k, Asym_New0[k], Asym[k], Asym_Err[k], ChiSQ[j])<<endl;
			}
			ChiSQ_Sum+=ChiSQ[j];
			Weight[j] = TMath::Exp(-0.5 * ChiSQ[j]);
			Weight_Sum += Weight[j];
		    if(j==0)	
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
	cerr<<endl<<"--- Total valide replica = "<< N_Count<<endl;
	/*}}}*/
	
	/*Fill into ROOT trees{{{*/
	double Weight_Sum_Log = 1e-308;
    ofstream outfile(Form("%s_%s_%s_out_%s.dat",Experiment.Data(), Target.Data(), Particle.Data(),Norm.Data()));
	int count =0;
	for(int j=1;j<N_Replica;j++){
		//Note: weights have been normalized here; Don't normalized again.
		if(Weight[j]>-1.){
	        count++;
			Weight[j] /=Weight_Sum;
			Weight_Sum_Log += Weight[j] * log(Weight[j]);
			cerr<<Form("--- j=%10d, Weight = %10.4e, Sum = %10.4e",j, Weight[j], Weight_Sum_Log)<<endl;//<<"\r";
			outfile<<Form("--- j=%10d, Weight = %10.4e, Sum = %10.4e",j, Weight[j], Weight_Sum_Log)<<endl;//<<"\r";
		}
	}
	double N_eff = exp(-1.*Weight_Sum_Log)/ count *100.;
	cerr<<"N_eff = "<<N_eff<<endl;
	outfile<<"N_eff = "<<N_eff<<endl;
}
