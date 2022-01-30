void h_deltaY_gm2pro_daq_full_run1_9d_5040A_GLdocDB17018-v3_16355_16514()
{
//=========Macro generated from canvas: c/c
//=========  (Sun Jan 30 09:45:22 2022) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   c->SetHighLightColor(2);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   
   TH1D *hist__2 = new TH1D("hist__2","",2000,-100,100);
   hist__2->SetBinContent(1013,7);
   hist__2->SetBinContent(1014,74);
   hist__2->SetBinContent(1015,25);
   hist__2->SetBinContent(1016,1);
   hist__2->SetEntries(107);
   hist__2->SetStats(0);
   hist__2->GetXaxis()->SetTitle("#Delta#LTy_{calo}#GT [mm]");
   hist__2->GetXaxis()->CenterTitle(true);
   hist__2->GetXaxis()->SetLabelFont(42);
   hist__2->GetXaxis()->SetLabelSize(0.035);
   hist__2->GetXaxis()->SetTitleOffset(1.1);
   hist__2->GetXaxis()->SetTitleFont(42);
   hist__2->GetYaxis()->SetTitle("Runs / 0.2 mm");
   hist__2->GetYaxis()->CenterTitle(true);
   hist__2->GetYaxis()->SetNdivisions(4000510);
   hist__2->GetYaxis()->SetLabelFont(42);
   hist__2->GetYaxis()->SetLabelSize(0.035);
   hist__2->GetYaxis()->SetTitleOffset(1.1);
   hist__2->GetYaxis()->SetTitleFont(42);
   hist__2->GetZaxis()->SetLabelFont(42);
   hist__2->GetZaxis()->SetLabelSize(0.035);
   hist__2->GetZaxis()->SetTitleSize(0.035);
   hist__2->GetZaxis()->SetTitleFont(42);
   hist__2->Draw("HIST");
   
   TPaveText *pt = new TPaveText(0,0,0,0,"brNDC");
   pt->SetFillColor(0);
   pt->SetTextAlign(33);
   pt->SetTextFont(44);
   pt->SetTextSize(26);
   TText *pt_LaTex = pt->AddText("0.048
#pm0.003
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
