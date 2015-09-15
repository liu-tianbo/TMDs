/*C/C++ Includes{{{*/
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
//#include "Rtypes.h"
//#include "math.h"

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
#include <TApplication.h>
#include <Rtypes.h>
#include <TTree.h>
#include "LHAPDF/LHAPDF.h"
//#include <TMatrix.h>
/*}}}*/
using namespace std;

/*void ReadIn(particle_flag,Int_t Q2_bin =1){{{*/
void ReadIn(Int_t particle_flag, Int_t Q2_bin, Int_t z_bin,
	int* Count,	int* pt_bin, int* x_bin,
    double* Q2, double *pt, double *x, double* y, double *z,
    double * Astat, double *Astat_Siver, double *Astat_Collins, double* Astat_Pretz,
    double* N){

	int target_flag = 3;

	/*Input{{{*/
	TString target = "X";
	if(target_flag==1)
		target ="p";
	else if(target_flag==2)
		target ="d2";
	else if(target_flag==3)
		target ="3he";
	else{
		cerr<<"I don't know this particle flag!"<<endl;
	}
	TString particle = "X";
	if(particle_flag==1)
		particle ="pip";
	else if(particle_flag==2)
		particle ="pim";
	else{
		cerr<<"I don't know this particle flag!"<<endl;
	}
	TString filename;
	filename.Form("./%s_%s_%d_%d.dat",target.Data(),particle.Data(),z_bin,Q2_bin);
	ifstream infile(filename);
	cerr<<"--- Reading file = "<<filename.Data();
	/*}}}*/

	gStyle->SetOptStat(0);
	Int_t count1,count2;
	//Double_t Q2[5000],x[5000],z[5000],pt[5000],y[5000],[5000],N[5000];
	Double_t coverage[5000],coef[3][5000];
	//Double_t _Siver[5000],Astat_Collins[5000], Astat_Pretz[5000];
	//Int_t pt_bin[5000], x_bin[5000];

	//Double_t temp;
	Int_t pt_flag = -1, x_flag = -1;
	Int_t ncount=0;

	infile >> count1;
	Int_t pt_temp,x_temp;
	while(infile >> pt_flag >> count2){
		//cerr<<" pt_flag="<<pt_flag<<", count="<<count2<<endl;

		for (Int_t j1=0;j1<count2;j1++){
			infile >> pt_temp >> x_temp >> z[ncount] >> Q2[ncount] >> pt[ncount] >> x[ncount] >> y[ncount] >> Astat[ncount] >> N[ncount]>>
				coverage[ncount] >> coef[0][ncount] >> coef[1][ncount] >> coef[2][ncount];

			cerr<<Form(" Q2 = %d, z = %d, pt = %d, x = %d, N = %f  ", Q2_bin, z_bin, pt_temp, x_temp, N[ncount])<<endl;

            x_flag = j1;
			if(pt_temp==pt_flag && x_temp== x_flag){

				if (Astat[ncount]>0.&&Astat[ncount]<0.05){
					Astat_Siver[ncount] = Astat[ncount]*coef[0][ncount]; //coef[0]->Sivers,coef[1]->Collins, coef[2]->Pretzelosity
					Astat_Collins[ncount] = Astat[ncount]*coef[1][ncount]; //coef[0]->Sivers,coef[1]->Collins, coef[2]->Pretzelosity
					Astat_Pretz[ncount] = Astat[ncount]*coef[2][ncount]; //coef[0]->Sivers,coef[1]->Collins, coef[2]->Pretzelosity

					pt_bin[ncount] = pt_flag; x_bin[ncount] = x_flag;

					ncount ++;
				}
			}
		}
	}
	infile.close();

    Count[0] = ncount;

}
/*}}}*/

/*int main(){{{*/
void GentRoot(){

    int x_bin, z_bin, pt_bin, Q2_bin, N_Q2_z;
	double Q2, x, y, z, pt, Nstat;
    double Astat, Astat_Sivers, Astat_Collins, Astat_Pretz;
	Int_t Q2min,Q2max;
	Double_t zmin,zmax;

	TFile *file = new TFile("SIDIS_Neutron_Projection.root","recreate");

	TTree *Pip = new TTree("Pip","A new tree");
	Pip->Branch("Q2", &Q2, "Q2/D");
	Pip->Branch("pt", &pt, "pt/D");
	Pip->Branch("x", &x, "x/D");
	Pip->Branch("y", &y, "y/D");
	Pip->Branch("z", &z, "z/D");
	Pip->Branch("Astat", &Astat, "Astat/D");
	Pip->Branch("Astat_Sivers", &Astat_Sivers, "Astat_Sivers/D");
	Pip->Branch("Astat_Collins", &Astat_Collins, "Astat_Collins/D");
	Pip->Branch("Astat_Pretz", &Astat_Pretz, "Astat_Pretz/D");
	Pip->Branch("Nstat", &Nstat, "Nstat/D");
	Pip->Branch("Q2_bin", &Q2_bin, "Q2_bin/I");
	Pip->Branch("pt_bin", &pt_bin, "pt_bin/I");
	Pip->Branch("x_bin", &x_bin, "x_bin/I");
	Pip->Branch("z_bin", &z_bin, "z_bin/I");
	Pip->Branch("N_Q2_z", &N_Q2_z, "N_Q2_z/I");

	TTree *Pim = new TTree("Pim","A new tree");
	Pim->Branch("Q2", &Q2, "Q2/D");
	Pim->Branch("pt", &pt, "pt/D");
	Pim->Branch("x", &x, "x/D");
	Pim->Branch("y", &y, "y/D");
	Pim->Branch("z", &z, "z/D");
	Pim->Branch("Astat", &Astat, "Astat/D");
	Pim->Branch("Astat_Sivers", &Astat_Sivers, "Astat_Sivers/D");
	Pim->Branch("Astat_Collins", &Astat_Collins, "Astat_Collins/D");
	Pim->Branch("Astat_Pretz", &Astat_Pretz, "Astat_Pretz/D");
	Pim->Branch("Nstat", &Nstat, "Nstat/D");
	Pim->Branch("Q2_bin", &Q2_bin, "Q2_bin/I");
	Pim->Branch("pt_bin", &pt_bin, "pt_bin/I");
	Pim->Branch("x_bin", &x_bin, "x_bin/I");
	Pim->Branch("z_bin", &z_bin, "z_bin/I");
	Pim->Branch("N_Q2_z", &N_Q2_z, "N_Q2_z/I");

	double Q2_temp[5000], pt_temp[5000], x_temp[5000],z_temp[5000],y_temp[5000], Nstat_temp[5000];
	double Astat_temp[5000], Astat_Sivers_temp[5000], Astat_Collins_temp[5000], Astat_Pretz_temp[5000];
	int x_bin_temp[5000], pt_bin_temp[5000];

	for(int i=0;i<6;i++){
		for(int j=0;j<8;j++){
			Q2_bin = i+1;
			z_bin = j+1;
			/*Q2 & Z range{{{*/
			if (Q2_bin==1){
				Q2min = 1; Q2max =2;
			}else if (Q2_bin==2){
				Q2min = 2; Q2max =3;
			}else if (Q2_bin==3){
				Q2min = 3; Q2max =4;
			}else if (Q2_bin==4){
				Q2min = 4; Q2max =5;
			}else if (Q2_bin==5){
				Q2min = 5; Q2max =6;
			}else if (Q2_bin==6){
				Q2min = 6; Q2max =8;
			}

			if (z_bin==1){
				zmin = 0.3; zmax = 0.35;
			}else if (z_bin==2){
				zmin = 0.35; zmax = 0.4;
			}else if (z_bin==3){
				zmin = 0.4; zmax = 0.45;
			}else if (z_bin==4){
				zmin = 0.45; zmax = 0.5;
			}else if (z_bin==5){
				zmin = 0.5; zmax = 0.55;
			}else if (z_bin==6){
				zmin = 0.55; zmax = 0.6;
			}else if (z_bin==7){
				zmin = 0.6; zmax = 0.65;
			}else if (z_bin==8){
				zmin = 0.65; zmax = 0.7;
			}
			/*}}}*/

			/*Fill Pip{{{*/
			N_Q2_z = 0;
			ReadIn(1, Q2_bin, z_bin, &N_Q2_z, pt_bin_temp, x_bin_temp,
					Q2_temp, pt_temp,x_temp, y_temp, z_temp,
					Astat_temp, Astat_Sivers_temp, Astat_Collins_temp, Astat_Pretz_temp, Nstat_temp);	
               
			cerr<<"---Count="<<N_Q2_z<<endl;
		
			for(int k=0;k<N_Q2_z;k++){
				pt_bin = pt_bin_temp[k];
				x_bin = x_bin_temp[k];
				Q2 = Q2_temp[k];
				pt = pt_temp[k];
				x = x_temp[k];
				y = y_temp[k];
				z = z_temp[k];
			
               Nstat = Nstat_temp[k];				
               Astat = Astat_temp[k];				
               Astat_Sivers = Astat_Sivers_temp[k];				
               Astat_Collins = Astat_Collins_temp[k];				
               Astat_Pretz = Astat_Pretz_temp[k];				
		
			   Pip->Fill();	   
			}
			/*}}}*/

			/*Fill Pim{{{*/
			N_Q2_z = 0;
			ReadIn(2, Q2_bin, z_bin, &N_Q2_z, pt_bin_temp, x_bin_temp,
					Q2_temp, pt_temp,x_temp, y_temp, z_temp,
					Astat_temp, Astat_Sivers_temp, Astat_Collins_temp, Astat_Pretz_temp, Nstat_temp);	
               
            for(int k=0;k<N_Q2_z;k++){
				pt_bin = pt_bin_temp[k];
				x_bin = x_bin_temp[k];
				Q2 = Q2_temp[k];
				pt = pt_temp[k];
				x = x_temp[k];
				y = y_temp[k];
				z = z_temp[k];
			
               Nstat = Nstat_temp[k];				
               Astat = Astat_temp[k];				
               Astat_Sivers = Astat_Sivers_temp[k];				
               Astat_Collins = Astat_Collins_temp[k];				
               Astat_Pretz = Astat_Pretz_temp[k];				
		
			   Pim->Fill();	   
			}
			/*}}}*/

		}
	}
    file->cd();
	Pip->Write(); Pim->Write();
	file->Close();
}
/*}}}*/
