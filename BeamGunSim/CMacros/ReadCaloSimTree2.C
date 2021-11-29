void ReadCaloSimTree2() {

   // ++++++++++++++ Open tree and load branches ++++++++++++++
   // Get file
  //   string input = "../TestTrees/gm2calo_ana.root"; //
   string input = "../TestTrees/Fatemi_beamGun_4001_forSam.root";

   TFile *f1 = TFile::Open(input.c_str());
   cout<<"\nOpened tree:\t"<<input<<" "<<f1<<endl;

   // Get reader for tree
   TTreeReader treeReader("caloSimTrees/tree",f1);

   // Get branches
   TTreeReaderValue<unsigned int> runNum(treeReader,"runNum");
   TTreeReaderValue<unsigned int> subRunNum(treeReader,"subRunNum");
   TTreeReaderValue<unsigned int> eventNum(treeReader,"eventNum");
   TTreeReaderValue<int> ctag(treeReader,"ctag");
   TTreeReaderValue<vector<int>> caloNum(treeReader,"caloNum");
   TTreeReaderValue<vector<float>> caloHitEnergy(treeReader,"caloHitEnergy");
   TTreeReaderValue<vector<float>> caloHitTime(treeReader,"caloHitTime");
   TTreeReaderValue<vector<float>> caloHitX(treeReader,"caloHitX");
   TTreeReaderValue<vector<float>> caloHitY(treeReader,"caloHitX");

   // ++++++++++++++ Book histograms ++++++++++++++
   // All calos
   //TH2D *hxy = new TH2D("hxy", ";x [mm];y [mm]", 225, 0, 225, 150, 0, 150);
   //TH1D *hy = new TH1D("hy", ";y [mm];Clusters", 150, 0, 150);

   // Individual calos
//   vector<TH1D *> hy_calos;
//   for(int i_calo = 0; i_calo < 24; i_calo++) {
//   	TH1D *hy_tmp = (TH1D*) hy->Clone();
//   	hy_tmp->SetName( ("hy_"+to_string(i_calo+1)).c_str() );
//   	hy_calos.push_back(hy_tmp);
//   }

   // ++++++++++++++ Loop thro events ++++++++++++++
   int tot_ctag = 0;
   int tot_ctag_check = 0;
   int nEvents = 0;
   //int nClu = 0;
   

   while (treeReader.Next()){

     // Speeds things up significantly 
        if(*ctag<1) continue;
   	tot_ctag = tot_ctag + *ctag;
	//cout<<"ctags\t"<<*ctag<<endl;
	nEvents++;
	//	if(nEvents > 1000) break;

	// Get leaves
   	vector<int> caloNum_ = *caloNum;
   	vector<float> x_ = *caloHitX;
   	vector<float> y_ = *caloHitY;
   	vector<float> energy_ = *caloHitEnergy;
   	vector<float> time_ = *caloHitTime;

	// Number of clusters in this fill
   	int nClu = caloNum_.size(); 

	// Loop through clusters
   	for(int i_clu = 0; i_clu < nClu; i_clu++) { 

	  // Get cluster level variables
	  int caloNum =  caloNum_.at(i_clu);
	  float x = x_.at(i_clu); //  * 25;
	  float y = y_.at(i_clu); //  * 25; 
	  float energy = energy_.at(i_clu);
	  float time = time_.at(i_clu);
	  
	  //nClu++;
	  // Apply CTAG cuts
	  //if(energy > 50 && energy < 6000 && time > 24000) {

   		tot_ctag_check++;
		//	cout<<"tot_ctag_check\t"<<tot_ctag_check<<endl;

         // Fill y-position for all calos
   		//hxy->Fill(xmm, ymm);
   		//hy->Fill(ymm);
         //// Fill y-position for individual calos
   		//hy_calos.at(caloNum-1)->Fill(ymm);

		//	  }
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
   //   string output = "output.root";
   // TFile *f2 = new TFile(output.c_str(), "RECREATE");
   
   //f2->cd();
   //f2->mkdir("CaloBeamPosition"); f2->cd("CaloBeamPosition");
   //hy->Write();
   //f2->mkdir("PerCalo"); f2->cd("PerCalo");

//   for(int i_calo = 0; i_calo < hy_calos.size(); i_calo++) hy_calos.at(i_calo)->Write();
//   	f2->Close();

   //cout<<"\nMean y-position:\t"<<hy->GetMean()<<"+/-"<<hy->GetMeanError()<<endl;
   cout<<"Total ctags:\t"<<tot_ctag<<endl;
   cout<<"Total ctags check:\t"<<tot_ctag_check<<endl;
   //   cout<<"nEvents:\t"<<nEvents<<endl;
   //   cout<<"nClu:\t"<<nClu<<endl;

   //cout<<"\nWritten histograms to:\t"<<output<<" "<<f2<<endl;

   f1->Close();
   //f2->Close();

   return;

}
