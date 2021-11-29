declare -a i_=(-255 -305 -355 -405 -455) # -505 -555 -605 -655 -705)
for i in ${i_[@]}; do
	echo $i
done | xargs -i --max-procs=5 bash -c ". RunJob.sh {}"
