i=$1
echo "Submitting ${i} ns"
mkdir tmp${i}
cd tmp${i} && pwd
rm -f tmp${i}.fcl && cp ../main.fcl tmp${i}.fcl 
# append fcl
echo "services.gm2FieldManager.kTpeak : [${i}, ${i}, ${i}]" >> tmp${i}.fcl
gm2 -c tmp${i}.fcl -n 5000
wait
cd ../
