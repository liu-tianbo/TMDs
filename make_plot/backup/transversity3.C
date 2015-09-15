{
//=========Macro generated from canvas: transversity/transversity
//=========  (Wed Aug 27 10:41:14 2014) by ROOT version5.34/10
    /*Define{{{*/
	gROOT->SetStyle("Plain");
	gStyle->Reset();
	gStyle->SetTextFont(132);
	gStyle->SetLabelFont(132,"xyz");

	TCanvas *transversity = new TCanvas("transversity", "transversity",130,95,700,500);
	transversity->SetHighLightColor(2);
	transversity->Range(0,0,1,1);
	transversity->SetFillColor(0);
	transversity->SetFillStyle(4000);
	transversity->SetBorderMode(0);
	transversity->SetBorderSize(2);
	transversity->SetFrameFillStyle(0);
	transversity->SetFrameLineWidth(0);
	transversity->SetFrameBorderMode(0);
	TLatex *   tex = new TLatex(0.045,0.7,"x h_{1}(x,Q^{2})");
	tex->SetTextAngle(90);
	tex->SetLineWidth(2);
	tex->SetTextSize(0.08);
	tex->Draw();
	tex = new TLatex(0.1,0.82,"u");
	tex->SetTextAngle(90);
	tex->SetLineWidth(2);
	tex->SetTextSize(0.08);
	tex->Draw();
	tex = new TLatex(0.1,0.34,"d");
	tex->SetTextAngle(90);
	tex->SetLineWidth(2);
	tex->SetTextSize(0.08);
	tex->Draw();
	tex = new TLatex(0.8,0.05,"x");
	tex->SetLineWidth(2);
	tex->SetTextSize(0.08);
	tex->Draw();

	//int color = kGreen;

	int color = 8; //8 or 5

	// ------------>Primitives in pad: nemo
	TPad *nemo = new TPad("nemo", "This is nemo",0.1,0.1,1,1);
	nemo->Draw();
	nemo->cd();
	nemo->Range(0,0,10,10);
	nemo->SetFillColor(0);
	nemo->SetFillStyle(4000);
	nemo->SetBorderMode(0);
	nemo->SetBorderSize(0);
	nemo->SetLeftMargin(0.05);
	nemo->SetRightMargin(0.04761905);
	nemo->SetTopMargin(0.01538462);
	nemo->SetBottomMargin(0.01666667);
	nemo->SetFrameFillStyle(0);
	nemo->SetFrameLineWidth(0);
	nemo->SetFrameBorderMode(0);
    /*}}}*/

	//////////////////////////////////
	//Transversity-u
	//////////////////////////////////
	/* u{{{*/

	// ------------>Primitives in pad: nemo_1
	nemo_1 = new TPad("nemo_1", "This is nemo_1",0,0.55,1.,1.);
	nemo_1->Draw();
	nemo_1->cd();
	nemo_1->Range(-0.1766028,0,1.295087,0.160371);
	nemo_1->SetFillColor(0);
	nemo_1->SetFillStyle(4000);
	nemo_1->SetBorderMode(0);
	nemo_1->SetBorderSize(2);
	nemo_1->SetLeftMargin(0.12);
	nemo_1->SetRightMargin(0.17);
	nemo_1->SetTopMargin(0);
	nemo_1->SetBottomMargin(0);
	nemo_1->SetFrameFillStyle(0);
	nemo_1->SetFrameLineWidth(0);
	nemo_1->SetFrameBorderMode(0);
	nemo_1->SetFrameFillStyle(0);
	nemo_1->SetFrameLineWidth(0);
	nemo_1->SetFrameBorderMode(0);

	/* Q2 = 10 {{{*/ 
	TGraph *graph = new TGraph(100);
	graph->SetName("Graph0");
	graph->SetTitle("");
	graph->SetFillColor(1);
	graph->SetLineColor(2);
	graph->SetLineWidth(3);
	graph->SetPoint(0,0.001,0.001831567803);
	graph->SetPoint(1,0.001071711809,0.001908467543);
	graph->SetPoint(2,0.001148566202,0.00198943819);
	graph->SetPoint(3,0.001230931962,0.002074739418);
	graph->SetPoint(4,0.00131920432,0.002164848304);
	graph->SetPoint(5,0.001413806849,0.002259898108);
	graph->SetPoint(6,0.001515193495,0.002360243478);
	graph->SetPoint(7,0.001623850762,0.002466392004);
	graph->SetPoint(8,0.001740300038,0.002578591676);
	graph->SetPoint(9,0.001865100102,0.002697348934);
	graph->SetPoint(10,0.001998849805,0.002823240599);
	graph->SetPoint(11,0.002142190941,0.002956628231);
	graph->SetPoint(12,0.002295811329,0.003098082611);
	graph->SetPoint(13,0.002460448113,0.003248221908);
	graph->SetPoint(14,0.002636891298,0.003407615936);
	graph->SetPoint(15,0.002825987544,0.003577043618);
	graph->SetPoint(16,0.003028644223,0.003757310035);
	graph->SetPoint(17,0.003245833779,0.003949199585);
	graph->SetPoint(18,0.003478598392,0.004153463523);
	graph->SetPoint(19,0.003728054976,0.004371068514);
	graph->SetPoint(20,0.003995400543,0.004603146717);
	graph->SetPoint(21,0.004281917944,0.004850700992);
	graph->SetPoint(22,0.004588982027,0.005115089612);
	graph->SetPoint(23,0.00491806623,0.005397723793);
	graph->SetPoint(24,0.005270749657,0.005699639338);
	graph->SetPoint(25,0.00564872465,0.006022489797);
	graph->SetPoint(26,0.006053804915,0.006368062074);
	graph->SetPoint(27,0.006487934217,0.006737977682);
	graph->SetPoint(28,0.006953195718,0.007134518204);
	graph->SetPoint(29,0.007451821962,0.007559787687);
	graph->SetPoint(30,0.007986205596,0.008015619698);
	graph->SetPoint(31,0.008558910848,0.008504612324);
	graph->SetPoint(32,0.009172685829,0.009029481802);
	graph->SetPoint(33,0.009830475725,0.009593170775);
	graph->SetPoint(34,0.01053543692,0.01019940193);
	graph->SetPoint(35,0.01129095217,0.01085108355);
	graph->SetPoint(36,0.01210064677,0.01155129298);
	graph->SetPoint(37,0.01296840605,0.01230462365);
	graph->SetPoint(38,0.0138983939,0.01311553842);
	graph->SetPoint(39,0.01489507288,0.01398881126);
	graph->SetPoint(40,0.0159632255,0.01492976489);
	graph->SetPoint(41,0.01710797728,0.01594275053);
	graph->SetPoint(42,0.01833482128,0.01703349213);
	graph->SetPoint(43,0.01964964449,0.01820946818);
	graph->SetPoint(44,0.02105875604,0.01947830943);
	graph->SetPoint(45,0.02256891754,0.02084667433);
	graph->SetPoint(46,0.02418737544,0.02232113198);
	graph->SetPoint(47,0.02592189589,0.0239110176);
	graph->SetPoint(48,0.02778080195,0.02562567026);
	graph->SetPoint(49,0.02977301351,0.02747505934);
	graph->SetPoint(50,0.03190809018,0.02947057253);
	graph->SetPoint(51,0.03419627705,0.03162376185);
	graph->SetPoint(52,0.03664855394,0.0339457221);
	graph->SetPoint(53,0.03927668805,0.03644706254);
	graph->SetPoint(54,0.04209329041,0.03914148883);
	graph->SetPoint(55,0.04511187642,0.04204510751);
	graph->SetPoint(56,0.04834693069,0.04517521621);
	graph->SetPoint(57,0.05181397655,0.04854395971);
	graph->SetPoint(58,0.05552965055,0.05216553485);
	graph->SetPoint(59,0.05951178226,0.05605653033);
	graph->SetPoint(60,0.06377947983,0.0602351404);
	graph->SetPoint(61,0.06835322171,0.06471635125);
	graph->SetPoint(62,0.0732549549,0.06951364573);
	graph->SetPoint(63,0.07850820025,0.07464138066);
	graph->SetPoint(64,0.08413816532,0.08011302566);
	graph->SetPoint(65,0.09017186538,0.08593830265);
	graph->SetPoint(66,0.09663825298,0.0921211987);
	graph->SetPoint(67,0.1035683569,0.09866491951);
	graph->SetPoint(68,0.1109954312,0.1055654009);
	graph->SetPoint(69,0.1189551144,0.1128090562);
	graph->SetPoint(70,0.1274856008,0.1203745609);
	graph->SetPoint(71,0.1366278239,0.1282298319);
	graph->SetPoint(72,0.1464256523,0.1363320161);
	graph->SetPoint(73,0.1569261008,0.1446024781);
	graph->SetPoint(74,0.1681795553,0.1529684668);
	graph->SetPoint(75,0.1802400155,0.1613161949);
	graph->SetPoint(76,0.1931653531,0.1695095969);
	graph->SetPoint(77,0.2070175901,0.1773817902);
	graph->SetPoint(78,0.221863196,0.1847404034);
	graph->SetPoint(79,0.2377734071,0.1913409235);
	graph->SetPoint(80,0.2548245683,0.1969267872);
	graph->SetPoint(81,0.2730984991,0.2011991737);
	graph->SetPoint(82,0.2926828866,0.2038249015);
	graph->SetPoint(83,0.3136717059,0.2044650681);
	graph->SetPoint(84,0.3361656714,0.2027810886);
	graph->SetPoint(85,0.3602727199,0.1984547697);
	graph->SetPoint(86,0.3861085284,0.1912123356);
	graph->SetPoint(87,0.4137970695,0.1808660704);
	graph->SetPoint(88,0.443471206,0.167481825);
	graph->SetPoint(89,0.4752733285,0.1510842204);
	graph->SetPoint(90,0.5093560387,0.1321787998);
	graph->SetPoint(91,0.5458828818,0.1114037614);
	graph->SetPoint(92,0.5850291308,0.08957889071);
	graph->SetPoint(93,0.6269826282,0.06786232638);
	graph->SetPoint(94,0.6719446868,0.04756128783);
	graph->SetPoint(95,0.7201310559,0.02996101287);
	graph->SetPoint(96,0.7717729568,0.01616605578);
	graph->SetPoint(97,0.8271181917,0.006820041282);
	graph->SetPoint(98,0.8864323337,0.001823639032);
	graph->SetPoint(99,0.95,0.0001476876633);


	TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","",100,0,1.0449);
	Graph_Graph1->SetMinimum(-0.01);
	Graph_Graph1->SetMaximum(0.250371);
	Graph_Graph1->SetDirectory(0);
	Graph_Graph1->SetStats(0);
	Graph_Graph1->GetXaxis()->SetNdivisions(8);
	Graph_Graph1->GetXaxis()->SetLabelFont(42);
	Graph_Graph1->GetXaxis()->SetLabelOffset(0.06);
	Graph_Graph1->GetXaxis()->SetLabelSize(0.1);
	Graph_Graph1->GetXaxis()->SetTitleSize(0.035);
	Graph_Graph1->GetXaxis()->SetTitleColor(0);
	Graph_Graph1->GetXaxis()->SetTitleFont(42);
	Graph_Graph1->GetYaxis()->SetNdivisions(4);
	Graph_Graph1->GetYaxis()->SetLabelFont(42);
	Graph_Graph1->GetYaxis()->SetLabelOffset(0.02);
	Graph_Graph1->GetYaxis()->SetLabelSize(0.13);
	Graph_Graph1->GetYaxis()->SetTitleSize(0.035);
	Graph_Graph1->GetYaxis()->SetTitleFont(42);
	Graph_Graph1->GetZaxis()->SetLabelFont(42);
	Graph_Graph1->GetZaxis()->SetLabelSize(0.035);
	Graph_Graph1->GetZaxis()->SetTitleSize(0.035);
	Graph_Graph1->GetZaxis()->SetTitleFont(42);
	graph->SetHistogram(Graph_Graph1);

	graph->Draw("acp");
	/*}}}*/

	//ERROR BAND BEGIN
	graphbest = new TGraph(7);
	graphbest = graph;

	/*Old errors (not in used){{{*/
	int npoints = 10;
	TGraph *grmax = new TGraph(npoints);
	grmax->SetLineColor(color);
	grmax->SetLineWidth(3);

	graph = new TGraph(10);
	graph->SetName("Graph");
	graph->SetTitle("Graph");
	graph->SetFillColor(kGreen);
	graph->SetLineWidth(1);
	graph->SetPoint(0,0.01,0.006365633569);
	graph->SetPoint(1,0.02,0.012108105);
	graph->SetPoint(2,0.04,0.02427459847);
	graph->SetPoint(3,0.08,0.04973737862);
	graph->SetPoint(4,0.1,0.06229526751);
	graph->SetPoint(5,0.2,0.113413043);
	graph->SetPoint(6,0.3,0.1335295016);
	graph->SetPoint(7,0.5,0.08985387125);
	graph->SetPoint(8,0.7,0.02404030689);
	graph->SetPoint(9,0.9,0.0008003918701);

	double x1[npoints],y[npoints],x2[npoints],x3[npoints];

	for (int i = 0; i < npoints; i++) {

		graph->GetPoint(i,x1[i],x2[i]);
		grmax->SetPoint(i,x1[i],x2[i]);

	}


	TGraph *grmin = new TGraph(npoints);
	grmin->SetLineColor(color);
	grmin->SetLineWidth(3);

	graph = new TGraph(10);
	graph->SetName("Graph");
	graph->SetTitle("Graph");
	graph->SetFillColor(0);
	graph->SetLineWidth(2);
	graph->SetPoint(0,0.01,0.01604080539);
	graph->SetPoint(1,0.02,0.0281595071);
	graph->SetPoint(2,0.04,0.05221960559);
	graph->SetPoint(3,0.08,0.09919982477);
	graph->SetPoint(4,0.1,0.1215828369);
	graph->SetPoint(5,0.2,0.2178491777);
	graph->SetPoint(6,0.3,0.2520433655);
	graph->SetPoint(7,0.5,0.1655670533);
	graph->SetPoint(8,0.7,0.04404793066);
	graph->SetPoint(9,0.9,0.001437342128);

	for (int i = 0; i < npoints; i++) {

		graph->GetPoint(i,x1[i],x3[i]);
		grmin->SetPoint(i,x1[i],x3[i]);

	}

	TGraph *grshade = new TGraph(2*npoints);
	for (int i=0;i<npoints;i++) {
		grshade->SetPoint(i,x1[i],x3[i]);
		grshade->SetPoint(npoints+i,x1[npoints-i-1],x2[npoints-i-1]);
	}
	//grshade->SetFillColor(color);
	//grmin->Draw("cp");
	//grmin->Draw("cont3,same");
	//grmax->Draw("cp");
	//grmax->Draw("cont3,same");
	//grshade->Draw("f");
	/*}}}*/

	/*transversity-u errors {{{*/
	graph = new TGraph(101);
	graph->SetName("Graph1");
	graph->SetTitle("Graph");
	graph->SetFillColor(color);
	graph->SetLineWidth(0);
	graph->SetPoint(0,0.001,0.0003816257325);
	graph->SetPoint(1,0.02036734694,0.01232413103);
	graph->SetPoint(2,0.03973469388,0.02410891854);
	graph->SetPoint(3,0.05910204082,0.03637851305);
	graph->SetPoint(4,0.07846938776,0.04876323737);
	graph->SetPoint(5,0.09783673469,0.06095698351);
	graph->SetPoint(6,0.1172040816,0.07270285516);
	graph->SetPoint(7,0.1365714286,0.08378290493);
	graph->SetPoint(8,0.1559387755,0.0940191772);
	graph->SetPoint(9,0.1753061224,0.1032604881);
	graph->SetPoint(10,0.1946734694,0.1052207074);
	graph->SetPoint(11,0.2140408163,0.1023962879);
	graph->SetPoint(12,0.2334081633,0.09769145027);
	graph->SetPoint(13,0.2527755102,0.09153178995);
	graph->SetPoint(14,0.2721428571,0.08433180655);
	graph->SetPoint(15,0.2915102041,0.07647476215);
	graph->SetPoint(16,0.310877551,0.06830663299);
	graph->SetPoint(17,0.330244898,0.06012386713);
	graph->SetPoint(18,0.3496122449,0.05216828242);
	graph->SetPoint(19,0.3689795918,0.04462851988);
	graph->SetPoint(20,0.3883469388,0.03764367605);
	graph->SetPoint(21,0.4077142857,0.03130274245);
	graph->SetPoint(22,0.4270816327,0.02565989537);
	graph->SetPoint(23,0.4464489796,0.02073720808);
	graph->SetPoint(24,0.4658163265,0.01650196087);
	graph->SetPoint(25,0.4851836735,0.01293745976);
	graph->SetPoint(26,0.5045510204,0.009980401865);
	graph->SetPoint(27,0.5239183673,0.007571141903);
	graph->SetPoint(28,0.5432857143,0.005645944813);
	graph->SetPoint(29,0.5626530612,0.004130776968);
	graph->SetPoint(30,0.5820204082,0.002963845574);
	graph->SetPoint(31,0.6013877551,0.002082163556);
	graph->SetPoint(32,0.620755102,0.001429112769);
	graph->SetPoint(33,0.640122449,0.0009573782496);
	graph->SetPoint(34,0.6594897959,0.0006238847891);
	graph->SetPoint(35,0.6788571429,0.0003945823131);
	graph->SetPoint(36,0.6982244898,0.0002415929069);
	graph->SetPoint(37,0.7175918367,0.0001423317739);
	graph->SetPoint(38,0.7369591837,8.048485473e-05);
	graph->SetPoint(39,0.7563265306,4.337310709e-05);
	graph->SetPoint(40,0.7756938776,2.210032701e-05);
	graph->SetPoint(41,0.7950612245,1.057087173e-05);
	graph->SetPoint(42,0.8144285714,4.67073133e-06);
	graph->SetPoint(43,0.8337959184,1.882579794e-06);
	graph->SetPoint(44,0.8531632653,6.763797432e-07);
	graph->SetPoint(45,0.8725306122,2.091885866e-07);
	graph->SetPoint(46,0.8918979592,5.348193954e-08);
	graph->SetPoint(47,0.9112653061,1.041700148e-08);
	graph->SetPoint(48,0.9306326531,1.365600209e-09);
	graph->SetPoint(49,0.95,9.359842009e-11);
	graph->SetPoint(50,0.95,0.0001726726945);
	graph->SetPoint(51,0.9306326531,0.0004626501085);
	graph->SetPoint(52,0.9112653061,0.0009881755283);
	graph->SetPoint(53,0.8918979592,0.001837958466);
	graph->SetPoint(54,0.8725306122,0.003086164652);
	graph->SetPoint(55,0.8531632653,0.004834746615);
	graph->SetPoint(56,0.8337959184,0.007233979158);
	graph->SetPoint(57,0.8144285714,0.0103515405);
	graph->SetPoint(58,0.7950612245,0.01428723276);
	graph->SetPoint(59,0.7756938776,0.01907411859);
	graph->SetPoint(60,0.7563265306,0.02483132746);
	graph->SetPoint(61,0.7369591837,0.03157869283);
	graph->SetPoint(62,0.7175918367,0.03935422315);
	graph->SetPoint(63,0.6982244898,0.04839148895);
	graph->SetPoint(64,0.6788571429,0.05921520287);
	graph->SetPoint(65,0.6594897959,0.07136901442);
	graph->SetPoint(66,0.640122449,0.0847865484);
	graph->SetPoint(67,0.620755102,0.09935513052);
	graph->SetPoint(68,0.6013877551,0.1150630416);
	graph->SetPoint(69,0.5820204082,0.1316851878);
	graph->SetPoint(70,0.5626530612,0.1490726888);
	graph->SetPoint(71,0.5432857143,0.1670976581);
	graph->SetPoint(72,0.5239183673,0.1853746208);
	graph->SetPoint(73,0.5045510204,0.2037802674);
	graph->SetPoint(74,0.4851836735,0.221963499);
	graph->SetPoint(75,0.4658163265,0.2395430209);
	graph->SetPoint(76,0.4464489796,0.2563659658);
	graph->SetPoint(77,0.4270816327,0.2718186256);
	graph->SetPoint(78,0.4077142857,0.2857752257);
	graph->SetPoint(79,0.3883469388,0.2977852524);
	graph->SetPoint(80,0.3689795918,0.3075008479);
	graph->SetPoint(81,0.3496122449,0.3146222587);
	graph->SetPoint(82,0.330244898,0.3188737316);
	graph->SetPoint(83,0.310877551,0.3200191077);
	graph->SetPoint(84,0.2915102041,0.3178745682);
	graph->SetPoint(85,0.2721428571,0.3123052885);
	graph->SetPoint(86,0.2527755102,0.3032441926);
	graph->SetPoint(87,0.2334081633,0.290710796);
	graph->SetPoint(88,0.2140408163,0.2747957727);
	graph->SetPoint(89,0.1946734694,0.2556767844);
	graph->SetPoint(90,0.1753061224,0.2336168463);
	graph->SetPoint(91,0.1559387755,0.2089772925);
	graph->SetPoint(92,0.1365714286,0.1822289217);
	graph->SetPoint(93,0.1172040816,0.1543951058);
	graph->SetPoint(94,0.09783673469,0.1289773289);
	graph->SetPoint(95,0.07846938776,0.1026438284);
	graph->SetPoint(96,0.05910204082,0.07599733725);
	graph->SetPoint(97,0.03973469388,0.05190144317);
	graph->SetPoint(98,0.02036734694,0.02860241383);
	graph->SetPoint(99,0.001,0.0039650942);
	graph->SetPoint(100,0.001,0.0003816257325);

	graph->Draw("f");

	grapherror = new TGraph(101);
	grapherror = graph;

	TGraph *grmin1 = new TGraph(npoints);
	TGraph *grmax1 = new TGraph(npoints);

	int npoints = 50;
	double x11[npoints],y[npoints],x12[npoints],x13[npoints];


	for (int i = 0; i < npoints; i++) {
		grapherror->GetPoint(i,x11[i],x13[i]);
		grapherror->GetPoint(npoints+i,x11[npoints-i-1],x12[npoints-i-1]);

		grmax1->SetPoint(i,x11[npoints-i-1],x12[npoints-i-1]);
		grmin1->SetPoint(i,x11[i],x13[i]);

	}

	grmin1->Draw("c");
	grmax1->Draw("c");

	graph = graphbest; // back to best Graph
	//ERROR BAND END

	//gre->Draw("E4");
	//gre->Draw("p");

	TH1F *Graph_Graph_Graph12 = new TH1F("Graph_Graph_Graph12","",100,0,1.0449);
	Graph_Graph_Graph12->SetMinimum(-0.020);
	Graph_Graph_Graph12->SetMaximum(0.370);
	Graph_Graph_Graph12->SetDirectory(0);
	Graph_Graph_Graph12->SetStats(0);
	Graph_Graph_Graph12->GetXaxis()->SetNdivisions(8);
	Graph_Graph_Graph12->GetXaxis()->SetLabelFont(42);
	Graph_Graph_Graph12->GetXaxis()->SetLabelOffset(0.06);
	Graph_Graph_Graph12->GetXaxis()->SetLabelSize(0.1);
	Graph_Graph_Graph12->GetXaxis()->SetTitleSize(0.035);
	Graph_Graph_Graph12->GetXaxis()->SetTitleColor(0);
	Graph_Graph_Graph12->GetXaxis()->SetTitleFont(42);
	Graph_Graph_Graph12->GetYaxis()->SetNdivisions(4);
	Graph_Graph_Graph12->GetYaxis()->SetLabelFont(42);
	Graph_Graph_Graph12->GetYaxis()->SetLabelOffset(0.02);
	Graph_Graph_Graph12->GetYaxis()->SetLabelSize(0.12);
	Graph_Graph_Graph12->GetYaxis()->SetTitleSize(0.035);
	Graph_Graph_Graph12->GetYaxis()->SetTitleFont(42);
	Graph_Graph_Graph12->GetZaxis()->SetLabelFont(42);
	Graph_Graph_Graph12->GetZaxis()->SetLabelSize(0.035);
	Graph_Graph_Graph12->GetZaxis()->SetTitleSize(0.035);
	Graph_Graph_Graph12->GetZaxis()->SetTitleFont(42);
	graph->SetHistogram(Graph_Graph_Graph12);

	graph->Draw("cp");
	/*}}}*/

	/*Q2 = 1000{{{*/
	graph = new TGraph(100);
	graph->SetName("Graph0");
	graph->SetTitle("");
	graph->SetFillColor(1);
	graph->SetLineColor(1);
	graph->SetLineStyle(9);
	graph->SetLineWidth(3);
	graph->SetPoint(0,0.001,0.002055977343);
	graph->SetPoint(1,0.001071711809,0.0021493382);
	graph->SetPoint(2,0.001148566202,0.002248110013);
	graph->SetPoint(3,0.001230931962,0.002352673528);
	graph->SetPoint(4,0.00131920432,0.002463437043);
	graph->SetPoint(5,0.001413806849,0.002580836151);
	graph->SetPoint(6,0.001515193495,0.002705343467);
	graph->SetPoint(7,0.001623850762,0.002837472199);
	graph->SetPoint(8,0.001740300038,0.002977775717);
	graph->SetPoint(9,0.001865100102,0.003126861123);
	graph->SetPoint(10,0.001998849805,0.003285378352);
	graph->SetPoint(11,0.002142190941,0.003454005498);
	graph->SetPoint(12,0.002295811329,0.003633472816);
	graph->SetPoint(13,0.002460448113,0.003824581237);
	graph->SetPoint(14,0.002636891298,0.004028214711);
	graph->SetPoint(15,0.002825987544,0.0042453309);
	graph->SetPoint(16,0.003028644223,0.004476941431);
	graph->SetPoint(17,0.003245833779,0.004724112932);
	graph->SetPoint(18,0.003478598392,0.00498799534);
	graph->SetPoint(19,0.003728054976,0.005269848623);
	graph->SetPoint(20,0.003995400543,0.005571051572);
	graph->SetPoint(21,0.004281917944,0.005893105104);
	graph->SetPoint(22,0.004588982027,0.006237589017);
	graph->SetPoint(23,0.00491806623,0.006606181644);
	graph->SetPoint(24,0.005270749657,0.007000692348);
	graph->SetPoint(25,0.00564872465,0.00742306965);
	graph->SetPoint(26,0.006053804915,0.007875438836);
	graph->SetPoint(27,0.006487934217,0.008360121131);
	graph->SetPoint(28,0.006953195718,0.008879627614);
	graph->SetPoint(29,0.007451821962,0.009436559799);
	graph->SetPoint(30,0.007986205596,0.0100336186);
	graph->SetPoint(31,0.008558910848,0.01067374034);
	graph->SetPoint(32,0.009172685829,0.01136026768);
	graph->SetPoint(33,0.009830475725,0.01209687492);
	graph->SetPoint(34,0.01053543692,0.01288733612);
	graph->SetPoint(35,0.01129095217,0.0137353504);
	graph->SetPoint(36,0.01210064677,0.0146449197);
	graph->SetPoint(37,0.01296840605,0.01562081524);
	graph->SetPoint(38,0.0138983939,0.01666824652);
	graph->SetPoint(39,0.01489507288,0.01779234872);
	graph->SetPoint(40,0.0159632255,0.01899793954);
	graph->SetPoint(41,0.01710797728,0.02029080952);
	graph->SetPoint(42,0.01833482128,0.02167739841);
	graph->SetPoint(43,0.01964964449,0.02316458519);
	graph->SetPoint(44,0.02105875604,0.02475869622);
	graph->SetPoint(45,0.02256891754,0.02646678326);
	graph->SetPoint(46,0.02418737544,0.0282964977);
	graph->SetPoint(47,0.02592189589,0.03025539477);
	graph->SetPoint(48,0.02778080195,0.03235134559);
	graph->SetPoint(49,0.02977301351,0.03459292151);
	graph->SetPoint(50,0.03190809018,0.03698985429);
	graph->SetPoint(51,0.03419627705,0.03955024634);
	graph->SetPoint(52,0.03664855394,0.04228176395);
	graph->SetPoint(53,0.03927668805,0.04519245392);
	graph->SetPoint(54,0.04209329041,0.04829262422);
	graph->SetPoint(55,0.04511187642,0.05159143727);
	graph->SetPoint(56,0.04834693069,0.05509598167);
	graph->SetPoint(57,0.05181397655,0.05881237882);
	graph->SetPoint(58,0.05552965055,0.06274700689);
	graph->SetPoint(59,0.05951178226,0.0669056197);
	graph->SetPoint(60,0.06377947983,0.0712908172);
	graph->SetPoint(61,0.06835322171,0.07590354962);
	graph->SetPoint(62,0.0732549549,0.08074236657);
	graph->SetPoint(63,0.07850820025,0.08580255913);
	graph->SetPoint(64,0.08413816532,0.0910746151);
	graph->SetPoint(65,0.09017186538,0.09654479296);
	graph->SetPoint(66,0.09663825298,0.1021948797);
	graph->SetPoint(67,0.1035683569,0.1079981908);
	graph->SetPoint(68,0.1109954312,0.1139199931);
	graph->SetPoint(69,0.1189551144,0.1199169763);
	graph->SetPoint(70,0.1274856008,0.125938094);
	graph->SetPoint(71,0.1366278239,0.1319186226);
	graph->SetPoint(72,0.1464256523,0.1377812192);
	graph->SetPoint(73,0.1569261008,0.1434303394);
	graph->SetPoint(74,0.1681795553,0.1487644572);
	graph->SetPoint(75,0.1802400155,0.1536586704);
	graph->SetPoint(76,0.1931653531,0.157977621);
	graph->SetPoint(77,0.2070175901,0.1615645083);
	graph->SetPoint(78,0.221863196,0.1642590436);
	graph->SetPoint(79,0.2377734071,0.1658808205);
	graph->SetPoint(80,0.2548245683,0.1662479361);
	graph->SetPoint(81,0.2730984991,0.1651817603);
	graph->SetPoint(82,0.2926828866,0.162511259);
	graph->SetPoint(83,0.3136717059,0.1580862426);
	graph->SetPoint(84,0.3361656714,0.1517968398);
	graph->SetPoint(85,0.3602727199,0.1435932655);
	graph->SetPoint(86,0.3861085284,0.1334884189);
	graph->SetPoint(87,0.4137970695,0.121586299);
	graph->SetPoint(88,0.443471206,0.108165183);
	graph->SetPoint(89,0.4752733285,0.09353480027);
	graph->SetPoint(90,0.5093560387,0.07818273415);
	graph->SetPoint(91,0.5458828818,0.06272140123);
	graph->SetPoint(92,0.5850291308,0.0478116165);
	graph->SetPoint(93,0.6269826282,0.03413784424);
	graph->SetPoint(94,0.6719446868,0.02238186829);
	graph->SetPoint(95,0.7201310559,0.01305403212);
	graph->SetPoint(96,0.7717729568,0.006423226618);
	graph->SetPoint(97,0.8271181917,0.002411284439);
	graph->SetPoint(98,0.8864323337,0.0005470824907);
	graph->SetPoint(99,0.95,3.261394227e-05);

	graph->Draw("cp");
	/*}}}*/

	/* Q2 = 2.4{{{*/
	TGraph *graph = new TGraph(100);
	graph->SetName("Graph0");
	graph->SetTitle("");
	graph->SetFillColor(1);
	graph->SetLineColor(1);
	graph->SetLineWidth(3);
	graph->SetLineStyle(2);
	graph->SetPoint(0,0.001,0.001746968073);
	graph->SetPoint(1,0.001071711809,0.001817996519);
	graph->SetPoint(2,0.001148566202,0.001892438881);
	graph->SetPoint(3,0.001230931962,0.001970349852);
	graph->SetPoint(4,0.00131920432,0.002053005678);
	graph->SetPoint(5,0.001413806849,0.002139786015);
	graph->SetPoint(6,0.001515193495,0.002230997493);
	graph->SetPoint(7,0.001623850762,0.00232757933);
	graph->SetPoint(8,0.001740300038,0.002429314728);
	graph->SetPoint(9,0.001865100102,0.002536654628);
	graph->SetPoint(10,0.001998849805,0.002650300288);
	graph->SetPoint(11,0.002142190941,0.002770570018);
	graph->SetPoint(12,0.002295811329,0.002897692646);
	graph->SetPoint(13,0.002460448113,0.00303218222);
	graph->SetPoint(14,0.002636891298,0.003175073979);
	graph->SetPoint(15,0.002825987544,0.003326323843);
	graph->SetPoint(16,0.003028644223,0.003486676537);
	graph->SetPoint(17,0.003245833779,0.003657888309);
	graph->SetPoint(18,0.003478598392,0.003839155203);
	graph->SetPoint(19,0.003728054976,0.004031616891);
	graph->SetPoint(20,0.003995400543,0.004237485779);
	graph->SetPoint(21,0.004281917944,0.004455797282);
	graph->SetPoint(22,0.004588982027,0.004688556141);
	graph->SetPoint(23,0.00491806623,0.004938078091);
	graph->SetPoint(24,0.005270749657,0.005203062236);
	graph->SetPoint(25,0.00564872465,0.005486201235);
	graph->SetPoint(26,0.006053804915,0.005789753891);
	graph->SetPoint(27,0.006487934217,0.006112922418);
	graph->SetPoint(28,0.006953195718,0.006459671165);
	graph->SetPoint(29,0.007451821962,0.006832038221);
	graph->SetPoint(30,0.007986205596,0.007229202858);
	graph->SetPoint(31,0.008558910848,0.007655814605);
	graph->SetPoint(32,0.009172685829,0.008113880433);
	graph->SetPoint(33,0.009830475725,0.008604129811);
	graph->SetPoint(34,0.01053543692,0.009132331716);
	graph->SetPoint(35,0.01129095217,0.009700406808);
	graph->SetPoint(36,0.01210064677,0.01030969953);
	graph->SetPoint(37,0.01296840605,0.01096557439);
	graph->SetPoint(38,0.0138983939,0.01167216749);
	graph->SetPoint(39,0.01489507288,0.01243346297);
	graph->SetPoint(40,0.0159632255,0.01325388325);
	graph->SetPoint(41,0.01710797728,0.01413854434);
	graph->SetPoint(42,0.01833482128,0.01509230737);
	graph->SetPoint(43,0.01964964449,0.01612004932);
	graph->SetPoint(44,0.02105875604,0.01723225447);
	graph->SetPoint(45,0.02256891754,0.01843502421);
	graph->SetPoint(46,0.02418737544,0.01973222389);
	graph->SetPoint(47,0.02592189589,0.02113424703);
	graph->SetPoint(48,0.02778080195,0.02265006672);
	graph->SetPoint(49,0.02977301351,0.0242893279);
	graph->SetPoint(50,0.03190809018,0.02606511109);
	graph->SetPoint(51,0.03419627705,0.02798809709);
	graph->SetPoint(52,0.03664855394,0.03006934994);
	graph->SetPoint(53,0.03927668805,0.03232217117);
	graph->SetPoint(54,0.04209329041,0.03475881395);
	graph->SetPoint(55,0.04511187642,0.03739658333);
	graph->SetPoint(56,0.04834693069,0.04025753794);
	graph->SetPoint(57,0.05181397655,0.04335636855);
	graph->SetPoint(58,0.05552965055,0.04670923912);
	graph->SetPoint(59,0.05951178226,0.05033535714);
	graph->SetPoint(60,0.06377947983,0.05425914164);
	graph->SetPoint(61,0.06835322171,0.05850213337);
	graph->SetPoint(62,0.0732549549,0.06308479701);
	graph->SetPoint(63,0.07850820025,0.06802927777);
	graph->SetPoint(64,0.08413816532,0.07335789059);
	graph->SetPoint(65,0.09017186538,0.07909307288);
	graph->SetPoint(66,0.09663825298,0.08525665353);
	graph->SetPoint(67,0.1035683569,0.0918584386);
	graph->SetPoint(68,0.1109954312,0.09891299864);
	graph->SetPoint(69,0.1189551144,0.1064384473);
	graph->SetPoint(70,0.1274856008,0.1144207142);
	graph->SetPoint(71,0.1366278239,0.1228538326);
	graph->SetPoint(72,0.1464256523,0.1317222584);
	graph->SetPoint(73,0.1569261008,0.1409704723);
	graph->SetPoint(74,0.1681795553,0.1505518778);
	graph->SetPoint(75,0.1802400155,0.1603785311);
	graph->SetPoint(76,0.1931653531,0.1703296829);
	graph->SetPoint(77,0.2070175901,0.1802601827);
	graph->SetPoint(78,0.221863196,0.1899804703);
	graph->SetPoint(79,0.2377734071,0.1992423439);
	graph->SetPoint(80,0.2548245683,0.2077784896);
	graph->SetPoint(81,0.2730984991,0.2152438889);
	graph->SetPoint(82,0.2926828866,0.2212424332);
	graph->SetPoint(83,0.3136717059,0.2253534803);
	graph->SetPoint(84,0.3361656714,0.2271148343);
	graph->SetPoint(85,0.3602727199,0.2260506722);
	graph->SetPoint(86,0.3861085284,0.2217062785);
	graph->SetPoint(87,0.4137970695,0.2136552327);
	graph->SetPoint(88,0.443471206,0.2017736947);
	graph->SetPoint(89,0.4752733285,0.1858387546);
	graph->SetPoint(90,0.5093560387,0.1662687795);
	graph->SetPoint(91,0.5458828818,0.1435254046);
	graph->SetPoint(92,0.5850291308,0.1184074413);
	graph->SetPoint(93,0.6269826282,0.09230976041);
	graph->SetPoint(94,0.6719446868,0.06680205148);
	graph->SetPoint(95,0.7201310559,0.043659642);
	graph->SetPoint(96,0.7717729568,0.02461281126);
	graph->SetPoint(97,0.8271181917,0.01097400063);
	graph->SetPoint(98,0.8864323337,0.003170304885);
	graph->SetPoint(99,0.95,0.0002966620536);

	graph->Draw("cp");
	/*}}}*/
	/*}}}*/

	TLine *line = new TLine(0,0,1.0449,0);
	line->Draw();

	nemo_1->Modified();
	nemo->cd();

	//////////////////////////////////
	//Transversity-d
	//////////////////////////////////
	/*Hd{{{*/

	// ------------>Primitives in pad: nemo_3
	nemo_3 = new TPad("nemo_3", "This is nemo_3",0,0,1.,0.55);
	nemo_3->Draw();
	nemo_3->cd();
	nemo_3->Range(-0.1766028,-0.1060926,1.295087,0.009642718);
	nemo_3->SetFillColor(0);
	nemo_3->SetFillStyle(4000);
	nemo_3->SetBorderMode(0);
	nemo_3->SetBorderSize(2);
	nemo_3->SetLeftMargin(0.12);
	nemo_3->SetRightMargin(0.17);
	nemo_3->SetTopMargin(0);
	nemo_3->SetBottomMargin(0.17);
	nemo_3->SetFrameFillStyle(0);
	nemo_3->SetFrameLineWidth(0);
	nemo_3->SetFrameBorderMode(0);
	nemo_3->SetFrameFillStyle(0);
	nemo_3->SetFrameLineWidth(0);
	nemo_3->SetFrameBorderMode(0);

	/* Q2 = 10{{{*/ 
	graph = new TGraph(100);
	graph->SetName("Graph0");
	graph->SetTitle("");
	graph->SetFillColor(1);
	graph->SetLineColor(2);
	graph->SetLineWidth(3);
	graph->SetPoint(0,0.001,-0.000104127967);
	graph->SetPoint(1,0.001071711809,-0.0001164348671);
	graph->SetPoint(2,0.001148566202,-0.0001302079398);
	graph->SetPoint(3,0.001230931962,-0.0001456231433);
	graph->SetPoint(4,0.00131920432,-0.0001628846081);
	graph->SetPoint(5,0.001413806849,-0.0001822079962);
	graph->SetPoint(6,0.001515193495,-0.0002038432874);
	graph->SetPoint(7,0.001623850762,-0.0002280747773);
	graph->SetPoint(8,0.001740300038,-0.0002552069452);
	graph->SetPoint(9,0.001865100102,-0.0002855956565);
	graph->SetPoint(10,0.001998849805,-0.0003196415377);
	graph->SetPoint(11,0.002142190941,-0.0003577778285);
	graph->SetPoint(12,0.002295811329,-0.0004005017839);
	graph->SetPoint(13,0.002460448113,-0.0004483687826);
	graph->SetPoint(14,0.002636891298,-0.0005019922782);
	graph->SetPoint(15,0.002825987544,-0.0005620829868);
	graph->SetPoint(16,0.003028644223,-0.000629427866);
	graph->SetPoint(17,0.003245833779,-0.0007048936011);
	graph->SetPoint(18,0.003478598392,-0.0007894525004);
	graph->SetPoint(19,0.003728054976,-0.0008842091801);
	graph->SetPoint(20,0.003995400543,-0.0009904070356);
	graph->SetPoint(21,0.004281917944,-0.001109412209);
	graph->SetPoint(22,0.004588982027,-0.00124277464);
	graph->SetPoint(23,0.00491806623,-0.001392220262);
	graph->SetPoint(24,0.005270749657,-0.001559631796);
	graph->SetPoint(25,0.00564872465,-0.001747197978);
	graph->SetPoint(26,0.006053804915,-0.001957349631);
	graph->SetPoint(27,0.006487934217,-0.002192729513);
	graph->SetPoint(28,0.006953195718,-0.002456331029);
	graph->SetPoint(29,0.007451821962,-0.002751431957);
	graph->SetPoint(30,0.007986205596,-0.003081639867);
	graph->SetPoint(31,0.008558910848,-0.003451275166);
	graph->SetPoint(32,0.009172685829,-0.003864926194);
	graph->SetPoint(33,0.009830475725,-0.004327487714);
	graph->SetPoint(34,0.01053543692,-0.004844333762);
	graph->SetPoint(35,0.01129095217,-0.005421623177);
	graph->SetPoint(36,0.01210064677,-0.006066308587);
	graph->SetPoint(37,0.01296840605,-0.006786122399);
	graph->SetPoint(38,0.0138983939,-0.00758874585);
	graph->SetPoint(39,0.01489507288,-0.008482731786);
	graph->SetPoint(40,0.0159632255,-0.009478078096);
	graph->SetPoint(41,0.01710797728,-0.01058541021);
	graph->SetPoint(42,0.01833482128,-0.01181618893);
	graph->SetPoint(43,0.01964964449,-0.01318259473);
	graph->SetPoint(44,0.02105875604,-0.0146964194);
	graph->SetPoint(45,0.02256891754,-0.01637060807);
	graph->SetPoint(46,0.02418737544,-0.01821994636);
	graph->SetPoint(47,0.02592189589,-0.02026261212);
	graph->SetPoint(48,0.02778080195,-0.02251429554);
	graph->SetPoint(49,0.02977301351,-0.02498774302);
	graph->SetPoint(50,0.03190809018,-0.02769297844);
	graph->SetPoint(51,0.03419627705,-0.03064507159);
	graph->SetPoint(52,0.03664855394,-0.03386425156);
	graph->SetPoint(53,0.03927668805,-0.03737367473);
	graph->SetPoint(54,0.04209329041,-0.04117496241);
	graph->SetPoint(55,0.04511187642,-0.04526312396);
	graph->SetPoint(56,0.04834693069,-0.04963348813);
	graph->SetPoint(57,0.05181397655,-0.05430926483);
	graph->SetPoint(58,0.05552965055,-0.05928101233);
	graph->SetPoint(59,0.05951178226,-0.06451217702);
	graph->SetPoint(60,0.06377947983,-0.06997044789);
	graph->SetPoint(61,0.06835322171,-0.07563310351);
	graph->SetPoint(62,0.0732549549,-0.08146107594);
	graph->SetPoint(63,0.07850820025,-0.08736658055);
	graph->SetPoint(64,0.08413816532,-0.09326729229);
	graph->SetPoint(65,0.09017186538,-0.09906858122);
	graph->SetPoint(66,0.09663825298,-0.1046537754);
	graph->SetPoint(67,0.1035683569,-0.1098770899);
	graph->SetPoint(68,0.1109954312,-0.1145889968);
	graph->SetPoint(69,0.1189551144,-0.1186397899);
	graph->SetPoint(70,0.1274856008,-0.1218426299);
	graph->SetPoint(71,0.1366278239,-0.1240178845);
	graph->SetPoint(72,0.1464256523,-0.1250008133);
	graph->SetPoint(73,0.1569261008,-0.1246318399);
	graph->SetPoint(74,0.1681795553,-0.122779201);
	graph->SetPoint(75,0.1802400155,-0.1193619272);
	graph->SetPoint(76,0.1931653531,-0.1143426277);
	graph->SetPoint(77,0.2070175901,-0.1077623969);
	graph->SetPoint(78,0.221863196,-0.09971472067);
	graph->SetPoint(79,0.2377734071,-0.09042391299);
	graph->SetPoint(80,0.2548245683,-0.08014257832);
	graph->SetPoint(81,0.2730984991,-0.06922898469);
	graph->SetPoint(82,0.2926828866,-0.05810608696);
	graph->SetPoint(83,0.3136717059,-0.04720358521);
	graph->SetPoint(84,0.3361656714,-0.03695211589);
	graph->SetPoint(85,0.3602727199,-0.0277340584);
	graph->SetPoint(86,0.3861085284,-0.0198396885);
	graph->SetPoint(87,0.4137970695,-0.01343603013);
	graph->SetPoint(88,0.443471206,-0.008529568096);
	graph->SetPoint(89,0.4752733285,-0.005027129534);
	graph->SetPoint(90,0.5093560387,-0.002708713139);
	graph->SetPoint(91,0.5458828818,-0.001311808035);
	graph->SetPoint(92,0.5850291308,-0.0005592897905);
	graph->SetPoint(93,0.6269826282,-0.000204370115);
	graph->SetPoint(94,0.6719446868,-6.174288673e-05);
	graph->SetPoint(95,0.7201310559,-1.45547131e-05);
	graph->SetPoint(96,0.7717729568,-2.400223905e-06);
	graph->SetPoint(97,0.8271181917,-2.197106399e-07);
	graph->SetPoint(98,0.8864323337,-6.373847773e-09);
	graph->SetPoint(99,0.95,-7.983881185e-12);

	TH1F *Graph_Graph3 = new TH1F("Graph_Graph3","",100,0,1.0449);
	Graph_Graph3->SetMinimum(-0.17);
	Graph_Graph3->SetMaximum(0.09);
	Graph_Graph3->SetDirectory(0);
	Graph_Graph3->SetStats(0);
	Graph_Graph3->GetXaxis()->SetNdivisions(8);
	Graph_Graph3->GetXaxis()->SetLabelFont(42);
	Graph_Graph3->GetXaxis()->SetLabelOffset(0.06);
	Graph_Graph3->GetXaxis()->SetLabelSize(0.11);
	Graph_Graph3->GetXaxis()->SetTitleSize(0.035);
	Graph_Graph3->GetXaxis()->SetTitleColor(0);
	Graph_Graph3->GetXaxis()->SetTitleFont(42);
	Graph_Graph3->GetYaxis()->SetNdivisions(6);
	Graph_Graph3->GetYaxis()->SetLabelFont(42);
	Graph_Graph3->GetYaxis()->SetLabelOffset(0.02);
	Graph_Graph3->GetYaxis()->SetLabelSize(0.09);
	Graph_Graph3->GetYaxis()->SetTitleSize(0.035);
	Graph_Graph3->GetYaxis()->SetTitleFont(42);
	Graph_Graph3->GetZaxis()->SetLabelFont(42);
	Graph_Graph3->GetZaxis()->SetLabelSize(0.035);
	Graph_Graph3->GetZaxis()->SetTitleSize(0.035);
	Graph_Graph3->GetZaxis()->SetTitleFont(42);
	graph->SetHistogram(Graph_Graph3);

	graph->Draw("acp");
	/*}}}*/

	//ERROR BAND BEGIN
	graphbest = new TGraph(7);
	graphbest = graph;


	/*old error shade (no use now){{{*/
	int npoints = 10;
	TGraph *grmax = new TGraph(npoints);
	grmax->SetLineColor(color);
	grmax->SetLineWidth(3);

	graph = new TGraph(10);
	graph->SetName("Graph");
	graph->SetTitle("Graph");
	graph->SetFillColor(1);
	graph->SetLineWidth(1);
	graph->SetPoint(0,0.01,-0.009639427719);
	graph->SetPoint(1,0.02,-0.02778329211);
	graph->SetPoint(2,0.04,-0.07075136273);
	graph->SetPoint(3,0.08,-0.1328429325);
	graph->SetPoint(4,0.1,-0.1436830833);
	graph->SetPoint(5,0.2,-0.1112139692);
	graph->SetPoint(6,0.3,-0.06363526641);
	graph->SetPoint(7,0.5,-0.006868272374);
	graph->SetPoint(8,0.7,-0.0001628711549);
	graph->SetPoint(9,0.9,-1.167297445e-07);

	double x1[npoints],y[npoints],x2[npoints],x3[npoints];

	for (int i = 0; i < npoints; i++) {

		graph->GetPoint(i,x1[i],x2[i]);
		grmax->SetPoint(i,x1[i],x2[i]);

	}

	TGraph *grmin = new TGraph(npoints);
	grmin->SetLineColor(color);
	grmin->SetLineWidth(3);

	graph = new TGraph(10);
	graph->SetName("Graph");
	graph->SetTitle("Graph");
	graph->SetFillColor(1);
	graph->SetLineWidth(2);
	graph->SetPoint(0,0.01,-0.001371575104);
	graph->SetPoint(1,0.02,-0.004971105309);
	graph->SetPoint(2,0.04,-0.0169984069);
	graph->SetPoint(3,0.08,-0.04887113567);
	graph->SetPoint(4,0.1,-0.06331879015);
	graph->SetPoint(5,0.2,-0.04701644765);
	graph->SetPoint(6,0.3,-0.008531614158);
	graph->SetPoint(7,0.5,-4.207845163e-05);
	graph->SetPoint(8,0.7,-8.037111425e-09);
	graph->SetPoint(9,0.9,-1.907677516e-16);

	for (int i = 0; i < npoints; i++) {

		graph->GetPoint(i,x1[i],x3[i]);
		grmin->SetPoint(i,x1[i],x3[i]);

	}

	TGraph *grshade = new TGraph(2*npoints);
	for (int i=0;i<npoints;i++) {
		grshade->SetPoint(i,x1[i],x3[i]);
		grshade->SetPoint(npoints+i,x1[npoints-i-1],x2[npoints-i-1]);
	}
	//rshade->SetFillColor(color);
	//grmin->Draw("cont1");
	//grmax->Draw("cont1");
	//grshade->Draw("E4");
	/*}}}*/

	/*transversity-d errors   {{{*/
	graph = new TGraph(101);
	graph->SetName("Graph1");
	graph->SetTitle("Graph");
	graph->SetFillColor(color);
	graph->SetLineWidth(0);
	graph->SetPoint(0,0.001,-0.02495246324);
	graph->SetPoint(1,0.02036734694,-0.05542694249);
	graph->SetPoint(2,0.03973469388,-0.09733135628);
	graph->SetPoint(3,0.05910204082,-0.125784102);
	graph->SetPoint(4,0.07846938776,-0.1416886183);
	graph->SetPoint(5,0.09783673469,-0.1472663291);
	graph->SetPoint(6,0.1172040816,-0.144897957);
	graph->SetPoint(7,0.1365714286,-0.1370944098);
	graph->SetPoint(8,0.1559387755,-0.129335972);
	graph->SetPoint(9,0.1753061224,-0.1219351968);
	graph->SetPoint(10,0.1946734694,-0.1136954871);
	graph->SetPoint(11,0.2140408163,-0.1043162919);
	graph->SetPoint(12,0.2334081633,-0.09574532127);
	graph->SetPoint(13,0.2527755102,-0.08761674845);
	graph->SetPoint(14,0.2721428571,-0.0807576423);
	graph->SetPoint(15,0.2915102041,-0.07321280956);
	graph->SetPoint(16,0.310877551,-0.06556197029);
	graph->SetPoint(17,0.330244898,-0.05843830108);
	graph->SetPoint(18,0.3496122449,-0.05109043796);
	graph->SetPoint(19,0.3689795918,-0.04375162766);
	graph->SetPoint(20,0.3883469388,-0.03672426735);
	graph->SetPoint(21,0.4077142857,-0.03023638875);
	graph->SetPoint(22,0.4270816327,-0.02465371842);
	graph->SetPoint(23,0.4464489796,-0.02001332066);
	graph->SetPoint(24,0.4658163265,-0.01605244873);
	graph->SetPoint(25,0.4851836735,-0.01269962612);
	graph->SetPoint(26,0.5045510204,-0.00991485201);
	graph->SetPoint(27,0.5239183673,-0.0076373141);
	graph->SetPoint(28,0.5432857143,-0.005799473777);
	graph->SetPoint(29,0.5626530612,-0.005211329558);
	graph->SetPoint(30,0.5820204082,-0.005375225031);
	graph->SetPoint(31,0.6013877551,-0.005368865132);
	graph->SetPoint(32,0.620755102,-0.005190770138);
	graph->SetPoint(33,0.640122449,-0.004851873617);
	graph->SetPoint(34,0.6594897959,-0.004382181464);
	graph->SetPoint(35,0.6788571429,-0.003818170519);
	graph->SetPoint(36,0.6982244898,-0.003201840801);
	graph->SetPoint(37,0.7175918367,-0.002578501388);
	graph->SetPoint(38,0.7369591837,-0.001984861089);
	graph->SetPoint(39,0.7563265306,-0.001453169128);
	graph->SetPoint(40,0.7756938776,-0.001040864631);
	graph->SetPoint(41,0.7950612245,-0.000945655947);
	graph->SetPoint(42,0.8144285714,-0.000840772952);
	graph->SetPoint(43,0.8337959184,-0.0007276861015);
	graph->SetPoint(44,0.8531632653,-0.0006094517204);
	graph->SetPoint(45,0.8725306122,-0.0004901752337);
	graph->SetPoint(46,0.8918979592,-0.0003742247232);
	graph->SetPoint(47,0.9112653061,-0.0002667819672);
	graph->SetPoint(48,0.9306326531,-0.0001730189376);
	graph->SetPoint(49,0.95,-9.696500088e-05);
	graph->SetPoint(50,0.95,2.340535142e-07);
	graph->SetPoint(51,0.9306326531,1.048715044e-06);
	graph->SetPoint(52,0.9112653061,3.326196206e-06);
	graph->SetPoint(53,0.8918979592,8.518205885e-06);
	graph->SetPoint(54,0.8725306122,1.882131973e-05);
	graph->SetPoint(55,0.8531632653,3.732939312e-05);
	graph->SetPoint(56,0.8337959184,6.82304656e-05);
	graph->SetPoint(57,0.8144285714,0.0001169449379);
	graph->SetPoint(58,0.7950612245,0.0001904060719);
	graph->SetPoint(59,0.7756938776,0.000297594595);
	graph->SetPoint(60,0.7563265306,0.0004494781224);
	graph->SetPoint(61,0.7369591837,0.0006602245402);
	graph->SetPoint(62,0.7175918367,0.0009471382009);
	graph->SetPoint(63,0.6982244898,0.001330917089);
	graph->SetPoint(64,0.6788571429,0.001837612779);
	graph->SetPoint(65,0.6594897959,0.002495261995);
	graph->SetPoint(66,0.640122449,0.003336692814);
	graph->SetPoint(67,0.620755102,0.004397664906);
	graph->SetPoint(68,0.6013877551,0.005711329985);
	graph->SetPoint(69,0.5820204082,0.007313964085);
	graph->SetPoint(70,0.5626530612,0.009232102506);
	graph->SetPoint(71,0.5432857143,0.01148479352);
	graph->SetPoint(72,0.5239183673,0.01408779784);
	graph->SetPoint(73,0.5045510204,0.01702513859);
	graph->SetPoint(74,0.4851836735,0.02028242434);
	graph->SetPoint(75,0.4658163265,0.02382054364);
	graph->SetPoint(76,0.4464489796,0.02755853338);
	graph->SetPoint(77,0.4270816327,0.03145504973);
	graph->SetPoint(78,0.4077142857,0.03598294363);
	graph->SetPoint(79,0.3883469388,0.04125722815);
	graph->SetPoint(80,0.3689795918,0.04665572614);
	graph->SetPoint(81,0.3496122449,0.0520391509);
	graph->SetPoint(82,0.330244898,0.05878715333);
	graph->SetPoint(83,0.310877551,0.06524419239);
	graph->SetPoint(84,0.2915102041,0.07106897752);
	graph->SetPoint(85,0.2721428571,0.07589260811);
	graph->SetPoint(86,0.2527755102,0.07934296753);
	graph->SetPoint(87,0.2334081633,0.08104726286);
	graph->SetPoint(88,0.2140408163,0.08069054684);
	graph->SetPoint(89,0.1946734694,0.07805332142);
	graph->SetPoint(90,0.1753061224,0.07305405639);
	graph->SetPoint(91,0.1559387755,0.06577600164);
	graph->SetPoint(92,0.1365714286,0.05650899862);
	graph->SetPoint(93,0.1172040816,0.04578582884);
	graph->SetPoint(94,0.09783673469,0.03436971265);
	graph->SetPoint(95,0.07846938776,0.02320831875);
	graph->SetPoint(96,0.05910204082,0.01336823545);
	graph->SetPoint(97,0.03973469388,0.005854416259);
	graph->SetPoint(98,0.02036734694,0.00236141171);
	graph->SetPoint(99,0.001,2.696339496e-05);
	graph->Draw("f");

	grapherror = new TGraph(101);
	grapherror = graph;

	TGraph *grmin1 = new TGraph(npoints);
	TGraph *grmax1 = new TGraph(npoints);

	int npoints = 50;
	double x11[npoints],y[npoints],x12[npoints],x13[npoints];


	for (int i = 0; i < npoints; i++) {
		grapherror->GetPoint(i,x11[i],x13[i]);
		grapherror->GetPoint(npoints+i,x11[npoints-i-1],x12[npoints-i-1]);

		grmax1->SetPoint(i,x11[npoints-i-1],x12[npoints-i-1]);
		grmin1->SetPoint(i,x11[i],x13[i]);

	}

	grmin1->Draw("c");
	grmax1->Draw("c");
	/*}}}*/

	graph = graphbest; // back to best Graph
	//ERROR BAND END

	//gre->Draw("E4");
	graph->Draw("cp");
	graph->Draw("cp");
	line = new TLine(0,0,1.0449,0);
	line->Draw();

	/* Q2 = 1000{{{*/
	graph = new TGraph(100);
	graph->SetName("Graph0");
	graph->SetTitle("");
	graph->SetFillColor(1);
	graph->SetLineColor(1);
	graph->SetLineStyle(9);
	graph->SetLineWidth(3);
	graph->SetPoint(0,0.001,-0.0002337217876);
	graph->SetPoint(1,0.001071711809,-0.0002601548159);
	graph->SetPoint(2,0.001148566202,-0.0002895583456);
	graph->SetPoint(3,0.001230931962,-0.0003222623835);
	graph->SetPoint(4,0.00131920432,-0.0003586331358);
	graph->SetPoint(5,0.001413806849,-0.0003990775898);
	graph->SetPoint(6,0.001515193495,-0.0004440462065);
	graph->SetPoint(7,0.001623850762,-0.0004940375319);
	graph->SetPoint(8,0.001740300038,-0.0005496032587);
	graph->SetPoint(9,0.001865100102,-0.0006113573941);
	graph->SetPoint(10,0.001998849805,-0.0006799798873);
	graph->SetPoint(11,0.002142190941,-0.000756219743);
	graph->SetPoint(12,0.002295811329,-0.0008409029877);
	graph->SetPoint(13,0.002460448113,-0.0009349457521);
	graph->SetPoint(14,0.002636891298,-0.001039365798);
	graph->SetPoint(15,0.002825987544,-0.001155281994);
	graph->SetPoint(16,0.003028644223,-0.001283926563);
	graph->SetPoint(17,0.003245833779,-0.001426657363);
	graph->SetPoint(18,0.003478598392,-0.001584978814);
	graph->SetPoint(19,0.003728054976,-0.001760539319);
	graph->SetPoint(20,0.003995400543,-0.001955149126);
	graph->SetPoint(21,0.004281917944,-0.00217081008);
	graph->SetPoint(22,0.004588982027,-0.002409725324);
	graph->SetPoint(23,0.00491806623,-0.00267429745);
	graph->SetPoint(24,0.005270749657,-0.002967122023);
	graph->SetPoint(25,0.00564872465,-0.003291089667);
	graph->SetPoint(26,0.006053804915,-0.003649381067);
	graph->SetPoint(27,0.006487934217,-0.004045465485);
	graph->SetPoint(28,0.006953195718,-0.004482987804);
	graph->SetPoint(29,0.007451821962,-0.004965971631);
	graph->SetPoint(30,0.007986205596,-0.005498879911);
	graph->SetPoint(31,0.008558910848,-0.00608659867);
	graph->SetPoint(32,0.009172685829,-0.006734208904);
	graph->SetPoint(33,0.009830475725,-0.007447081049);
	graph->SetPoint(34,0.01053543692,-0.008231184764);
	graph->SetPoint(35,0.01129095217,-0.009092984186);
	graph->SetPoint(36,0.01210064677,-0.01003928846);
	graph->SetPoint(37,0.01296840605,-0.01107704516);
	graph->SetPoint(38,0.0138983939,-0.01221395227);
	graph->SetPoint(39,0.01489507288,-0.01345804292);
	graph->SetPoint(40,0.0159632255,-0.01481743987);
	graph->SetPoint(41,0.01710797728,-0.01630015903);
	graph->SetPoint(42,0.01833482128,-0.01791528942);
	graph->SetPoint(43,0.01964964449,-0.01967280042);
	graph->SetPoint(44,0.02105875604,-0.0215805919);
	graph->SetPoint(45,0.02256891754,-0.0236456445);
	graph->SetPoint(46,0.02418737544,-0.0258755479);
	graph->SetPoint(47,0.02592189589,-0.02828286352);
	graph->SetPoint(48,0.02778080195,-0.03087427805);
	graph->SetPoint(49,0.02977301351,-0.03365125002);
	graph->SetPoint(50,0.03190809018,-0.03661133459);
	graph->SetPoint(51,0.03419627705,-0.03976359707);
	graph->SetPoint(52,0.03664855394,-0.04311400596);
	graph->SetPoint(53,0.03927668805,-0.04665625786);
	graph->SetPoint(54,0.04209329041,-0.05037171121);
	graph->SetPoint(55,0.04511187642,-0.05424699066);
	graph->SetPoint(56,0.04834693069,-0.0582751878);
	graph->SetPoint(57,0.05181397655,-0.0624322473);
	graph->SetPoint(58,0.05552965055,-0.06668197981);
	graph->SetPoint(59,0.05951178226,-0.07098048393);
	graph->SetPoint(60,0.06377947983,-0.07528902339);
	graph->SetPoint(61,0.06835322171,-0.07955317831);
	graph->SetPoint(62,0.0732549549,-0.08370531352);
	graph->SetPoint(63,0.07850820025,-0.08766884794);
	graph->SetPoint(64,0.08413816532,-0.0913611072);
	graph->SetPoint(65,0.09017186538,-0.09469012601);
	graph->SetPoint(66,0.09663825298,-0.0975539007);
	graph->SetPoint(67,0.1035683569,-0.09985038495);
	graph->SetPoint(68,0.1109954312,-0.1014753871);
	graph->SetPoint(69,0.1189551144,-0.1023252586);
	graph->SetPoint(70,0.1274856008,-0.1023024041);
	graph->SetPoint(71,0.1366278239,-0.1013225403);
	graph->SetPoint(72,0.1464256523,-0.09932126595);
	graph->SetPoint(73,0.1569261008,-0.09625774221);
	graph->SetPoint(74,0.1681795553,-0.09212637457);
	graph->SetPoint(75,0.1802400155,-0.08696104722);
	graph->SetPoint(76,0.1931653531,-0.08083457496);
	graph->SetPoint(77,0.2070175901,-0.07387922448);
	graph->SetPoint(78,0.221863196,-0.0662520674);
	graph->SetPoint(79,0.2377734071,-0.05817580955);
	graph->SetPoint(80,0.2548245683,-0.04989566721);
	graph->SetPoint(81,0.2730984991,-0.04167616616);
	graph->SetPoint(82,0.2926828866,-0.03379095279);
	graph->SetPoint(83,0.3136717059,-0.02649418114);
	graph->SetPoint(84,0.3361656714,-0.01999887443);
	graph->SetPoint(85,0.3602727199,-0.01445815533);
	graph->SetPoint(86,0.3861085284,-0.009950398699);
	graph->SetPoint(87,0.4137970695,-0.006473189766);
	graph->SetPoint(88,0.443471206,-0.003941089961);
	graph->SetPoint(89,0.4752733285,-0.00222251579);
	graph->SetPoint(90,0.5093560387,-0.001143811568);
	graph->SetPoint(91,0.5458828818,-0.0005278794833);
	graph->SetPoint(92,0.5850291308,-0.0002139224738);
	graph->SetPoint(93,0.6269826282,-7.407634223e-05);
	graph->SetPoint(94,0.6719446868,-2.109628324e-05);
	graph->SetPoint(95,0.7201310559,-4.643108455e-06);
	graph->SetPoint(96,0.7717729568,-7.028494482e-07);
	graph->SetPoint(97,0.8271181917,-5.73836439e-08);
	graph->SetPoint(98,0.8864323337,-1.409643848e-09);
	graph->SetPoint(99,0.95,-1.301717451e-12);

	graph->Draw("cp");
	/*}}}*/

	/* Q2 = 2.4{{{*/
	graph = new TGraph(100);
	graph->SetName("Graph0");
	graph->SetTitle("");
	graph->SetFillColor(1);
	graph->SetLineColor(1);
	graph->SetLineWidth(3);
	graph->SetLineStyle(2);
	graph->SetPoint(0,0.001,-6.658522531e-05);
	graph->SetPoint(1,0.001071711809,-7.455226893e-05);
	graph->SetPoint(2,0.001148566202,-8.347603244e-05);
	graph->SetPoint(3,0.001230931962,-9.347015138e-05);
	graph->SetPoint(4,0.00131920432,-0.0001047180635);
	graph->SetPoint(5,0.001413806849,-0.0001173263558);
	graph->SetPoint(6,0.001515193495,-0.0001314705677);
	graph->SetPoint(7,0.001623850762,-0.0001473794693);
	graph->SetPoint(8,0.001740300038,-0.0001652350749);
	graph->SetPoint(9,0.001865100102,-0.0001852902796);
	graph->SetPoint(10,0.001998849805,-0.0002078452606);
	graph->SetPoint(11,0.002142190941,-0.0002332104514);
	graph->SetPoint(12,0.002295811329,-0.0002617174863);
	graph->SetPoint(13,0.002460448113,-0.0002937685871);
	graph->SetPoint(14,0.002636891298,-0.0003298700279);
	graph->SetPoint(15,0.002825987544,-0.0003704561188);
	graph->SetPoint(16,0.003028644223,-0.0004161214725);
	graph->SetPoint(17,0.003245833779,-0.0004676543576);
	graph->SetPoint(18,0.003478598392,-0.0005255734649);
	graph->SetPoint(19,0.003728054976,-0.0005907806287);
	graph->SetPoint(20,0.003995400543,-0.0006644264537);
	graph->SetPoint(21,0.004281917944,-0.0007472421841);
	graph->SetPoint(22,0.004588982027,-0.0008406002203);
	graph->SetPoint(23,0.00491806623,-0.0009460534965);
	graph->SetPoint(24,0.005270749657,-0.001064640125);
	graph->SetPoint(25,0.00564872465,-0.001198454017);
	graph->SetPoint(26,0.006053804915,-0.001349635096);
	graph->SetPoint(27,0.006487934217,-0.001519783031);
	graph->SetPoint(28,0.006953195718,-0.001711874396);
	graph->SetPoint(29,0.007451821962,-0.00192869918);
	graph->SetPoint(30,0.007986205596,-0.002172701381);
	graph->SetPoint(31,0.008558910848,-0.002448348628);
	graph->SetPoint(32,0.009172685829,-0.002759523457);
	graph->SetPoint(33,0.009830475725,-0.003109968391);
	graph->SetPoint(34,0.01053543692,-0.003505294341);
	graph->SetPoint(35,0.01129095217,-0.003950742247);
	graph->SetPoint(36,0.01210064677,-0.004452266243);
	graph->SetPoint(37,0.01296840605,-0.00501802083);
	graph->SetPoint(38,0.0138983939,-0.005655033863);
	graph->SetPoint(39,0.01489507288,-0.006371158503);
	graph->SetPoint(40,0.0159632255,-0.007176285247);
	graph->SetPoint(41,0.01710797728,-0.008081828805);
	graph->SetPoint(42,0.01833482128,-0.009099617418);
	graph->SetPoint(43,0.01964964449,-0.0102416309);
	graph->SetPoint(44,0.02105875604,-0.01152023083);
	graph->SetPoint(45,0.02256891754,-0.01295009509);
	graph->SetPoint(46,0.02418737544,-0.01454849888);
	graph->SetPoint(47,0.02592189589,-0.0163349189);
	graph->SetPoint(48,0.02778080195,-0.01833067502);
	graph->SetPoint(49,0.02977301351,-0.02055306581);
	graph->SetPoint(50,0.03190809018,-0.02300825891);
	graph->SetPoint(51,0.03419627705,-0.02572421901);
	graph->SetPoint(52,0.03664855394,-0.0287309257);
	graph->SetPoint(53,0.03927668805,-0.03204733251);
	graph->SetPoint(54,0.04209329041,-0.0356997542);
	graph->SetPoint(55,0.04511187642,-0.03969535718);
	graph->SetPoint(56,0.04834693069,-0.04402418733);
	graph->SetPoint(57,0.05181397655,-0.04872271021);
	graph->SetPoint(58,0.05552965055,-0.05380805809);
	graph->SetPoint(59,0.05951178226,-0.05927012452);
	graph->SetPoint(60,0.06377947983,-0.06506620373);
	graph->SetPoint(61,0.06835322171,-0.07118880575);
	graph->SetPoint(62,0.0732549549,-0.07762886686);
	graph->SetPoint(63,0.07850820025,-0.08432837031);
	graph->SetPoint(64,0.08413816532,-0.09118720952);
	graph->SetPoint(65,0.09017186538,-0.09810945542);
	graph->SetPoint(66,0.09663825298,-0.1050261485);
	graph->SetPoint(67,0.1035683569,-0.1117523435);
	graph->SetPoint(68,0.1109954312,-0.118118387);
	graph->SetPoint(69,0.1189551144,-0.1239855759);
	graph->SetPoint(70,0.1274856008,-0.129116516);
	graph->SetPoint(71,0.1366278239,-0.1332821223);
	graph->SetPoint(72,0.1464256523,-0.136269809);
	graph->SetPoint(73,0.1569261008,-0.1378509383);
	graph->SetPoint(74,0.1681795553,-0.1378106188);
	graph->SetPoint(75,0.1802400155,-0.1359878642);
	graph->SetPoint(76,0.1931653531,-0.1322603861);
	graph->SetPoint(77,0.2070175901,-0.1265822341);
	graph->SetPoint(78,0.221863196,-0.1189827434);
	graph->SetPoint(79,0.2377734071,-0.1096402102);
	graph->SetPoint(80,0.2548245683,-0.0987655188);
	graph->SetPoint(81,0.2730984991,-0.08674973226);
	graph->SetPoint(82,0.2926828866,-0.07406811029);
	graph->SetPoint(83,0.3136717059,-0.06122756684);
	graph->SetPoint(84,0.3361656714,-0.04879156327);
	graph->SetPoint(85,0.3602727199,-0.0372952749);
	graph->SetPoint(86,0.3861085284,-0.02718449919);
	graph->SetPoint(87,0.4137970695,-0.01877154137);
	graph->SetPoint(88,0.443471206,-0.01216099517);
	graph->SetPoint(89,0.4752733285,-0.007321186482);
	graph->SetPoint(90,0.5093560387,-0.00403263785);
	graph->SetPoint(91,0.5458828818,-0.001998881514);
	graph->SetPoint(92,0.5850291308,-0.000873245944);
	graph->SetPoint(93,0.6269826282,-0.0003273628627);
	graph->SetPoint(94,0.6719446868,-0.0001016971318);
	graph->SetPoint(95,0.7201310559,-2.475837544e-05);
	graph->SetPoint(96,0.7717729568,-4.249967709e-06);
	graph->SetPoint(97,0.8271181917,-4.104811158e-07);
	graph->SetPoint(98,0.8864323337,-1.287670826e-08);
	graph->SetPoint(99,0.95,-1.861085194e-11);
	graph->Draw("cp");
	/*}}}*/

	/*}}}*/

	/*Draw Lines{{{ */
	// LINE Q2 = 2.4 
	line = new TLine(0.5,-0.05,0.65,-0.05);
	line->SetLineColor(1);
	line->SetLineStyle(2);
	line->SetLineWidth(3);
	line->Draw();


	tex = new TLatex(0.65,-0.05,"Q^{2} = 2.4 GeV^{2}");
	tex->SetLineWidth(2);
	tex->SetTextSize(0.115);
	tex->Draw();

	// LINE Q2 = 10 
	line = new TLine(0.5,-0.08,0.65,-0.08);
	line->SetLineColor(2);
	line->SetLineStyle(1);
	line->SetLineWidth(3);
	line->Draw();


	tex = new TLatex(0.65,-0.08,"Q^{2} = 10 GeV^{2}");
	tex->SetLineWidth(2);
	tex->SetTextSize(0.115);
	tex->Draw();


	// LINE Q2 = 1000 
	line = new TLine(0.5,-0.11,0.65,-0.11);
	line->SetLineColor(1);
	line->SetLineStyle(9);
	line->SetLineWidth(3);
	line->Draw();


	tex = new TLatex(0.65,-0.11,"Q^{2} = 1000 GeV^{2}");
	tex->SetLineWidth(2);
	tex->SetTextSize(0.115);
	tex->Draw();

	nemo_3->Modified();
	nemo->cd();
	nemo->Modified();
	transversity->cd();
	transversity->Modified();
	transversity->cd();
	transversity->SetSelected(transversity);
	/*}}}*/

}
