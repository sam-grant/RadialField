for run in 1 2; do

    list=../txt/MissingRunNumbers/run${run}.txt

    rm -f ../txt/MissingFiles/run${run}.txt

    if [[ ! -d ../txt/MissingFiles/run${run} ]]; then
	mkdir ../txt/MissingFiles/run${run}
    fi

    for subRun in `cat $list`; do

	echo $subRun

	if [[ -f ../txt/CaloFileLists/run${run}/${subRun}.txt ]]; then 
	    echo "Found ../txt/CaloFileLists/run${run}/${subRun}.txt"
	    cp ../txt/CaloFileLists/run${run}/${subRun}.txt ../txt/MissingFiles/run${run}/
	else 
	    echo "File list for sub-run $subRun not found"
	fi


    done

done

    

