# Radial magnetic field estimation 

- Direct measurement code can be found in **EDM**

- Radial field estimation code can be found in `RadialFieldEstimation`, which may be operated in the following way: 

  0) I have a SAM dataset for the beam position histograms, called caloBeamPosPlots_EDM. Might be worth updating it. 
 
  1) CMacros/ReadNearlineTrees.C is only , since we're not using the nearline here.
 
Step 2:
 
  CMacros/PlotCaloYvsRun.C does pretty much what it's called: produces a ROOT file with graphs of <y> vs run, and the same for individual calos. It's controlled by Scripts/Run_CaloY_vs_Run_All_DS.sh, which just feeds it the name of the dataset as an argument (you don't want to re-run all the Run-1/2 datasets so this will require simple modifications). The macro itself will need to be updated on line 174, which is just a case of adding the run ranges for the new datasets. It will also need new text files listing the runs in each dataset, which can be generated with Scripts/makeRunList.txt
 
Step 3: 
 
  CMacros/GetRefPos.C can also be skipped. It produces a pol0 fit to the period of Run-4 where I claim to know what <Br> is. This fit live in Plots/RefPos_NoBadCalos_Run4_2021.root
 
Step 4: 
 
  CMacros/CheckCaloAlignment.C, produces some histograms which I use to estimate the level of calorimeter misalignment between the dataset of interest and Run-4, writing to Plots/CaloAlignment_<dataset_name>.root. It's controlled by a script, Scripts/Run_Calo_Alignment.sh, which feeds it the dataset name as an argument. The new dataset names will need to be added in the main, should be self-explanatory.  
 
Step 4:
 
  CMacos/EstimateRadialField.C is where most of the real work happens. It looks a bit complicated, but it just takes the various ROOT files produced by previous macros and tries to estimate the radial field and it's uncertainty, writing to Plots/radialFieldEstimationPlots_<dataset_name>.root. It will need to be updated in similar manner to CMacros/PlotCaloYvsRun.C on line 143.
 
Step 5: 
 
  CMacros/PlotBrvsDS2.C just takes the ROOT files produced by CMacos/EstimateRadialField.C and plots the average <Br> in a TGraphErrors. CMacros/PlotBrvsDS.C also works but I prefer this one.
 
Step 6: 
 
  CMacros/PrintUncertainties.C: I don't remember writing this but I it appears to just print contributions to the uncertainty on Br. I'm not sure why CMacros/EstimateRadialField.C can't do this but maybe there's a reason, or maybe I just decided it was too much hassle to figure it out.



