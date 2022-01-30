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

//const double QHV = 18.3;

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

void DrawHist(TH1D *hist, std::string title, std::string fname) { 

  TCanvas *c = new TCanvas("c","c",800,600);

  hist->SetTitle(title.c_str());

  hist->SetStats(0);
      
  hist->GetXaxis()->SetTitleSize(.04);
  hist->GetYaxis()->SetTitleSize(.04);
  hist->GetXaxis()->SetTitleOffset(1.1);
  hist->GetYaxis()->SetTitleOffset(1.1);
  hist->GetXaxis()->CenterTitle(1);
  hist->GetYaxis()->CenterTitle(1);
  hist->GetYaxis()->SetMaxDigits(4);
  hist->SetLineColor(1);

  //hist->GetXaxis()->SetRangeUser(.8, 1.5);

  //hist->SetFillStyle(3001);
  //hist->SetFillColor(kBlack);
  hist->Draw("HIST");

  ////////

  TString mean = Round(hist->GetMean(), 3);
  TString mean_err = Round(hist->GetMeanError(), 1);

  TString rms = Round(hist->GetRMS(), 3);
  TString rms_err = Round(hist->GetRMSError(), 1);

  TPaveText *names = new TPaveText(0.60,0.80,0.70,0.89,"NDC");
  names->SetTextAlign(13);
  //names->AddText("#LT#Deltay#GT [mm]");
  names->AddText("#sigma [mm]");
  names->SetTextSize(26); // 26
  names->SetTextFont(44);
  names->SetFillColor(0);

  TPaveText *values = new TPaveText(0.79,0.80,0.89,0.89,"NDC");
  values->SetTextAlign(33);
  //values->AddText(mean+"#pm"+mean_err);
  values->AddText(rms+"#pm"+rms_err);
  values->SetTextSize(26); // 26
  values->SetTextFont(44);
  values->SetFillColor(0);

  values->Draw("same");
  names->Draw("same");

  ////////

  //c->SetRightMargin(0.13);
  
  c->SaveAs((fname+".C").c_str());
  c->SaveAs((fname+".pdf").c_str());
  c->SaveAs((fname+".png").c_str());

  delete c;

  return;

}


/*Read input files and store a histogram of all cluster positions and a graph of average cluster
position versus run in a tuple */

std::tuple<TH1D*, TGraphErrors*> GetAvgCaloYPlots(vector<string> runs, string dataset, string inputDir) { 

  // Total cluster-y position histogram
  TH1D *hy_tot = new TH1D("hy_tot", ";y [mm]; Clusters",  150, 0, 150);

  // Vectors for TGraphErrors 
  vector<double> y_; vector<double> ey_; 
  vector<double> x_; vector<double> ex_;

  for( int i_run = 0; i_run < runs.size(); i_run++ ) {

    string run = runs.at(i_run);

    // Regular method
    string inputName;

    if(dataset=="Run1") { 

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

    if(hy->GetMean()==0) {
      fin->Close();
      //cout<<"Warning: run "+run+" has a mean y-position of zero. Skipping."<<endl;
      continue;
    }

    // "DQC" for the nearline. 
    if(hy->GetEntries() < 1e4) {
      fin->Close();
      continue;
    }

    // Add to master hist
    hy_tot->Add(hy); 

    double y = hy->GetMean(); double ey = hy->GetMeanError();

    // Fill vectors
    y_.push_back(y); ey_.push_back(ey);
    x_.push_back(std::stod(run)); ex_.push_back(0.);

    fin->Close();

  }

  // Create TGraphErrors 
  TGraphErrors *gr = GenerateTGraphErrors(x_, y_, ex_, ey_); 
  gr->Draw("AP*");

  return make_tuple(hy_tot, gr);

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

  //TH1D *hist = new TH1D("hist", "", 100, 0, 1);//100, -10, 10);
  TH1D *hist = new TH1D("hist", "", 2000, -100, 100);//100, -10, 10);
  
  // Formatted for Run-1a

  // You will get underflow/overflows but we don't use this hist for anything except presentation
  //TH1D *hist = new TH1D("hist", "", 20, 0.65, 1.65);
  for (int i_point = 0; i_point < n; i_point++) { 
    double entry = input->GetY()[i_point] - zero; 
    hist->Fill(entry);
  } 

  int underflow = hist->GetBinContent(hist->GetBin(0));
  int overflow = hist->GetBinContent(hist->GetBin(hist->GetNbinsX()+1));

  cout<<"underflow = "<<underflow<<endl;
  cout<<"overflow = "<<overflow<<endl;

//  if(underflow !=0 || overflow !=0) {
//    cout<<"ERROR: DELTA Y HIST HAS "<<underflow<<" UNDERFLOWs AND "<<overflow<<" OVERFLOWS"<<endl;
//    return 0;
//  }

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
  std::transform(v.begin(), v.end(), diff.begin(), std::bind2nd(std::minus<double>(), mean));
  double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
  double stdev = std::sqrt(sq_sum / v.size());

  return stdev;

}

double GetCaloAlignError(string dataset) { 

  TFile *fin = TFile::Open(("../Plots/CaloAlignment_"+dataset+".root").c_str());
  TH1D *hist = (TH1D*)fin->Get("hists/h_diff"); 

  return hist->GetRMS(); 

}

tuple<double, double, double, double, double> GetConversionParams() { 

  TFile *input = TFile::Open("../Plots/mm2ppm_fits.root");

  TGraphErrors *gr = (TGraphErrors*)input->Get("mainFit");

  TF1 *fit = (TF1*)gr->GetFunction("fit");

  double p0 = fit->GetParameter(0); double e0 = fit->GetParError(0);
  double p1 = fit->GetParameter(1); double e1 = fit->GetParError(1);

  // GetConversionParams
  TFitResultPtr fitPtr = gr->Fit(fit,"SMQ");

  double cov = fitPtr->GetCovarianceMatrix()(0,1);

  //cout<<"Conversion params"<<endl;
  cout<<"p0\t"<<p0<<" ± "<<e0<<endl;
  cout<<"p1\t"<<p1<<" ± "<<e1<<endl;
  cout<<"cov\t"<<cov<<endl;

  return make_tuple(p0, e0, p1, p0, cov); 

}

double GetQHV(string dataset) { 

  // See Run-1 BD paper table 1
  if(dataset=="gm2pro_daq_full_run1_HighKick_5042B_GLdocDB20949-v3" || dataset=="gm2pro_daq_full_run1_9d_5040A_GLdocDB17018-v3") return 20.3;
  else return 18.3;

}


///////////////////////////////////////
// These functions are no longer used 

double mm2ppm(double QHV, double p0, double p1) {
  return 1 / ( (p1/QHV) + (p0) );
}

double mm2ppm_err(double QHV, double p0, double e0, double p1, double e1, double cov) {
  // Taylor 9.9
  double a = -1/pow(((p1/QHV) + p0),2);// * pow(e0,2); 
  double b = (1/QHV) * -1/pow(((p1/QHV) + p0),2);// * pow(e1,2);
  double c = 2*a*b*cov;
  return sqrt(pow(a,2)*pow(e0,2)+pow(b,2)*pow(e1,2)-c);
}

///////////////////////////////////////


tuple<double, double> GetBrBkg() { 

  TFile *input = TFile::Open("../Plots/RadialFieldScanFits_2.root");
  
  TGraphErrors *result = (TGraphErrors*)input->Get("mainFit/mainFit");

  TF1 *mainFit = result->GetFunction("mainFit");
  TFitResultPtr mainFitRes = result->Fit(mainFit,"SMQ");

  double p0 = mainFit->GetParameter(0); double p0_err = mainFit->GetParError(0);
  double p1 = mainFit->GetParameter(1); double p1_err = mainFit->GetParError(1);

  // x-intercept 
  double xint = -p0/p1;
  double Br = -xint;

  // From Taylor 9.9
  double BrErr = fabs(Br) * sqrt(pow(p0_err/p0,2) + pow(p1_err/p1,2) - 2*mainFitRes->GetCovarianceMatrix()(0,1)/(p0*p1));

  //cout<<"Br\t"<<Br<<" ± "<<BrErr<<endl;

  return make_tuple(Br, BrErr);

}

// Including all errors (including correlated ones)
TGraphErrors *GetBrVsRun_StatErr(TGraphErrors *input, double QHV, double BrBkg, double k, bool empircalEstimation) { 

  int n = input->GetN();

  double x[n]; double ex[n];
  double y[n]; double ey[n];

  for (int i_point = 0; i_point < n; i_point++) { 

    x[i_point] = input->GetX()[i_point]; 
    ex[i_point] = 0.;

    if(empircalEstimation) { 
      // Add the background field at zero point
      y[i_point] = (input->GetY()[i_point] * k) + BrBkg; 
      // Total error on dy
      ey[i_point] = input->GetEY()[i_point] * k; 
    } else { 
      // Add the background field at zero point
      y[i_point] = (input->GetY()[i_point] * QHV) + BrBkg; 
      // Total error on dy
      ey[i_point] = input->GetEY()[i_point] * QHV; 
    }


  }

  return new TGraphErrors(n, x, y, ex, ey);

}

// Including all errors (including correlated ones)
TGraphErrors *GetBrVsRun_AllErr(TGraphErrors *input, double QHV, double BrBkg, double BrBkgErr, double k, double err_k, double err_align, double err_ref, bool empircalEstimation) { 

  int n = input->GetN();

  double x[n]; double ex[n];
  double y[n]; double ey[n];

  for (int i_point = 0; i_point < n; i_point++) { 

    x[i_point] = input->GetX()[i_point]; 
    ex[i_point] = 0.;

    if(empircalEstimation) { 
      // Add the background field at zero point
      y[i_point] = (input->GetY()[i_point] * k) + BrBkg; 
      // Total error on dy
      ey[i_point] = sqrt(pow(input->GetEY()[i_point],2) + pow(err_align, 2) + pow(err_ref, 2));
      // Total error on the shift in Br 
      ey[i_point] = y[i_point] * sqrt( pow((err_k/k),2) + pow((ey[i_point]/input->GetY()[i_point]), 2) );
      // Total error on the absolute Br
      ey[i_point] = sqrt( pow(ey[i_point], 2) + pow(BrBkgErr, 2) );
    } else {
      // Add the background field at zero point
      y[i_point] = (input->GetY()[i_point] * QHV) + BrBkg; 
      // Total error on dy
      ey[i_point] = sqrt(pow(input->GetEY()[i_point],2) + pow(err_align, 2) + pow(err_ref, 2));
      // Total error on the shift in Br 
      ey[i_point] = y[i_point] * ey[i_point]/input->GetY()[i_point];
      // Total error on the absolute Br
      ey[i_point] = sqrt( pow(ey[i_point], 2) + pow(BrBkgErr, 2) );
    }

  }

  return new TGraphErrors(n, x, y, ex, ey);

}


void DrawBrVsRun(TGraphErrors *statErr, TGraphErrors *allErr, std::string title, std::string fname) {

  TCanvas *c = new TCanvas("c","c",800,600);

  allErr->SetTitle(title.c_str());
  allErr->GetXaxis()->SetTitleSize(.04);
  allErr->GetYaxis()->SetTitleSize(.04);
  allErr->GetXaxis()->SetTitleOffset(1.1);
  allErr->GetYaxis()->SetTitleOffset(1.2);
  allErr->GetXaxis()->CenterTitle(true);
  allErr->GetYaxis()->CenterTitle(true);
  allErr->GetYaxis()->SetMaxDigits(4);
  allErr->SetMarkerStyle(20); //  Full circle
  statErr->SetMarkerStyle(20); //  Full circle
  allErr->SetMarkerColor(kBlack);
  statErr->SetMarkerColor(kBlack);

  allErr->SetFillColor(kRed);
  allErr->SetFillStyle(3004);

  statErr->SetFillColor(kBlue);
  statErr->SetFillStyle(3004);

  allErr->GetYaxis()->SetRangeUser(-3, 5);
  allErr->Draw("A3");
  statErr->Draw("P3 SAME");

  // TLegend *leg = new TLegend(.15, 0.69, .45, .89);
  TLegend *leg = new TLegend(.15, 0.79, .65, .89);
  leg->SetNColumns(2); //BorderSize(0);
  leg->SetBorderSize(0);

  //allErr->SetMarkerColor(kRed);
  leg->AddEntry(statErr, "Uncorrelated errors");
  leg->AddEntry(allErr, "Correlated errors");
  leg->Draw("same");

  //c->SetGridx();

  c->SaveAs((fname+".pdf").c_str());
  c->SaveAs((fname+".png").c_str());
  c->SaveAs((fname+".C").c_str());

  delete c;

  return;

}

int main(int argc, char *argv[]) {

  bool write = true;

  bool empircalEstimation = false;
  // Get inputs
  // If you're getting a logic error it's because you haven't provided an argument 
  string dataset = argv[1];//"gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2"; //  // "gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2"; //  // "gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2";//argv[1];
  //string dataset = "gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2"; // "gm2pro_daq_full_run1_9d_5040A_GLdocDB17018-v3"; // argv[1]; // "gm2pro_daq_full_run1_60h_5039A_GLdocDB16021-v2";//argv[1];
  string config = "CaloBeamPos";

  // Read in y-positions
  cout<<"\n**********************************\nReading y-positions\n**********************************\n"<<endl;
  vector<string> runs = csvReader("../txt/"+dataset+".txt");

  string inputDir = "/pnfs/GM2/persistent/EDM/Data/Br/"+config+"/"+dataset;

  cout<<"\n**********************************\nGetting calo avg y plots\n**********************************\n"<<endl;

  tuple<TH1D*, TGraphErrors*> AvgCaloYPlots = GetAvgCaloYPlots(runs, dataset, inputDir);
  
  TH1D *h_AvgCaloYTot =  get<0>(AvgCaloYPlots);
  TGraphErrors *gr_AvgCaloYvsRun = get<1>(AvgCaloYPlots);

  cout<<h_AvgCaloYTot<<endl;
  cout<<gr_AvgCaloYvsRun<<endl;

  // Get calo avg y vs run 
//  cout<<"\n**********************************\nGetting calo avg y vs run\n**********************************\n"<<endl;
//  TGraphErrors *gr_AvgCaloYvsRun = GetAvgCaloYVsRun(runs, dataset, inputDir);
  DrawTGraphErrors(gr_AvgCaloYvsRun, ";Run number;#LTy_{Calo}#GT [mm]", "../Images/EstimateRadialField/gr_AvgCaloYvsRun_"+dataset+"_"+runs.at(0)+"_"+runs.at(runs.size()-1));  
//
//  cout<<"\n**********************************\nGetting total calo avg y\n**********************************\n"<<endl;
//  TH1D *h_AvgCaloYTot = GetTotAvgCaloY(runs, dataset, inputDir);
  
  // Clone to be safe
  TH1D *h_AvgCaloYTot_clone = (TH1D*)h_AvgCaloYTot->Clone("h_AvgCaloYTot_clone");
  DrawHist(h_AvgCaloYTot_clone, "", "../Images/EstimateRadialField/h_AvgCaloYTot_"+dataset+"_"+runs.at(0)+"_"+runs.at(runs.size()-1));

  cout<<"Total calo average y = "<<h_AvgCaloYTot->GetMean()<<"±"<<h_AvgCaloYTot->GetMeanError()<<endl;

  // Get zero point
  cout<<"\n**********************************\nGetting zero point\n**********************************\n"<<endl;

  // Make sure this excludes 5 & 9
  bool noBadCalos = true;
  tuple<double, double> refPoint = GetRefPos(noBadCalos);
  double ref = get<0>(refPoint); double err_ref = get<1>(refPoint);

  cout<<"ref pos\t\t"<<ref<<endl;
  cout<<"ref pos error\t"<<err_ref<<endl;

  // Get y minus zero point
  cout<<"\n**********************************\nGetting delta y\n**********************************\n"<<endl;
  TGraphErrors *gr_AvgCaloDeltaY = GetDeltaYVsRun(gr_AvgCaloYvsRun, ref, err_ref);
  DrawTGraphErrors(gr_AvgCaloDeltaY, ";Run number;#Delta#LTy_{calo}#GT [mm]", "../Images/EstimateRadialField/deltaY_"+dataset+"_"+runs.at(0)+"_"+runs.at(runs.size()-1));

  // Histogram of means
  TH1D *h_AvgCaloDeltaY = GetDeltaY1D(gr_AvgCaloYvsRun, ref, err_ref);
  DrawHist(h_AvgCaloDeltaY, ";#Delta#LTy_{calo}#GT [mm];Runs / 0.2 mm","../Images/EstimateRadialField/h_deltaY_"+dataset+"_"+runs.at(0)+"_"+runs.at(runs.size()-1));
  
  //for(int i(0); i<h_AvgCaloDeltaY->GetXaxis()->GetNbins(); i++) cout<<h_AvgCaloDeltaY->GetBinContent(i+1)<<endl;
  // All cluster average delta Y for this DS
  double tot_deltaY =  h_AvgCaloYTot->GetMean() - ref; 

  // Errors on dy 
  double err_stat = h_AvgCaloYTot->GetMeanError();

  // cout<<h_AvgCaloDeltaY->GetMeanError()<<endl;
  double err_drift = StandardDeviation(gr_AvgCaloYvsRun, ref);// h_AvgCaloDeltaY->GetRMS(); // h_AvgCaloYTot->GetRMS(); // h_AvgCaloDeltaY->GetRMS();
  double err_align = GetCaloAlignError(dataset);

  double err_tot_deltaY = sqrt(pow(err_stat,2)+pow(err_ref,2)+pow(err_drift,2)+pow(err_align,2));

  cout<<"\n*** Uncertainties on delta Y ***\nstat:\t"<<err_stat<<"\nref:\t"<<err_ref<<"\ndrift:\t"<<err_drift<<"\nalign:\t"<<err_align<<"\ntot:\t"<<err_tot_deltaY<<endl;

  cout<<"\n**********************************\nGetting QHV\n**********************************\n"<<endl;

  double QHV = GetQHV(dataset);

  cout<<"QHV for "<<dataset<<" is "<<QHV<<" kV"<<endl;

  cout<<"\n**********************************\nGetting conversion params\n**********************************\n"<<endl;

  tuple<double, double, double, double, double> conversionParams = GetConversionParams(); 
  double p0 = get<0>(conversionParams); double e0 = get<1>(conversionParams); 
  double p1 = get<2>(conversionParams); double e1 = get<3>(conversionParams); 
  double cov = get<4>(conversionParams);

  double k = mm2ppm(QHV, p0, p1);
  double err_k = mm2ppm_err(QHV, p0, e0, p1, e1, cov);
  cout<<"\nk = "<<k<<"±"<<err_k<<endl;

  cout<<"\n**********************************\nGetting total shift in Br\n**********************************\n"<<endl;

  // This is ONLY possible is the reference point has a background field consitent with zero 
  double tot_deltaBr; //  = k * tot_deltaY;
  double err_tot_deltaBr; // = tot_deltaBr * sqrt( pow((err_k/k),2) + pow((err_tot_deltaY/tot_deltaY), 2) );

  if(empircalEstimation) {
    tot_deltaBr = k * tot_deltaY;
    err_tot_deltaBr = tot_deltaBr * sqrt( pow((err_k/k),2) + pow((err_tot_deltaY/tot_deltaY), 2) );
  } else { 
    tot_deltaBr = QHV * tot_deltaY;
    err_tot_deltaBr = tot_deltaBr * err_tot_deltaY/tot_deltaY; 
  }

  cout<<"Total delta Br:\t"<<tot_deltaBr<<"±"<<err_tot_deltaBr<<" ppm"<<endl;

  // Get background radial field
  cout<<"\n**********************************\nGetting Br background\n**********************************\n"<<endl;

  //tuple<double, double> BrB = GetBrBkg();
  double BrBkg = get<0>(GetBrBkg()); double BrBkgErr = get<1>(GetBrBkg());

  cout<<"\nBr Bkg = "<<BrBkg<<"±"<<BrBkgErr<<" ppm"<<endl;

  cout<<"\n**********************************\nGetting absolute Br\n**********************************\n"<<endl;
  // Combine 
  double tot_Br = BrBkg + tot_deltaBr;
  double err_tot_Br = sqrt(pow(BrBkgErr,2)+pow(err_tot_deltaBr,2));

  cout<<"\nAbsolute Br = "<<tot_Br<<"±"<<err_tot_Br<<" ppm"<<endl;

  cout<<"\n**********************************\nPlotting absolute Br vs run\n**********************************\n"<<endl;

  TGraphErrors *gr_AvgBrVsRun_StatErr = GetBrVsRun_StatErr(gr_AvgCaloDeltaY, QHV, BrBkg, k, empircalEstimation);
  TGraphErrors *gr_AvgBrVsRun_AllErr = GetBrVsRun_AllErr(gr_AvgCaloDeltaY, QHV, BrBkg, BrBkgErr, k, err_k, err_align, err_ref, empircalEstimation);

  string BrVsRunName = "../Images/EstimateRadialField/BrVsRun_"+dataset+"_"+runs.at(0)+"_"+runs.at(runs.size()-1); 
  if(empircalEstimation) BrVsRunName += "_crossCheck";

  DrawBrVsRun(gr_AvgBrVsRun_StatErr, gr_AvgBrVsRun_AllErr, ";Run number;#LTB_{r}#GT [ppm]", "../Images/EstimateRadialField/BrVsRun_"+dataset+"_"+runs.at(0)+"_"+runs.at(runs.size()-1));

  // Need to draw bands for correlated and stat errors. 

  cout<<"\n**********************************\nStarting per calo analysis\n**********************************\n"<<endl;

  cout<<"TODO TODO TODO TODO TODO TODO"<<endl;

  cout<<"\n**********************************\nWriting plots\n**********************************\n"<<endl;

    // Write to ROOT

  // Set output
  string outputName = "../Plots/radialFieldEstimationPlots_"+dataset+"_"+runs.at(0)+"_"+runs.at(runs.size()-1);// 
  if(empircalEstimation) outputName += "_crossCheck.root";
  else outputName += ".root";

  if(!write) outputName = "delete_me.root";

  TFile *output = new TFile( outputName.c_str(), "RECREATE");
  
  output->mkdir("RadialFieldValue"); output->mkdir("CaloAveragePlots"); output->mkdir("PerCaloPlots"); //output->mkdir("PerCaloMeanSubtracted");

  output->cd("RadialFieldValue");

  TTree *resultTree = new TTree("resultTree", "resultTree");

  resultTree->Branch("Br", &tot_Br);
  resultTree->Branch("BrErr", &err_tot_Br);

  resultTree->Fill();

  output->cd("CaloAveragePlots");

  gr_AvgCaloYvsRun->Write("gr_AvgCaloYvsRun");
  h_AvgCaloYTot->Write("h_AvgCaloYTot");
  gr_AvgCaloDeltaY->Write("gr_AvgCaloDeltaY");
  h_AvgCaloDeltaY->Write("h_AvgCaloDeltaY");
  gr_AvgBrVsRun_StatErr->Write("gr_AvgBrVsRun_StatErr");
  gr_AvgBrVsRun_AllErr->Write("gr_AvgBrVsRun_AllErr");
  // Br per run

  output->Write();
  output->Close();

  cout<<"\n**********************************\nWritten plots to "<<outputName<<"\n**********************************\n"<<endl;

  cout<<"\n**********************************\nEND\n**********************************\n"<<endl;

  return 0;

}




