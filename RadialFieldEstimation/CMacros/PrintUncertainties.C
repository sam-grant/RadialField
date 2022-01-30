#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <numeric>


#include "RootInclude.h"
#include "FancyDraw.h"
#include "Utils.h"
#include "TTree.h"
//#include "TVector.h"
//#include "TVectorD.h"
//#include "TVectorT.h"

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


TGraphErrors *GetAvgCaloYVsRun(vector<string> runs, string dataset, string inputDir) { 

  // string basename = "caloBeamPositionPlots_"; 
  // if(nearline) "gm2nearline_hists_run"; 

  vector<double> y_; vector<double> ey_; 
  vector<double> x_; vector<double> ex_;

  for( int i_run = 0; i_run < runs.size(); i_run++ ) {

    string run = runs.at(i_run);

    // Regular method
    // TFile *fin = TFile::Open((inputDir+"/caloBeamPositionPlots_"+run+".root").c_str());
    string inputName;

    if(dataset=="Run1") { // } || dataset=="Run2" || dataset=="Run3") { 

      if(stod(run) <= 15991) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 16355 && stod(run) <= 16514) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_9d_5040A_GLdocDB17018-v3/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 16113 && stod(run) <= 16234) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_HighKick_5042B_GLdocDB20949-v3/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 17065 && stod(run) <= 17527) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_EndGame_5042B_GLdocDB20839-v1/caloBeamPositionPlots_"+run+".root";

    } else if(dataset=="Run2") {

      if(stod(run) >= 24636 && stod(run) <= 24576) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2B/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 24683 && stod(run) <= 25045) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2C/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 25894 && stod(run) <= 26383) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2D/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26478 && stod(run) <= 26611) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2E/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26675 && stod(run) <= 26803) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2F/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26999 && stod(run) <= 27042) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2G/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 27166 && stod(run) <= 27212) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2G/caloBeamPositionPlots_"+run+".root";

    } else if(dataset=="Run3") { 

      if(stod(run) >= 34184 && stod(run) <= 34618) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run3N_5207A/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 34702 && stod(run) <= 34920) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run3O_5207A/caloBeamPositionPlots_"+run+".root";

    } else if(dataset=="All") { 

      if(stod(run) <= 15991) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 16355 && stod(run) <= 16514) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_9d_5040A_GLdocDB17018-v3/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 16113 && stod(run) <= 16234) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_HighKick_5042B_GLdocDB20949-v3/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 17065 && stod(run) <= 17527) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_EndGame_5042B_GLdocDB20839-v1/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 24636 && stod(run) <= 24576) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2B/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 24683 && stod(run) <= 25045) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2C/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 25894 && stod(run) <= 26383) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2D/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26478 && stod(run) <= 26611) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2E/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26675 && stod(run) <= 26803) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2F/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26999 && stod(run) <= 27042) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2G/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 27166 && stod(run) <= 27212) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2G/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 34184 && stod(run) <= 34618) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run3N_5207A/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 34702 && stod(run) <= 34920) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run3O_5207A/caloBeamPositionPlots_"+run+".root";

    }

    inputName = inputDir+"/caloBeamPositionPlots_"+run+".root";

    if(run=="17113") continue;

    //cout<<"Getting file "<<inputName<<endl;

    TFile *fin = TFile::Open((inputName).c_str());

    //cout<<"Got file "<<inputName<<", "<<fin<<endl;

    if(fin==0) continue;

    TH1D *hy = (TH1D*)fin->Get("CaloBeamPosition/clusterY");

    double y = hy->GetMean(); double ey = hy->GetMeanError();

    if(hy->GetMean()==0) {
      fin->Close();
      // cout<<"Warning: run "+run+" has a mean y-position of zero. Skipping."<<endl;
      continue;
    }

    y_.push_back(y); ey_.push_back(ey);
    x_.push_back(std::stod(run)); ex_.push_back(0.);

    //cout<<run<<","<<y<<","<<ey<<endl;
  
    fin->Close();

  }

  // Create TGraph 
  TGraphErrors *gr = GenerateTGraphErrors(x_, y_, ex_, ey_); 

  gr->Draw("AP*");

  return gr;

}

TH1D *GetTotAvgCaloY(vector<string> runs, string dataset, string inputDir) { 

  TH1D *hy_tot = new TH1D("hy_tot", ";y [mm]; Clusters",  150, 0, 150);

  for( int i_run = 0; i_run < runs.size(); i_run++ ) {

    string run = runs.at(i_run);

    // Regular method
    // TFile *fin = TFile::Open((inputDir+"/caloBeamPositionPlots_"+run+".root").c_str());
    string inputName;

    if(dataset=="Run1") { // } || dataset=="Run2" || dataset=="Run3") { 

      if(stod(run) <= 15991) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 16355 && stod(run) <= 16514) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_9d_5040A_GLdocDB17018-v3/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 16113 && stod(run) <= 16234) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_HighKick_5042B_GLdocDB20949-v3/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 17065 && stod(run) <= 17527) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_EndGame_5042B_GLdocDB20839-v1/caloBeamPositionPlots_"+run+".root";

    } else if(dataset=="Run2") {

      if(stod(run) >= 24636 && stod(run) <= 24576) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2B/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 24683 && stod(run) <= 25045) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2C/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 25894 && stod(run) <= 26383) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2D/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26478 && stod(run) <= 26611) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2E/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26675 && stod(run) <= 26803) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2F/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26999 && stod(run) <= 27042) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2G/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 27166 && stod(run) <= 27212) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2G/caloBeamPositionPlots_"+run+".root";

    } else if(dataset=="Run3") { 

      if(stod(run) >= 34184 && stod(run) <= 34618) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run3N_5207A/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 34702 && stod(run) <= 34920) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run3O_5207A/caloBeamPositionPlots_"+run+".root";

    } else if(dataset=="All") { 

      if(stod(run) <= 15991) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 16355 && stod(run) <= 16514) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_9d_5040A_GLdocDB17018-v3/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 16113 && stod(run) <= 16234) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_HighKick_5042B_GLdocDB20949-v3/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 17065 && stod(run) <= 17527) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_full_run1_EndGame_5042B_GLdocDB20839-v1/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 24636 && stod(run) <= 24576) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2B/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 24683 && stod(run) <= 25045) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2C/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 25894 && stod(run) <= 26383) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2D/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26478 && stod(run) <= 26611) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2E/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26675 && stod(run) <= 26803) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2F/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 26999 && stod(run) <= 27042) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2G/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 27166 && stod(run) <= 27212) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run2G/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 34184 && stod(run) <= 34618) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run3N_5207A/caloBeamPositionPlots_"+run+".root";
      else if(stod(run) >= 34702 && stod(run) <= 34920) inputName = "/pnfs/GM2/persistent/EDM/Data/Br/CaloBeamPos/gm2pro_daq_offline_dqc_run3O_5207A/caloBeamPositionPlots_"+run+".root";

    }

    inputName = inputDir+"/caloBeamPositionPlots_"+run+".root";

    if(run=="17113") continue;

    TFile *fin = TFile::Open((inputName).c_str());
    
    if(fin==0) continue;

    TH1D *hy = (TH1D*)fin->Get("CaloBeamPosition/clusterY");

    double y = hy->GetMean(); double ey = hy->GetMeanError();

    if(hy->GetMean()==0) {
      fin->Close();
      cout<<"Warning: run "+run+" has a mean y-position of zero. Skipping."<<endl;
      continue;
    }

    // Add to master hist
    hy_tot->Add(hy); 


  
    fin->Close();

  }

  // cout<<hy_tot->GetMean()<<endl;

  return hy_tot;

}

tuple<double, double> GetRefPos(bool noBadCalos) { 

  string fname = "";
  if(noBadCalos) fname += "../Plots/RefPos_NoBadCalos_Run4_2021.root";
  else if(!noBadCalos) fname += "../Plots/RefPos_Run4_2021.root";

  TFile *fin = TFile::Open(fname.c_str());

  TGraphErrors *gr = (TGraphErrors*)fin->Get("CaloAvg/y_vs_run");
  TF1 *fit = (TF1*)gr->GetFunction("RefPos");

  return make_tuple(fit->GetParameter(0), fit->GetParError(0));

}


double GetCaloAlignError(string dataset) { 

  TFile *fin = TFile::Open(("../Plots/CaloAlignment_"+dataset+".root").c_str());
  TH1D *hist = (TH1D*)fin->Get("hists/h_diff"); 

  return hist->GetRMS(); 

}

TGraphErrors *GetDeltaYVsRun(TGraphErrors *input, double zero, double zero_err) { 

  int n = input->GetN();

  double x[n]; double ex[n];
  double y[n]; double ey[n];

  for (int i_point = 0; i_point < n; i_point++) { 

    x[i_point] = input->GetX()[i_point];//PointX(i_point); 
    ex[i_point] = 0.;
    y[i_point] = input->GetY()[i_point] - zero;//PointY(i_point) - zero;
    ey[i_point] = sqrt(pow(input->GetErrorY(i_point),2) + pow(zero_err,2));

  } 
  
  return new TGraphErrors(n, x, y, ex, ey);

}

TH1D *GetDeltaY1D(TGraphErrors *input, double zero, double zero_err) { 

  int n = input->GetN();

  // TH1D *hist = new TH1D("hist", "", 100, 0.8, 1.8);//100, -10, 10);
  TH1D *hist = new TH1D("hist", "", 20, 0.65, 1.65);//100, -10, 10);

  for (int i_point = 0; i_point < n; i_point++) { 

    hist->Fill(input->GetY()[i_point] - zero);

  } 

  return hist;

}


// Calculate this by hand to avoid running into overflow/underflow issues
double StandardDeviation(TGraphErrors *input, double zero) { 

  vector<double> v; 

  for (int i_point(0); i_point < input->GetN(); i_point++)  {
      double entry = input->GetY()[i_point] - zero; 
      v.push_back(entry);
  }

  double sum = std::accumulate(v.begin(), v.end(), 0.0);
  double mean = sum / v.size();

  std::vector<double> diff(v.size());
  std::transform(v.begin(), v.end(), diff.begin(),
               std::bind2nd(std::minus<double>(), mean));
  double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
  double stdev = std::sqrt(sq_sum / v.size());

  return stdev;

}

int main(int argc, char *argv[]) { 

  // Get inputs
  // If you're getting a logic error it's because you haven't provided an argument 
  string dataset = argv[1];//"gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2"; //  // "gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2"; //  // "gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2";//argv[1];
  
  string config = "CaloBeamPos";

  // Read in y-positions
  
  vector<string> runs = csvReader("../txt/"+dataset+".txt");

  string inputDir = "/pnfs/GM2/persistent/EDM/Data/Br/"+config+"/"+dataset;

  
  TGraphErrors *gr_AvgCaloYvsRun = GetAvgCaloYVsRun(runs, dataset, inputDir);

  TH1D *h_AvgCaloYTot = GetTotAvgCaloY(runs, dataset, inputDir);
  
  // Clone to be safe
  TH1D *h_AvgCaloYTot_clone = (TH1D*)h_AvgCaloYTot->Clone("h_AvgCaloYTot_clone");

  // Get zero point
 

  // Make sure this excludes 5 & 9
  bool noBadCalos = true;
  tuple<double, double> refPoint = GetRefPos(noBadCalos);
  double ref = get<0>(refPoint); double err_ref = get<1>(refPoint);

  // Get y minus zero point
  
  TGraphErrors *gr_AvgCaloDeltaY = GetDeltaYVsRun(gr_AvgCaloYvsRun, ref, err_ref);

  // Histogram of means
  TH1D *h_AvgCaloDeltaY = GetDeltaY1D(gr_AvgCaloYvsRun, ref, err_ref);
  
  // All cluster average delta Y for this DS
  double tot_deltaY =  h_AvgCaloYTot->GetMean() - ref; 

  // Errors on dy 
  double err_stat = h_AvgCaloYTot->GetMeanError();
  double err_drift = StandardDeviation(gr_AvgCaloYvsRun, ref);//h_AvgCaloDeltaY->GetRMS();

  std::cout << h_AvgCaloDeltaY << std::endl;
  std::cout << err_drift * 1e3 << std::endl;
  std::cout << h_AvgCaloYTot->GetRMS() << std::endl;
  double err_align = GetCaloAlignError(dataset);

  double err_tot_deltaY = sqrt(pow(err_stat,2)+pow(err_ref,2)+pow(err_drift,2)+pow(err_align,2));


  cout<<sqrt(pow(err_stat,2)+pow(err_ref,2))<<", "<<err_drift<<", "<<err_align<<endl;

	return 0;

}

/*void PrintUncertainties() { 

	return;

}*/
