void count(){
	TString experiment; cerr<<"-- Experiment = "; cin >> experiment;
	TString target; cerr<<"-- Target = "; cin >> target;
	TString particle; cerr<<"-- Particle = "; cin >> particle;

	const int N_replica = 100000;
	TString FileName;
	for(int i=0;i<N_replica;i++){
		FileName = Form("%s_%s_%s/new_%s_data_%s_%s_%d.dat", experiment.Data(), target.Data(), particle.Data(), experiment.Data(), target.Data(), particle.Data(),i); 
		ifstream infile(FileName);
		if(infile)
			infile.close();
		else
			cerr<<" *** Cannot find file = "<<FileName.Data()<<endl;	
	}


}
