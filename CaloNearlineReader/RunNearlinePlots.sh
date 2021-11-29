for run in `cat ../txt/NearlineRunNumbers/NearlineRunNumbers_run4.txt`; do
    if [[ $run -lt 37858 ]]; then
	continue
    fi
    if [[ head /pnfs/GM2/daq/run4/nearline/nearlineHists_merged/gm2nearline_hists_run${run}.root -eq 0 ]]; then
	echo "poo"
    fi
    ReadNearlineTrees.exe $run 
done
