dataset=run2
rm -f ${dataset}.txt && touch ${dataset}.txt
for file in `ls ../../../Plots/Data/RadialFieldEstimation/BeamYPosMonitoring/Input/${dataset}`; do
	run=${file##*_}
	run=${run%%.*}
	echo $run >> ${dataset}.txt
done
