#include <iostream>
#include <vector>

#include "TFile.h"
#include "TTreeReader.h"
#include "TH1D.h"
#include "TH2D.h"

using namespace std;

void ReadYPos(string input, string output, double eMin, double eMax, double tMin, double tMax) {

  bool removeBadCalos = false;

  // ++++++++++++++ Open tree and load branches ++++++++++++++
  // Get file
  TFile *f1 = TFile::Open(input.c_str());
  cout<<"\nOpened tree:\t"<<input<<" "<<f1<<endl;

  // Get reader for tree

  // TODO: stop using TreeReader it's pretty bad 
  TTreeReader treeReader("nearlineHistTree/eventTree",f1);

  // Get branches
  TTreeReaderValue<unsigned int> runNum(treeReader,"runNum");
  TTreeReaderValue<unsigned int> subRunNum(treeReader,"subRunNum");
  TTreeReaderValue<unsigned int> eventNum(treeReader,"eventNum");
  TTreeReaderValue<unsigned int> ctag(treeReader,"ctag");
  TTreeReaderValue<vector<int>> caloNum(treeReader,"caloNum");
  TTreeReaderValue<std::vector<double>> energy(treeReader,"energy");
  TTreeReaderValue<std::vector<double>> times(treeReader,"time");
  TTreeReaderValue<std::vector<double>> x(treeReader,"x");
  TTreeReaderValue<std::vector<double>> y(treeReader,"y");


  // ++++++++++++++ Book histograms ++++++++++++++
  // All calos
  //TH2D *hxy = new TH2D("hxy", ";x [mm];y [mm]", 225, 0, 225, 150, 0, 150);
  TH1D *hy = new TH1D("clusterY", ";y [mm];Clusters", 150, 0, 150);

  // Individual calos
  vector<TH1D *> hy_calos;

  for(int i_calo = 0; i_calo < 24; i_calo++) {
   	TH1D *hy_tmp = (TH1D*) hy->Clone();
   	hy_tmp->SetName( ("clusterY_"+to_string(i_calo+1)).c_str() );
   	hy_calos.push_back(hy_tmp);
  }

  // ++++++++++++++ Loop thro events ++++++++++++++
  unsigned int tot_ctag = 0;
  unsigned int tot_ctag_check = 0;

  int counter = 0;

  while (treeReader.Next()){

    //unsigned int ctag = ctag*;
    tot_ctag = tot_ctag + *ctag;

    // Get leaves
    vector<int> caloNum_ = *caloNum;

    // Skip calos 5 & 9 
    vector<double> x_ = *x;
    vector<double> y_ = *y;
    vector<double> energy_ = *energy;
    vector<double> times_ = *times;

    // Number of clusters in this fill
    int nClu = caloNum_.size(); 

    // Loop through clusters
    for(int i_clu = 0; i_clu < nClu; i_clu++) { 

      // Get cluster level variables
      int caloNum =  caloNum_.at(i_clu);
      double xmm = x_.at(i_clu) * 25;
      double ymm = y_.at(i_clu) * 25; 
      double energy = energy_.at(i_clu);
      double time = times_.at(i_clu) * 1.25 * 1e-3; // ct -> us

      // Variable cuts
      if(energy > eMin && energy < eMax && time > tMin && time < tMax) {

	       tot_ctag_check++;

	       // Fill y-position for all calos
	       //hxy->Fill(xmm, ymm);
	       hy->Fill(ymm);
	       // Fill y-position for individual calos
	       hy_calos.at(caloNum-1)->Fill(ymm);

      }

      counter++;

    }

  }

  // ++++++++++++++ Draw sanity plots ++++++++++++++

  /*// use fancy draw
    TCanvas *c1 = new TCanvas("c1","c1",800,600);
    gStyle->SetOptStat(2210);
    hy->Draw("HIST");
    c1->SaveAs("Images/hy.png");

    TCanvas *c2 = new TCanvas("c2","c2",800,600);
    gStyle->SetOptStat(2210);
    hy_calos.at(0)->Draw("HIST");
    c2->SaveAs("Images/hy_1.png");

    TCanvas *c3 = new TCanvas("c3","c3",800,600);
    gStyle->SetOptStat(0);
    gStyle->SetPalette(55);
    hxy->Draw("COLZ");
    c3->SaveAs("Images/hxy.png");*/

  // ++++++++++++++ Write to file ++++++++++++++


  hy->SetName("clusterY");
  TFile *f2 = new TFile(output.c_str(), "RECREATE");
  f2->mkdir("CaloBeamPosition"); f2->cd("CaloBeamPosition"); 

  hy->Write();
  f2->mkdir("CaloBeamPosition/PerCalo"); f2->cd("CaloBeamPosition/PerCalo");
  for(int i_calo = 0; i_calo < hy_calos.size(); i_calo++) hy_calos.at(i_calo)->Write();
  f2->Close();

  cout<<"\nMean y-position:\t"<<hy->GetMean()<<"+/-"<<hy->GetMeanError()<<endl;

  cout<<"\nWritten histograms to:\t"<<output<<" "<<f2<<endl;

  f1->Close();
  f2->Close();

  return;

}

int main(int argc, char *argv[]) {

  string run = argv[1];
  //string file = argv[2];

  string eMin = "1000";//argv[2];
  string eMax = "2750";//argv[3];
  string tMin = "30";//argv[4];
  string tMax = "300";//argv[5];

  string outDir = eMin+"MeV_"+eMax+"MeV_"+tMin+"us_"+tMax+"us";

  cout<<"Running\t" <<run<<endl;

  string input = "/pnfs/GM2/daq/run5/nearline/nearlineHists_merged/runs_46000/"+run+"/gm2nearline_hists_run"+run+".root";
  string output = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/Run5_Nearline/caloBeamPositionPlots_"+run+".root"; 

  cout<<std::stod(eMin)<<" < E [MeV] < "<<std::stod(eMax)<<", "<<std::stod(tMin)<<" < t [us] < "<<std::stod(tMax)<<endl;

  ReadYPos(input, output, std::stod(eMin), std::stod(eMax), std::stod(tMin), std::stod(tMax));

  return 0;
}
