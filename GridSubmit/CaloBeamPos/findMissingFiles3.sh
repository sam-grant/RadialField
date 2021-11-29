for i in C D E F G H; do 

    dataset="gm2pro_daq_offline_dqc_run2${i}"

    echo $dataset
    
    . findMissingFiles.sh $dataset | wc -l 

done
