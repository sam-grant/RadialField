void h_caloHitEnergy()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Mar 22 11:32:42 2021) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   
   TH1F *h_caloHitEnergy__1 = new TH1F("h_caloHitEnergy__1","",128,0,3200);
   h_caloHitEnergy__1->GetXaxis()->SetTitle("Calo hit energy [MeV]");
   h_caloHitEnergy__1->GetXaxis()->CenterTitle(true);
   h_caloHitEnergy__1->GetXaxis()->SetLabelFont(42);
   h_caloHitEnergy__1->GetXaxis()->SetLabelSize(0.035);
   h_caloHitEnergy__1->GetXaxis()->SetTitleOffset(1.1);
   h_caloHitEnergy__1->GetXaxis()->SetTitleFont(42);
   h_caloHitEnergy__1->GetYaxis()->SetTitle("Entries");
   h_caloHitEnergy__1->GetYaxis()->CenterTitle(true);
   h_caloHitEnergy__1->GetYaxis()->SetNdivisions(4000510);
   h_caloHitEnergy__1->GetYaxis()->SetLabelFont(42);
   h_caloHitEnergy__1->GetYaxis()->SetLabelSize(0.035);
   h_caloHitEnergy__1->GetYaxis()->SetTitleOffset(1.1);
   h_caloHitEnergy__1->GetYaxis()->SetTitleFont(42);
   h_caloHitEnergy__1->GetZaxis()->SetLabelFont(42);
   h_caloHitEnergy__1->GetZaxis()->SetLabelSize(0.035);
   h_caloHitEnergy__1->GetZaxis()->SetTitleSize(0.035);
   h_caloHitEnergy__1->GetZaxis()->SetTitleFont(42);
   h_caloHitEnergy__1->Draw("HIST");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
