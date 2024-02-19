# The radial magnetic field analysis

- Direct measurement code can be found in **EDM**

- `BeamGunSim` comprises a failed attempt to make a proper go at a radial field simulation using the beam gun. 

- `GridSubmit` is a directory used for submission to FermiGrid (for making beam position histograms). 

- Radial field estimation code can be found in `RadialFieldEstimation`, which may be operated in the following way: 
 
  1) `CMacros/ReadNearlineTrees.C` is for producing beam position histograms from the nearline if you want results quickly. If you have a production dataset to work with use `gm2analyses/EDM/fcl/RunCaloBeamPositionPlots.fcl`. I have a SAM dataset for the beam position histograms made already, called `caloBeamPosPlots_EDM`. Might be worth updating it as we add more datasets. The plots themselves are stored on `/pnfs/GM2/persistent/EDM/Data`.
  
  2) `CMacros/PlotCaloYvsRun.C` does what it's called: it produces a ROOT file with graphs of <y> vs run, and the same for individual calos. It's controlled by `Scripts/Run_CaloY_vs_Run_All_DS.sh`, which feeds it the name of the dataset as an argument. For re-use, the `C++` macro will need to be updated around line 174, which is just a case of adding the run ranges for the new datasets. It will also need new text files listing the runs in each dataset, which can be generated with `Scripts/makeRunList.txt`
 
  3) `CMacros/GetRefPos.C` produces a pol0 fit to the period of Run-4 where I claim to know what <Br> is. This fit lives in Plots/RefPos_NoBadCalos_Run4_2021.root
 
  4) `CMacros/CheckCaloAlignment.C` produces some histograms used to estimate the level of calorimeter misalignment between the dataset of interest and Run-4, writing to Plots/CaloAlignment_<dataset_name>.root. It's controlled by  `Scripts/Run_Calo_Alignment.sh`, which feeds it the dataset name as an argument. The new dataset names will need to be added in the main, should be self-explanatory.  
 
  5) `CMacos/EstimateRadialField.C` is where most of the real work happens. It looks a bit complicated, but it just takes the various ROOT files produced by previous macros and tries to estimate the radial field and it's uncertainty, writing to `Plots/radialFieldEstimationPlots_<dataset_name>.root`. For re-use, it will need to be updated in similar manner to `CMacros/PlotCaloYvsRun.C` around line 143.
 
  6) `CMacros/PlotBrvsDS2.C` takes the ROOT files produced by `CMacos/EstimateRadialField.C` and plots the average <Br> in nice graph. `CMacros/PlotBrvsDS.C` also works but I prefer this one.
 
  7) `CMacros/PrintUncertainties.C` is a re-write of `CMacos/EstimateRadialField.C` which just print contributions to the uncertainty on Br. 



