dataset=run1

for run in `cat ../MissingRunNumbers/${dataset}.txt`; do
    echo $run
    rm -f ${dataset}/${run}.txt && touch ${dataset}/${run}.txt
    cp ../CaloFileLists/${dataset}/${run}.txt ${dataset}
done
