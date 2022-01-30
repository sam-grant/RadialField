void hDiff_gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2()
{
//=========Macro generated from canvas: c/c
//=========  (Thu Jan 27 10:11:36 2022) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   c->SetHighLightColor(2);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   
   TH1D *hist__1 = new TH1D("hist__1","",30,-1.5,1.5);
   hist__1->SetBinContent(8,1);
   hist__1->SetBinContent(11,1);
   hist__1->SetBinContent(12,3);
   hist__1->SetBinContent(13,1);
   hist__1->SetBinContent(14,4);
   hist__1->SetBinContent(15,2);
   hist__1->SetBinContent(16,2);
   hist__1->SetBinContent(17,2);
   hist__1->SetBinContent(18,4);
   hist__1->SetBinContent(20,1);
   hist__1->SetBinContent(21,1);
   hist__1->SetBinContent(24,1);
   hist__1->SetEntries(23);
   hist__1->SetStats(0);
   hist__1->GetXaxis()->SetTitle("#Delta(#LTy_{n}#GT #minus #LTy_{n+1}#GT) [mm]");
   hist__1->GetXaxis()->CenterTitle(true);
   hist__1->GetXaxis()->SetLabelFont(42);
   hist__1->GetXaxis()->SetLabelSize(0.035);
   hist__1->GetXaxis()->SetTitleOffset(1.1);
   hist__1->GetXaxis()->SetTitleFont(42);
   hist__1->GetYaxis()->SetTitle("Calorimeters / 0.1 mm");
   hist__1->GetYaxis()->CenterTitle(true);
   hist__1->GetYaxis()->SetNdivisions(4000510);
   hist__1->GetYaxis()->SetLabelFont(42);
   hist__1->GetYaxis()->SetLabelSize(0.035);
   hist__1->GetYaxis()->SetTitleOffset(1.1);
   hist__1->GetYaxis()->SetTitleFont(42);
   hist__1->GetZaxis()->SetLabelFont(42);
   hist__1->GetZaxis()->SetLabelSize(0.035);
   hist__1->GetZaxis()->SetTitleSize(0.035);
   hist__1->GetZaxis()->SetTitleFont(42);
   hist__1->Draw("HIST");
   
   TPaveText *pt = new TPaveText(0,0,0,0,"brNDC");
   pt->SetFillColor(0);
   pt->SetTextAlign(33);
   pt->SetTextFont(44);
   pt->SetTextSize(26);
   TText *pt_LaTex = pt->AddText("0.35
#pm0.05
");
   pt->Draw();
   
   pt = new TPaveText(0,0,0,0,"brNDC");
   pt->SetFillColor(0);
   pt->SetTextAlign(13);
   pt->SetTextFont(44);
   pt->SetTextSize(26);
   pt_LaTex = pt->AddText("#sigma [mm]");
   pt->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
