#include <iostream>
#include <vector>
#include <fstream>

#include "RootInclude.h"
#include "FancyDraw.h"
#include "Utils.h"

using namespace std;

// Read in list of sub-runs 
vector<string> csvReader(string infile) {

  vector<string> result;

  // Open file
  std::ifstream myFile(infile);

  // Check that it opened correctly 
  if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line; int val; 
    // Read data, line by line
    while(std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);
        while(ss >> val) result.push_back(to_string(val));
    }

    // Close file
    myFile.close();

    return result;

}

int main(int argc, char *argv[]) {

  // Get inputs
  //string config = argv[1];
  string dataset = argv[1];

  string config = "CaloBeamPos";

//  if( dataset!="60h" || dataset!="Run1" || dataset!="Run2" || dataset!="Run3" || dataset!="Run4" ) { 
//    cout<<"Invalid dataset, enter eg 'Run1'. Stopping."<<endl;
//    return 0;
//  }

  vector<string> runs = csvReader("../txt/"+dataset+".txt");

  string inputDir = "/pnfs/GM2/persistent/EDM/Data/RadialField/"+config+"/"+dataset;
  // testing 
  if(dataset=="60h") inputDir="/pnfs/GM2/persistent/EDM/Data/RadialField/"+config+"/Run1";

  // Set output
  string outputName = "../Plots/"+config+"VsRun_"+dataset+"_"+runs.at(0)+"_"+runs.at(runs.size()-1)+".root";
  TFile *output = new TFile( outputName.c_str(), "RECREATE");
  output->mkdir("CaloAverage"); output->mkdir("PerCalo"); output->mkdir("PerCaloMeanSubtracted");

  vector<double> y_; vector<double> ey_; 
  vector<double> x_; vector<double> ex_;

  for( int i_run = 0; i_run < runs.size(); i_run++ ) {

    string run = runs.at(i_run);

    TFile *fin = TFile::Open((inputDir+"/caloBeamPositionPlots_"+run+".root").c_str());

    if(fin==0) continue;

    TH1D *hy = (TH1D*)fin->Get("CaloBeamPosition/clusterY");

    double y = hy->GetMean(); double ey = hy->GetMeanError();

    if(hy->GetMean()==0) {
      fin->Close();
      cout<<"Warning: run "+run+" has a mean y-position of zero. Skipping."<<endl;
      continue;
    }

    // Makes plots look nicer
    // if(y < 70 || y > 80) continue;

    y_.push_back(y); ey_.push_back(ey);
    x_.push_back(std::stod(run)); ex_.push_back(0.);

    cout<<run<<","<<y<<","<<ey<<endl;
  
    fin->Close();

  }

  // Create TGraph 
  TGraphErrors *gr = GenerateTGraphErrors(x_, y_, ex_, ey_); 

  //gr->GetYaxis()->SetRangeUser(ymin1, ymax1);  

  gr->Draw("AP*");

  output->cd("CaloAverage"); 
  gr->SetName("gr");
  gr->Write();

  DrawTGraphErrors(gr, ";Run number;#LTy_{Calo}#GT [mm]", "../Images/"+config+"VsRun_"+dataset+"_"+runs.at(0)+"_"+runs.at(runs.size()-1));  

  output->Write();
  output->Close();

  return 0;

}

/*


  // Get diff from zero point
  // Plot the mean with zero line drawn

  vector<TGraphErrors*> caloGraphs_; vector<TGraphErrors*> caloGraphs_meanSub_;
  vector<string> caloNames_;

  for( int i_calo = 1; i_calo < 25; i_calo++ ) {

    cout<<"\nProcessing calo "<<i_calo<<endl;

    vector<double> yCalo_; vector<double> eyCalo_; 
    vector<double> xCalo_; vector<double> exCalo_;

    for( int i_run = 0; i_run < runs.size(); i_run++ ) {

      string run = runs.at(i_run);
      //string input = "../Plots/Data/RadialFieldEstimation/BeamYPosMonitoring/Input/"+dataset+"/y-pos_"+run+".root";
      string input = "../Plots/Data/RadialFieldEstimation/BeamYPosMonitoring/Input/Run4_Jan/y-pos_"+run+".root";
      TFile *fin = TFile::Open(input.c_str());
      TH1D *hy_calo = (TH1D*)fin->Get(("CaloBeamPosition/PerCalo/clusterY_"+to_string(i_calo)).c_str());
      if(hy_calo->GetMean()==0) {
        fin->Close();
        continue;
      }

      double ymean = hy_calo->GetMean(); 
      if(ymean < 70 || ymean > 80) continue;
      //cout<<"ymean\t"<<ymean<<endl;

      yCalo_.push_back(ymean); eyCalo_.push_back(hy_calo->GetMeanError());
      xCalo_.push_back(std::stod(run)); exCalo_.push_back(0.);

      fin->Close();

    }

    int n_calo = yCalo_.size();

    double x_calo[n_calo]; double ex_calo[n_calo];
    double y_calo[n_calo]; double ey_calo[n_calo];
    double y_calo_mean_sub[n_calo];

    // Get calo mean 
    float average = 0.0f;
    if ( n_calo != 0) average = accumulate( yCalo_.begin(), yCalo_.end(), 0.0) / n_calo;

    for( int i_run = 0; i_run < n_calo; i_run++ ) {

      x_calo[i_run] = xCalo_.at(i_run); ex_calo[i_run] = exCalo_.at(i_run);
      y_calo[i_run] = yCalo_.at(i_run); ey_calo[i_run] = eyCalo_.at(i_run);
      y_calo_mean_sub[i_run] = yCalo_.at(i_run) - average; 


    }

    TGraphErrors *gr_calo = new TGraphErrors(n_calo, x_calo, y_calo, ex_calo, ey_calo);
    TGraphErrors *gr_calo_mean_sub = new TGraphErrors(n_calo, x_calo, y_calo_mean_sub, ex_calo, ey_calo);

    gr_calo->Draw("AP*");
    output->cd("PerCalo"); 
    gr_calo->SetName(("gr_"+to_string(i_calo)).c_str());
    gr_calo->Write();

    gr_calo_mean_sub->Draw("AP*");

    output->cd("PerCaloMeanSubtracted");
    gr_calo_mean_sub->SetName(("gr_"+to_string(i_calo)).c_str());
    gr_calo_mean_sub->Write();

    caloGraphs_.push_back(gr_calo);
    caloGraphs_meanSub_.push_back(gr_calo_mean_sub);
    caloNames_.push_back("Calo "+to_string(i_calo));

    cout<<"Done"<<endl;

  }

  DrawManyTGraphErrors(caloGraphs_, caloNames_, ";Run number;#LTy_{Calo}#GT [mm]", "../Images/Data/RadialFieldEstimation/BeamYPosMonitoring/"+dataset+"/y-pos_calos_"+runs.at(0)+"-"+runs.at(runs.size()-1), ymin1, ymax1); 
  DrawManyTGraphErrors(caloGraphs_meanSub_, caloNames_, ";Run number;Mean subtracted #LTy_{Calo}#GT [mm]", "../Images/Data/RadialFieldEstimation/BeamYPosMonitoring/"+dataset+"/y-pos_calos_meanSub_"+runs.at(0)+"-"+runs.at(runs.size()-1), ymin2, ymax2); 

  output->Write();
  output->Close();

  cout<<"\nWritten plots to ROOT file\n"<<outputName<<"\n"<<output<<endl;

  return 0;

}

*/
