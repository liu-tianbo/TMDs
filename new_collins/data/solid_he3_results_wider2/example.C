//void read_data(int , int, int, int, int);
void example(){

	int target_flag = 3; // 1->p, 2->d2, 3->3he
	int particle_flag = 1; //1->pip, 2->pim
	int Q2_flag = 1;//See the range of Q2 below
	int z_flag = 1; //See the range of Z below

	/*Get Z and Q2 Bin{{{*/
	double zmin =0., zmax = 0., Q2min=0., Q2max=0.;
	if (z_flag==1){
		zmin = 0.3; zmax = 0.35;
	}else if (z_flag==2){
		zmin = 0.35; zmax = 0.4;
	}else if (z_flag==3){
		zmin = 0.4; zmax = 0.5;
	}else if (z_flag==4){
		zmin = 0.5; zmax = 0.7;
	}
	if (Q2_flag==1){
		Q2min = 1.; Q2max = 2.0;
	}else if (Q2_flag==2){
		Q2min = 2.0; Q2max = 3.5;
	}else if (Q2_flag==3){
		Q2min = 3.5; Q2max = 5.5;
	}else if (Q2_flag==4){
		Q2min = 5.5; Q2max = 10.;
	}
	/*}}}*/

	int flag_t = 1; //1->Colllins, 2->Sivers,3->Pretzelosity
	read_data(target_flag, particle_flag, Q2_flag, z_flag, flag_t);
}

void read_data(int target_flag=3, int particle_flag=1, int Q2_flag=1, int z_flag =1, int flag_t=0){
	//target_flag = 1->"p", 2->"d2" or 3->"3he"
	//particle_flag = 1->pip,2->pim
	//Q2_flag = 1 ~ 6
	//z_flag  = 1 ~ 8
	//flag_t: //1->Colllins, 2->Sivers,3->Pretzelosity

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
	filename.Form("./%s_%s_%d_%d.dat",target.Data(),particle.Data(),z_flag,Q2_flag);
	ifstream infile(filename);

	gStyle->SetOptStat(0);
	int count1,count2;
	double Q2[5000],x[5000],z[5000],pt[5000],y[5000],Astat[5000],N[5000],coverage[5000],coef[3][5000];
	double Q2[5000],x[5000];
	double temp;
	int pt_flag = -1;
	int ncount=0;

	infile >> count1;
	int pt_temp,x_temp;
	while(infile >> pt_flag >> count2){
		for (int j1=0;j1<count2;j1++){
			infile >> pt_temp >> x_temp >> z[ncount] >> Q2[ncount] >> pt[ncount] >> x[ncount] >> y[ncount] >> Astat[ncount] >> N[ncount]>>
				coverage[ncount] >> coef[0][ncount] >> coef[1][ncount] >> coef[2][ncount];

			if(pt_temp==pt_flag && x_temp== j1){

				Astat[ncount] *= coef[2-flag_t][ncount]; //coef[0]->Sivers,coef[1]->Collins, coef[2]->Pretzelosity

				//Only use the data points with err<5%
				if (Astat[ncount]>0.&&Astat[ncount]<0.05){
					cerr<<Form("---z=%d, Q=%d pt = %f, x = %f, Asys= %f",z_flag,Q2_flag, pt[ncount],x[ncount], Astat[ncount])<<endl;
					ncount ++;
				}
			}
		}
	}

	infile.close();
}
