{
//=========Macro generated from canvas: result/result
//=========  (Fri Sep 12 12:13:50 2014) by ROOT version5.34/10
  gROOT->SetStyle("Plain");
  gStyle->Reset();
  gStyle->SetTextFont(132);
  gStyle->SetLabelFont(132,"xyz");



   TCanvas *result = new TCanvas("result", "result",10,32,700,500);
   result->SetHighLightColor(2);
   result->Range(0,0,1,1);
   result->SetFillColor(0);
   result->SetFillStyle(4000);
   result->SetBorderMode(0);
   result->SetBorderSize(2);
   result->SetFrameFillStyle(0);
   result->SetFrameBorderMode(0);
   TLatex *      tex = new TLatex(0.07,0.6,"A_{UT}^{sin (#phi_{S}+ #phi_{h})}");
   tex->SetTextSize(0.09);
   tex->SetTextAngle(90);
   tex->SetLineWidth(2);
   tex->Draw();
 
      tex = new TLatex(0.75,0.05,"x_{B}");
   tex->SetLineWidth(2);
   tex->SetTextSize(0.08);
   tex->Draw();
   
   double pip_min = -0.21;
   double pip_max = 0.21;

   int color = kGreen;
 
// ------------>Primitives in pad: nemo
   TPad *nemo = new TPad("nemo", "This is nemo",0.1,0.1,1,1);
   nemo->Draw();
   nemo->cd();
   nemo->Range(-0.16375,-0.0875,1.47375,0.2875);
   nemo->SetFillColor(0);
   //nemo->SetLogx();
   nemo->SetFillStyle(4000);
   nemo->SetBorderMode(0);
   nemo->SetBorderSize(0);
   nemo->SetFrameFillStyle(0);
   nemo->SetFrameBorderMode(0);
   nemo->SetFrameFillStyle(0);
   nemo->SetFrameBorderMode(0);
   
 //PLOT proton
   TGraph *graph = new TGraph(10);
   graph->SetName("Graph");
   graph->SetTitle("");
   graph->SetFillColor(1);
   graph->SetLineColor(2);
   graph->SetLineWidth(4);
   graph->SetPoint(0,0.08,-0.01193068737);
   graph->SetPoint(1,0.1544444444,0.0149059102);
   graph->SetPoint(2,0.2288888889,0.03608452823);
   graph->SetPoint(3,0.3033333333,0.05183536288);
   graph->SetPoint(4,0.3777777778,0.06649587986);
   graph->SetPoint(5,0.4522222222,0.08193729644);
   graph->SetPoint(6,0.5266666667,0.09861883031);
   graph->SetPoint(7,0.6011111111,0.1165776246);
   graph->SetPoint(8,0.6755555556,0.1349315282);
   graph->SetPoint(9,0.75,0.1525446359);
   
   TH1F *Graph1 = new TH1F("Graph1","",100,0.0002,0.95);
   Graph1->SetMinimum(pip_min);
   Graph1->SetMaximum(pip_max);
   Graph1->SetDirectory(0);
   Graph1->SetStats(0);
   Graph1->GetXaxis()->SetNdivisions(8);
   Graph1->GetXaxis()->SetLabelOffset(0.04);
   Graph1->GetXaxis()->SetLabelSize(0.06);
   Graph1->GetXaxis()->SetTitleColor(0);
   Graph1->GetYaxis()->SetNdivisions(8);
   Graph1->GetYaxis()->SetLabelOffset(0.02);
   Graph1->GetYaxis()->SetLabelSize(0.06);
   graph->SetHistogram(Graph1);
   
   graph->Draw("acp");



   //ERROR BAND BEGIN
   graphbest = new TGraph(10);
   graphbest = graph;


   graph = new TGraph(21);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");
   graph->SetFillStyle(3359);
   graph->SetFillColor(color);
   graph->SetLineWidth(1);
   graph->SetPoint(0,0.08,-0.01537058313);
   graph->SetPoint(1,0.1544444444,0.01090725744);
   graph->SetPoint(2,0.2288888889,0.02539430767);
   graph->SetPoint(3,0.3033333333,0.0253038507);
   graph->SetPoint(4,0.3777777778,0.0200856492);
   graph->SetPoint(5,0.4522222222,0.01372875532);
   graph->SetPoint(6,0.5266666667,0.00816798368);
   graph->SetPoint(7,0.6011111111,0.00415306529);
   graph->SetPoint(8,0.6755555556,0.001715397837);
   graph->SetPoint(9,0.75,0.0005221957542);
   graph->SetPoint(10,0.75,0.1959374397);
   graph->SetPoint(11,0.6755555556,0.1845420221);
   graph->SetPoint(12,0.6011111111,0.1700601611);
   graph->SetPoint(13,0.5266666667,0.1497430989);
   graph->SetPoint(14,0.4522222222,0.1263704043);
   graph->SetPoint(15,0.3777777778,0.1011132468);
   graph->SetPoint(16,0.3033333333,0.0747970672);
   graph->SetPoint(17,0.2288888889,0.04735104661);
   graph->SetPoint(18,0.1544444444,0.01852633319);
   graph->SetPoint(19,0.08,-0.008469328336);
   graph->SetPoint(20,0.08,-0.01537058313);

   //graph->Draw("l");
   //graph->Draw("f");


   graphcor = new TGraph(21);
   graphcor = graph;


   graph = graphbest; // back to best Graph
   //ERROR BAND END

   graph->Draw("cp");


   // neutron
   TGraph *graph = new TGraph(10);
   graph->SetName("Graph0");
   graph->SetTitle("");
   graph->SetFillColor(1);
   graph->SetLineColor(2);
   graph->SetLineWidth(4);
   graph->SetLineStyle(9);
   graph->SetPoint(0,0.08,0.01757229557);
   graph->SetPoint(1,0.1544444444,-0.02302587618);
   graph->SetPoint(2,0.2288888889,-0.0482134614);
   graph->SetPoint(3,0.3033333333,-0.05557891727);
   graph->SetPoint(4,0.3777777778,-0.05798414551);
   graph->SetPoint(5,0.4522222222,-0.06305094647);
   graph->SetPoint(6,0.5266666667,-0.07358136312);
   graph->SetPoint(7,0.6011111111,-0.08961066767);
   graph->SetPoint(8,0.6755555556,-0.1082824851);
   graph->SetPoint(9,0.75,-0.1236420615);

 
   //graph->Draw("cp");

  
   graphbest1 = new TGraph(10);
   graphbest1 = graph;
 

   graph = new TGraph(21);
   graph->SetName("Graph1");
   graph->SetTitle("Graph");
   graph->SetFillStyle(1023);
   graph->SetFillColor(kYellow-8);
   graph->SetLineWidth(1);
   graph->SetPoint(0,0.08,0.000784337015);
   graph->SetPoint(1,0.1544444444,-0.02533742376);
   graph->SetPoint(2,0.2288888889,-0.05223663913);
   graph->SetPoint(3,0.3033333333,-0.06640172496);
   graph->SetPoint(4,0.3777777778,-0.07789520551);
   graph->SetPoint(5,0.4522222222,-0.08682761344);
   graph->SetPoint(6,0.5266666667,-0.1038779078);
   graph->SetPoint(7,0.6011111111,-0.1278188467);
   graph->SetPoint(8,0.6755555556,-0.1499433152);
   graph->SetPoint(9,0.75,-0.1768641787);
   graph->SetPoint(10,0.75,-0.0005991624185);
   graph->SetPoint(11,0.6755555556,-0.00207757144);
   graph->SetPoint(12,0.6011111111,-0.005304084833);
   graph->SetPoint(13,0.5266666667,-0.01115529328);
   graph->SetPoint(14,0.4522222222,-0.02016785946);
   graph->SetPoint(15,0.3777777778,-0.004569481005);
   graph->SetPoint(16,0.3033333333,0.007610849108);
   graph->SetPoint(17,0.2288888889,0.009137795126);
   graph->SetPoint(18,0.1544444444,0.002508588403);
   graph->SetPoint(19,0.08,0.03062082377);
   graph->SetPoint(20,0.08,0.000784337015);

   //graph->Draw("l");
    //graph->Draw("f");


   graphcor1 = new TGraph(21);
   graphcor1 = graph;


   // Drawing here
   graphcor1->Draw("l");
   graphcor1->Draw("f");

   graphcor->Draw("l");
   graphcor->Draw("f");

   graphbest1->Draw("cp");

   graphbest->Draw("cp");

   TLine *line = new TLine(0.0002,0,0.95,0);
   line->Draw();
      tex = new TLatex(0.1,0.08,"#pi^{+}");
   tex->SetTextColor(1);
   tex->SetTextSize(0.1);
   tex->SetLineWidth(2);
   tex->Draw();
   nemo->Modified();
   nemo->cd();

 
}
