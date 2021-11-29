for run in `cat ../txt/BeamPosRuns2.txt`; do

	file=`ls /pnfs/GM2/daq/run4/nearline/nearlineHists_merged/gm2nearline_hists_run${run}.root`
	file=${file##*/}
	path=`echo /pnfs/GM2/daq/run4/nearline/nearlineHists_merged`

	echo "Run ${run}"
	echo "Path ${path}"
	echo "File ${file}"

	if [[ ! -f ../NearlinePlots/y-pos_${run}.root ]] ; then
	    ./ReadNearlineTrees.exe ${run} ${path} ${file} 
	fi
	
done

