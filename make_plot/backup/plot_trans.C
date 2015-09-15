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

void plot_trans(){
 ifstream infile("fit_trans_pim.dat");

 double x[101], scaleU[101], hU[101], hU_Err[101], scaleD[101], hD[101], hD_Err[101];
 double hU_New_Err[101],hD_New_Err[101];
 int i=0;

 double Max = -100000, Min = 1000000000;
 while(!(infile.eof())) {
	 infile >>x[i]>>scaleU[i]>>hU[i]>>hU_Err[i]>>scaleD[i]>>hD[i]>>hD_Err[i];
	 
	 if(scaleU[i]>1.0) scaleU[i]=1.0;
	 if(scaleD[i]>1.0) scaleD[i]=1.0;
	 if(scaleU[i]<0.0) scaleU[i]=1.0;
	 if(scaleD[i]<0.0) scaleD[i]=1.0;

	 hU_New_Err[i] = scaleU[i]*hU_Err[i];
	 hD_New_Err[i] = scaleD[i]*hD_Err[i];

	 if(hU_New_Err[i] > Max) Max=hU_New_Err[i];
	 if(hD_New_Err[i] > Max) Max=hD_New_Err[i];
	 if(hU_New_Err[i] < Min) Min=hU_New_Err[i];
	 if(hD_New_Err[i] < Min) Min=hD_New_Err[i];
	 i++;
 }

 double x2[202], scaleU2[202], hU_New_Err2[202], hU_Err2[202], scaleD2[202], hD_New_Err2[202], hD_Err2[202];
 double hU2[202],hD2[202], Zero[202];

 for(int i=0;i<101;i++){
	 Zero[i]=0.0;
     x2[i]=x[i];
     x2[i+101]=x[100-i];

 	 scaleU2[i]=scaleU[i];
     scaleU2[i+101]=scaleU[100-i];
	 scaleD2[i]=scaleD[i];
     scaleD2[i+101]=scaleD[100-i];
 
     hU_New_Err2[i]=hU_New_Err[i];
     hU_New_Err2[i+101]=hU_New_Err[100-i];
	 hD_New_Err2[i]=hD_New_Err[i];
	 hD_New_Err2[i+101]=hD_New_Err[100-i];

     hU2[i]=hU[i];
     hU2[i+101]=hU[100-i];
	 hD2[i]=hD[i];
	 hD2[i+101]=hD[100-i];

     hU_Err2[i]=hU_Err[i];
     hU_Err2[i+101]=hU_Err[100-i];
	 hD_Err2[i]=hD_Err[i];
	 hD_Err2[i+101]=hD_Err[100-i];
 }

 TCanvas *c1 = new TCanvas("c1","c1",800,600);
 TH2D *h1 = new TH2D("h1","h_{1}^{d}",500,0.0,1.0,500,-0.5, 0.5);
 h1->SetXTitle("x_{B}");
 h1->SetYTitle("#sigma(h_{1}^{d})");
 h1->Draw();

 TGraphErrors *gr0 = new TGraphErrors(202, x2,Zero,Zero, hD_Err2);
 gr0->SetLineColor(2);
 gr0->SetFillColor(2);
 gr0->SetMarkerSize(0);
 gr0->Draw("p");

 TGraphErrors *gr1 = new TGraphErrors(202, x2,Zero,Zero, hD_New_Err2);
 gr1->SetLineColor(4);
 gr1->SetFillColor(4);
 gr1->SetMarkerSize(0);
 gr1->Draw("p");

}
