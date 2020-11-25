void tutorial_dataset_BFsig_cls()
{
//=========Macro generated from canvas: tutorial_dataset_BFsig_clsUID1/p-value curves
//=========  (Tue Nov 24 14:54:17 2020) by ROOT version 6.18/04
   TCanvas *tutorial_dataset_BFsig_clsUID1 = new TCanvas("tutorial_dataset_BFsig_clsUID1", "p-value curves",0,0,800,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   tutorial_dataset_BFsig_clsUID1->SetHighLightColor(2);
   tutorial_dataset_BFsig_clsUID1->Range(-3.027027e-08,-0.2833333,1.589189e-07,1.383333);
   tutorial_dataset_BFsig_clsUID1->SetFillColor(0);
   tutorial_dataset_BFsig_clsUID1->SetBorderMode(0);
   tutorial_dataset_BFsig_clsUID1->SetBorderSize(2);
   tutorial_dataset_BFsig_clsUID1->SetLeftMargin(0.16);
   tutorial_dataset_BFsig_clsUID1->SetTopMargin(0.05);
   tutorial_dataset_BFsig_clsUID1->SetBottomMargin(0.17);
   tutorial_dataset_BFsig_clsUID1->SetFrameBorderMode(0);
   tutorial_dataset_BFsig_clsUID1->SetFrameBorderMode(0);
   
   Double_t UID5_fx1[54] = {
   -1.4e-09,
   -1.4e-09,
   2.799993e-11,
   2.884e-09,
   5.74e-09,
   8.596e-09,
   1.1452e-08,
   1.4308e-08,
   1.7164e-08,
   2.002e-08,
   2.2876e-08,
   2.5732e-08,
   2.8588e-08,
   3.1444e-08,
   3.43e-08,
   3.7156e-08,
   4.0012e-08,
   4.2868e-08,
   4.5724e-08,
   4.858e-08,
   5.1436e-08,
   5.4292e-08,
   5.7148e-08,
   6.0004e-08,
   6.286e-08,
   6.5716e-08,
   6.8572e-08,
   7.1428e-08,
   7.4284e-08,
   7.714e-08,
   7.9996e-08,
   8.2852e-08,
   8.5708e-08,
   8.8564e-08,
   9.142e-08,
   9.4276e-08,
   9.7132e-08,
   9.9988e-08,
   1.02844e-07,
   1.057e-07,
   1.08556e-07,
   1.11412e-07,
   1.14268e-07,
   1.17124e-07,
   1.1998e-07,
   1.22836e-07,
   1.25692e-07,
   1.28548e-07,
   1.31404e-07,
   1.3426e-07,
   1.37116e-07,
   1.39972e-07,
   1.414e-07,
   1.414e-07};
   Double_t UID5_fy1[54] = {
   0,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   0};
   TGraph *graph = new TGraph(54,UID5_fx1,UID5_fy1);
   graph->SetName("UID5");
   graph->SetTitle("Graph");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#6666ff");
   graph->SetFillColor(ci);

   ci = TColor::GetColor("#6666ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_haxesUID61 = new TH1F("Graph_haxesUID61","",100,0,1.4e-07);
   Graph_haxesUID61->SetMinimum(0);
   Graph_haxesUID61->SetMaximum(1.3);
   Graph_haxesUID61->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_haxesUID61->SetLineColor(ci);
   Graph_haxesUID61->GetXaxis()->SetTitle("BFsig");
   Graph_haxesUID61->GetXaxis()->SetNdivisions(407);
   Graph_haxesUID61->GetXaxis()->SetLabelFont(133);
   Graph_haxesUID61->GetXaxis()->SetLabelSize(35);
   Graph_haxesUID61->GetXaxis()->SetTitleSize(45);
   Graph_haxesUID61->GetXaxis()->SetTitleOffset(0.9);
   Graph_haxesUID61->GetXaxis()->SetTitleFont(133);
   Graph_haxesUID61->GetYaxis()->SetTitle("1#minusCL");
   Graph_haxesUID61->GetYaxis()->SetNdivisions(407);
   Graph_haxesUID61->GetYaxis()->SetLabelFont(133);
   Graph_haxesUID61->GetYaxis()->SetLabelOffset(0.01);
   Graph_haxesUID61->GetYaxis()->SetLabelSize(35);
   Graph_haxesUID61->GetYaxis()->SetTitleSize(45);
   Graph_haxesUID61->GetYaxis()->SetTitleOffset(0.85);
   Graph_haxesUID61->GetYaxis()->SetTitleFont(133);
   Graph_haxesUID61->GetZaxis()->SetLabelFont(42);
   Graph_haxesUID61->GetZaxis()->SetLabelSize(0.035);
   Graph_haxesUID61->GetZaxis()->SetTitleSize(0.035);
   Graph_haxesUID61->GetZaxis()->SetTitleOffset(1);
   Graph_haxesUID61->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_haxesUID61);
   
   graph->Draw(" f a");
   
   TH1F *haxesUID10__3 = new TH1F("haxesUID10__3","",100,0,1.4e-07);
   haxesUID10__3->SetMinimum(0);
   haxesUID10__3->SetMaximum(1.3);
   haxesUID10__3->SetStats(0);

   ci = TColor::GetColor("#000099");
   haxesUID10__3->SetLineColor(ci);
   haxesUID10__3->GetXaxis()->SetTitle("BFsig");
   haxesUID10__3->GetXaxis()->SetNdivisions(407);
   haxesUID10__3->GetXaxis()->SetLabelFont(133);
   haxesUID10__3->GetXaxis()->SetLabelSize(35);
   haxesUID10__3->GetXaxis()->SetTitleSize(45);
   haxesUID10__3->GetXaxis()->SetTitleOffset(0.9);
   haxesUID10__3->GetXaxis()->SetTitleFont(133);
   haxesUID10__3->GetYaxis()->SetTitle("1#minusCL");
   haxesUID10__3->GetYaxis()->SetNdivisions(407);
   haxesUID10__3->GetYaxis()->SetLabelFont(133);
   haxesUID10__3->GetYaxis()->SetLabelOffset(0.01);
   haxesUID10__3->GetYaxis()->SetLabelSize(35);
   haxesUID10__3->GetYaxis()->SetTitleSize(45);
   haxesUID10__3->GetYaxis()->SetTitleOffset(0.85);
   haxesUID10__3->GetYaxis()->SetTitleFont(133);
   haxesUID10__3->GetZaxis()->SetLabelFont(42);
   haxesUID10__3->GetZaxis()->SetLabelSize(0.035);
   haxesUID10__3->GetZaxis()->SetTitleSize(0.035);
   haxesUID10__3->GetZaxis()->SetTitleOffset(1);
   haxesUID10__3->GetZaxis()->SetTitleFont(42);
   haxesUID10__3->Draw("axissame");
   
   Double_t UID9_fx2[54] = {
   -1.4e-09,
   -1.4e-09,
   2.799993e-11,
   2.884e-09,
   5.74e-09,
   8.596e-09,
   1.1452e-08,
   1.4308e-08,
   1.7164e-08,
   2.002e-08,
   2.2876e-08,
   2.5732e-08,
   2.8588e-08,
   3.1444e-08,
   3.43e-08,
   3.7156e-08,
   4.0012e-08,
   4.2868e-08,
   4.5724e-08,
   4.858e-08,
   5.1436e-08,
   5.4292e-08,
   5.7148e-08,
   6.0004e-08,
   6.286e-08,
   6.5716e-08,
   6.8572e-08,
   7.1428e-08,
   7.4284e-08,
   7.714e-08,
   7.9996e-08,
   8.2852e-08,
   8.5708e-08,
   8.8564e-08,
   9.142e-08,
   9.4276e-08,
   9.7132e-08,
   9.9988e-08,
   1.02844e-07,
   1.057e-07,
   1.08556e-07,
   1.11412e-07,
   1.14268e-07,
   1.17124e-07,
   1.1998e-07,
   1.22836e-07,
   1.25692e-07,
   1.28548e-07,
   1.31404e-07,
   1.3426e-07,
   1.37116e-07,
   1.39972e-07,
   1.414e-07,
   1.414e-07};
   Double_t UID9_fy2[54] = {
   0,
   1,
   1,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   graph = new TGraph(54,UID9_fx2,UID9_fy2);
   graph->SetName("UID9");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#9999cc");
   graph->SetFillColor(ci);

   ci = TColor::GetColor("#9999cc");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_haxesUID102 = new TH1F("Graph_haxesUID102","",100,0,1.4e-07);
   Graph_haxesUID102->SetMinimum(0);
   Graph_haxesUID102->SetMaximum(1.3);
   Graph_haxesUID102->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_haxesUID102->SetLineColor(ci);
   Graph_haxesUID102->GetXaxis()->SetTitle("BFsig");
   Graph_haxesUID102->GetXaxis()->SetNdivisions(407);
   Graph_haxesUID102->GetXaxis()->SetLabelFont(133);
   Graph_haxesUID102->GetXaxis()->SetLabelSize(35);
   Graph_haxesUID102->GetXaxis()->SetTitleSize(45);
   Graph_haxesUID102->GetXaxis()->SetTitleOffset(0.9);
   Graph_haxesUID102->GetXaxis()->SetTitleFont(133);
   Graph_haxesUID102->GetYaxis()->SetTitle("1#minusCL");
   Graph_haxesUID102->GetYaxis()->SetNdivisions(407);
   Graph_haxesUID102->GetYaxis()->SetLabelFont(133);
   Graph_haxesUID102->GetYaxis()->SetLabelOffset(0.01);
   Graph_haxesUID102->GetYaxis()->SetLabelSize(35);
   Graph_haxesUID102->GetYaxis()->SetTitleSize(45);
   Graph_haxesUID102->GetYaxis()->SetTitleOffset(0.85);
   Graph_haxesUID102->GetYaxis()->SetTitleFont(133);
   Graph_haxesUID102->GetZaxis()->SetLabelFont(42);
   Graph_haxesUID102->GetZaxis()->SetLabelSize(0.035);
   Graph_haxesUID102->GetZaxis()->SetTitleSize(0.035);
   Graph_haxesUID102->GetZaxis()->SetTitleOffset(1);
   Graph_haxesUID102->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_haxesUID102);
   
   graph->Draw(" f");
   
   TH1F *haxesUID15__4 = new TH1F("haxesUID15__4","",100,0,1.4e-07);
   haxesUID15__4->SetMinimum(0);
   haxesUID15__4->SetMaximum(1.3);
   haxesUID15__4->SetStats(0);

   ci = TColor::GetColor("#000099");
   haxesUID15__4->SetLineColor(ci);
   haxesUID15__4->GetXaxis()->SetTitle("BFsig");
   haxesUID15__4->GetXaxis()->SetNdivisions(407);
   haxesUID15__4->GetXaxis()->SetLabelFont(133);
   haxesUID15__4->GetXaxis()->SetLabelSize(35);
   haxesUID15__4->GetXaxis()->SetTitleSize(45);
   haxesUID15__4->GetXaxis()->SetTitleOffset(0.9);
   haxesUID15__4->GetXaxis()->SetTitleFont(133);
   haxesUID15__4->GetYaxis()->SetTitle("1#minusCL");
   haxesUID15__4->GetYaxis()->SetNdivisions(407);
   haxesUID15__4->GetYaxis()->SetLabelFont(133);
   haxesUID15__4->GetYaxis()->SetLabelOffset(0.01);
   haxesUID15__4->GetYaxis()->SetLabelSize(35);
   haxesUID15__4->GetYaxis()->SetTitleSize(45);
   haxesUID15__4->GetYaxis()->SetTitleOffset(0.85);
   haxesUID15__4->GetYaxis()->SetTitleFont(133);
   haxesUID15__4->GetZaxis()->SetLabelFont(42);
   haxesUID15__4->GetZaxis()->SetLabelSize(0.035);
   haxesUID15__4->GetZaxis()->SetTitleSize(0.035);
   haxesUID15__4->GetZaxis()->SetTitleOffset(1);
   haxesUID15__4->GetZaxis()->SetTitleFont(42);
   haxesUID15__4->Draw("axissame");
   
   Double_t UID14_fx3[54] = {
   -1.4e-09,
   -1.4e-09,
   2.799993e-11,
   2.884e-09,
   5.74e-09,
   8.596e-09,
   1.1452e-08,
   1.4308e-08,
   1.7164e-08,
   2.002e-08,
   2.2876e-08,
   2.5732e-08,
   2.8588e-08,
   3.1444e-08,
   3.43e-08,
   3.7156e-08,
   4.0012e-08,
   4.2868e-08,
   4.5724e-08,
   4.858e-08,
   5.1436e-08,
   5.4292e-08,
   5.7148e-08,
   6.0004e-08,
   6.286e-08,
   6.5716e-08,
   6.8572e-08,
   7.1428e-08,
   7.4284e-08,
   7.714e-08,
   7.9996e-08,
   8.2852e-08,
   8.5708e-08,
   8.8564e-08,
   9.142e-08,
   9.4276e-08,
   9.7132e-08,
   9.9988e-08,
   1.02844e-07,
   1.057e-07,
   1.08556e-07,
   1.11412e-07,
   1.14268e-07,
   1.17124e-07,
   1.1998e-07,
   1.22836e-07,
   1.25692e-07,
   1.28548e-07,
   1.31404e-07,
   1.3426e-07,
   1.37116e-07,
   1.39972e-07,
   1.414e-07,
   1.414e-07};
   Double_t UID14_fy3[54] = {
   0,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   1,
   0};
   graph = new TGraph(54,UID14_fx3,UID14_fy3);
   graph->SetName("UID14");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#6666ff");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_haxesUID153 = new TH1F("Graph_haxesUID153","",100,0,1.4e-07);
   Graph_haxesUID153->SetMinimum(0);
   Graph_haxesUID153->SetMaximum(1.3);
   Graph_haxesUID153->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_haxesUID153->SetLineColor(ci);
   Graph_haxesUID153->GetXaxis()->SetTitle("BFsig");
   Graph_haxesUID153->GetXaxis()->SetNdivisions(407);
   Graph_haxesUID153->GetXaxis()->SetLabelFont(133);
   Graph_haxesUID153->GetXaxis()->SetLabelSize(35);
   Graph_haxesUID153->GetXaxis()->SetTitleSize(45);
   Graph_haxesUID153->GetXaxis()->SetTitleOffset(0.9);
   Graph_haxesUID153->GetXaxis()->SetTitleFont(133);
   Graph_haxesUID153->GetYaxis()->SetTitle("1#minusCL");
   Graph_haxesUID153->GetYaxis()->SetNdivisions(407);
   Graph_haxesUID153->GetYaxis()->SetLabelFont(133);
   Graph_haxesUID153->GetYaxis()->SetLabelOffset(0.01);
   Graph_haxesUID153->GetYaxis()->SetLabelSize(35);
   Graph_haxesUID153->GetYaxis()->SetTitleSize(45);
   Graph_haxesUID153->GetYaxis()->SetTitleOffset(0.85);
   Graph_haxesUID153->GetYaxis()->SetTitleFont(133);
   Graph_haxesUID153->GetZaxis()->SetLabelFont(42);
   Graph_haxesUID153->GetZaxis()->SetLabelSize(0.035);
   Graph_haxesUID153->GetZaxis()->SetTitleSize(0.035);
   Graph_haxesUID153->GetZaxis()->SetTitleOffset(1);
   Graph_haxesUID153->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_haxesUID153);
   
   graph->Draw(" l");
   
   TH1F *haxesUID19__5 = new TH1F("haxesUID19__5","",100,0,1.4e-07);
   haxesUID19__5->SetMinimum(0);
   haxesUID19__5->SetMaximum(1.3);
   haxesUID19__5->SetStats(0);

   ci = TColor::GetColor("#000099");
   haxesUID19__5->SetLineColor(ci);
   haxesUID19__5->GetXaxis()->SetTitle("BFsig");
   haxesUID19__5->GetXaxis()->SetNdivisions(407);
   haxesUID19__5->GetXaxis()->SetLabelFont(133);
   haxesUID19__5->GetXaxis()->SetLabelSize(35);
   haxesUID19__5->GetXaxis()->SetTitleSize(45);
   haxesUID19__5->GetXaxis()->SetTitleOffset(0.9);
   haxesUID19__5->GetXaxis()->SetTitleFont(133);
   haxesUID19__5->GetYaxis()->SetTitle("1#minusCL");
   haxesUID19__5->GetYaxis()->SetNdivisions(407);
   haxesUID19__5->GetYaxis()->SetLabelFont(133);
   haxesUID19__5->GetYaxis()->SetLabelOffset(0.01);
   haxesUID19__5->GetYaxis()->SetLabelSize(35);
   haxesUID19__5->GetYaxis()->SetTitleSize(45);
   haxesUID19__5->GetYaxis()->SetTitleOffset(0.85);
   haxesUID19__5->GetYaxis()->SetTitleFont(133);
   haxesUID19__5->GetZaxis()->SetLabelFont(42);
   haxesUID19__5->GetZaxis()->SetLabelSize(0.035);
   haxesUID19__5->GetZaxis()->SetTitleSize(0.035);
   haxesUID19__5->GetZaxis()->SetTitleOffset(1);
   haxesUID19__5->GetZaxis()->SetTitleFont(42);
   haxesUID19__5->Draw("axissame");
   
   Double_t UID18_fx4[54] = {
   -1.4e-09,
   -1.4e-09,
   2.799993e-11,
   2.884e-09,
   5.74e-09,
   8.596e-09,
   1.1452e-08,
   1.4308e-08,
   1.7164e-08,
   2.002e-08,
   2.2876e-08,
   2.5732e-08,
   2.8588e-08,
   3.1444e-08,
   3.43e-08,
   3.7156e-08,
   4.0012e-08,
   4.2868e-08,
   4.5724e-08,
   4.858e-08,
   5.1436e-08,
   5.4292e-08,
   5.7148e-08,
   6.0004e-08,
   6.286e-08,
   6.5716e-08,
   6.8572e-08,
   7.1428e-08,
   7.4284e-08,
   7.714e-08,
   7.9996e-08,
   8.2852e-08,
   8.5708e-08,
   8.8564e-08,
   9.142e-08,
   9.4276e-08,
   9.7132e-08,
   9.9988e-08,
   1.02844e-07,
   1.057e-07,
   1.08556e-07,
   1.11412e-07,
   1.14268e-07,
   1.17124e-07,
   1.1998e-07,
   1.22836e-07,
   1.25692e-07,
   1.28548e-07,
   1.31404e-07,
   1.3426e-07,
   1.37116e-07,
   1.39972e-07,
   1.414e-07,
   1.414e-07};
   Double_t UID18_fy4[54] = {
   0,
   1,
   1,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0};
   graph = new TGraph(54,UID18_fx4,UID18_fy4);
   graph->SetName("UID18");
   graph->SetTitle("Graph");

   ci = TColor::GetColor("#9999cc");
   graph->SetLineColor(ci);
   graph->SetLineWidth(2);
   
   TH1F *Graph_haxesUID194 = new TH1F("Graph_haxesUID194","",100,0,1.4e-07);
   Graph_haxesUID194->SetMinimum(0);
   Graph_haxesUID194->SetMaximum(1.3);
   Graph_haxesUID194->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_haxesUID194->SetLineColor(ci);
   Graph_haxesUID194->GetXaxis()->SetTitle("BFsig");
   Graph_haxesUID194->GetXaxis()->SetNdivisions(407);
   Graph_haxesUID194->GetXaxis()->SetLabelFont(133);
   Graph_haxesUID194->GetXaxis()->SetLabelSize(35);
   Graph_haxesUID194->GetXaxis()->SetTitleSize(45);
   Graph_haxesUID194->GetXaxis()->SetTitleOffset(0.9);
   Graph_haxesUID194->GetXaxis()->SetTitleFont(133);
   Graph_haxesUID194->GetYaxis()->SetTitle("1#minusCL");
   Graph_haxesUID194->GetYaxis()->SetNdivisions(407);
   Graph_haxesUID194->GetYaxis()->SetLabelFont(133);
   Graph_haxesUID194->GetYaxis()->SetLabelOffset(0.01);
   Graph_haxesUID194->GetYaxis()->SetLabelSize(35);
   Graph_haxesUID194->GetYaxis()->SetTitleSize(45);
   Graph_haxesUID194->GetYaxis()->SetTitleOffset(0.85);
   Graph_haxesUID194->GetYaxis()->SetTitleFont(133);
   Graph_haxesUID194->GetZaxis()->SetLabelFont(42);
   Graph_haxesUID194->GetZaxis()->SetLabelSize(0.035);
   Graph_haxesUID194->GetZaxis()->SetTitleSize(0.035);
   Graph_haxesUID194->GetZaxis()->SetTitleOffset(1);
   Graph_haxesUID194->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_haxesUID194);
   
   graph->Draw(" l");
   TGaxis *gaxis = new TGaxis(0,1,1.4e-07,1,0,1.4e-07,407,"-U");
   gaxis->SetLabelOffset(0.005);
   gaxis->SetLabelSize(0.04);
   gaxis->SetTickSize(0.03);
   gaxis->SetGridLength(0);
   gaxis->SetTitleOffset(1);
   gaxis->SetTitleSize(0.04);
   gaxis->SetTitleColor(1);
   gaxis->SetTitleFont(62);
   gaxis->SetName("axist");
   gaxis->Draw();
   gaxis = new TGaxis(1.4e-07,0,1.4e-07,1.3,0,1.3,407,"+");
   gaxis->SetLabelOffset(0.005);
   gaxis->SetLabelSize(0);
   gaxis->SetTickSize(0.03);
   gaxis->SetGridLength(0);
   gaxis->SetTitleOffset(1);
   gaxis->SetTitleSize(0.04);
   gaxis->SetTitleColor(0);
   gaxis->SetTitleFont(62);
   gaxis->SetName("axisr");
   gaxis->SetLabelColor(0);
   gaxis->Draw();
   
   TH1F *Graph_haxesUID194 = new TH1F("Graph_haxesUID194","",100,0,1.4e-07);
   Graph_haxesUID194->SetMinimum(0);
   Graph_haxesUID194->SetMaximum(1.3);
   Graph_haxesUID194->SetStats(0);

   ci = TColor::GetColor("#000099");
   Graph_haxesUID194->SetLineColor(ci);
   Graph_haxesUID194->GetXaxis()->SetTitle("BFsig");
   Graph_haxesUID194->GetXaxis()->SetNdivisions(407);
   Graph_haxesUID194->GetXaxis()->SetLabelFont(133);
   Graph_haxesUID194->GetXaxis()->SetLabelSize(35);
   Graph_haxesUID194->GetXaxis()->SetTitleSize(45);
   Graph_haxesUID194->GetXaxis()->SetTitleOffset(0.9);
   Graph_haxesUID194->GetXaxis()->SetTitleFont(133);
   Graph_haxesUID194->GetYaxis()->SetTitle("1#minusCL");
   Graph_haxesUID194->GetYaxis()->SetNdivisions(407);
   Graph_haxesUID194->GetYaxis()->SetLabelFont(133);
   Graph_haxesUID194->GetYaxis()->SetLabelOffset(0.01);
   Graph_haxesUID194->GetYaxis()->SetLabelSize(35);
   Graph_haxesUID194->GetYaxis()->SetTitleSize(45);
   Graph_haxesUID194->GetYaxis()->SetTitleOffset(0.85);
   Graph_haxesUID194->GetYaxis()->SetTitleFont(133);
   Graph_haxesUID194->GetZaxis()->SetLabelFont(42);
   Graph_haxesUID194->GetZaxis()->SetLabelSize(0.035);
   Graph_haxesUID194->GetZaxis()->SetTitleSize(0.035);
   Graph_haxesUID194->GetZaxis()->SetTitleOffset(1);
   Graph_haxesUID194->GetZaxis()->SetTitleFont(42);
   Graph_haxesUID194->Draw("axissame");
   
   TLegend *leg = new TLegend(0.19,0.78,0.5,0.9440559,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(133);
   leg->SetTextSize(21.75);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);

   ci = TColor::GetColor("#ffffff");
   leg->SetFillColor(ci);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("UID5","Prob CLs","f");

   ci = TColor::GetColor("#6666ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#6666ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(133);
   entry=leg->AddEntry("UID9","Prob","f");

   ci = TColor::GetColor("#9999cc");
   entry->SetFillColor(ci);
   entry->SetFillStyle(1001);

   ci = TColor::GetColor("#9999cc");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(2);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(133);
   leg->Draw();
   
   TPaveText *pt = new TPaveText(1.4e-08,0.3373,8.4e-08,0.3873,"BR");
   pt->SetBorderSize(0);
   pt->SetFillStyle(0);
   pt->SetTextAlign(12);
   pt->SetTextFont(133);
   pt->SetTextSize(35);
   TText *pt_LaTex = pt->AddText("68.3%");
   pt->Draw();
   TLine *line = new TLine(0,0.3173,1.4e-07,0.3173);
   line->SetLineStyle(3);
   line->Draw();
   
   pt = new TPaveText(1.4e-08,0.0655,8.4e-08,0.1155,"BR");
   pt->SetBorderSize(0);
   pt->SetFillStyle(0);
   pt->SetTextAlign(12);
   pt->SetTextFont(133);
   pt->SetTextSize(35);
   pt_LaTex = pt->AddText("95.5%");
   pt->Draw();
   line = new TLine(0,0.0455,1.4e-07,0.0455);
   line->SetLineStyle(3);
   line->Draw();
   
   pt = new TPaveText(0.65,0.6,0.875,0.725,"BRNDC");
   pt->SetBorderSize(0);
   pt->SetFillStyle(0);
   pt->SetTextAlign(32);
   pt->SetTextFont(133);
   pt->SetTextSize(45);
   pt_LaTex = pt->AddText("GammaCombo");
   pt->Draw();
   tutorial_dataset_BFsig_clsUID1->Modified();
   tutorial_dataset_BFsig_clsUID1->cd();
   tutorial_dataset_BFsig_clsUID1->SetSelected(tutorial_dataset_BFsig_clsUID1);
}
