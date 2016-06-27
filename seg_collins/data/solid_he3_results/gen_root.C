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
  #include <TTree.h>
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
  #include <TLatex.h>
  #include <TRandom3.h>
  //#include <TMatrix.h>
  /*}}}*/
using namespace std;

void gen_root(){
	int PID, Q2_bin, Z_bin;
	double x,y, z, pt, q2, w, wp, Astat, x_be_s10, x_be_b10, Astat2, sig_noise, dilute,rate, N;
    double coverage, sivers,collins,prez;

	TString part="pip"; cerr<<"--- Particle (pip, pim) = "; cin >> part;
	/*ROOTfile and Tree{{{*/
	TFile *f1 = new TFile(Form("new_%s_bin.root",part.Data()),"recreate");
	TTree *T = new TTree("T","T");

	T->Branch("PID",&PID,"PID/I");
	T->Branch("Q2_bin",&Q2_bin,"Q2_bin/I");
	T->Branch("Z_bin",&Z_bin,"Z_bin/I");
	T->Branch("x",  &x,  "x/D");
	T->Branch("z",  &z,  "z/D");
	T->Branch("w",  &w,  "w/D");
	T->Branch("N",  &N,  "N/D");
	T->Branch("pt", &pt, "pt/D");
	T->Branch("q2", &q2, "q2/D");
	T->Branch("wp", &wp, "wp/D");
	T->Branch("Astat", &Astat, "Astat/D");
	T->Branch("Astat2", &Astat2, "Astat2/D");
	T->Branch("x_be_s10",  &x_be_s10,  "x_be_s10/D");
	T->Branch("x_be_b10",  &x_be_b10,  "x_be_b10/D");
	T->Branch("dilute", &dilute, "dilute/D");
	T->Branch("sig_noise", &sig_noise, "sig_noise/D");
	T->Branch("coverage",  &coverage,  "coverage/D");
	T->Branch("sivers",  &sivers,  "sivers/D");
	T->Branch("collins",  &collins,  "collins/D");
	T->Branch("prez",  &prez,  "prez/D");
	/*}}}*/

	double N_Total = 0.0;

	int temp;
	int vQ2[48],vPT[48];
	double vN[48];
	TLatex *latex[3][48];

	int count=0;
	for(int i=1;i<=6;i++){
		for(int j=1;j<=8;j++){
                        
			Z_bin = j; Q2_bin = i; N = 0.0;
			
			/*Get Z and Q2 Bin{{{*/
			double zmin =0., zmax = 0., Q2min=0., Q2max=0.;
             int z_flag = Z_bin, Q2_flag = Q2_bin;
			if (z_flag==1){
				zmin = 0.3; zmax = 0.35;
			}else if (z_flag==2){
				zmin = 0.35; zmax = 0.4;
			}else if (z_flag==3){
				zmin = 0.4; zmax = 0.45;
			}else if (z_flag==4){
				zmin = 0.45; zmax = 0.5;
			}else if (z_flag==5){
				zmin = 0.5; zmax = 0.55;
			}else if (z_flag==6){
				zmin = 0.55; zmax = 0.6;
			}else if (z_flag==7){
				zmin = 0.6; zmax = 0.65;
			}else if (z_flag==8){
				zmin = 0.65; zmax = 0.7;
			}
			if (Q2_flag==1){
				Q2min = 1.; Q2max = 2.0;
			}else if (Q2_flag==2){
				Q2min = 2.0; Q2max = 3.0;
			}else if (Q2_flag==3){
				Q2min = 3.0; Q2max = 4.0;
			}else if (Q2_flag==4){
				Q2min = 4.0; Q2max = 5.0;
			}else if (Q2_flag==5){
				Q2min = 5.0; Q2max = 6.0;
			}else if (Q2_flag==6){
				Q2min = 6.0; Q2max = 8.0;
			}else if (Q2_flag==7){//Not in used!!!
				Q2min = 8.0; Q2max = 10.0;
			}
			/*}}}*/

			TString filename;
			filename.Form("3he_%s_%d_%d.dat",part.Data(),Z_bin,Q2_bin);
			ifstream infile(filename);

			Int_t count1,count2;
			Int_t pt_flag = -1;

			infile >> count1;
			Int_t pt_temp,x_temp;
			while(infile >> pt_flag >> count2){
				//cerr<<" pt_flag="<<pt_flag<<", count="<<count2<<endl;

				for (Int_t j1=0;j1<count2;j1++){
					infile >> pt_temp >> x_temp >> z >> q2 >> pt >> x >> y >> Astat >> rate
						>>coverage >> sivers >> collins >> prez;

					if(pt_temp==pt_flag && x_temp== j1){
						cerr<<Form("---z=%d, Q=%d pt = %d, x = %f, Asys= %f",Z_bin,Q2_bin, pt_flag,x, Astat)<<endl;
				       
						if (Astat>0.&&Astat<0.05&&coverage>6.28/15.&&(sivers+collins+prez)/3<3.){
							N += 1.0/pow(Astat,2);
							N_Total += rate;
							//N_Total += 1.0/pow(Astat,2);
							T->Fill();
						}
						}
					}
				} 
				infile.close();
				vQ2[count] = -Q2_bin;
				vPT[count] = Z_bin;
				vN[count] = N;
	            double Off = 0.98;
				if(Z_bin>5)
					Off = 0.96;
				latex[0][count] = new TLatex( (Z_bin+0.2+0.)/9, ((6-Q2_bin*Off)+1.4)/7,Form("%d<Q2<%d", (int)Q2min,(int)Q2max));
				latex[1][count] = new TLatex( (Z_bin+0.2+0.)/9, ((6-Q2_bin*Off)+1.2)/7,Form("%3.2f<z<%3.2f", zmin,zmax));
				latex[2][count] = new TLatex( (Z_bin+0.2+0.)/9, ((6-Q2_bin*Off)+1.0)/7,Form("N=%3.2e", N));
		//		latex[0][count] = new TLatex( (Q2_bin+0.2)/7,(Z_bin*Off+0.8+0.)/9, Form("%d<Q2<%d", (int)Q2min,(int)Q2max));
		//		latex[1][count] = new TLatex( (Q2_bin+0.2)/7,(Z_bin*Off+0.6+0.)/9, Form("%3.2f<z<%3.2f", zmin,zmax));
		//		latex[2][count] = new TLatex( (Q2_bin+0.2)/7,(Z_bin*Off+0.4+0.)/9, Form("N=%3.2e", N));
				count++;
		}	
	}
	T->Write(); f1->Close();
	cerr<<Form("--- Total of number of events for %s = %e",part.Data(), N_Total)<<endl;

	TCanvas *c1 = new TCanvas("c1","c1", 1400,800);
//	gPad->SetBottomMargin(0.05);
	gPad->SetTopMargin(0.03);
//	gPad->SetLeftMargin(0.06);
	gPad->SetRightMargin(0.03);
    gStyle->SetOptStat(0);
	TH2F *h1 = new TH2F("h1","",6,0,8,8,-6,0 );
	h1->SetXTitle("pt");
	h1->SetYTitle("Q2");
    gPad->SetGridy(1);
    gPad->SetGridx(1);
	h1->Draw();

	TGraph *err = new TGraph(count, vPT, vQ2);
    err->Draw("p");
	for(int i=0;i<48;i++){
	  latex[0][i]->SetNDC(); latex[0][i]->SetTextSize(0.02); latex[0][i]->Draw();
	  latex[1][i]->SetNDC(); latex[1][i]->SetTextSize(0.02); latex[1][i]->Draw();
	  latex[2][i]->SetNDC(); latex[2][i]->SetTextSize(0.025);latex[2][i]->SetTextColor(4); latex[2][i]->Draw();
	}

	}
