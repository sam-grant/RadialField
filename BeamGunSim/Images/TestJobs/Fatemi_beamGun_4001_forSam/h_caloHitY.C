void h_caloHitY()
{
//=========Macro generated from canvas: c/c
//=========  (Mon Mar 22 11:32:42 2021) by ROOT version 6.12/04
   TCanvas *c = new TCanvas("c", "c",0,0,800,600);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   
   TH1F *h_caloHitY__2 = new TH1F("h_caloHitY__2","",150,-75,75);
   h_caloHitY__2->GetXaxis()->SetTitle("Calo hit Y [mm]");
   h_caloHitY__2->GetXaxis()->CenterTitle(true);
   h_caloHitY__2->GetXaxis()->SetLabelFont(42);
   h_caloHitY__2->GetXaxis()->SetLabelSize(0.035);
   h_caloHitY__2->GetXaxis()->SetTitleOffset(1.1);
   h_caloHitY__2->GetXaxis()->SetTitleFont(42);
   h_caloHitY__2->GetYaxis()->SetTitle("Entries");
   h_caloHitY__2->GetYaxis()->CenterTitle(true);
   h_caloHitY__2->GetYaxis()->SetNdivisions(4000510);
   h_caloHitY__2->GetYaxis()->SetLabelFont(42);
   h_caloHitY__2->GetYaxis()->SetLabelSize(0.035);
   h_caloHitY__2->GetYaxis()->SetTitleOffset(1.1);
   h_caloHitY__2->GetYaxis()->SetTitleFont(42);
   h_caloHitY__2->GetZaxis()->SetLabelFont(42);
   h_caloHitY__2->GetZaxis()->SetLabelSize(0.035);
   h_caloHitY__2->GetZaxis()->SetTitleSize(0.035);
   h_caloHitY__2->GetZaxis()->SetTitleFont(42);
   h_caloHitY__2->Draw("HIST");
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
