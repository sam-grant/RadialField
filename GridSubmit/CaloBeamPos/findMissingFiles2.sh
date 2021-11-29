dataset=$1
a=`samweb list-definition-files $dataset | wc -l`
b=`. findMissingFiles.sh $dataset | wc -l`
echo "${a} total files, ${b} missing files"
echo "scale=2; (1-${b}/${a})*100" | bc -l
#per=$((b / a))
#per=$((per * 100))
#echo "${per}% done"
