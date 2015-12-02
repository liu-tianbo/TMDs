void Get_Psudo(){
	double Z[2000], xB[2000], Q2[2000], Pt[2000], Sigma_Unp[2000], Asym[2000], Asym_Err[2000], deltaU[2000], deltaD[2000], deltaU_SoLID[2000], deltaD_SoLID[2000];
    int Bin[2000];

	TString experiment="x"; cerr<<"--- Experiment (solid or clas or sbs) = "; cin >> experiment;
	TString target="x"; cerr<<"--- Target (3he or p) = "; cin >> target;
	TString particle="x"; cerr<<"--- Particle (pip or pim)"; cin >> particle;

    //TString FileName = Form("%s_data_%s_%s_%d.dat",
    TString FileName = Form("/w/halla-scifs2/solid/yez/TMDs/collins_clean_new/f1K_%s_%s_%s/new_%s_data_%s_%s_%d.dat",
            experiment.Data(),target.Data(),particle.Data(),
            experiment.Data(),target.Data(),particle.Data(),0);
    ifstream infile(FileName.Data());

	int i=0;
	while(!(infile.eof())){
		infile >> Bin[i]>> Z[i]>> xB[i]>> Q2[i] >> Pt[i] 
			   >> Sigma_Unp[i] >> Asym[i] >> Asym_Err[i] 
			   >> deltaU[i] >> deltaD[i] >> deltaU_SoLID[i] >> deltaD_SoLID[i];
		i++;
	}
	const int Bin_Total = i-1;
	cerr<<"--- Total Bin = "<< Bin_Total<<endl;

	ofstream outfile(Form("f1K_new_%s_data_%s_%s_0.dat",experiment.Data(),target.Data(), particle.Data(),experiment.Data(),target.Data(), particle.Data()));
	double Asym_New[Bin_Total];
	double ChiSQ;
	gRandom->SetSeed(0);

	TH1F *h1 = new TH1F("h1","",100, 0, 2000);

	for(int j=0;j<20000;j++){
		ChiSQ = 0;
		for(int k=0;k<Bin_Total;k++){
			double R = gRandom->Gaus(0,1);
			Asym_New[k] = Asym[k]+R*Asym_Err[k];
			ChiSQ += pow((Asym_New[k]-Asym[k])/Asym_Err[k],2);
			//cerr<<Form("--- k=%d, R = %5.4f, Asym = %10.4e, Asym_Err = %10.4e, Asym_New=%10.4e, ChiSQ=%f",
			//		k, R, Asym[k]o Asym_Err[k], Asym_New[k],ChiSQ)<<endl;
		}
		cerr<<Form("--- j=%10d, ChiSQ = %f",j,ChiSQ)<<"\r";
        //ChiSQ = sqrt(ChiSQ);
		h1->Fill(ChiSQ);
		if(fabs(ChiSQ-Bin_Total)<0.01){
            cerr<<"--- Find one at ChiSQ = "<<ChiSQ<<endl;
			for(int k=0;k<Bin_Total;k++){
				outfile << Form("%5d %10.6f %10.6f %10.6f %10.6f %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e %10.6e",
						Bin[k], Z[k], xB[k], Q2[k],Pt[k], Sigma_Unp[k], Asym[k], Asym_New[k], Asym_Err[k], 
						deltaU[k], deltaD[k],deltaU_SoLID[k],deltaD_SoLID[k]) <<endl;
			}
			outfile.close();
		    break;
		}
	}

	TCanvas *c1 = new TCanvas("c1","c1",800,600);
	c1->Divide(1,2);
    h1->Draw();
}
