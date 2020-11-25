void tutorial_dataset_BFsig_cls_fit()
{
//=========Macro generated from canvas: UID6/S+B and B only fits to the dataset for Lb_DTFLambdaPV_M
//=========  (Tue Nov 24 14:54:16 2020) by ROOT version 6.18/04
   TCanvas *UID6 = new TCanvas("UID6", "S+B and B only fits to the dataset for Lb_DTFLambdaPV_M",0,0,800,600);
   gStyle->SetOptStat(0);
   gStyle->SetOptTitle(0);
   UID6->SetHighLightColor(2);
   UID6->Range(4355.443,-32.71503,6633.924,159.7263);
   UID6->SetFillColor(0);
   UID6->SetBorderMode(0);
   UID6->SetBorderSize(2);
   UID6->SetLeftMargin(0.16);
   UID6->SetRightMargin(0.05);
   UID6->SetTopMargin(0.05);
   UID6->SetBottomMargin(0.17);
   UID6->SetFrameBorderMode(0);
   UID6->SetFrameBorderMode(0);
   
   TH1D *frame_125425e0__1 = new TH1D("frame_125425e0__1","A RooPlot of \"Lb_DTFLambdaPV_M\"",100,4720,6520);
   frame_125425e0__1->SetBinContent(1,150.1043);
   frame_125425e0__1->SetMaximum(150.1043);
   frame_125425e0__1->SetEntries(1);
   frame_125425e0__1->SetDirectory(0);
   frame_125425e0__1->SetStats(0);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   frame_125425e0__1->SetLineColor(ci);
   frame_125425e0__1->GetXaxis()->SetTitle("Lb_DTFLambdaPV_M");
   frame_125425e0__1->GetXaxis()->SetLabelFont(42);
   frame_125425e0__1->GetXaxis()->SetLabelSize(0.035);
   frame_125425e0__1->GetXaxis()->SetTitleSize(0.035);
   frame_125425e0__1->GetXaxis()->SetTitleOffset(1);
   frame_125425e0__1->GetXaxis()->SetTitleFont(42);
   frame_125425e0__1->GetYaxis()->SetTitle("Events / ( 18 )");
   frame_125425e0__1->GetYaxis()->SetLabelFont(42);
   frame_125425e0__1->GetYaxis()->SetLabelOffset(0.01);
   frame_125425e0__1->GetYaxis()->SetLabelSize(0.035);
   frame_125425e0__1->GetYaxis()->SetTitleSize(0.035);
   frame_125425e0__1->GetYaxis()->SetTitleFont(42);
   frame_125425e0__1->GetZaxis()->SetLabelFont(42);
   frame_125425e0__1->GetZaxis()->SetLabelSize(0.035);
   frame_125425e0__1->GetZaxis()->SetTitleSize(0.035);
   frame_125425e0__1->GetZaxis()->SetTitleOffset(1);
   frame_125425e0__1->GetZaxis()->SetTitleFont(42);
   frame_125425e0__1->Draw("FUNC");
   
   TH1D *frame_125425e0__2 = new TH1D("frame_125425e0__2","A RooPlot of \"Lb_DTFLambdaPV_M\"",100,4720,6520);
   frame_125425e0__2->SetBinContent(1,150.1043);
   frame_125425e0__2->SetMaximum(150.1043);
   frame_125425e0__2->SetEntries(1);
   frame_125425e0__2->SetDirectory(0);
   frame_125425e0__2->SetStats(0);

   ci = TColor::GetColor("#000099");
   frame_125425e0__2->SetLineColor(ci);
   frame_125425e0__2->GetXaxis()->SetTitle("Lb_DTFLambdaPV_M");
   frame_125425e0__2->GetXaxis()->SetLabelFont(42);
   frame_125425e0__2->GetXaxis()->SetLabelSize(0.035);
   frame_125425e0__2->GetXaxis()->SetTitleSize(0.035);
   frame_125425e0__2->GetXaxis()->SetTitleOffset(1);
   frame_125425e0__2->GetXaxis()->SetTitleFont(42);
   frame_125425e0__2->GetYaxis()->SetTitle("Events / ( 18 )");
   frame_125425e0__2->GetYaxis()->SetLabelFont(42);
   frame_125425e0__2->GetYaxis()->SetLabelOffset(0.01);
   frame_125425e0__2->GetYaxis()->SetLabelSize(0.035);
   frame_125425e0__2->GetYaxis()->SetTitleSize(0.035);
   frame_125425e0__2->GetYaxis()->SetTitleFont(42);
   frame_125425e0__2->GetZaxis()->SetLabelFont(42);
   frame_125425e0__2->GetZaxis()->SetLabelSize(0.035);
   frame_125425e0__2->GetZaxis()->SetTitleSize(0.035);
   frame_125425e0__2->GetZaxis()->SetTitleOffset(1);
   frame_125425e0__2->GetZaxis()->SetTitleFont(42);
   frame_125425e0__2->Draw("AXISSAME");
   
   TLegend *leg = new TLegend(0.6,0.7,0.92,0.92,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("h_data","Background Only Fit","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h_data","Free Fit","L");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   UID6->Modified();
   UID6->cd();
   UID6->SetSelected(UID6);
}
